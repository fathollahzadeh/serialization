package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.util.Const;
import at.tugraz.util.RootData;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class DataLoadToMemorySingle {

    public static void main(String[] args) {

        String inDataPath = System.getProperty("inDataPath");
        String seqRand = System.getProperty("seqRand");
        int nrow = Integer.parseInt(System.getProperty("nrow"));
        ObjectReader reader = new ObjectReader(inDataPath, "Kryo");
        int size = Const.BATCHSIZE;

        if (seqRand.equalsIgnoreCase("sequential")) {
            for (int i = 0; i < nrow; ) {
                RootData[] rd = reader.readObjects(i, size);
                i += rd.length;
                size = Math.min(nrow - i + 1, Const.BATCHSIZE);
            }
        }
        else{
            String randomDataPath = System.getProperty("randomDataPath");
            int[] randomIDs= new int[nrow];
            try (BufferedReader br = new BufferedReader(new FileReader(randomDataPath))) {
                String line;
                int index=0;
                while ((line = br.readLine()) != null) {
                    randomIDs[index++] = Integer.parseInt(line);
                }
                for (int i: randomIDs ) {
                    reader.readObjects(i, 1);
                }

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
