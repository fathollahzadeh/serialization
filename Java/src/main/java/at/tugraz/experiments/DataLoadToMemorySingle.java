package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.util.Const;
import at.tugraz.util.RootData;

public class DataLoadToMemorySingle {

    public static void main(String[] args) {

        String inDataPath = System.getProperty("inDataPath");
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        ObjectReader reader = new ObjectReader(inDataPath, "Kryo");
        int size = Const.BATCHSIZE;
        for (int i = 0; i < nrow; ) {
            RootData[] rd = reader.readObjects(i, size);
            i += rd.length;
            size = Math.min(nrow - i + 1, Const.BATCHSIZE);
        }
    }
}
