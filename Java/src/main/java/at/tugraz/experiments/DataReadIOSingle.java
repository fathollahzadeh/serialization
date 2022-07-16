package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.util.Const;
import at.tugraz.util.RootData;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class DataReadIOSingle {

    public static void main(String[] args) throws IOException {

        String inDataPath = System.getProperty("inDataPath");
        String method = System.getProperty("method");
        String seqRand = System.getProperty("seqRand");
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        ObjectReader reader = new ObjectReader(inDataPath, method);
        if (seqRand.equalsIgnoreCase("sequential")) {
            reader.readIO(0, nrow);
        }
        else {
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
