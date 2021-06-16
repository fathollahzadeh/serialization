package edu.bu.filehandler;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.BlockingQueue;
import java.util.stream.Stream;

public class ReadTweet implements Runnable {

	private String inputFile;

	private boolean readStatus;

	private BlockingQueue<String> queue;

	public ReadTweet(BlockingQueue<String> q, String inputFile) {
		this.queue = q;
		this.inputFile = inputFile;
	}

	public void setReadStatus(boolean readStatus) {
		this.readStatus = readStatus;
	}

	@Override public void run() {

		while(this.readStatus) {

			try(Stream<String> stream = Files.lines(Paths.get(inputFile))) {
				stream.forEach(e -> {
					try {
						if(readStatus) {
							queue.put(e);
						}
					}
					catch(InterruptedException ex) {
						ex.printStackTrace();
					}
				});
			}
			catch(IOException e) {
				e.printStackTrace();
			}
		}
	}
}
