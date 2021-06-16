// automatically generated by the FlatBuffers compiler, do not modify

package edu.bu.tweet.flatbuffers;

import java.nio.*;
import java.lang.*;
import java.util.*;
import com.google.flatbuffers.*;

@SuppressWarnings("unused")
public final class VideoEntityFBS extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_1_12_0(); }
  public static VideoEntityFBS getRootAsVideoEntityFBS(ByteBuffer _bb) { return getRootAsVideoEntityFBS(_bb, new VideoEntityFBS()); }
  public static VideoEntityFBS getRootAsVideoEntityFBS(ByteBuffer _bb, VideoEntityFBS obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public VideoEntityFBS __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int aspectRatio(int j) { int o = __offset(4); return o != 0 ? bb.getInt(__vector(o) + j * 4) : 0; }
  public int aspectRatioLength() { int o = __offset(4); return o != 0 ? __vector_len(o) : 0; }
  public IntVector aspectRatioVector() { return aspectRatioVector(new IntVector()); }
  public IntVector aspectRatioVector(IntVector obj) { int o = __offset(4); return o != 0 ? obj.__assign(__vector(o), bb) : null; }
  public ByteBuffer aspectRatioAsByteBuffer() { return __vector_as_bytebuffer(4, 4); }
  public ByteBuffer aspectRatioInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 4, 4); }
  public boolean mutateAspectRatio(int j, int aspect_ratio) { int o = __offset(4); if (o != 0) { bb.putInt(__vector(o) + j * 4, aspect_ratio); return true; } else { return false; } }
  public int durationMillis() { int o = __offset(6); return o != 0 ? bb.getInt(o + bb_pos) : 0; }
  public boolean mutateDurationMillis(int duration_millis) { int o = __offset(6); if (o != 0) { bb.putInt(o + bb_pos, duration_millis); return true; } else { return false; } }
  public edu.bu.tweet.flatbuffers.VariantEntityFBS variants(int j) { return variants(new edu.bu.tweet.flatbuffers.VariantEntityFBS(), j); }
  public edu.bu.tweet.flatbuffers.VariantEntityFBS variants(edu.bu.tweet.flatbuffers.VariantEntityFBS obj, int j) { int o = __offset(8); return o != 0 ? obj.__assign(__indirect(__vector(o) + j * 4), bb) : null; }
  public int variantsLength() { int o = __offset(8); return o != 0 ? __vector_len(o) : 0; }
  public edu.bu.tweet.flatbuffers.VariantEntityFBS.Vector variantsVector() { return variantsVector(new edu.bu.tweet.flatbuffers.VariantEntityFBS.Vector()); }
  public edu.bu.tweet.flatbuffers.VariantEntityFBS.Vector variantsVector(edu.bu.tweet.flatbuffers.VariantEntityFBS.Vector obj) { int o = __offset(8); return o != 0 ? obj.__assign(__vector(o), 4, bb) : null; }

  public static int createVideoEntityFBS(FlatBufferBuilder builder,
      int aspect_ratioOffset,
      int duration_millis,
      int variantsOffset) {
    builder.startTable(3);
    VideoEntityFBS.addVariants(builder, variantsOffset);
    VideoEntityFBS.addDurationMillis(builder, duration_millis);
    VideoEntityFBS.addAspectRatio(builder, aspect_ratioOffset);
    return VideoEntityFBS.endVideoEntityFBS(builder);
  }

  public static void startVideoEntityFBS(FlatBufferBuilder builder) { builder.startTable(3); }
  public static void addAspectRatio(FlatBufferBuilder builder, int aspectRatioOffset) { builder.addOffset(0, aspectRatioOffset, 0); }
  public static int createAspectRatioVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addInt(data[i]); return builder.endVector(); }
  public static void startAspectRatioVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static void addDurationMillis(FlatBufferBuilder builder, int durationMillis) { builder.addInt(1, durationMillis, 0); }
  public static void addVariants(FlatBufferBuilder builder, int variantsOffset) { builder.addOffset(2, variantsOffset, 0); }
  public static int createVariantsVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addOffset(data[i]); return builder.endVector(); }
  public static void startVariantsVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static int endVideoEntityFBS(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }
  public static void finishVideoEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finish(offset); }
  public static void finishSizePrefixedVideoEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finishSizePrefixed(offset); }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public VideoEntityFBS get(int j) { return get(new VideoEntityFBS(), j); }
    public VideoEntityFBS get(VideoEntityFBS obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}

