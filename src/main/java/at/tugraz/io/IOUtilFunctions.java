package at.tugraz.io;

import org.apache.commons.io.input.ReaderInputStream;

import java.io.InputStream;
import java.io.StringReader;

public class IOUtilFunctions {

	public static InputStream toInputStream(String input) {
		if( input == null )
			return null;
		return new ReaderInputStream(new StringReader(input), "UTF-8");
	}
}
