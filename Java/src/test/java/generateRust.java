import edu.bu.tweet.*;

import java.lang.reflect.Field;

public class generateRust {


    public static void main(String[] args) throws NoSuchFieldException {
        OptionEntity obj=new OptionEntity();
        Class cls = obj.getClass();
        Field[] field = cls.getDeclaredFields();

        String os="pub struct OptionEntity { \n";
        for (Field f:field){
            if (f.getType().getName().equals("java.lang.String")){
                os+=f.getName()+ ": String , \n";
            }

            else   if (f.getType().getName().equals("java.lang.Long") || f.getType().getName().equals("long")){
                os+=f.getName()+ ": i64 , \n";
            }

            else   if ( f.getType().getName().equals("boolean")){
                os+=f.getName()+ ": bool , \n";
            }
            else   if ( f.getType().getName().equals("int")){
                os+=f.getName()+ ": i32 , \n";
            }
            else {
                os+=f.getName()+ ": "+ f.getType().getSimpleName()+", \n";
            }

        }
        os+="\n}";
        System.out.println(os);

    }
}
