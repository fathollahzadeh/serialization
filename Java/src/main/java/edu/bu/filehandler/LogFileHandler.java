package edu.bu.filehandler;

import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.Writer;

public class LogFileHandler {

    private String fileName;

    public LogFileHandler() {
    }

    public LogFileHandler(String fileName) {
        this.fileName = fileName;
    }

    public void addLog(boolean read,int serializationType, boolean seq,String datatype, double iotime, double totaltime,boolean taskset){

        String log;
        if (read)
            log="[ReadTimeJAVA]#"+taskset+"#";
        else
            log="[WriteTimeJAVA]#"+taskset+"#";
        String method="";
        switch (serializationType) {
            case 1:
                method = "Java Default";
                break;
            case 2:
                method = "Java Json+Gzip";
                break;
            case 3:
                method = "Java Bson";
                break;
            case 4:
                method = "Java ProtoBuf";
                break;
            case 5:
                method = "Java Kryo";
                break;
            case 6:
                method = "Java Byte Buffer";
                break;
            case 7:
                method = "Java FlatBuffers";
                break;
            case 8:
                method = "Java Json";
                break;
            case 9:
                method = "Java Gson";
                break;
        }
        String seqString="true";
        if (!seq)
            seqString="false";

        log+=method+"#";
        log+=seqString+"#";
        log+=datatype+"#";
        log+=iotime+"#";
        log+=totaltime+"\n";
        try (Writer writer = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream(this.fileName,true), "utf-8"))) {
            writer.write(log);
        }catch (Exception ex) {

        }
    }
}
