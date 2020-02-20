package edu.bu.tweet;

import edu.bu.util.Base;
import edu.bu.util.RootData;
import org.apache.log4j.Logger;
import javax.json.*;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class VideoEntity extends Base implements RootData {

    static Logger logger = Logger.getLogger(VideoEntity.class);

    private List<Integer> aspect_ratio;
    private int duration_millis;
    private List<VariantEntity> variants;

    public VideoEntity() {
        this.aspect_ratio=new ArrayList<>();
        this.variants=new ArrayList<>();
    }

    public List<Integer> getAspect_ratio() {
        return aspect_ratio;
    }

    public void setAspect_ratio(List<Integer> aspect_ratio) {
        this.aspect_ratio = aspect_ratio;
    }

    public int getDuration_millis() {
        return duration_millis;
    }

    public void setDuration_millis(int duration_millis) {
        this.duration_millis = duration_millis;
    }

    public List<VariantEntity> getVariants() {
        return variants;
    }

    public void setVariants(List<VariantEntity> variants) {
        this.variants = variants;
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
        allocatedBufferSize+=4*(aspect_ratio.size()+1); //aspect_ratio
        allocatedBufferSize+=4;

        List<byte[]> variantsBytes=new ArrayList<>();
        for (VariantEntity variantEntity:variants){
            byte[] variantBytes=variantEntity.writeByteBuffer();
            allocatedBufferSize+=variantBytes.length;
            allocatedBufferSize+=4;
            variantsBytes.add(variantBytes);
        }
        allocatedBufferSize+=4;

        allocatedBufferSize+=4;//duration_millis

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
        byteBuffer.putInt(aspect_ratio.size());
        for (int i=0;i<aspect_ratio.size();i++){
            byteBuffer.putInt(aspect_ratio.get(i));
        }
        byteBuffer.putInt(duration_millis);

        byteBuffer.putInt(variantsBytes.size());
        for (byte[] b:variantsBytes){
            byteBuffer.putInt(b.length);
            byteBuffer.put(b);
        }

        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {
        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);

        int numberOfAspect_ratio=byteBuffer.getInt();
        for (int i=0;i<numberOfAspect_ratio;i++){
            this.aspect_ratio.add(byteBuffer.getInt());
        }

        this.duration_millis=byteBuffer.getInt();

        int numberOfVariants=byteBuffer.getInt();
        for (int i=0;i<numberOfVariants;i++){
            byte[] variantBytes = new byte[byteBuffer.getInt()];
            byteBuffer.get(variantBytes, 0, variantBytes.length);
            VariantEntity variantEntity = new VariantEntity();
            variantEntity.readByteBuffer(variantBytes);
            this.variants.add(variantEntity);
        }
        return this;
    }

    public JsonObject jsonObjectBuilder() {
        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();

        if (this.aspect_ratio!=null) {
            JsonArrayBuilder jsonAspect_ratioArray = Json.createArrayBuilder();
            for (Integer integer : aspect_ratio) {
                jsonAspect_ratioArray.add(integer);
            }
            objectBuilder.add("aspect_ratio", jsonAspect_ratioArray);
        }

        objectBuilder.add("duration_millis",this.duration_millis);

        if (this.variants!=null) {
            JsonArrayBuilder jsonVariantsArray = Json.createArrayBuilder();
            for (VariantEntity variantEntity : variants) {
                jsonVariantsArray.add(variantEntity.jsonObjectBuilder());
            }
            objectBuilder.add("variants",jsonVariantsArray);
        }
        JsonObject jsonObject = objectBuilder.build();
        return jsonObject;
    }

    public VideoEntity readJSONVideoEntity(JsonObject jsonObject) {
        if (jsonObject.getJsonArray("aspect_ratio") != null) {
            JsonArray aspect_ratioArray = jsonObject.getJsonArray("aspect_ratio");
            for (int i = 0; i < aspect_ratioArray.size(); i++) {
                this.aspect_ratio.add(aspect_ratioArray.getInt(i));
            }
        }
        this.duration_millis=jsonObject.getInt("duration_millis");

        if (jsonObject.getJsonArray("variants") != null) {
            JsonArray jsonVariantsArray = jsonObject.getJsonArray("variants");
            for (int i = 0; i < jsonVariantsArray.size(); i++) {
                JsonObject variantsJsonObject = jsonVariantsArray.getJsonObject(i);
                this.variants.add(new VariantEntity().readJSONVariantEntity(variantsJsonObject));
            }
        }
        return  this;
    }

    public int compareTo(RootData o) {
        return 0;
    }
}
