// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_COMPLEXOBJECT4_COMPLEXOBJECTFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_COMPLEXOBJECT4_COMPLEXOBJECTFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

#include "ComplexObject5FBS.h"

namespace complexobjectflatbuffers {

struct ComplexObject4FBS;
struct ComplexObject4FBSBuilder;
struct ComplexObject4FBST;

struct ComplexObject4FBST : public flatbuffers::NativeTable {
  typedef ComplexObject4FBS TableType;
  std::string var_string{};
  std::unique_ptr<complexobjectflatbuffers::ComplexObject5FBST> complexobject{};
  ComplexObject4FBST() = default;
  ComplexObject4FBST(const ComplexObject4FBST &o);
  ComplexObject4FBST(ComplexObject4FBST&&) FLATBUFFERS_NOEXCEPT = default;
  ComplexObject4FBST &operator=(ComplexObject4FBST o) FLATBUFFERS_NOEXCEPT;
};

struct ComplexObject4FBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ComplexObject4FBST NativeTableType;
  typedef ComplexObject4FBSBuilder Builder;
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
  const complexobjectflatbuffers::ComplexObject5FBS *complexobject() const {
    return GetPointer<const complexobjectflatbuffers::ComplexObject5FBS *>(VT_COMPLEXOBJECT);
  }
  complexobjectflatbuffers::ComplexObject5FBS *mutable_complexobject() {
    return GetPointer<complexobjectflatbuffers::ComplexObject5FBS *>(VT_COMPLEXOBJECT);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VAR_STRING) &&
           verifier.VerifyString(var_string()) &&
           VerifyOffset(verifier, VT_COMPLEXOBJECT) &&
           verifier.VerifyTable(complexobject()) &&
           verifier.EndTable();
  }
  ComplexObject4FBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ComplexObject4FBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<ComplexObject4FBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject4FBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ComplexObject4FBSBuilder {
  typedef ComplexObject4FBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_var_string(flatbuffers::Offset<flatbuffers::String> var_string) {
    fbb_.AddOffset(ComplexObject4FBS::VT_VAR_STRING, var_string);
  }
  void add_complexobject(flatbuffers::Offset<complexobjectflatbuffers::ComplexObject5FBS> complexobject) {
    fbb_.AddOffset(ComplexObject4FBS::VT_COMPLEXOBJECT, complexobject);
  }
  explicit ComplexObject4FBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<ComplexObject4FBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ComplexObject4FBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<ComplexObject4FBS> CreateComplexObject4FBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> var_string = 0,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject5FBS> complexobject = 0) {
  ComplexObject4FBSBuilder builder_(_fbb);
  builder_.add_complexobject(complexobject);
  builder_.add_var_string(var_string);
  return builder_.Finish();
}

inline flatbuffers::Offset<ComplexObject4FBS> CreateComplexObject4FBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *var_string = nullptr,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject5FBS> complexobject = 0) {
  auto var_string__ = var_string ? _fbb.CreateString(var_string) : 0;
  return complexobjectflatbuffers::CreateComplexObject4FBS(
      _fbb,
      var_string__,
      complexobject);
}

flatbuffers::Offset<ComplexObject4FBS> CreateComplexObject4FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject4FBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline ComplexObject4FBST::ComplexObject4FBST(const ComplexObject4FBST &o)
      : var_string(o.var_string),
        complexobject((o.complexobject) ? new complexobjectflatbuffers::ComplexObject5FBST(*o.complexobject) : nullptr) {
}

inline ComplexObject4FBST &ComplexObject4FBST::operator=(ComplexObject4FBST o) FLATBUFFERS_NOEXCEPT {
  std::swap(var_string, o.var_string);
  std::swap(complexobject, o.complexobject);
  return *this;
}

inline ComplexObject4FBST *ComplexObject4FBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<ComplexObject4FBST>(new ComplexObject4FBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void ComplexObject4FBS::UnPackTo(ComplexObject4FBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = var_string(); if (_e) _o->var_string = _e->str(); }
  { auto _e = complexobject(); if (_e) { if(_o->complexobject) { _e->UnPackTo(_o->complexobject.get(), _resolver); } else { _o->complexobject = std::unique_ptr<complexobjectflatbuffers::ComplexObject5FBST>(_e->UnPack(_resolver)); } } else if (_o->complexobject) { _o->complexobject.reset(); } }
}

inline flatbuffers::Offset<ComplexObject4FBS> ComplexObject4FBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject4FBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateComplexObject4FBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<ComplexObject4FBS> CreateComplexObject4FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject4FBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ComplexObject4FBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _var_string = _o->var_string.empty() ? 0 : _fbb.CreateString(_o->var_string);
  auto _complexobject = _o->complexobject ? CreateComplexObject5FBS(_fbb, _o->complexobject.get(), _rehasher) : 0;
  return complexobjectflatbuffers::CreateComplexObject4FBS(
      _fbb,
      _var_string,
      _complexobject);
}

inline const complexobjectflatbuffers::ComplexObject4FBS *GetComplexObject4FBS(const void *buf) {
  return flatbuffers::GetRoot<complexobjectflatbuffers::ComplexObject4FBS>(buf);
}

inline const complexobjectflatbuffers::ComplexObject4FBS *GetSizePrefixedComplexObject4FBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<complexobjectflatbuffers::ComplexObject4FBS>(buf);
}

inline ComplexObject4FBS *GetMutableComplexObject4FBS(void *buf) {
  return flatbuffers::GetMutableRoot<ComplexObject4FBS>(buf);
}

inline complexobjectflatbuffers::ComplexObject4FBS *GetMutableSizePrefixedComplexObject4FBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<complexobjectflatbuffers::ComplexObject4FBS>(buf);
}

inline bool VerifyComplexObject4FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<complexobjectflatbuffers::ComplexObject4FBS>(nullptr);
}

inline bool VerifySizePrefixedComplexObject4FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<complexobjectflatbuffers::ComplexObject4FBS>(nullptr);
}

inline void FinishComplexObject4FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject4FBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedComplexObject4FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject4FBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject4FBST> UnPackComplexObject4FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject4FBST>(GetComplexObject4FBS(buf)->UnPack(res));
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject4FBST> UnPackSizePrefixedComplexObject4FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject4FBST>(GetSizePrefixedComplexObject4FBS(buf)->UnPack(res));
}

}  // namespace complexobjectflatbuffers

#endif  // FLATBUFFERS_GENERATED_COMPLEXOBJECT4_COMPLEXOBJECTFLATBUFFERS_H_
