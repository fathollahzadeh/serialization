package edu.bu.tweet;

import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;
import org.apache.log4j.Logger;

import java.util.List;

public class VideoEntity extends Base implements RootData {

    static Logger logger = Logger.getLogger(VideoEntity.class);

    private List<Integer> aspect_ratio;
    private int duration_millis;
    private List<VariantEntity> variants;

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
        return new byte[0];
    }

    public RootData readByteBuffer(byte[] buffData) {
        return null;
    }

    public int compareTo(RootData o) {
        return 0;
    }
}
