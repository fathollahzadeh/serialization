// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_COMPLEXOBJECT11_COMPLEXOBJECTFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_COMPLEXOBJECT11_COMPLEXOBJECTFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

#include "ComplexObject12FBS.h"

namespace complexobjectflatbuffers {

struct ComplexObject11FBS;
struct ComplexObject11FBSBuilder;
struct ComplexObject11FBST;

struct ComplexObject11FBST : public flatbuffers::NativeTable {
  typedef ComplexObject11FBS TableType;
  std::string var_string{};
  std::unique_ptr<complexobjectflatbuffers::ComplexObject12FBST> complexobject{};
  ComplexObject11FBST() = default;
  ComplexObject11FBST(const ComplexObject11FBST &o);
  ComplexObject11FBST(ComplexObject11FBST&&) FLATBUFFERS_NOEXCEPT = default;
  ComplexObject11FBST &operator=(ComplexObject11FBST o) FLATBUFFERS_NOEXCEPT;
};

struct ComplexObject11FBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ComplexObject11FBST NativeTableType;
  typedef ComplexObject11FBSBuilder Builder;
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
  const complexobjectflatbuffers::ComplexObject12FBS *complexobject() const {
    return GetPointer<const complexobjectflatbuffers::ComplexObject12FBS *>(VT_COMPLEXOBJECT);
  }
  complexobjectflatbuffers::ComplexObject12FBS *mutable_complexobject() {
    return GetPointer<complexobjectflatbuffers::ComplexObject12FBS *>(VT_COMPLEXOBJECT);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VAR_STRING) &&
           verifier.VerifyString(var_string()) &&
           VerifyOffset(verifier, VT_COMPLEXOBJECT) &&
           verifier.VerifyTable(complexobject()) &&
           verifier.EndTable();
  }
  ComplexObject11FBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ComplexObject11FBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<ComplexObject11FBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject11FBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ComplexObject11FBSBuilder {
  typedef ComplexObject11FBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_var_string(flatbuffers::Offset<flatbuffers::String> var_string) {
    fbb_.AddOffset(ComplexObject11FBS::VT_VAR_STRING, var_string);
  }
  void add_complexobject(flatbuffers::Offset<complexobjectflatbuffers::ComplexObject12FBS> complexobject) {
    fbb_.AddOffset(ComplexObject11FBS::VT_COMPLEXOBJECT, complexobject);
  }
  explicit ComplexObject11FBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<ComplexObject11FBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ComplexObject11FBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<ComplexObject11FBS> CreateComplexObject11FBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> var_string = 0,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject12FBS> complexobject = 0) {
  ComplexObject11FBSBuilder builder_(_fbb);
  builder_.add_complexobject(complexobject);
  builder_.add_var_string(var_string);
  return builder_.Finish();
}

inline flatbuffers::Offset<ComplexObject11FBS> CreateComplexObject11FBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *var_string = nullptr,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject12FBS> complexobject = 0) {
  auto var_string__ = var_string ? _fbb.CreateString(var_string) : 0;
  return complexobjectflatbuffers::CreateComplexObject11FBS(
      _fbb,
      var_string__,
      complexobject);
}

flatbuffers::Offset<ComplexObject11FBS> CreateComplexObject11FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject11FBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline ComplexObject11FBST::ComplexObject11FBST(const ComplexObject11FBST &o)
      : var_string(o.var_string),
        complexobject((o.complexobject) ? new complexobjectflatbuffers::ComplexObject12FBST(*o.complexobject) : nullptr) {
}

inline ComplexObject11FBST &ComplexObject11FBST::operator=(ComplexObject11FBST o) FLATBUFFERS_NOEXCEPT {
  std::swap(var_string, o.var_string);
  std::swap(complexobject, o.complexobject);
  return *this;
}

inline ComplexObject11FBST *ComplexObject11FBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<ComplexObject11FBST>(new ComplexObject11FBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void ComplexObject11FBS::UnPackTo(ComplexObject11FBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = var_string(); if (_e) _o->var_string = _e->str(); }
  { auto _e = complexobject(); if (_e) { if(_o->complexobject) { _e->UnPackTo(_o->complexobject.get(), _resolver); } else { _o->complexobject = std::unique_ptr<complexobjectflatbuffers::ComplexObject12FBST>(_e->UnPack(_resolver)); } } else if (_o->complexobject) { _o->complexobject.reset(); } }
}

inline flatbuffers::Offset<ComplexObject11FBS> ComplexObject11FBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject11FBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateComplexObject11FBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<ComplexObject11FBS> CreateComplexObject11FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject11FBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ComplexObject11FBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _var_string = _o->var_string.empty() ? 0 : _fbb.CreateString(_o->var_string);
  auto _complexobject = _o->complexobject ? CreateComplexObject12FBS(_fbb, _o->complexobject.get(), _rehasher) : 0;
  return complexobjectflatbuffers::CreateComplexObject11FBS(
      _fbb,
      _var_string,
      _complexobject);
}

inline const complexobjectflatbuffers::ComplexObject11FBS *GetComplexObject11FBS(const void *buf) {
  return flatbuffers::GetRoot<complexobjectflatbuffers::ComplexObject11FBS>(buf);
}

inline const complexobjectflatbuffers::ComplexObject11FBS *GetSizePrefixedComplexObject11FBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<complexobjectflatbuffers::ComplexObject11FBS>(buf);
}

inline ComplexObject11FBS *GetMutableComplexObject11FBS(void *buf) {
  return flatbuffers::GetMutableRoot<ComplexObject11FBS>(buf);
}

inline complexobjectflatbuffers::ComplexObject11FBS *GetMutableSizePrefixedComplexObject11FBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<complexobjectflatbuffers::ComplexObject11FBS>(buf);
}

inline bool VerifyComplexObject11FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<complexobjectflatbuffers::ComplexObject11FBS>(nullptr);
}

inline bool VerifySizePrefixedComplexObject11FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<complexobjectflatbuffers::ComplexObject11FBS>(nullptr);
}

inline void FinishComplexObject11FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject11FBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedComplexObject11FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject11FBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject11FBST> UnPackComplexObject11FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject11FBST>(GetComplexObject11FBS(buf)->UnPack(res));
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject11FBST> UnPackSizePrefixedComplexObject11FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject11FBST>(GetSizePrefixedComplexObject11FBS(buf)->UnPack(res));
}

}  // namespace complexobjectflatbuffers

#endif  // FLATBUFFERS_GENERATED_COMPLEXOBJECT11_COMPLEXOBJECTFLATBUFFERS_H_
