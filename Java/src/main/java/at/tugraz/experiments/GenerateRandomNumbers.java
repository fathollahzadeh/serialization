package at.tugraz.experiments;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class GenerateRandomNumbers {

    public static void main(String[] args) {
        int low= 0;
        int high= 8000000;
        String fname = "../Experiments/data";
        for (int i=1; i<=8;i++){
            int length = i*1000000;
            int[] randomList = new int[length];
            for (int j=0; j<length; j++)
                randomList[j] = getRandomNumber(low, high);
            writeToFile(fname+"/random_list"+i+"m.dat", randomList);
        }
    }

    public static int getRandomNumber(int low, int high) {
        Random r = new Random();
        int result = r.nextInt(high - low) + low;
        return result;
    }

    public static void writeToFile(String fname, int[] randomList){
        try {
            FileWriter writer = new FileWriter(fname);
            for (int v: randomList)
                writer.write(v+"\n");
            writer.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}
