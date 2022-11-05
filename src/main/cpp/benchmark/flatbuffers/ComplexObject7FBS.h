// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_COMPLEXOBJECT7_COMPLEXOBJECTFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_COMPLEXOBJECT7_COMPLEXOBJECTFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

#include "ComplexObject8FBS.h"

namespace complexobjectflatbuffers {

struct ComplexObject7FBS;
struct ComplexObject7FBSBuilder;
struct ComplexObject7FBST;

struct ComplexObject7FBST : public flatbuffers::NativeTable {
  typedef ComplexObject7FBS TableType;
  std::string var_string{};
  std::unique_ptr<complexobjectflatbuffers::ComplexObject8FBST> complexobject{};
  ComplexObject7FBST() = default;
  ComplexObject7FBST(const ComplexObject7FBST &o);
  ComplexObject7FBST(ComplexObject7FBST&&) FLATBUFFERS_NOEXCEPT = default;
  ComplexObject7FBST &operator=(ComplexObject7FBST o) FLATBUFFERS_NOEXCEPT;
};

struct ComplexObject7FBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ComplexObject7FBST NativeTableType;
  typedef ComplexObject7FBSBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_VAR_STRING = 4,
    VT_COMPLEXOBJECT = 6
  };
  const flatbuffers::String *var_string() const {
    return GetPointer<const flatbuffers::String *>(VT_VAR_STRING);
  }
  flatbuffers::String *mutable_var_string() {
    return GetPointer<flatbuffers::String *>(VT_VAR_STRING);
  }
  const complexobjectflatbuffers::ComplexObject8FBS *complexobject() const {
    return GetPointer<const complexobjectflatbuffers::ComplexObject8FBS *>(VT_COMPLEXOBJECT);
  }
  complexobjectflatbuffers::ComplexObject8FBS *mutable_complexobject() {
    return GetPointer<complexobjectflatbuffers::ComplexObject8FBS *>(VT_COMPLEXOBJECT);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VAR_STRING) &&
           verifier.VerifyString(var_string()) &&
           VerifyOffset(verifier, VT_COMPLEXOBJECT) &&
           verifier.VerifyTable(complexobject()) &&
           verifier.EndTable();
  }
  ComplexObject7FBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ComplexObject7FBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<ComplexObject7FBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject7FBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ComplexObject7FBSBuilder {
  typedef ComplexObject7FBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_var_string(flatbuffers::Offset<flatbuffers::String> var_string) {
    fbb_.AddOffset(ComplexObject7FBS::VT_VAR_STRING, var_string);
  }
  void add_complexobject(flatbuffers::Offset<complexobjectflatbuffers::ComplexObject8FBS> complexobject) {
    fbb_.AddOffset(ComplexObject7FBS::VT_COMPLEXOBJECT, complexobject);
  }
  explicit ComplexObject7FBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<ComplexObject7FBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ComplexObject7FBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<ComplexObject7FBS> CreateComplexObject7FBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> var_string = 0,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject8FBS> complexobject = 0) {
  ComplexObject7FBSBuilder builder_(_fbb);
  builder_.add_complexobject(complexobject);
  builder_.add_var_string(var_string);
  return builder_.Finish();
}

inline flatbuffers::Offset<ComplexObject7FBS> CreateComplexObject7FBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *var_string = nullptr,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject8FBS> complexobject = 0) {
  auto var_string__ = var_string ? _fbb.CreateString(var_string) : 0;
  return complexobjectflatbuffers::CreateComplexObject7FBS(
      _fbb,
      var_string__,
      complexobject);
}

flatbuffers::Offset<ComplexObject7FBS> CreateComplexObject7FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject7FBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline ComplexObject7FBST::ComplexObject7FBST(const ComplexObject7FBST &o)
      : var_string(o.var_string),
        complexobject((o.complexobject) ? new complexobjectflatbuffers::ComplexObject8FBST(*o.complexobject) : nullptr) {
}

inline ComplexObject7FBST &ComplexObject7FBST::operator=(ComplexObject7FBST o) FLATBUFFERS_NOEXCEPT {
  std::swap(var_string, o.var_string);
  std::swap(complexobject, o.complexobject);
  return *this;
}

inline ComplexObject7FBST *ComplexObject7FBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<ComplexObject7FBST>(new ComplexObject7FBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void ComplexObject7FBS::UnPackTo(ComplexObject7FBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = var_string(); if (_e) _o->var_string = _e->str(); }
  { auto _e = complexobject(); if (_e) { if(_o->complexobject) { _e->UnPackTo(_o->complexobject.get(), _resolver); } else { _o->complexobject = std::unique_ptr<complexobjectflatbuffers::ComplexObject8FBST>(_e->UnPack(_resolver)); } } else if (_o->complexobject) { _o->complexobject.reset(); } }
}

inline flatbuffers::Offset<ComplexObject7FBS> ComplexObject7FBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject7FBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateComplexObject7FBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<ComplexObject7FBS> CreateComplexObject7FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject7FBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ComplexObject7FBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _var_string = _o->var_string.empty() ? 0 : _fbb.CreateString(_o->var_string);
  auto _complexobject = _o->complexobject ? CreateComplexObject8FBS(_fbb, _o->complexobject.get(), _rehasher) : 0;
  return complexobjectflatbuffers::CreateComplexObject7FBS(
      _fbb,
      _var_string,
      _complexobject);
}

inline const complexobjectflatbuffers::ComplexObject7FBS *GetComplexObject7FBS(const void *buf) {
  return flatbuffers::GetRoot<complexobjectflatbuffers::ComplexObject7FBS>(buf);
}

inline const complexobjectflatbuffers::ComplexObject7FBS *GetSizePrefixedComplexObject7FBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<complexobjectflatbuffers::ComplexObject7FBS>(buf);
}

inline ComplexObject7FBS *GetMutableComplexObject7FBS(void *buf) {
  return flatbuffers::GetMutableRoot<ComplexObject7FBS>(buf);
}

inline complexobjectflatbuffers::ComplexObject7FBS *GetMutableSizePrefixedComplexObject7FBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<complexobjectflatbuffers::ComplexObject7FBS>(buf);
}

inline bool VerifyComplexObject7FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<complexobjectflatbuffers::ComplexObject7FBS>(nullptr);
}

inline bool VerifySizePrefixedComplexObject7FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<complexobjectflatbuffers::ComplexObject7FBS>(nullptr);
}

inline void FinishComplexObject7FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject7FBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedComplexObject7FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject7FBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject7FBST> UnPackComplexObject7FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject7FBST>(GetComplexObject7FBS(buf)->UnPack(res));
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject7FBST> UnPackSizePrefixedComplexObject7FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject7FBST>(GetSizePrefixedComplexObject7FBS(buf)->UnPack(res));
}

}  // namespace complexobjectflatbuffers

#endif  // FLATBUFFERS_GENERATED_COMPLEXOBJECT7_COMPLEXOBJECTFLATBUFFERS_H_