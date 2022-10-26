// automatically generated by the FlatBuffers compiler, do not modify

package at.tugraz.tweet.flatbuffers;

import java.nio.*;
import java.lang.*;
import java.util.*;
import com.google.flatbuffers.*;

@SuppressWarnings("unused")
public final class ExtendedTweetFBS extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_2_0_8(); }
  public static ExtendedTweetFBS getRootAsExtendedTweetFBS(ByteBuffer _bb) { return getRootAsExtendedTweetFBS(_bb, new ExtendedTweetFBS()); }
  public static ExtendedTweetFBS getRootAsExtendedTweetFBS(ByteBuffer _bb, ExtendedTweetFBS obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public ExtendedTweetFBS __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public String fullText() { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer fullTextAsByteBuffer() { return __vector_as_bytebuffer(4, 1); }
  public ByteBuffer fullTextInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 4, 1); }
  public int displayTextRange(int j) { int o = __offset(6); return o != 0 ? bb.getInt(__vector(o) + j * 4) : 0; }
  public int displayTextRangeLength() { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; }
  public IntVector displayTextRangeVector() { return displayTextRangeVector(new IntVector()); }
  public IntVector displayTextRangeVector(IntVector obj) { int o = __offset(6); return o != 0 ? obj.__assign(__vector(o), bb) : null; }
  public ByteBuffer displayTextRangeAsByteBuffer() { return __vector_as_bytebuffer(6, 4); }
  public ByteBuffer displayTextRangeInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 6, 4); }
  public boolean mutateDisplayTextRange(int j, int display_text_range) { int o = __offset(6); if (o != 0) { bb.putInt(__vector(o) + j * 4, display_text_range); return true; } else { return false; } }
  public at.tugraz.tweet.flatbuffers.EntitiesFBS entities() { return entities(new at.tugraz.tweet.flatbuffers.EntitiesFBS()); }
  public at.tugraz.tweet.flatbuffers.EntitiesFBS entities(at.tugraz.tweet.flatbuffers.EntitiesFBS obj) { int o = __offset(8); return o != 0 ? obj.__assign(__indirect(o + bb_pos), bb) : null; }
  public at.tugraz.tweet.flatbuffers.ExtendedEntitiesFBS extendedEntities() { return extendedEntities(new at.tugraz.tweet.flatbuffers.ExtendedEntitiesFBS()); }
  public at.tugraz.tweet.flatbuffers.ExtendedEntitiesFBS extendedEntities(at.tugraz.tweet.flatbuffers.ExtendedEntitiesFBS obj) { int o = __offset(10); return o != 0 ? obj.__assign(__indirect(o + bb_pos), bb) : null; }

  public static int createExtendedTweetFBS(FlatBufferBuilder builder,
      int fullTextOffset,
      int displayTextRangeOffset,
      int entitiesOffset,
      int extendedEntitiesOffset) {
    builder.startTable(4);
    ExtendedTweetFBS.addExtendedEntities(builder, extendedEntitiesOffset);
    ExtendedTweetFBS.addEntities(builder, entitiesOffset);
    ExtendedTweetFBS.addDisplayTextRange(builder, displayTextRangeOffset);
    ExtendedTweetFBS.addFullText(builder, fullTextOffset);
    return ExtendedTweetFBS.endExtendedTweetFBS(builder);
  }

  public static void startExtendedTweetFBS(FlatBufferBuilder builder) { builder.startTable(4); }
  public static void addFullText(FlatBufferBuilder builder, int fullTextOffset) { builder.addOffset(0, fullTextOffset, 0); }
  public static void addDisplayTextRange(FlatBufferBuilder builder, int displayTextRangeOffset) { builder.addOffset(1, displayTextRangeOffset, 0); }
  public static int createDisplayTextRangeVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addInt(data[i]); return builder.endVector(); }
  public static void startDisplayTextRangeVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static void addEntities(FlatBufferBuilder builder, int entitiesOffset) { builder.addOffset(2, entitiesOffset, 0); }
  public static void addExtendedEntities(FlatBufferBuilder builder, int extendedEntitiesOffset) { builder.addOffset(3, extendedEntitiesOffset, 0); }
  public static int endExtendedTweetFBS(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }
  public static void finishExtendedTweetFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finish(offset); }
  public static void finishSizePrefixedExtendedTweetFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finishSizePrefixed(offset); }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public ExtendedTweetFBS get(int j) { return get(new ExtendedTweetFBS(), j); }
    public ExtendedTweetFBS get(ExtendedTweetFBS obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}

