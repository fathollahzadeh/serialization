// automatically generated by the FlatBuffers compiler, do not modify

package edu.bu.tweet.flatbuffers;

import java.nio.*;
import java.lang.*;
import java.util.*;
import com.google.flatbuffers.*;

@SuppressWarnings("unused")
public final class SymbolEntityFBS extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_1_12_0(); }
  public static SymbolEntityFBS getRootAsSymbolEntityFBS(ByteBuffer _bb) { return getRootAsSymbolEntityFBS(_bb, new SymbolEntityFBS()); }
  public static SymbolEntityFBS getRootAsSymbolEntityFBS(ByteBuffer _bb, SymbolEntityFBS obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public SymbolEntityFBS __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int indices(int j) { int o = __offset(4); return o != 0 ? bb.getInt(__vector(o) + j * 4) : 0; }
  public int indicesLength() { int o = __offset(4); return o != 0 ? __vector_len(o) : 0; }
  public IntVector indicesVector() { return indicesVector(new IntVector()); }
  public IntVector indicesVector(IntVector obj) { int o = __offset(4); return o != 0 ? obj.__assign(__vector(o), bb) : null; }
  public ByteBuffer indicesAsByteBuffer() { return __vector_as_bytebuffer(4, 4); }
  public ByteBuffer indicesInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 4, 4); }
  public boolean mutateIndices(int j, int indices) { int o = __offset(4); if (o != 0) { bb.putInt(__vector(o) + j * 4, indices); return true; } else { return false; } }
  public String text() { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer textAsByteBuffer() { return __vector_as_bytebuffer(6, 1); }
  public ByteBuffer textInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 6, 1); }

  public static int createSymbolEntityFBS(FlatBufferBuilder builder,
      int indicesOffset,
      int textOffset) {
    builder.startTable(2);
    SymbolEntityFBS.addText(builder, textOffset);
    SymbolEntityFBS.addIndices(builder, indicesOffset);
    return SymbolEntityFBS.endSymbolEntityFBS(builder);
  }

  public static void startSymbolEntityFBS(FlatBufferBuilder builder) { builder.startTable(2); }
  public static void addIndices(FlatBufferBuilder builder, int indicesOffset) { builder.addOffset(0, indicesOffset, 0); }
  public static int createIndicesVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addInt(data[i]); return builder.endVector(); }
  public static void startIndicesVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static void addText(FlatBufferBuilder builder, int textOffset) { builder.addOffset(1, textOffset, 0); }
  public static int endSymbolEntityFBS(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }
  public static void finishSymbolEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finish(offset); }
  public static void finishSizePrefixedSymbolEntityFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finishSizePrefixed(offset); }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public SymbolEntityFBS get(int j) { return get(new SymbolEntityFBS(), j); }
    public SymbolEntityFBS get(SymbolEntityFBS obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}

