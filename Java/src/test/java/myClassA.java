import org.bson.BsonBinary;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;

public class myClassA {

    private String str;

    private  int i;

    public myClassA(String str, int i) {
        this.str = str;
        this.i = i;
    }

    public byte[] bsonSerialization(){

        BasicOutputBuffer outputBuffer = new BasicOutputBuffer();

        BsonBinaryWriter writer=new BsonBinaryWriter(outputBuffer);

        writer.writeStartDocument();
        writer.writeString("str",this.str);
        writer.writeInt32("i",this.i);

        writer.writeEndDocument();
        return outputBuffer.toByteArray();
    }



    public String getStr() {
        return str;
    }

    public void setStr(String str) {
        this.str = str;
    }

    public int getI() {
        return i;
    }

    public void setI(int i) {
        this.i = i;
    }
}
