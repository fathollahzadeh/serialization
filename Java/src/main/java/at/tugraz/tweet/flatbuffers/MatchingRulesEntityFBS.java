// automatically generated by the FlatBuffers compiler, do not modify

package at.tugraz.tweet.flatbuffers;

import java.nio.*;
import java.lang.*;

import com.google.flatbuffers.*;

@SuppressWarnings("unused")
public final class MatchingRulesEntityFBS extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_2_0_0(); }
  public static MatchingRulesEntityFBS getRootAsMatchingRulesEntityFBS(ByteBuffer _bb) { return getRootAsMatchingRulesEntityFBS(_bb, new MatchingRulesEntityFBS()); }
  public static MatchingRulesEntityFBS getRootAsMatchingRulesEntityFBS(ByteBuffer _bb, MatchingRulesEntityFBS obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public MatchingRulesEntityFBS __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public String tag() { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer tagAsByteBuffer() { return __vector_as_bytebuffer(4, 1); }
  public ByteBuffer tagInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 4, 1); }
  public long id() { int o = __offset(6); return o != 0 ? bb.getLong(o + bb_pos) : 0L; }
  public boolean mutateId(long id) { int o = __offset(6); if (o != 0) { bb.putLong(o + bb_pos, id); return true; } else { return false; } }
  public String idStr() { int o = __offset(8); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer idStrAsByteBuffer() { return __vector_as_bytebuffer(8, 1); }
  public ByteBuffer idStrInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 8, 1); }

  public static int createMatchingRulesEntityFBS(FlatBufferBuilder builder,
      int tagOffset,
      long id,
      int id_strOffset) {
    builder.startTable(3);
    MatchingRulesEntityFBS.addId(builder, id);
    MatchingRulesEntityFBS.addIdStr(builder, id_strOffset);
    MatchingRulesEntityFBS.addTag(builder, tagOffset);
    return MatchingRulesEntityFBS.endMatchingRulesEntityFBS(builder);
  }

  public static void startMatchingRulesEntityFBS(FlatBufferBuilder builder) { builder.startTable(3); }
  public static void addTag(FlatBufferBuilder builder, int tagOffset) { builder.addOffset(0, tagOffset, 0); }
  public static void addId(FlatBufferBuilder builder, long id) { builder.addLong(1, id, 0L); }
  public static void addIdStr(FlatBufferBuilder builder, int idStrOffset) { builder.addOffset(2, idStrOffset, 0); }
  public static int endMatchingRulesEntityFBS(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }
  public static void finishMatchingRulesEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finish(offset); }
  public static void finishSizePrefixedMatchingRulesEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finishSizePrefixed(offset); }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public MatchingRulesEntityFBS get(int j) { return get(new MatchingRulesEntityFBS(), j); }
    public MatchingRulesEntityFBS get(MatchingRulesEntityFBS obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}

