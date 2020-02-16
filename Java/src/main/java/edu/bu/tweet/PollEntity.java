package edu.bu.tweet;

import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;
import org.apache.log4j.Logger;

import java.util.List;

public class PollEntity extends Base implements RootData {

    static Logger logger = Logger.getLogger(PollEntity.class);

    private List<OptionEntity > options;
    private String end_datetime;
    private String duration_minutes;

    public List<OptionEntity> getOptions() {
        return options;
    }

    public void setOptions(List<OptionEntity> options) {
        this.options = options;
    }

    public String getEnd_datetime() {
        return end_datetime;
    }

    public void setEnd_datetime(String end_datetime) {
        this.end_datetime = end_datetime;
    }

    public String getDuration_minutes() {
        return duration_minutes;
    }

    public void setDuration_minutes(String duration_minutes) {
        this.duration_minutes = duration_minutes;
    }

    @Override
    public List<RootData> generateObjects(int number) {
        return null;
    }

    @Override
    public RootData javaDefaultDeserialization(byte[] buf) {
        return null;
    }

    @Override
    public byte[] jsonSerialization() {
        return new byte[0];
    }

    @Override
    public RootData jsonDeserialization(byte[] buf) {
        return null;
    }

    @Override
    public byte[] jsonSerialization_withGZIP() {
        return new byte[0];
    }

    @Override
    public RootData jsonDeserialization_withGZIP(byte[] buf) {
        return null;
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
        return new byte[0];
    }

    @Override
    public RootData readByteBuffer(byte[] buffData) {
        return null;
    }

    @Override
    public int compareTo(RootData o) {
        return 0;
    }
}
