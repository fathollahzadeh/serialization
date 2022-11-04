// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_COMPLEXOBJECT1_COMPLEXOBJECTFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_COMPLEXOBJECT1_COMPLEXOBJECTFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

#include "ComplexObject2FBS.h"

namespace complexobjectflatbuffers {

struct ComplexObject1FBS;
struct ComplexObject1FBSBuilder;
struct ComplexObject1FBST;

struct ComplexObject1FBST : public flatbuffers::NativeTable {
  typedef ComplexObject1FBS TableType;
  std::string var_string{};
  std::unique_ptr<complexobjectflatbuffers::ComplexObject2FBST> complexobject{};
  ComplexObject1FBST() = default;
  ComplexObject1FBST(const ComplexObject1FBST &o);
  ComplexObject1FBST(ComplexObject1FBST&&) FLATBUFFERS_NOEXCEPT = default;
  ComplexObject1FBST &operator=(ComplexObject1FBST o) FLATBUFFERS_NOEXCEPT;
};

struct ComplexObject1FBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ComplexObject1FBST NativeTableType;
  typedef ComplexObject1FBSBuilder Builder;
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
  const complexobjectflatbuffers::ComplexObject2FBS *complexobject() const {
    return GetPointer<const complexobjectflatbuffers::ComplexObject2FBS *>(VT_COMPLEXOBJECT);
  }
  complexobjectflatbuffers::ComplexObject2FBS *mutable_complexobject() {
    return GetPointer<complexobjectflatbuffers::ComplexObject2FBS *>(VT_COMPLEXOBJECT);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VAR_STRING) &&
           verifier.VerifyString(var_string()) &&
           VerifyOffset(verifier, VT_COMPLEXOBJECT) &&
           verifier.VerifyTable(complexobject()) &&
           verifier.EndTable();
  }
  ComplexObject1FBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ComplexObject1FBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<ComplexObject1FBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject1FBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ComplexObject1FBSBuilder {
  typedef ComplexObject1FBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_var_string(flatbuffers::Offset<flatbuffers::String> var_string) {
    fbb_.AddOffset(ComplexObject1FBS::VT_VAR_STRING, var_string);
  }
  void add_complexobject(flatbuffers::Offset<complexobjectflatbuffers::ComplexObject2FBS> complexobject) {
    fbb_.AddOffset(ComplexObject1FBS::VT_COMPLEXOBJECT, complexobject);
  }
  explicit ComplexObject1FBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<ComplexObject1FBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ComplexObject1FBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<ComplexObject1FBS> CreateComplexObject1FBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> var_string = 0,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject2FBS> complexobject = 0) {
  ComplexObject1FBSBuilder builder_(_fbb);
  builder_.add_complexobject(complexobject);
  builder_.add_var_string(var_string);
  return builder_.Finish();
}

inline flatbuffers::Offset<ComplexObject1FBS> CreateComplexObject1FBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *var_string = nullptr,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject2FBS> complexobject = 0) {
  auto var_string__ = var_string ? _fbb.CreateString(var_string) : 0;
  return complexobjectflatbuffers::CreateComplexObject1FBS(
      _fbb,
      var_string__,
      complexobject);
}

flatbuffers::Offset<ComplexObject1FBS> CreateComplexObject1FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject1FBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline ComplexObject1FBST::ComplexObject1FBST(const ComplexObject1FBST &o)
      : var_string(o.var_string),
        complexobject((o.complexobject) ? new complexobjectflatbuffers::ComplexObject2FBST(*o.complexobject) : nullptr) {
}

inline ComplexObject1FBST &ComplexObject1FBST::operator=(ComplexObject1FBST o) FLATBUFFERS_NOEXCEPT {
  std::swap(var_string, o.var_string);
  std::swap(complexobject, o.complexobject);
  return *this;
}

inline ComplexObject1FBST *ComplexObject1FBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<ComplexObject1FBST>(new ComplexObject1FBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void ComplexObject1FBS::UnPackTo(ComplexObject1FBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = var_string(); if (_e) _o->var_string = _e->str(); }
  { auto _e = complexobject(); if (_e) { if(_o->complexobject) { _e->UnPackTo(_o->complexobject.get(), _resolver); } else { _o->complexobject = std::unique_ptr<complexobjectflatbuffers::ComplexObject2FBST>(_e->UnPack(_resolver)); } } else if (_o->complexobject) { _o->complexobject.reset(); } }
}

inline flatbuffers::Offset<ComplexObject1FBS> ComplexObject1FBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject1FBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateComplexObject1FBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<ComplexObject1FBS> CreateComplexObject1FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject1FBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ComplexObject1FBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _var_string = _o->var_string.empty() ? 0 : _fbb.CreateString(_o->var_string);
  auto _complexobject = _o->complexobject ? CreateComplexObject2FBS(_fbb, _o->complexobject.get(), _rehasher) : 0;
  return complexobjectflatbuffers::CreateComplexObject1FBS(
      _fbb,
      _var_string,
      _complexobject);
}

inline const complexobjectflatbuffers::ComplexObject1FBS *GetComplexObject1FBS(const void *buf) {
  return flatbuffers::GetRoot<complexobjectflatbuffers::ComplexObject1FBS>(buf);
}

inline const complexobjectflatbuffers::ComplexObject1FBS *GetSizePrefixedComplexObject1FBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<complexobjectflatbuffers::ComplexObject1FBS>(buf);
}

inline ComplexObject1FBS *GetMutableComplexObject1FBS(void *buf) {
  return flatbuffers::GetMutableRoot<ComplexObject1FBS>(buf);
}

inline complexobjectflatbuffers::ComplexObject1FBS *GetMutableSizePrefixedComplexObject1FBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<complexobjectflatbuffers::ComplexObject1FBS>(buf);
}

inline bool VerifyComplexObject1FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<complexobjectflatbuffers::ComplexObject1FBS>(nullptr);
}

inline bool VerifySizePrefixedComplexObject1FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<complexobjectflatbuffers::ComplexObject1FBS>(nullptr);
}

inline void FinishComplexObject1FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject1FBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedComplexObject1FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject1FBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject1FBST> UnPackComplexObject1FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject1FBST>(GetComplexObject1FBS(buf)->UnPack(res));
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject1FBST> UnPackSizePrefixedComplexObject1FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject1FBST>(GetSizePrefixedComplexObject1FBS(buf)->UnPack(res));
}

}  // namespace complexobjectflatbuffers

#endif  // FLATBUFFERS_GENERATED_COMPLEXOBJECT1_COMPLEXOBJECTFLATBUFFERS_H_
