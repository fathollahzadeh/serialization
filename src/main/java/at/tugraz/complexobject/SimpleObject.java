package at.tugraz.complexobject;

import at.tugraz.tweet.*;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;
import org.apache.log4j.Logger;

import javax.json.*;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class SimpleObject extends Base implements RootData {
    static Logger logger = Logger.getLogger(SimpleObject.class);
    public int var_int;
    public long var_long;
    public float var_float;
    public double var_double;
    public String var_string;
    public boolean var_bool;
    public char var_char;

    @Override
    public List<RootData> generateObjects(int number) {
        return null;
    }

    @Override
    public RootData javaDefaultDeserialization(byte[] buf) {
        ByteArrayInputStream b = new ByteArrayInputStream(buf);
        ObjectInputStream objectInputStream;

        SimpleObject p = null;

        try {
            objectInputStream = new ObjectInputStream(b);
            p = (SimpleObject) objectInputStream.readObject();

        } catch (IOException | ClassNotFoundException e) {
            logger.error("Can't read object from byteArray", e);
        }
        return p;
    }

    @Override
    public byte[] jsonSerialization() {
        Map<String, Object> properties = new HashMap<String, Object>(1);
        //		properties.put(JsonGenerator.PRETTY_PRINTING, true);

        JsonWriterFactory writerFactory = Json.createWriterFactory(properties);
        ByteArrayOutputStream bos = new ByteArrayOutputStream();

        try {
            JsonWriter jsonWriter = writerFactory.createWriter(bos);
            jsonWriter.writeObject(this.jsonObjectBuilder());
            jsonWriter.close();
        } catch (Exception e) {
            e.printStackTrace();
            logger.error(e);
        }

        // Get the bytes of the serialized JSON object
        byte[] buf = bos.toByteArray();
        return buf;
    }

    private JsonObject jsonObjectBuilder() {
        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        objectBuilder.add("var_int", this.var_int);
        objectBuilder.add("var_long", this.var_long);
        objectBuilder.add("var_float", this.var_float);
        objectBuilder.add("var_double", this.var_double);
        objectBuilder.add("var_string", this.var_string);
        objectBuilder.add("var_bool", this.var_bool);
        objectBuilder.add("var_char", this.var_char);
        JsonObject jsonObject = objectBuilder.build();
        return jsonObject;
    }


    @Override
    public RootData jsonDeserialization(byte[] buf) {
        SimpleObject simpleObject;
        ByteArrayInputStream b = new ByteArrayInputStream(buf);

        try {
            // create JsonReader object
            JsonReader jsonReader = Json.createReader(b);

            // get JsonObject from JsonReader
            JsonObject jsonObject = jsonReader.readObject();

            simpleObject = readJSONSimpleObject(jsonObject);

            // we can close IO resource and JsonReader now
            b.close();
            jsonReader.close();

        } catch (Exception e) {
            logger.error("Can not read JSON object TweetStatus from byteArray", e);
            return null;
        }

        return simpleObject;
    }

    private SimpleObject readJSONSimpleObject(JsonObject jsonObject) {

        this.var_int = jsonObject.getInt("var_int");
        this.var_long = Long.parseLong(jsonObject.getJsonNumber("var_long").toString());
        this.var_float =  Float.parseFloat(jsonObject.getJsonNumber("var_float").toString());
        this.var_double = Double.parseDouble(jsonObject.getJsonNumber("var_double").toString());
        this.var_string = jsonObject.getString("var_string");
        this.var_bool = jsonObject.getBoolean("var_bool");
        this.var_char = jsonObject.getString("var_char").charAt(0);
        return this;
    }

    @Override
    public byte[] jsonSerialization_withGZIP() {
        return this.gZIPCompression(this.jsonSerialization());

    }

    @Override
    public RootData jsonDeserialization_withGZIP(byte[] buf) {
        return jsonDeserialization(this.gZIP_DE_Compression(buf));
    }

    @Override
    public byte[] protocolBufferWrite() {
        return new byte[0];
    }

    @Override
    public RootData protocolBufferRead(byte[] buf) {
        return null;
    }

    @Override
    public byte[] writeByteBuffer() {
        int allocatedBufferSize = 0;

        byte[] var_stringBytes = var_string.getBytes(StandardCharsets.UTF_8);
        allocatedBufferSize += var_stringBytes.length + 4;

        allocatedBufferSize ++; // var_char
        allocatedBufferSize ++; // var_bool

        //reserve size for primitive variables:
        allocatedBufferSize += 4; //var_int
        allocatedBufferSize += 8; //var_long
        allocatedBufferSize += 4; //var_float
        allocatedBufferSize += 8; //var_double

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
        byteBuffer.putInt(var_int);
        byteBuffer.putLong(var_long);
        byteBuffer.putFloat(var_float);
        byteBuffer.putDouble(var_double);
        byteBuffer.putInt(var_stringBytes.length);
        byteBuffer.put(var_stringBytes);
        byteBuffer.putChar(var_char);
        byteBuffer.put(convertToByte(var_bool));
        return byteBuffer.array();
    }

    @Override
    public RootData readByteBuffer(byte[] buffData) {
        return null;
    }

    @Override
    public byte[] bsonSerialization() {
        return new byte[0];
    }

    @Override
    public RootData bsonDeSerialization(byte[] buffData) {
        return null;
    }

    @Override
    public int compareTo(RootData rootData) {
        return 0;
    }
}
