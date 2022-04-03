package at.tugraz.io;

import at.tugraz.util.Const;
import at.tugraz.util.RootObject;
import at.tugraz.util.SerializationType;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.List;

public abstract class Serializer {
	static Logger logger = LogManager.getLogger(Serializer.class);

	protected long currentPageNumber;
	protected long currentOffset;
	protected byte[] pageBuffer;
	protected String fileName;

	protected RandomAccessFile randOutStreamRegularFile; //Output Stream: For Writing
	protected BufferedOutputStream bosIndexFile; //Output Stream: For Index Writing
	protected List<Long> pageIndex; //Page index
	protected List<Long> objectIndex; //Object index
	protected List<Long> objectLength; //Object Length

	public Serializer(String fileName) {
		this.fileName = fileName;
		this.currentOffset = 0;
		this.pageIndex = new ArrayList<>();
		this.objectIndex = new ArrayList<>();
		this.objectLength = new ArrayList<>();

		//Allocates write page buffer:
		this.pageBuffer = new byte[2 * Const.PAGESIZE]; // this is our page

		try {
			// open a random access file for writing objects to it.
			File outStreamRegularFile = new File(this.fileName);
			FileOutputStream outIndexFile = new FileOutputStream(this.fileName + ".index");

			this.randOutStreamRegularFile = new RandomAccessFile(outStreamRegularFile, "rw");
			this.bosIndexFile = new BufferedOutputStream(outIndexFile);
			this.currentPageNumber = 0;
		}
		catch(Exception ex) {
			logger.error(ex);
		}
	}

	public abstract void writeToFile(RootObject object);

	protected void writeToFile(byte[] buffer) {
		int objectSize;
		try {
			objectSize = buffer.length;

			//check capacity of the current page size
			//if current page is full should be write to the file and then reset the page
			if((currentOffset + objectSize) > Const.PAGESIZE) {
				randOutStreamRegularFile.seek(currentPageNumber * Const.PAGESIZE);
				randOutStreamRegularFile.write(this.pageBuffer);
				currentPageNumber++;
				currentOffset = 0;
				this.pageBuffer = new byte[2 * Const.PAGESIZE];
			}
			System.arraycopy(buffer, 0, this.pageBuffer, (int) this.currentOffset, objectSize);
			this.pageIndex.add(currentPageNumber);
			this.objectIndex.add(currentOffset);
			this.objectLength.add((long) objectSize);
			currentOffset += objectSize;
		}
		catch(Exception ex) {
			logger.error(ex);
		}
	}
}
