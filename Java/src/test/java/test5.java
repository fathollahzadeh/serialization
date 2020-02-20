public class test5 {

    public static void main(String[] args) {

        long s1=System.nanoTime();
        String str1="str";
        String str2="str";
        String str3=new String("str");

        long s2=System.nanoTime();

        System.out.println(s2-s1);
    }
}
