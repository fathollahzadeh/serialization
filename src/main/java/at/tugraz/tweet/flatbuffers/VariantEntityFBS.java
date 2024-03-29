// automatically generated by the FlatBuffers compiler, do not modify

package at.tugraz.tweet.flatbuffers;

import java.nio.*;
import java.lang.*;
import java.util.*;
import com.google.flatbuffers.*;

@SuppressWarnings("unused")
public final class VariantEntityFBS extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_2_0_8(); }
  public static VariantEntityFBS getRootAsVariantEntityFBS(ByteBuffer _bb) { return getRootAsVariantEntityFBS(_bb, new VariantEntityFBS()); }
  public static VariantEntityFBS getRootAsVariantEntityFBS(ByteBuffer _bb, VariantEntityFBS obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public VariantEntityFBS __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public long bitrate() { int o = __offset(4); return o != 0 ? bb.getLong(o + bb_pos) : 0L; }
  public boolean mutateBitrate(long bitrate) { int o = __offset(4); if (o != 0) { bb.putLong(o + bb_pos, bitrate); return true; } else { return false; } }
  public String contentType() { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer contentTypeAsByteBuffer() { return __vector_as_bytebuffer(6, 1); }
  public ByteBuffer contentTypeInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 6, 1); }
  public String url() { int o = __offset(8); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer urlAsByteBuffer() { return __vector_as_bytebuffer(8, 1); }
  public ByteBuffer urlInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 8, 1); }

  public static int createVariantEntityFBS(FlatBufferBuilder builder,
      long bitrate,
      int contentTypeOffset,
      int urlOffset) {
    builder.startTable(3);
    VariantEntityFBS.addBitrate(builder, bitrate);
    VariantEntityFBS.addUrl(builder, urlOffset);
    VariantEntityFBS.addContentType(builder, contentTypeOffset);
    return VariantEntityFBS.endVariantEntityFBS(builder);
  }

  public static void startVariantEntityFBS(FlatBufferBuilder builder) { builder.startTable(3); }
  public static void addBitrate(FlatBufferBuilder builder, long bitrate) { builder.addLong(0, bitrate, 0L); }
  public static void addContentType(FlatBufferBuilder builder, int contentTypeOffset) { builder.addOffset(1, contentTypeOffset, 0); }
  public static void addUrl(FlatBufferBuilder builder, int urlOffset) { builder.addOffset(2, urlOffset, 0); }
  public static int endVariantEntityFBS(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }
  public static void finishVariantEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finish(offset); }
  public static void finishSizePrefixedVariantEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finishSizePrefixed(offset); }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public VariantEntityFBS get(int j) { return get(new VariantEntityFBS(), j); }
    public VariantEntityFBS get(VariantEntityFBS obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}

