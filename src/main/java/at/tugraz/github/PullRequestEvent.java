package at.tugraz.github;
import at.tugraz.tweet.MatchingRulesEntity;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;
import org.apache.log4j.Logger;

import javax.json.Json;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonWriter;
import javax.json.JsonWriterFactory;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class PullRequestEvent extends Base implements RootData {

    static Logger logger = Logger.getLogger(PullRequestEvent.class);
    private String id;
    private String type;
    private Actor actor;
    private Repo repo;
    private Payload payload;
    private boolean isPublic;
    private String createdAt;
    private Org org;

    public PullRequestEvent() {
        this.actor = null;
        this.repo = null;
        this.payload = null;
        this.isPublic = false;
        this.org = null;
    }

    @Override
    public List<RootData> generateObjects(int number) {
        return null;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public Actor getActor() {
        return actor;
    }

    public void setActor(Actor actor) {
        this.actor = actor;
    }

    public Repo getRepo() {
        return repo;
    }

    public void setRepo(Repo repo) {
        this.repo = repo;
    }

    public Payload getPayload() {
        return payload;
    }

    public void setPayload(Payload payload) {
        this.payload = payload;
    }

    public boolean isPublic() {
        return isPublic;
    }

    public void setPublic(boolean aPublic) {
        isPublic = aPublic;
    }

    public String getCreatedAt() {
        return createdAt;
    }

    public void setCreatedAt(String createdAt) {
        this.createdAt = createdAt;
    }

    public Org getOrg() {
        return org;
    }

    public void setOrg(Org org) {
        this.org = org;
    }

    @Override
    public RootData javaDefaultDeserialization(byte[] buf) {
        ByteArrayInputStream b = new ByteArrayInputStream(buf);
        ObjectInputStream objectInputStream;

        PullRequestEvent p = null;

        try {
            objectInputStream = new ObjectInputStream(b);
            p = (PullRequestEvent) objectInputStream.readObject();

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
            logger.error(e);
        }

        // Get the bytes of the serialized JSON object
        return bos.toByteArray();
    }

    private JsonObject jsonObjectBuilder() {
        JsonObjectBuilder preObjectBuilder = Json.createObjectBuilder();
        preObjectBuilder.add("id", this.getId());
        preObjectBuilder.add("type", this.getType());
//        if (this.actor != null)
//            preObjectBuilder.add("actor", this.getId_str());
//        if (this.repo !=null)
//            preObjectBuilder.add("repo", this.getText());
//        if (this.payload !=null)
//            preObjectBuilder.add("payload", this.getSource());
//
        preObjectBuilder.add("isPublic", this.isPublic());
        preObjectBuilder.add("createdAt", this.getCreatedAt());

        JsonObject preJsonObject = preObjectBuilder.build();
        return preJsonObject;
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
