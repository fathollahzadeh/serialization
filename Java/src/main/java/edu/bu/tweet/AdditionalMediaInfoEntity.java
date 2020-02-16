package edu.bu.tweet;

import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;
import org.apache.log4j.Logger;

import java.util.List;

public class AdditionalMediaInfoEntity extends Base implements RootData {

    static Logger logger = Logger.getLogger(AdditionalMediaInfoEntity.class);

    private String title;
    private String description;
    private boolean embeddable;
    private boolean monetizable;

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public boolean isEmbeddable() {
        return embeddable;
    }

    public void setEmbeddable(boolean embeddable) {
        this.embeddable = embeddable;
    }

    public boolean isMonetizable() {
        return monetizable;
    }

    public void setMonetizable(boolean monetizable) {
        this.monetizable = monetizable;
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
