// automatically generated by the FlatBuffers compiler, do not modify

package at.tugraz.tweet.flatbuffers;

import java.nio.*;
import java.lang.*;

import com.google.flatbuffers.*;

@SuppressWarnings("unused")
public final class PlaceFBS extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_1_12_0(); }
  public static PlaceFBS getRootAsPlaceFBS(ByteBuffer _bb) { return getRootAsPlaceFBS(_bb, new PlaceFBS()); }
  public static PlaceFBS getRootAsPlaceFBS(ByteBuffer _bb, PlaceFBS obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public PlaceFBS __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public String name() { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer nameAsByteBuffer() { return __vector_as_bytebuffer(4, 1); }
  public ByteBuffer nameInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 4, 1); }
  public String countryCode() { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer countryCodeAsByteBuffer() { return __vector_as_bytebuffer(6, 1); }
  public ByteBuffer countryCodeInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 6, 1); }
  public String id() { int o = __offset(8); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer idAsByteBuffer() { return __vector_as_bytebuffer(8, 1); }
  public ByteBuffer idInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 8, 1); }
  public String country() { int o = __offset(10); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer countryAsByteBuffer() { return __vector_as_bytebuffer(10, 1); }
  public ByteBuffer countryInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 10, 1); }
  public String placeType() { int o = __offset(12); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer placeTypeAsByteBuffer() { return __vector_as_bytebuffer(12, 1); }
  public ByteBuffer placeTypeInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 12, 1); }
  public String url() { int o = __offset(14); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer urlAsByteBuffer() { return __vector_as_bytebuffer(14, 1); }
  public ByteBuffer urlInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 14, 1); }
  public String fullName() { int o = __offset(16); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer fullNameAsByteBuffer() { return __vector_as_bytebuffer(16, 1); }
  public ByteBuffer fullNameInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 16, 1); }
  public at.tugraz.tweet.flatbuffers.BoundingBoxCoordinateFBS boundingBox() { return boundingBox(new at.tugraz.tweet.flatbuffers.BoundingBoxCoordinateFBS()); }
  public at.tugraz.tweet.flatbuffers.BoundingBoxCoordinateFBS boundingBox(at.tugraz.tweet.flatbuffers.BoundingBoxCoordinateFBS obj) { int o = __offset(18); return o != 0 ? obj.__assign(__indirect(o + bb_pos), bb) : null; }

  public static int createPlaceFBS(FlatBufferBuilder builder,
      int nameOffset,
      int country_codeOffset,
      int idOffset,
      int countryOffset,
      int place_typeOffset,
      int urlOffset,
      int full_nameOffset,
      int bounding_boxOffset) {
    builder.startTable(8);
    PlaceFBS.addBoundingBox(builder, bounding_boxOffset);
    PlaceFBS.addFullName(builder, full_nameOffset);
    PlaceFBS.addUrl(builder, urlOffset);
    PlaceFBS.addPlaceType(builder, place_typeOffset);
    PlaceFBS.addCountry(builder, countryOffset);
    PlaceFBS.addId(builder, idOffset);
    PlaceFBS.addCountryCode(builder, country_codeOffset);
    PlaceFBS.addName(builder, nameOffset);
    return PlaceFBS.endPlaceFBS(builder);
  }

  public static void startPlaceFBS(FlatBufferBuilder builder) { builder.startTable(8); }
  public static void addName(FlatBufferBuilder builder, int nameOffset) { builder.addOffset(0, nameOffset, 0); }
  public static void addCountryCode(FlatBufferBuilder builder, int countryCodeOffset) { builder.addOffset(1, countryCodeOffset, 0); }
  public static void addId(FlatBufferBuilder builder, int idOffset) { builder.addOffset(2, idOffset, 0); }
  public static void addCountry(FlatBufferBuilder builder, int countryOffset) { builder.addOffset(3, countryOffset, 0); }
  public static void addPlaceType(FlatBufferBuilder builder, int placeTypeOffset) { builder.addOffset(4, placeTypeOffset, 0); }
  public static void addUrl(FlatBufferBuilder builder, int urlOffset) { builder.addOffset(5, urlOffset, 0); }
  public static void addFullName(FlatBufferBuilder builder, int fullNameOffset) { builder.addOffset(6, fullNameOffset, 0); }
  public static void addBoundingBox(FlatBufferBuilder builder, int boundingBoxOffset) { builder.addOffset(7, boundingBoxOffset, 0); }
  public static int endPlaceFBS(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }
  public static void finishPlaceFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finish(offset); }
  public static void finishSizePrefixedPlaceFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finishSizePrefixed(offset); }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public PlaceFBS get(int j) { return get(new PlaceFBS(), j); }
    public PlaceFBS get(PlaceFBS obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}
