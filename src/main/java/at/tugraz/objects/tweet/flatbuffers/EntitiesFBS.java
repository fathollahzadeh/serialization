// automatically generated by the FlatBuffers compiler, do not modify

package at.tugraz.tweet.flatbuffers;

import java.nio.*;
import java.lang.*;

import com.google.flatbuffers.*;

@SuppressWarnings("unused")
public final class EntitiesFBS extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_1_12_0(); }
  public static EntitiesFBS getRootAsEntitiesFBS(ByteBuffer _bb) { return getRootAsEntitiesFBS(_bb, new EntitiesFBS()); }
  public static EntitiesFBS getRootAsEntitiesFBS(ByteBuffer _bb, EntitiesFBS obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public EntitiesFBS __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public at.tugraz.tweet.flatbuffers.HashtagEntityFBS hashtags(int j) { return hashtags(new at.tugraz.tweet.flatbuffers.HashtagEntityFBS(), j); }
  public at.tugraz.tweet.flatbuffers.HashtagEntityFBS hashtags(at.tugraz.tweet.flatbuffers.HashtagEntityFBS obj, int j) { int o = __offset(4); return o != 0 ? obj.__assign(__indirect(__vector(o) + j * 4), bb) : null; }
  public int hashtagsLength() { int o = __offset(4); return o != 0 ? __vector_len(o) : 0; }
  public at.tugraz.tweet.flatbuffers.HashtagEntityFBS.Vector hashtagsVector() { return hashtagsVector(new at.tugraz.tweet.flatbuffers.HashtagEntityFBS.Vector()); }
  public at.tugraz.tweet.flatbuffers.HashtagEntityFBS.Vector hashtagsVector(at.tugraz.tweet.flatbuffers.HashtagEntityFBS.Vector obj) { int o = __offset(4); return o != 0 ? obj.__assign(__vector(o), 4, bb) : null; }
  public at.tugraz.tweet.flatbuffers.MediaEntityFBS media(int j) { return media(new at.tugraz.tweet.flatbuffers.MediaEntityFBS(), j); }
  public at.tugraz.tweet.flatbuffers.MediaEntityFBS media(at.tugraz.tweet.flatbuffers.MediaEntityFBS obj, int j) { int o = __offset(6); return o != 0 ? obj.__assign(__indirect(__vector(o) + j * 4), bb) : null; }
  public int mediaLength() { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; }
  public at.tugraz.tweet.flatbuffers.MediaEntityFBS.Vector mediaVector() { return mediaVector(new at.tugraz.tweet.flatbuffers.MediaEntityFBS.Vector()); }
  public at.tugraz.tweet.flatbuffers.MediaEntityFBS.Vector mediaVector(at.tugraz.tweet.flatbuffers.MediaEntityFBS.Vector obj) { int o = __offset(6); return o != 0 ? obj.__assign(__vector(o), 4, bb) : null; }
  public at.tugraz.tweet.flatbuffers.URLEntityFBS urls(int j) { return urls(new at.tugraz.tweet.flatbuffers.URLEntityFBS(), j); }
  public at.tugraz.tweet.flatbuffers.URLEntityFBS urls(at.tugraz.tweet.flatbuffers.URLEntityFBS obj, int j) { int o = __offset(8); return o != 0 ? obj.__assign(__indirect(__vector(o) + j * 4), bb) : null; }
  public int urlsLength() { int o = __offset(8); return o != 0 ? __vector_len(o) : 0; }
  public at.tugraz.tweet.flatbuffers.URLEntityFBS.Vector urlsVector() { return urlsVector(new at.tugraz.tweet.flatbuffers.URLEntityFBS.Vector()); }
  public at.tugraz.tweet.flatbuffers.URLEntityFBS.Vector urlsVector(at.tugraz.tweet.flatbuffers.URLEntityFBS.Vector obj) { int o = __offset(8); return o != 0 ? obj.__assign(__vector(o), 4, bb) : null; }
  public at.tugraz.tweet.flatbuffers.UserMentionEntityFBS userMentions(int j) { return userMentions(new at.tugraz.tweet.flatbuffers.UserMentionEntityFBS(), j); }
  public at.tugraz.tweet.flatbuffers.UserMentionEntityFBS userMentions(at.tugraz.tweet.flatbuffers.UserMentionEntityFBS obj, int j) { int o = __offset(10); return o != 0 ? obj.__assign(__indirect(__vector(o) + j * 4), bb) : null; }
  public int userMentionsLength() { int o = __offset(10); return o != 0 ? __vector_len(o) : 0; }
  public at.tugraz.tweet.flatbuffers.UserMentionEntityFBS.Vector userMentionsVector() { return userMentionsVector(new at.tugraz.tweet.flatbuffers.UserMentionEntityFBS.Vector()); }
  public at.tugraz.tweet.flatbuffers.UserMentionEntityFBS.Vector userMentionsVector(at.tugraz.tweet.flatbuffers.UserMentionEntityFBS.Vector obj) { int o = __offset(10); return o != 0 ? obj.__assign(__vector(o), 4, bb) : null; }
  public at.tugraz.tweet.flatbuffers.SymbolEntityFBS symbols(int j) { return symbols(new at.tugraz.tweet.flatbuffers.SymbolEntityFBS(), j); }
  public at.tugraz.tweet.flatbuffers.SymbolEntityFBS symbols(at.tugraz.tweet.flatbuffers.SymbolEntityFBS obj, int j) { int o = __offset(12); return o != 0 ? obj.__assign(__indirect(__vector(o) + j * 4), bb) : null; }
  public int symbolsLength() { int o = __offset(12); return o != 0 ? __vector_len(o) : 0; }
  public at.tugraz.tweet.flatbuffers.SymbolEntityFBS.Vector symbolsVector() { return symbolsVector(new at.tugraz.tweet.flatbuffers.SymbolEntityFBS.Vector()); }
  public at.tugraz.tweet.flatbuffers.SymbolEntityFBS.Vector symbolsVector(at.tugraz.tweet.flatbuffers.SymbolEntityFBS.Vector obj) { int o = __offset(12); return o != 0 ? obj.__assign(__vector(o), 4, bb) : null; }
  public at.tugraz.tweet.flatbuffers.PollEntityFBS polls(int j) { return polls(new at.tugraz.tweet.flatbuffers.PollEntityFBS(), j); }
  public at.tugraz.tweet.flatbuffers.PollEntityFBS polls(at.tugraz.tweet.flatbuffers.PollEntityFBS obj, int j) { int o = __offset(14); return o != 0 ? obj.__assign(__indirect(__vector(o) + j * 4), bb) : null; }
  public int pollsLength() { int o = __offset(14); return o != 0 ? __vector_len(o) : 0; }
  public at.tugraz.tweet.flatbuffers.PollEntityFBS.Vector pollsVector() { return pollsVector(new at.tugraz.tweet.flatbuffers.PollEntityFBS.Vector()); }
  public at.tugraz.tweet.flatbuffers.PollEntityFBS.Vector pollsVector(at.tugraz.tweet.flatbuffers.PollEntityFBS.Vector obj) { int o = __offset(14); return o != 0 ? obj.__assign(__vector(o), 4, bb) : null; }

  public static int createEntitiesFBS(FlatBufferBuilder builder,
      int hashtagsOffset,
      int mediaOffset,
      int urlsOffset,
      int user_mentionsOffset,
      int symbolsOffset,
      int pollsOffset) {
    builder.startTable(6);
    EntitiesFBS.addPolls(builder, pollsOffset);
    EntitiesFBS.addSymbols(builder, symbolsOffset);
    EntitiesFBS.addUserMentions(builder, user_mentionsOffset);
    EntitiesFBS.addUrls(builder, urlsOffset);
    EntitiesFBS.addMedia(builder, mediaOffset);
    EntitiesFBS.addHashtags(builder, hashtagsOffset);
    return EntitiesFBS.endEntitiesFBS(builder);
  }

  public static void startEntitiesFBS(FlatBufferBuilder builder) { builder.startTable(6); }
  public static void addHashtags(FlatBufferBuilder builder, int hashtagsOffset) { builder.addOffset(0, hashtagsOffset, 0); }
  public static int createHashtagsVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addOffset(data[i]); return builder.endVector(); }
  public static void startHashtagsVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static void addMedia(FlatBufferBuilder builder, int mediaOffset) { builder.addOffset(1, mediaOffset, 0); }
  public static int createMediaVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addOffset(data[i]); return builder.endVector(); }
  public static void startMediaVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static void addUrls(FlatBufferBuilder builder, int urlsOffset) { builder.addOffset(2, urlsOffset, 0); }
  public static int createUrlsVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addOffset(data[i]); return builder.endVector(); }
  public static void startUrlsVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static void addUserMentions(FlatBufferBuilder builder, int userMentionsOffset) { builder.addOffset(3, userMentionsOffset, 0); }
  public static int createUserMentionsVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addOffset(data[i]); return builder.endVector(); }
  public static void startUserMentionsVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static void addSymbols(FlatBufferBuilder builder, int symbolsOffset) { builder.addOffset(4, symbolsOffset, 0); }
  public static int createSymbolsVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addOffset(data[i]); return builder.endVector(); }
  public static void startSymbolsVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static void addPolls(FlatBufferBuilder builder, int pollsOffset) { builder.addOffset(5, pollsOffset, 0); }
  public static int createPollsVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addOffset(data[i]); return builder.endVector(); }
  public static void startPollsVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static int endEntitiesFBS(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }
  public static void finishEntitiesFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finish(offset); }
  public static void finishSizePrefixedEntitiesFBSBuffer(FlatBufferBuilder builder, int offset) { builder.finishSizePrefixed(offset); }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public EntitiesFBS get(int j) { return get(new EntitiesFBS(), j); }
    public EntitiesFBS get(EntitiesFBS obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}
