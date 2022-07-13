package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.util.Const;
import at.tugraz.util.RootData;

import java.io.IOException;

public class DataReadIOSingle {

    public static void main(String[] args) throws IOException {

        String inDataPath = System.getProperty("inDataPath");
        String method = System.getProperty("method");
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        ObjectReader reader = new ObjectReader(inDataPath, method);
        reader.readIO(0, nrow);
    }
}
