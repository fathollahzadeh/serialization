import org.bson.*;
import org.bson.io.BasicOutputBuffer;
import org.bson.io.ByteBufferBsonInput;

import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;

public class MongoDB_BSON {

    public static void main(String[] args) {

//        BsonDocument document=new BsonDocument();
//        BsonWriter bsonWriter=new BsonDocumentWriter(document);
//
//        bsonWriter.writeStartDocument();
//
//        myClassA mca=new myClassA("saeed",1234);
//
//        bsonWriter.writeName("aaa");
//        bsonWriter.writeBinaryData(new BsonBinary(mca.bsonSerialization()));
//        bsonWriter.writeEndDocument();
//
//        System.out.println(document.toJson());


        BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
        BsonBinaryWriter writer=new BsonBinaryWriter(outputBuffer);
        writer.writeStartDocument();
        writer.writeString("a","1");
        writer.writeString("b","2");
        myClassA mca=new myClassA("saeed",1234);
        writer.writeBinaryData("mca",new BsonBinary(mca.bsonSerialization()));
        writer.writeEndDocument();
        outputBuffer.toByteArray();

        //-------------------------------------------------
        ByteBuffer buf = ByteBuffer.wrap(outputBuffer.toByteArray());

        BsonBinaryReader reader;
        reader = new BsonBinaryReader(buf);

        reader.readStartDocument();
        System.out.println(reader.readString("a"));
        System.out.println(reader.readString("b"));

        reader.readName();
        String currentName=reader.getCurrentName();
        System.out.println(currentName);

        BsonBinary bsonBinary=reader.readBinaryData("mca");
        System.out.println(">>>>>>>>>>>> "+ bsonBinary.getData().length);


    }
}
