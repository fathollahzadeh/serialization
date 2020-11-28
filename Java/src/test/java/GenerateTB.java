import edu.bu.tweet.*;
import edu.bu.tweet.flatbuffers.AdditionalMediaInfoEntityFBS;
import edu.bu.tweet.flatbuffers.PlaceFBS;
import edu.bu.tweet.flatbuffers.UserFBS;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;

public class GenerateTB {


    public static void main(String[] args) throws IllegalAccessException {

        VideoEntity tweetStatus=new VideoEntity();
        String name="videoEntityFBS";


        Field[] fields = tweetStatus.getClass().getDeclaredFields();
//        for (Field field : fields) {
//            if (Modifier.isPrivate(field.getModifiers())) {
//                field.setAccessible(true);
//                //System.out.println(field.getName());
//                if (field.getType().getName().equals("java.lang.String")){
//                    // int name = builder.createString(this.created_at);
//                    System.out.println("int "+field.getName()+"Builder=this."+field.getName()+"!=null? builder.createString(this."+field.getName()+"):0;");
//
//                   // System.out.println(" AdditionalMediaInfoEntityFBS.add(builder, "+field.getName()+"Builder);");
//                }
//
//
//            }
//        }


        for (Field field : fields) {
            if (Modifier.isPrivate(field.getModifiers())) {
                field.setAccessible(true);
//                //System.out.println(field.getName());
//                if (field.getType().getName().equals("java.lang.String")){
//                    // int name = builder.createString(this.created_at);
//                   // System.out.println("int "+field.getName()+"Builder=this."+field.getName()+"!=null? builder.createString(this."+field.getName()+"):0;");
//
//                    System.out.println(name+".add(builder, "+field.getName()+"Builder);");
//                }
//                else {
//                    System.out.println(name+".add(builder, this."+field.getName()+");");
//                }
                System.out.println("this."+field.getName()+"="+name+".;");

            }
        }
    }
}
