package at.tugraz.complexobject;

import com.google.gson.Gson;

import java.util.Random;

public class GenerateComplexObject {

    public static void main(String[] args) {
        Gson gson = new Gson();

        // dataset 0: simple, without nested object
        SimpleObject simpleObject = new SimpleObject();
        generateSimpleObject(simpleObject);

        // dataset 1: 1 object as nested
        ObjectL1 objectL1 = new ObjectL1();
        generateSimpleObject(objectL1);
        objectL1.var_object1 = simpleObject;
        System.out.println(gson.toJson(objectL1));

        // dataset 1: 1 object as nested
        ObjectL2 objectL2 = new ObjectL2();
        generateSimpleObject(objectL2);
        objectL2.var_object2 = objectL1;
        System.out.println(gson.toJson(objectL2));

        // dataset 1: 1 object as nested
        ObjectL3 objectL3 = new ObjectL3();
        generateSimpleObject(objectL3);
        objectL3.var_object3 = objectL2;
        System.out.println(gson.toJson(objectL3));

        // dataset 1: 1 object as nested
        ObjectL4 objectL4 = new ObjectL4();
        generateSimpleObject(objectL4);
        objectL4.var_object4 = objectL3;
        System.out.println(gson.toJson(objectL4));

        // dataset 1: 1 object as nested
        ObjectL5 objectL5 = new ObjectL5();
        generateSimpleObject(objectL5);
        objectL5.var_object5 = objectL4;
        System.out.println(gson.toJson(objectL5));
    }

    private static SimpleObject generateSimpleObject(SimpleObject simpleObject){
        Random r = new Random();
        simpleObject.var_int = r.nextInt();
        simpleObject.var_long = r.nextLong();
        simpleObject.var_float = r.nextFloat();
        simpleObject.var_double = r.nextDouble();
        simpleObject.var_bool = r.nextBoolean();
        simpleObject.var_char = getRandomChar();

        int str_length = 50;//r.nextInt(200);
        simpleObject.var_string = getRandomString(str_length);
        return simpleObject;
    }


    public static String getRandomString(int length) {
        String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789";
        StringBuilder salt = new StringBuilder();
        Random rnd = new Random();
        while(salt.length() < length) { // length of the random string.
            int index = (int) (rnd.nextFloat() * alphabet.length());
            salt.append(alphabet.charAt(index));
        }
        String saltStr = salt.toString();
        return saltStr;

    }

    public static char getRandomChar() {
        String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789";
        Random rnd = new Random();
        int index = (int) (rnd.nextFloat() * alphabet.length());
        return alphabet.charAt(index);
    }
}
