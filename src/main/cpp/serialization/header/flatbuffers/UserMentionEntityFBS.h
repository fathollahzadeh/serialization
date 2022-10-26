// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_USERMENTIONENTITY_TWEETSTATUSFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_USERMENTIONENTITY_TWEETSTATUSFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

namespace tweetstatusflatbuffers {

struct UserMentionEntityFBS;
struct UserMentionEntityFBSBuilder;
struct UserMentionEntityFBST;

struct UserMentionEntityFBST : public flatbuffers::NativeTable {
  typedef UserMentionEntityFBS TableType;
  int64_t id = 0;
  std::string id_str{};
  std::vector<int32_t> indices{};
  std::string name{};
  std::string screen_name{};
};

struct UserMentionEntityFBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef UserMentionEntityFBST NativeTableType;
  typedef UserMentionEntityFBSBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ID = 4,
    VT_ID_STR = 6,
    VT_INDICES = 8,
    VT_NAME = 10,
    VT_SCREEN_NAME = 12
  };
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
  const flatbuffers::Vector<int32_t> *indices() const {
    return GetPointer<const flatbuffers::Vector<int32_t> *>(VT_INDICES);
  }
  flatbuffers::Vector<int32_t> *mutable_indices() {
    return GetPointer<flatbuffers::Vector<int32_t> *>(VT_INDICES);
  }
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  flatbuffers::String *mutable_name() {
    return GetPointer<flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::String *screen_name() const {
    return GetPointer<const flatbuffers::String *>(VT_SCREEN_NAME);
  }
  flatbuffers::String *mutable_screen_name() {
    return GetPointer<flatbuffers::String *>(VT_SCREEN_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int64_t>(verifier, VT_ID, 8) &&
           VerifyOffset(verifier, VT_ID_STR) &&
           verifier.VerifyString(id_str()) &&
           VerifyOffset(verifier, VT_INDICES) &&
           verifier.VerifyVector(indices()) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_SCREEN_NAME) &&
           verifier.VerifyString(screen_name()) &&
           verifier.EndTable();
  }
  UserMentionEntityFBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(UserMentionEntityFBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<UserMentionEntityFBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const UserMentionEntityFBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct UserMentionEntityFBSBuilder {
  typedef UserMentionEntityFBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(int64_t id) {
    fbb_.AddElement<int64_t>(UserMentionEntityFBS::VT_ID, id, 0);
  }
  void add_id_str(flatbuffers::Offset<flatbuffers::String> id_str) {
    fbb_.AddOffset(UserMentionEntityFBS::VT_ID_STR, id_str);
  }
  void add_indices(flatbuffers::Offset<flatbuffers::Vector<int32_t>> indices) {
    fbb_.AddOffset(UserMentionEntityFBS::VT_INDICES, indices);
  }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(UserMentionEntityFBS::VT_NAME, name);
  }
  void add_screen_name(flatbuffers::Offset<flatbuffers::String> screen_name) {
    fbb_.AddOffset(UserMentionEntityFBS::VT_SCREEN_NAME, screen_name);
  }
  explicit UserMentionEntityFBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<UserMentionEntityFBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<UserMentionEntityFBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<UserMentionEntityFBS> CreateUserMentionEntityFBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    int64_t id = 0,
    flatbuffers::Offset<flatbuffers::String> id_str = 0,
    flatbuffers::Offset<flatbuffers::Vector<int32_t>> indices = 0,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::String> screen_name = 0) {
  UserMentionEntityFBSBuilder builder_(_fbb);
  builder_.add_id(id);
  builder_.add_screen_name(screen_name);
  builder_.add_name(name);
  builder_.add_indices(indices);
  builder_.add_id_str(id_str);
  return builder_.Finish();
}

inline flatbuffers::Offset<UserMentionEntityFBS> CreateUserMentionEntityFBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int64_t id = 0,
    const char *id_str = nullptr,
    const std::vector<int32_t> *indices = nullptr,
    const char *name = nullptr,
    const char *screen_name = nullptr) {
  auto id_str__ = id_str ? _fbb.CreateString(id_str) : 0;
  auto indices__ = indices ? _fbb.CreateVector<int32_t>(*indices) : 0;
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto screen_name__ = screen_name ? _fbb.CreateString(screen_name) : 0;
  return tweetstatusflatbuffers::CreateUserMentionEntityFBS(
      _fbb,
      id,
      id_str__,
      indices__,
      name__,
      screen_name__);
}

flatbuffers::Offset<UserMentionEntityFBS> CreateUserMentionEntityFBS(flatbuffers::FlatBufferBuilder &_fbb, const UserMentionEntityFBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline UserMentionEntityFBST *UserMentionEntityFBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<UserMentionEntityFBST>(new UserMentionEntityFBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void UserMentionEntityFBS::UnPackTo(UserMentionEntityFBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = id(); _o->id = _e; }
  { auto _e = id_str(); if (_e) _o->id_str = _e->str(); }
  { auto _e = indices(); if (_e) { _o->indices.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->indices[_i] = _e->Get(_i); } } else { _o->indices.resize(0); } }
  { auto _e = name(); if (_e) _o->name = _e->str(); }
  { auto _e = screen_name(); if (_e) _o->screen_name = _e->str(); }
}

inline flatbuffers::Offset<UserMentionEntityFBS> UserMentionEntityFBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const UserMentionEntityFBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateUserMentionEntityFBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<UserMentionEntityFBS> CreateUserMentionEntityFBS(flatbuffers::FlatBufferBuilder &_fbb, const UserMentionEntityFBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const UserMentionEntityFBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _id = _o->id;
  auto _id_str = _o->id_str.empty() ? 0 : _fbb.CreateString(_o->id_str);
  auto _indices = _o->indices.size() ? _fbb.CreateVector(_o->indices) : 0;
  auto _name = _o->name.empty() ? 0 : _fbb.CreateString(_o->name);
  auto _screen_name = _o->screen_name.empty() ? 0 : _fbb.CreateString(_o->screen_name);
  return tweetstatusflatbuffers::CreateUserMentionEntityFBS(
      _fbb,
      _id,
      _id_str,
      _indices,
      _name,
      _screen_name);
}

inline const tweetstatusflatbuffers::UserMentionEntityFBS *GetUserMentionEntityFBS(const void *buf) {
  return flatbuffers::GetRoot<tweetstatusflatbuffers::UserMentionEntityFBS>(buf);
}

inline const tweetstatusflatbuffers::UserMentionEntityFBS *GetSizePrefixedUserMentionEntityFBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<tweetstatusflatbuffers::UserMentionEntityFBS>(buf);
}

inline UserMentionEntityFBS *GetMutableUserMentionEntityFBS(void *buf) {
  return flatbuffers::GetMutableRoot<UserMentionEntityFBS>(buf);
}

inline tweetstatusflatbuffers::UserMentionEntityFBS *GetMutableSizePrefixedUserMentionEntityFBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<tweetstatusflatbuffers::UserMentionEntityFBS>(buf);
}

inline bool VerifyUserMentionEntityFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<tweetstatusflatbuffers::UserMentionEntityFBS>(nullptr);
}

inline bool VerifySizePrefixedUserMentionEntityFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<tweetstatusflatbuffers::UserMentionEntityFBS>(nullptr);
}

inline void FinishUserMentionEntityFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::UserMentionEntityFBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedUserMentionEntityFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::UserMentionEntityFBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<tweetstatusflatbuffers::UserMentionEntityFBST> UnPackUserMentionEntityFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::UserMentionEntityFBST>(GetUserMentionEntityFBS(buf)->UnPack(res));
}

inline std::unique_ptr<tweetstatusflatbuffers::UserMentionEntityFBST> UnPackSizePrefixedUserMentionEntityFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::UserMentionEntityFBST>(GetSizePrefixedUserMentionEntityFBS(buf)->UnPack(res));
}

}  // namespace tweetstatusflatbuffers

#endif  // FLATBUFFERS_GENERATED_USERMENTIONENTITY_TWEETSTATUSFLATBUFFERS_H_
