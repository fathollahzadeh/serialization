// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_MATCHINGRULESENTITY_TWEETSTATUSFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_MATCHINGRULESENTITY_TWEETSTATUSFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

namespace tweetstatusflatbuffers {

struct MatchingRulesEntityFBS;
struct MatchingRulesEntityFBSBuilder;
struct MatchingRulesEntityFBST;

struct MatchingRulesEntityFBST : public flatbuffers::NativeTable {
  typedef MatchingRulesEntityFBS TableType;
  std::string tag{};
  int64_t id = 0;
  std::string id_str{};
};

struct MatchingRulesEntityFBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef MatchingRulesEntityFBST NativeTableType;
  typedef MatchingRulesEntityFBSBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TAG = 4,
    VT_ID = 6,
    VT_ID_STR = 8
  };
  const flatbuffers::String *tag() const {
    return GetPointer<const flatbuffers::String *>(VT_TAG);
  }
  flatbuffers::String *mutable_tag() {
    return GetPointer<flatbuffers::String *>(VT_TAG);
  }
  int64_t id() const {
    return GetField<int64_t>(VT_ID, 0);
  }
  bool mutate_id(int64_t _id = 0) {
    return SetField<int64_t>(VT_ID, _id, 0);
  }
  const flatbuffers::String *id_str() const {
    return GetPointer<const flatbuffers::String *>(VT_ID_STR);
  }
  flatbuffers::String *mutable_id_str() {
    return GetPointer<flatbuffers::String *>(VT_ID_STR);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_TAG) &&
           verifier.VerifyString(tag()) &&
           VerifyField<int64_t>(verifier, VT_ID, 8) &&
           VerifyOffset(verifier, VT_ID_STR) &&
           verifier.VerifyString(id_str()) &&
           verifier.EndTable();
  }
  MatchingRulesEntityFBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(MatchingRulesEntityFBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<MatchingRulesEntityFBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const MatchingRulesEntityFBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct MatchingRulesEntityFBSBuilder {
  typedef MatchingRulesEntityFBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_tag(flatbuffers::Offset<flatbuffers::String> tag) {
    fbb_.AddOffset(MatchingRulesEntityFBS::VT_TAG, tag);
  }
  void add_id(int64_t id) {
    fbb_.AddElement<int64_t>(MatchingRulesEntityFBS::VT_ID, id, 0);
  }
  void add_id_str(flatbuffers::Offset<flatbuffers::String> id_str) {
    fbb_.AddOffset(MatchingRulesEntityFBS::VT_ID_STR, id_str);
  }
  explicit MatchingRulesEntityFBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<MatchingRulesEntityFBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<MatchingRulesEntityFBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<MatchingRulesEntityFBS> CreateMatchingRulesEntityFBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> tag = 0,
    int64_t id = 0,
    flatbuffers::Offset<flatbuffers::String> id_str = 0) {
  MatchingRulesEntityFBSBuilder builder_(_fbb);
  builder_.add_id(id);
  builder_.add_id_str(id_str);
  builder_.add_tag(tag);
  return builder_.Finish();
}

inline flatbuffers::Offset<MatchingRulesEntityFBS> CreateMatchingRulesEntityFBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *tag = nullptr,
    int64_t id = 0,
    const char *id_str = nullptr) {
  auto tag__ = tag ? _fbb.CreateString(tag) : 0;
  auto id_str__ = id_str ? _fbb.CreateString(id_str) : 0;
  return tweetstatusflatbuffers::CreateMatchingRulesEntityFBS(
      _fbb,
      tag__,
      id,
      id_str__);
}

flatbuffers::Offset<MatchingRulesEntityFBS> CreateMatchingRulesEntityFBS(flatbuffers::FlatBufferBuilder &_fbb, const MatchingRulesEntityFBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline MatchingRulesEntityFBST *MatchingRulesEntityFBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<MatchingRulesEntityFBST>(new MatchingRulesEntityFBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void MatchingRulesEntityFBS::UnPackTo(MatchingRulesEntityFBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = tag(); if (_e) _o->tag = _e->str(); }
  { auto _e = id(); _o->id = _e; }
  { auto _e = id_str(); if (_e) _o->id_str = _e->str(); }
}

inline flatbuffers::Offset<MatchingRulesEntityFBS> MatchingRulesEntityFBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const MatchingRulesEntityFBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateMatchingRulesEntityFBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<MatchingRulesEntityFBS> CreateMatchingRulesEntityFBS(flatbuffers::FlatBufferBuilder &_fbb, const MatchingRulesEntityFBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const MatchingRulesEntityFBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _tag = _o->tag.empty() ? 0 : _fbb.CreateString(_o->tag);
  auto _id = _o->id;
  auto _id_str = _o->id_str.empty() ? 0 : _fbb.CreateString(_o->id_str);
  return tweetstatusflatbuffers::CreateMatchingRulesEntityFBS(
      _fbb,
      _tag,
      _id,
      _id_str);
}

inline const tweetstatusflatbuffers::MatchingRulesEntityFBS *GetMatchingRulesEntityFBS(const void *buf) {
  return flatbuffers::GetRoot<tweetstatusflatbuffers::MatchingRulesEntityFBS>(buf);
}

inline const tweetstatusflatbuffers::MatchingRulesEntityFBS *GetSizePrefixedMatchingRulesEntityFBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<tweetstatusflatbuffers::MatchingRulesEntityFBS>(buf);
}

inline MatchingRulesEntityFBS *GetMutableMatchingRulesEntityFBS(void *buf) {
  return flatbuffers::GetMutableRoot<MatchingRulesEntityFBS>(buf);
}

inline tweetstatusflatbuffers::MatchingRulesEntityFBS *GetMutableSizePrefixedMatchingRulesEntityFBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<tweetstatusflatbuffers::MatchingRulesEntityFBS>(buf);
}

inline bool VerifyMatchingRulesEntityFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<tweetstatusflatbuffers::MatchingRulesEntityFBS>(nullptr);
}

inline bool VerifySizePrefixedMatchingRulesEntityFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<tweetstatusflatbuffers::MatchingRulesEntityFBS>(nullptr);
}

inline void FinishMatchingRulesEntityFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::MatchingRulesEntityFBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedMatchingRulesEntityFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::MatchingRulesEntityFBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<tweetstatusflatbuffers::MatchingRulesEntityFBST> UnPackMatchingRulesEntityFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::MatchingRulesEntityFBST>(GetMatchingRulesEntityFBS(buf)->UnPack(res));
}

inline std::unique_ptr<tweetstatusflatbuffers::MatchingRulesEntityFBST> UnPackSizePrefixedMatchingRulesEntityFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::MatchingRulesEntityFBST>(GetSizePrefixedMatchingRulesEntityFBS(buf)->UnPack(res));
}

}  // namespace tweetstatusflatbuffers

#endif  // FLATBUFFERS_GENERATED_MATCHINGRULESENTITY_TWEETSTATUSFLATBUFFERS_H_
