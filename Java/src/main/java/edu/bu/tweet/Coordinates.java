package edu.bu.tweet;


import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.List;
import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonValue;

import com.google.flatbuffers.FlatBufferBuilder;
import edu.bu.tweet.flatbuffers.AdditionalMediaInfoEntityFBS;
import edu.bu.tweet.flatbuffers.CoordinatesFBS;
import edu.bu.tweet.flatbuffers.URLEntityFBS;
import edu.bu.tweet.flatbuffers.UserFBS;
import org.apache.log4j.Logger;

import edu.bu.util.Base;
import edu.bu.util.RootData;
import org.bson.BsonBinary;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;

public class Coordinates extends Base implements RootData {

    private static final long serialVersionUID = 767200407069467768L;

    static Logger logger = Logger.getLogger(Coordinates.class);

    private String type;
    private double[] coordinates;

    public Coordinates() {
        this.coordinates = new double[0];
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public double[] getCoordinates() {
        return coordinates;
    }

    public void setCoordinates(double[] coordinates) {
        this.coordinates = coordinates;
    }

    public List<RootData> generateObjects(int number) {
        return null;
    }

    public RootData javaDefaultDeserialization(byte[] buf) {
        return null;
    }

    public byte[] jsonSerialization() {
        return new byte[0];
    }

    public RootData jsonDeserialization(byte[] buf) {
        return null;
    }

    public byte[] jsonSerialization_withGZIP() {
        return new byte[0];
    }

    public RootData jsonDeserialization_withGZIP(byte[] buf) {
        return null;
    }

    public byte[] protocolBufferWrite() {
        return new byte[0];
    }

    public RootData protocolBufferRead(byte[] buf) {
        return null;
    }

    public byte[] writeByteBuffer() {

        int allocatedBufferSize = 0;

        byte[] typeBytes = type.getBytes(Charset.forName("UTF-8"));
        allocatedBufferSize += typeBytes.length + 4;

        //coordinate size
        // 4 bytes is for an additional integer for write the size byteArray
        allocatedBufferSize += 8 * this.coordinates.length + 4;

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);

        byteBuffer.putInt(typeBytes.length);
        byteBuffer.put(typeBytes);

        byteBuffer.putInt(coordinates.length);
        for (double d : coordinates) {
            byteBuffer.putDouble(d);
        }
        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {

        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
        int stringSize;

        stringSize = byteBuffer.getInt();
        this.type = extractString(byteBuffer, stringSize);

        int numOfCoordinates = byteBuffer.getInt();
        this.coordinates = new double[numOfCoordinates];
        for (int i = 0; i < numOfCoordinates; i++) {
            this.coordinates[i] = byteBuffer.getDouble();
        }

        return this;
    }

    public int compareTo(RootData o) {
        return 0;
    }

    public JsonObject jsonObjectBuilder() {

        JsonObjectBuilder coordinatesObjectBuilder = Json.createObjectBuilder();
        coordinatesObjectBuilder.add("type", this.type);

        JsonArrayBuilder jsonCoordinatesArray = Json.createArrayBuilder();
        for (Double d : this.coordinates) {
            jsonCoordinatesArray.add(d);
        }
        coordinatesObjectBuilder.add("coordinates", jsonCoordinatesArray);
        JsonObject coordinatesJsonObject = coordinatesObjectBuilder.build();
        return coordinatesJsonObject;

    }

    public Coordinates readJSONCoordinates(JsonObject jsonObject) {
        if (jsonObject.get("type") != null && jsonObject.get("type") != JsonValue.NULL) {
            this.type = jsonObject.getString("type");
        }

        if (jsonObject.getJsonArray("coordinates") != null) {
            JsonArray coordinatesArray = jsonObject.getJsonArray("coordinates");
            this.coordinates = new double[coordinatesArray.size()];
            for (int i = 0; i < coordinatesArray.size(); i++) {
                this.coordinates[i] = Double.parseDouble(coordinatesArray.getJsonNumber(i).toString());
            }
        }
        return this;
    }

    public byte[] bsonSerialization() {
        BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
        BsonBinaryWriter writer = new BsonBinaryWriter(outputBuffer);

        writer.writeStartDocument();
        if (this.type != null)
            writer.writeString("type", this.type);

        writer.writeInt32("coordinates_size", this.coordinates.length);

        writer.writeName("coordinates");
        writer.writeStartArray();
        for (Double d : this.coordinates) {
            writer.writeDouble(d);
        }
        writer.writeEndArray();

        writer.writeEndDocument();

        return outputBuffer.toByteArray();

    }

    public RootData bsonDeSerialization(byte[] buffData) {
        ByteBuffer buf = ByteBuffer.wrap(buffData);
        BsonBinaryReader reader = new BsonBinaryReader(buf);

        reader.readStartDocument();

        String currentName = reader.readName();
        if (currentName.equals("type")) {
            this.type = reader.readString();
            reader.readName();
        }

        int coordinates_size = reader.readInt32();
        this.coordinates = new double[coordinates_size];
        reader.readName("coordinates");
        reader.readStartArray();
        for (int i = 0; i < coordinates_size; i++) {
            this.coordinates[i] = reader.readDouble();
        }
        reader.readEndArray();

        reader.readEndDocument();

        return this;
    }

    public int flatBuffersWriter(FlatBufferBuilder builder) {

        int typeBuilder = this.type != null ? builder.createString(this.type) : 0;
        int coordinatesBuilder = CoordinatesFBS.createCoordinatesVector(builder, this.coordinates);

        CoordinatesFBS.startCoordinatesFBS(builder);
        CoordinatesFBS.addType(builder, typeBuilder);
        CoordinatesFBS.addCoordinates(builder, coordinatesBuilder);
        int orc = CoordinatesFBS.endCoordinatesFBS(builder);
        return orc;
    }

    public Coordinates flatBuffersDeserialization(CoordinatesFBS coordinatesFBS) {

        this.type = coordinatesFBS.type();
        this.coordinates = new double[coordinatesFBS.coordinatesLength()];
        for (int i = 0; i < coordinatesFBS.coordinatesLength(); i++)
            this.coordinates[i] = coordinatesFBS.coordinates(i);

        return this;
    }
}