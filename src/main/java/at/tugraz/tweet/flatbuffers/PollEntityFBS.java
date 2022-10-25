// automatically generated by the FlatBuffers compiler, do not modify

package at.tugraz.tweet.flatbuffers;

import java.nio.*;
import java.lang.*;
import java.util.*;
import com.google.flatbuffers.*;

@SuppressWarnings("unused")
public final class PollEntityFBS extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_2_0_8(); }
  public static PollEntityFBS getRootAsPollEntityFBS(ByteBuffer _bb) { return getRootAsPollEntityFBS(_bb, new PollEntityFBS()); }
  public static PollEntityFBS getRootAsPollEntityFBS(ByteBuffer _bb, PollEntityFBS obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public PollEntityFBS __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public at.tugraz.tweet.flatbuffers.OptionEntityFBS options(int j) { return options(new at.tugraz.tweet.flatbuffers.OptionEntityFBS(), j); }
  public at.tugraz.tweet.flatbuffers.OptionEntityFBS options(at.tugraz.tweet.flatbuffers.OptionEntityFBS obj, int j) { int o = __offset(4); return o != 0 ? obj.__assign(__indirect(__vector(o) + j * 4), bb) : null; }
  public int optionsLength() { int o = __offset(4); return o != 0 ? __vector_len(o) : 0; }
  public at.tugraz.tweet.flatbuffers.OptionEntityFBS.Vector optionsVector() { return optionsVector(new at.tugraz.tweet.flatbuffers.OptionEntityFBS.Vector()); }
  public at.tugraz.tweet.flatbuffers.OptionEntityFBS.Vector optionsVector(at.tugraz.tweet.flatbuffers.OptionEntityFBS.Vector obj) { int o = __offset(4); return o != 0 ? obj.__assign(__vector(o), 4, bb) : null; }
  public String endDatetime() { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer endDatetimeAsByteBuffer() { return __vector_as_bytebuffer(6, 1); }
  public ByteBuffer endDatetimeInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 6, 1); }
  public String durationMinutes() { int o = __offset(8); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer durationMinutesAsByteBuffer() { return __vector_as_bytebuffer(8, 1); }
  public ByteBuffer durationMinutesInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 8, 1); }

  public static int createPollEntityFBS(FlatBufferBuilder builder,
      int optionsOffset,
      int endDatetimeOffset,
      int durationMinutesOffset) {
    builder.startTable(3);
    PollEntityFBS.addDurationMinutes(builder, durationMinutesOffset);
    PollEntityFBS.addEndDatetime(builder, endDatetimeOffset);
    PollEntityFBS.addOptions(builder, optionsOffset);
    return PollEntityFBS.endPollEntityFBS(builder);
  }

  public static void startPollEntityFBS(FlatBufferBuilder builder) { builder.startTable(3); }
  public static void addOptions(FlatBufferBuilder builder, int optionsOffset) { builder.addOffset(0, optionsOffset, 0); }
  public static int createOptionsVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addOffset(data[i]); return builder.endVector(); }
  public static void startOptionsVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static void addEndDatetime(FlatBufferBuilder builder, int endDatetimeOffset) { builder.addOffset(1, endDatetimeOffset, 0); }
  public static void addDurationMinutes(FlatBufferBuilder builder, int durationMinutesOffset) { builder.addOffset(2, durationMinutesOffset, 0); }
  public static int endPollEntityFBS(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }
  public static void finishPollEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finish(offset); }
  public static void finishSizePrefixedPollEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finishSizePrefixed(offset); }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public PollEntityFBS get(int j) { return get(new PollEntityFBS(), j); }
    public PollEntityFBS get(PollEntityFBS obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}

