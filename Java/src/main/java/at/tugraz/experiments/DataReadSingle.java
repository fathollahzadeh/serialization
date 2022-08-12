package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.util.RootData;

import java.io.IOException;

public class DataReadSingle {

    public static void main(String[] args) throws IOException {

        String inDataPath = System.getProperty("inDataPath");
        String method = System.getProperty("method");
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        ObjectReader reader = new ObjectReader(inDataPath, method);
        RootData[] rd = reader.readObjects(0, nrow);
    }
}
