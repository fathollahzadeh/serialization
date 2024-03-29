// automatically generated by the FlatBuffers compiler, do not modify

package at.tugraz.tweet.flatbuffers;

import java.nio.*;
import java.lang.*;
import java.util.*;
import com.google.flatbuffers.*;

@SuppressWarnings("unused")
public final class CoordinatesFBS extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_2_0_8(); }
  public static CoordinatesFBS getRootAsCoordinatesFBS(ByteBuffer _bb) { return getRootAsCoordinatesFBS(_bb, new CoordinatesFBS()); }
  public static CoordinatesFBS getRootAsCoordinatesFBS(ByteBuffer _bb, CoordinatesFBS obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public CoordinatesFBS __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public String type() { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer typeAsByteBuffer() { return __vector_as_bytebuffer(4, 1); }
  public ByteBuffer typeInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 4, 1); }
  public double coordinates(int j) { int o = __offset(6); return o != 0 ? bb.getDouble(__vector(o) + j * 8) : 0; }
  public int coordinatesLength() { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; }
  public DoubleVector coordinatesVector() { return coordinatesVector(new DoubleVector()); }
  public DoubleVector coordinatesVector(DoubleVector obj) { int o = __offset(6); return o != 0 ? obj.__assign(__vector(o), bb) : null; }
  public ByteBuffer coordinatesAsByteBuffer() { return __vector_as_bytebuffer(6, 8); }
  public ByteBuffer coordinatesInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 6, 8); }
  public boolean mutateCoordinates(int j, double coordinates) { int o = __offset(6); if (o != 0) { bb.putDouble(__vector(o) + j * 8, coordinates); return true; } else { return false; } }

  public static int createCoordinatesFBS(FlatBufferBuilder builder,
      int typeOffset,
      int coordinatesOffset) {
    builder.startTable(2);
    CoordinatesFBS.addCoordinates(builder, coordinatesOffset);
    CoordinatesFBS.addType(builder, typeOffset);
    return CoordinatesFBS.endCoordinatesFBS(builder);
  }

  public static void startCoordinatesFBS(FlatBufferBuilder builder) { builder.startTable(2); }
  public static void addType(FlatBufferBuilder builder, int typeOffset) { builder.addOffset(0, typeOffset, 0); }
  public static void addCoordinates(FlatBufferBuilder builder, int coordinatesOffset) { builder.addOffset(1, coordinatesOffset, 0); }
  public static int createCoordinatesVector(FlatBufferBuilder builder, double[] data) { builder.startVector(8, data.length, 8); for (int i = data.length - 1; i >= 0; i--) builder.addDouble(data[i]); return builder.endVector(); }
  public static void startCoordinatesVector(FlatBufferBuilder builder, int numElems) { builder.startVector(8, numElems, 8); }
  public static int endCoordinatesFBS(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }
  public static void finishCoordinatesFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finish(offset); }
  public static void finishSizePrefixedCoordinatesFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finishSizePrefixed(offset); }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public CoordinatesFBS get(int j) { return get(new CoordinatesFBS(), j); }
    public CoordinatesFBS get(CoordinatesFBS obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}

