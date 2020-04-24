// automatically generated by the FlatBuffers compiler, do not modify

package edu.bu.tweet.flatbuffers;

import java.nio.*;
import java.lang.*;
import java.util.*;
import com.google.flatbuffers.*;

@SuppressWarnings("unused")
public final class AdditionalMediaInfoEntityFBS extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_1_12_0(); }
  public static AdditionalMediaInfoEntityFBS getRootAsAdditionalMediaInfoEntityFBS(ByteBuffer _bb) { return getRootAsAdditionalMediaInfoEntityFBS(_bb, new AdditionalMediaInfoEntityFBS()); }
  public static AdditionalMediaInfoEntityFBS getRootAsAdditionalMediaInfoEntityFBS(ByteBuffer _bb, AdditionalMediaInfoEntityFBS obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public AdditionalMediaInfoEntityFBS __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public String title() { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer titleAsByteBuffer() { return __vector_as_bytebuffer(4, 1); }
  public ByteBuffer titleInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 4, 1); }
  public String description() { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer descriptionAsByteBuffer() { return __vector_as_bytebuffer(6, 1); }
  public ByteBuffer descriptionInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 6, 1); }
  public boolean embeddable() { int o = __offset(8); return o != 0 ? 0!=bb.get(o + bb_pos) : false; }
  public boolean mutateEmbeddable(boolean embeddable) { int o = __offset(8); if (o != 0) { bb.put(o + bb_pos, (byte)(embeddable ? 1 : 0)); return true; } else { return false; } }
  public boolean monetizable() { int o = __offset(10); return o != 0 ? 0!=bb.get(o + bb_pos) : false; }
  public boolean mutateMonetizable(boolean monetizable) { int o = __offset(10); if (o != 0) { bb.put(o + bb_pos, (byte)(monetizable ? 1 : 0)); return true; } else { return false; } }

  public static int createAdditionalMediaInfoEntityFBS(FlatBufferBuilder builder,
      int titleOffset,
      int descriptionOffset,
      boolean embeddable,
      boolean monetizable) {
    builder.startTable(4);
    AdditionalMediaInfoEntityFBS.addDescription(builder, descriptionOffset);
    AdditionalMediaInfoEntityFBS.addTitle(builder, titleOffset);
    AdditionalMediaInfoEntityFBS.addMonetizable(builder, monetizable);
    AdditionalMediaInfoEntityFBS.addEmbeddable(builder, embeddable);
    return AdditionalMediaInfoEntityFBS.endAdditionalMediaInfoEntityFBS(builder);
  }

  public static void startAdditionalMediaInfoEntityFBS(FlatBufferBuilder builder) { builder.startTable(4); }
  public static void addTitle(FlatBufferBuilder builder, int titleOffset) { builder.addOffset(0, titleOffset, 0); }
  public static void addDescription(FlatBufferBuilder builder, int descriptionOffset) { builder.addOffset(1, descriptionOffset, 0); }
  public static void addEmbeddable(FlatBufferBuilder builder, boolean embeddable) { builder.addBoolean(2, embeddable, false); }
  public static void addMonetizable(FlatBufferBuilder builder, boolean monetizable) { builder.addBoolean(3, monetizable, false); }
  public static int endAdditionalMediaInfoEntityFBS(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }
  public static void finishAdditionalMediaInfoEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finish(offset); }
  public static void finishSizePrefixedAdditionalMediaInfoEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finishSizePrefixed(offset); }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public AdditionalMediaInfoEntityFBS get(int j) { return get(new AdditionalMediaInfoEntityFBS(), j); }
    public AdditionalMediaInfoEntityFBS get(AdditionalMediaInfoEntityFBS obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}

