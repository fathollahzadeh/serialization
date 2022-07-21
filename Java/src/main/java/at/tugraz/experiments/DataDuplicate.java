package at.tugraz.experiments;

import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.stream.Stream;

public class DataDuplicate {

    public static void main(String[] args) throws IOException {

        String inDataPath = System.getProperty("inDataPath");
        String outDataPath =System.getProperty("outDataPath");
        FileWriter myWriter = new FileWriter(outDataPath);
        ArrayList<String> list= new ArrayList<>();

        try (Stream<String> stream = Files.lines(Paths.get(inDataPath))) {
            stream.forEach(list::add);
        } catch (IOException e) {
            e.printStackTrace();
        }

        for (int i=0; i<1; i++){
            for (String e: list) {
                try {
                    myWriter.write(e + "\n");
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        }
        myWriter.close();

    }
}
