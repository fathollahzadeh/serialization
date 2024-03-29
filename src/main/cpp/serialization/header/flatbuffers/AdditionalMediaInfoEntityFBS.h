// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_ADDITIONALMEDIAINFOENTITY_TWEETSTATUSFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_ADDITIONALMEDIAINFOENTITY_TWEETSTATUSFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

namespace tweetstatusflatbuffers {

struct AdditionalMediaInfoEntityFBS;
struct AdditionalMediaInfoEntityFBSBuilder;
struct AdditionalMediaInfoEntityFBST;

struct AdditionalMediaInfoEntityFBST : public flatbuffers::NativeTable {
  typedef AdditionalMediaInfoEntityFBS TableType;
  std::string title{};
  std::string description{};
  bool embeddable = false;
  bool monetizable = false;
};

struct AdditionalMediaInfoEntityFBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef AdditionalMediaInfoEntityFBST NativeTableType;
  typedef AdditionalMediaInfoEntityFBSBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TITLE = 4,
    VT_DESCRIPTION = 6,
    VT_EMBEDDABLE = 8,
    VT_MONETIZABLE = 10
  };
  const flatbuffers::String *title() const {
    return GetPointer<const flatbuffers::String *>(VT_TITLE);
  }
  flatbuffers::String *mutable_title() {
    return GetPointer<flatbuffers::String *>(VT_TITLE);
  }
  const flatbuffers::String *description() const {
    return GetPointer<const flatbuffers::String *>(VT_DESCRIPTION);
  }
  flatbuffers::String *mutable_description() {
    return GetPointer<flatbuffers::String *>(VT_DESCRIPTION);
  }
  bool embeddable() const {
    return GetField<uint8_t>(VT_EMBEDDABLE, 0) != 0;
  }
  bool mutate_embeddable(bool _embeddable = 0) {
    return SetField<uint8_t>(VT_EMBEDDABLE, static_cast<uint8_t>(_embeddable), 0);
  }
  bool monetizable() const {
    return GetField<uint8_t>(VT_MONETIZABLE, 0) != 0;
  }
  bool mutate_monetizable(bool _monetizable = 0) {
    return SetField<uint8_t>(VT_MONETIZABLE, static_cast<uint8_t>(_monetizable), 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_TITLE) &&
           verifier.VerifyString(title()) &&
           VerifyOffset(verifier, VT_DESCRIPTION) &&
           verifier.VerifyString(description()) &&
           VerifyField<uint8_t>(verifier, VT_EMBEDDABLE, 1) &&
           VerifyField<uint8_t>(verifier, VT_MONETIZABLE, 1) &&
           verifier.EndTable();
  }
  AdditionalMediaInfoEntityFBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(AdditionalMediaInfoEntityFBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<AdditionalMediaInfoEntityFBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const AdditionalMediaInfoEntityFBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct AdditionalMediaInfoEntityFBSBuilder {
  typedef AdditionalMediaInfoEntityFBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_title(flatbuffers::Offset<flatbuffers::String> title) {
    fbb_.AddOffset(AdditionalMediaInfoEntityFBS::VT_TITLE, title);
  }
  void add_description(flatbuffers::Offset<flatbuffers::String> description) {
    fbb_.AddOffset(AdditionalMediaInfoEntityFBS::VT_DESCRIPTION, description);
  }
  void add_embeddable(bool embeddable) {
    fbb_.AddElement<uint8_t>(AdditionalMediaInfoEntityFBS::VT_EMBEDDABLE, static_cast<uint8_t>(embeddable), 0);
  }
  void add_monetizable(bool monetizable) {
    fbb_.AddElement<uint8_t>(AdditionalMediaInfoEntityFBS::VT_MONETIZABLE, static_cast<uint8_t>(monetizable), 0);
  }
  explicit AdditionalMediaInfoEntityFBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<AdditionalMediaInfoEntityFBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<AdditionalMediaInfoEntityFBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<AdditionalMediaInfoEntityFBS> CreateAdditionalMediaInfoEntityFBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> title = 0,
    flatbuffers::Offset<flatbuffers::String> description = 0,
    bool embeddable = false,
    bool monetizable = false) {
  AdditionalMediaInfoEntityFBSBuilder builder_(_fbb);
  builder_.add_description(description);
  builder_.add_title(title);
  builder_.add_monetizable(monetizable);
  builder_.add_embeddable(embeddable);
  return builder_.Finish();
}

inline flatbuffers::Offset<AdditionalMediaInfoEntityFBS> CreateAdditionalMediaInfoEntityFBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *title = nullptr,
    const char *description = nullptr,
    bool embeddable = false,
    bool monetizable = false) {
  auto title__ = title ? _fbb.CreateString(title) : 0;
  auto description__ = description ? _fbb.CreateString(description) : 0;
  return tweetstatusflatbuffers::CreateAdditionalMediaInfoEntityFBS(
      _fbb,
      title__,
      description__,
      embeddable,
      monetizable);
}

flatbuffers::Offset<AdditionalMediaInfoEntityFBS> CreateAdditionalMediaInfoEntityFBS(flatbuffers::FlatBufferBuilder &_fbb, const AdditionalMediaInfoEntityFBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline AdditionalMediaInfoEntityFBST *AdditionalMediaInfoEntityFBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<AdditionalMediaInfoEntityFBST>(new AdditionalMediaInfoEntityFBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void AdditionalMediaInfoEntityFBS::UnPackTo(AdditionalMediaInfoEntityFBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = title(); if (_e) _o->title = _e->str(); }
  { auto _e = description(); if (_e) _o->description = _e->str(); }
  { auto _e = embeddable(); _o->embeddable = _e; }
  { auto _e = monetizable(); _o->monetizable = _e; }
}

inline flatbuffers::Offset<AdditionalMediaInfoEntityFBS> AdditionalMediaInfoEntityFBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const AdditionalMediaInfoEntityFBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateAdditionalMediaInfoEntityFBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<AdditionalMediaInfoEntityFBS> CreateAdditionalMediaInfoEntityFBS(flatbuffers::FlatBufferBuilder &_fbb, const AdditionalMediaInfoEntityFBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const AdditionalMediaInfoEntityFBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _title = _o->title.empty() ? 0 : _fbb.CreateString(_o->title);
  auto _description = _o->description.empty() ? 0 : _fbb.CreateString(_o->description);
  auto _embeddable = _o->embeddable;
  auto _monetizable = _o->monetizable;
  return tweetstatusflatbuffers::CreateAdditionalMediaInfoEntityFBS(
      _fbb,
      _title,
      _description,
      _embeddable,
      _monetizable);
}

inline const tweetstatusflatbuffers::AdditionalMediaInfoEntityFBS *GetAdditionalMediaInfoEntityFBS(const void *buf) {
  return flatbuffers::GetRoot<tweetstatusflatbuffers::AdditionalMediaInfoEntityFBS>(buf);
}

inline const tweetstatusflatbuffers::AdditionalMediaInfoEntityFBS *GetSizePrefixedAdditionalMediaInfoEntityFBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<tweetstatusflatbuffers::AdditionalMediaInfoEntityFBS>(buf);
}

inline AdditionalMediaInfoEntityFBS *GetMutableAdditionalMediaInfoEntityFBS(void *buf) {
  return flatbuffers::GetMutableRoot<AdditionalMediaInfoEntityFBS>(buf);
}

inline tweetstatusflatbuffers::AdditionalMediaInfoEntityFBS *GetMutableSizePrefixedAdditionalMediaInfoEntityFBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<tweetstatusflatbuffers::AdditionalMediaInfoEntityFBS>(buf);
}

inline bool VerifyAdditionalMediaInfoEntityFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<tweetstatusflatbuffers::AdditionalMediaInfoEntityFBS>(nullptr);
}

inline bool VerifySizePrefixedAdditionalMediaInfoEntityFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<tweetstatusflatbuffers::AdditionalMediaInfoEntityFBS>(nullptr);
}

inline void FinishAdditionalMediaInfoEntityFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::AdditionalMediaInfoEntityFBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedAdditionalMediaInfoEntityFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::AdditionalMediaInfoEntityFBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<tweetstatusflatbuffers::AdditionalMediaInfoEntityFBST> UnPackAdditionalMediaInfoEntityFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::AdditionalMediaInfoEntityFBST>(GetAdditionalMediaInfoEntityFBS(buf)->UnPack(res));
}

inline std::unique_ptr<tweetstatusflatbuffers::AdditionalMediaInfoEntityFBST> UnPackSizePrefixedAdditionalMediaInfoEntityFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::AdditionalMediaInfoEntityFBST>(GetSizePrefixedAdditionalMediaInfoEntityFBS(buf)->UnPack(res));
}

}  // namespace tweetstatusflatbuffers

#endif  // FLATBUFFERS_GENERATED_ADDITIONALMEDIAINFOENTITY_TWEETSTATUSFLATBUFFERS_H_
