// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_COMPLEXOBJECT2_COMPLEXOBJECTFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_COMPLEXOBJECT2_COMPLEXOBJECTFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

#include "ComplexObject3FBS.h"

namespace complexobjectflatbuffers {

struct ComplexObject2FBS;
struct ComplexObject2FBSBuilder;
struct ComplexObject2FBST;

struct ComplexObject2FBST : public flatbuffers::NativeTable {
  typedef ComplexObject2FBS TableType;
  std::string var_string{};
  std::unique_ptr<complexobjectflatbuffers::ComplexObject3FBST> complexobject{};
  ComplexObject2FBST() = default;
  ComplexObject2FBST(const ComplexObject2FBST &o);
  ComplexObject2FBST(ComplexObject2FBST&&) FLATBUFFERS_NOEXCEPT = default;
  ComplexObject2FBST &operator=(ComplexObject2FBST o) FLATBUFFERS_NOEXCEPT;
};

struct ComplexObject2FBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ComplexObject2FBST NativeTableType;
  typedef ComplexObject2FBSBuilder Builder;
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
  const complexobjectflatbuffers::ComplexObject3FBS *complexobject() const {
    return GetPointer<const complexobjectflatbuffers::ComplexObject3FBS *>(VT_COMPLEXOBJECT);
  }
  complexobjectflatbuffers::ComplexObject3FBS *mutable_complexobject() {
    return GetPointer<complexobjectflatbuffers::ComplexObject3FBS *>(VT_COMPLEXOBJECT);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VAR_STRING) &&
           verifier.VerifyString(var_string()) &&
           VerifyOffset(verifier, VT_COMPLEXOBJECT) &&
           verifier.VerifyTable(complexobject()) &&
           verifier.EndTable();
  }
  ComplexObject2FBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ComplexObject2FBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<ComplexObject2FBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject2FBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ComplexObject2FBSBuilder {
  typedef ComplexObject2FBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_var_string(flatbuffers::Offset<flatbuffers::String> var_string) {
    fbb_.AddOffset(ComplexObject2FBS::VT_VAR_STRING, var_string);
  }
  void add_complexobject(flatbuffers::Offset<complexobjectflatbuffers::ComplexObject3FBS> complexobject) {
    fbb_.AddOffset(ComplexObject2FBS::VT_COMPLEXOBJECT, complexobject);
  }
  explicit ComplexObject2FBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<ComplexObject2FBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ComplexObject2FBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<ComplexObject2FBS> CreateComplexObject2FBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> var_string = 0,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject3FBS> complexobject = 0) {
  ComplexObject2FBSBuilder builder_(_fbb);
  builder_.add_complexobject(complexobject);
  builder_.add_var_string(var_string);
  return builder_.Finish();
}

inline flatbuffers::Offset<ComplexObject2FBS> CreateComplexObject2FBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *var_string = nullptr,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject3FBS> complexobject = 0) {
  auto var_string__ = var_string ? _fbb.CreateString(var_string) : 0;
  return complexobjectflatbuffers::CreateComplexObject2FBS(
      _fbb,
      var_string__,
      complexobject);
}

flatbuffers::Offset<ComplexObject2FBS> CreateComplexObject2FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject2FBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline ComplexObject2FBST::ComplexObject2FBST(const ComplexObject2FBST &o)
      : var_string(o.var_string),
        complexobject((o.complexobject) ? new complexobjectflatbuffers::ComplexObject3FBST(*o.complexobject) : nullptr) {
}

inline ComplexObject2FBST &ComplexObject2FBST::operator=(ComplexObject2FBST o) FLATBUFFERS_NOEXCEPT {
  std::swap(var_string, o.var_string);
  std::swap(complexobject, o.complexobject);
  return *this;
}

inline ComplexObject2FBST *ComplexObject2FBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<ComplexObject2FBST>(new ComplexObject2FBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void ComplexObject2FBS::UnPackTo(ComplexObject2FBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = var_string(); if (_e) _o->var_string = _e->str(); }
  { auto _e = complexobject(); if (_e) { if(_o->complexobject) { _e->UnPackTo(_o->complexobject.get(), _resolver); } else { _o->complexobject = std::unique_ptr<complexobjectflatbuffers::ComplexObject3FBST>(_e->UnPack(_resolver)); } } else if (_o->complexobject) { _o->complexobject.reset(); } }
}

inline flatbuffers::Offset<ComplexObject2FBS> ComplexObject2FBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject2FBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateComplexObject2FBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<ComplexObject2FBS> CreateComplexObject2FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject2FBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ComplexObject2FBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _var_string = _o->var_string.empty() ? 0 : _fbb.CreateString(_o->var_string);
  auto _complexobject = _o->complexobject ? CreateComplexObject3FBS(_fbb, _o->complexobject.get(), _rehasher) : 0;
  return complexobjectflatbuffers::CreateComplexObject2FBS(
      _fbb,
      _var_string,
      _complexobject);
}

inline const complexobjectflatbuffers::ComplexObject2FBS *GetComplexObject2FBS(const void *buf) {
  return flatbuffers::GetRoot<complexobjectflatbuffers::ComplexObject2FBS>(buf);
}

inline const complexobjectflatbuffers::ComplexObject2FBS *GetSizePrefixedComplexObject2FBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<complexobjectflatbuffers::ComplexObject2FBS>(buf);
}

inline ComplexObject2FBS *GetMutableComplexObject2FBS(void *buf) {
  return flatbuffers::GetMutableRoot<ComplexObject2FBS>(buf);
}

inline complexobjectflatbuffers::ComplexObject2FBS *GetMutableSizePrefixedComplexObject2FBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<complexobjectflatbuffers::ComplexObject2FBS>(buf);
}

inline bool VerifyComplexObject2FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<complexobjectflatbuffers::ComplexObject2FBS>(nullptr);
}

inline bool VerifySizePrefixedComplexObject2FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<complexobjectflatbuffers::ComplexObject2FBS>(nullptr);
}

inline void FinishComplexObject2FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject2FBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedComplexObject2FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject2FBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject2FBST> UnPackComplexObject2FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject2FBST>(GetComplexObject2FBS(buf)->UnPack(res));
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject2FBST> UnPackSizePrefixedComplexObject2FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject2FBST>(GetSizePrefixedComplexObject2FBS(buf)->UnPack(res));
}

}  // namespace complexobjectflatbuffers

#endif  // FLATBUFFERS_GENERATED_COMPLEXOBJECT2_COMPLEXOBJECTFLATBUFFERS_H_