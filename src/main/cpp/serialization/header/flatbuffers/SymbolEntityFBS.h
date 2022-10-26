// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_SYMBOLENTITY_TWEETSTATUSFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_SYMBOLENTITY_TWEETSTATUSFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

namespace tweetstatusflatbuffers {

struct SymbolEntityFBS;
struct SymbolEntityFBSBuilder;
struct SymbolEntityFBST;

struct SymbolEntityFBST : public flatbuffers::NativeTable {
  typedef SymbolEntityFBS TableType;
  std::vector<int32_t> indices{};
  std::string text{};
};

struct SymbolEntityFBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef SymbolEntityFBST NativeTableType;
  typedef SymbolEntityFBSBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_INDICES = 4,
    VT_TEXT = 6
  };
  const flatbuffers::Vector<int32_t> *indices() const {
    return GetPointer<const flatbuffers::Vector<int32_t> *>(VT_INDICES);
  }
  flatbuffers::Vector<int32_t> *mutable_indices() {
    return GetPointer<flatbuffers::Vector<int32_t> *>(VT_INDICES);
  }
  const flatbuffers::String *text() const {
    return GetPointer<const flatbuffers::String *>(VT_TEXT);
  }
  flatbuffers::String *mutable_text() {
    return GetPointer<flatbuffers::String *>(VT_TEXT);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_INDICES) &&
           verifier.VerifyVector(indices()) &&
           VerifyOffset(verifier, VT_TEXT) &&
           verifier.VerifyString(text()) &&
           verifier.EndTable();
  }
  SymbolEntityFBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(SymbolEntityFBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<SymbolEntityFBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const SymbolEntityFBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct SymbolEntityFBSBuilder {
  typedef SymbolEntityFBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_indices(flatbuffers::Offset<flatbuffers::Vector<int32_t>> indices) {
    fbb_.AddOffset(SymbolEntityFBS::VT_INDICES, indices);
  }
  void add_text(flatbuffers::Offset<flatbuffers::String> text) {
    fbb_.AddOffset(SymbolEntityFBS::VT_TEXT, text);
  }
  explicit SymbolEntityFBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<SymbolEntityFBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<SymbolEntityFBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<SymbolEntityFBS> CreateSymbolEntityFBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<int32_t>> indices = 0,
    flatbuffers::Offset<flatbuffers::String> text = 0) {
  SymbolEntityFBSBuilder builder_(_fbb);
  builder_.add_text(text);
  builder_.add_indices(indices);
  return builder_.Finish();
}

inline flatbuffers::Offset<SymbolEntityFBS> CreateSymbolEntityFBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<int32_t> *indices = nullptr,
    const char *text = nullptr) {
  auto indices__ = indices ? _fbb.CreateVector<int32_t>(*indices) : 0;
  auto text__ = text ? _fbb.CreateString(text) : 0;
  return tweetstatusflatbuffers::CreateSymbolEntityFBS(
      _fbb,
      indices__,
      text__);
}

flatbuffers::Offset<SymbolEntityFBS> CreateSymbolEntityFBS(flatbuffers::FlatBufferBuilder &_fbb, const SymbolEntityFBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline SymbolEntityFBST *SymbolEntityFBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<SymbolEntityFBST>(new SymbolEntityFBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void SymbolEntityFBS::UnPackTo(SymbolEntityFBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = indices(); if (_e) { _o->indices.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->indices[_i] = _e->Get(_i); } } else { _o->indices.resize(0); } }
  { auto _e = text(); if (_e) _o->text = _e->str(); }
}

inline flatbuffers::Offset<SymbolEntityFBS> SymbolEntityFBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const SymbolEntityFBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateSymbolEntityFBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<SymbolEntityFBS> CreateSymbolEntityFBS(flatbuffers::FlatBufferBuilder &_fbb, const SymbolEntityFBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const SymbolEntityFBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _indices = _o->indices.size() ? _fbb.CreateVector(_o->indices) : 0;
  auto _text = _o->text.empty() ? 0 : _fbb.CreateString(_o->text);
  return tweetstatusflatbuffers::CreateSymbolEntityFBS(
      _fbb,
      _indices,
      _text);
}

inline const tweetstatusflatbuffers::SymbolEntityFBS *GetSymbolEntityFBS(const void *buf) {
  return flatbuffers::GetRoot<tweetstatusflatbuffers::SymbolEntityFBS>(buf);
}

inline const tweetstatusflatbuffers::SymbolEntityFBS *GetSizePrefixedSymbolEntityFBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<tweetstatusflatbuffers::SymbolEntityFBS>(buf);
}

inline SymbolEntityFBS *GetMutableSymbolEntityFBS(void *buf) {
  return flatbuffers::GetMutableRoot<SymbolEntityFBS>(buf);
}

inline tweetstatusflatbuffers::SymbolEntityFBS *GetMutableSizePrefixedSymbolEntityFBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<tweetstatusflatbuffers::SymbolEntityFBS>(buf);
}

inline bool VerifySymbolEntityFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<tweetstatusflatbuffers::SymbolEntityFBS>(nullptr);
}

inline bool VerifySizePrefixedSymbolEntityFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<tweetstatusflatbuffers::SymbolEntityFBS>(nullptr);
}

inline void FinishSymbolEntityFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::SymbolEntityFBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedSymbolEntityFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::SymbolEntityFBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<tweetstatusflatbuffers::SymbolEntityFBST> UnPackSymbolEntityFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::SymbolEntityFBST>(GetSymbolEntityFBS(buf)->UnPack(res));
}

inline std::unique_ptr<tweetstatusflatbuffers::SymbolEntityFBST> UnPackSizePrefixedSymbolEntityFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::SymbolEntityFBST>(GetSizePrefixedSymbolEntityFBS(buf)->UnPack(res));
}

}  // namespace tweetstatusflatbuffers

#endif  // FLATBUFFERS_GENERATED_SYMBOLENTITY_TWEETSTATUSFLATBUFFERS_H_
