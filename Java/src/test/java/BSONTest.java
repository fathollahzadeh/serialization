import java.io.ByteArrayOutputStream;
import java.io.IOException;

public class BSONTest {

    public static void main(String[] args) throws IOException {

        // serialize data
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        try {
            com.fasterxml.jackson.core.JsonGenerator gen = BsonSinglton.getInstance().getFactory().createJsonGenerator(baos);

            gen.writeStartObject();



            gen.close();

        } catch (IOException e) {

        }

    }
}
