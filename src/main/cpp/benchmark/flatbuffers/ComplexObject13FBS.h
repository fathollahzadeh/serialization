// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_COMPLEXOBJECT13_COMPLEXOBJECTFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_COMPLEXOBJECT13_COMPLEXOBJECTFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

#include "ComplexObject14FBS.h"

namespace complexobjectflatbuffers {

struct ComplexObject13FBS;
struct ComplexObject13FBSBuilder;
struct ComplexObject13FBST;

struct ComplexObject13FBST : public flatbuffers::NativeTable {
  typedef ComplexObject13FBS TableType;
  std::string var_string{};
  std::unique_ptr<complexobjectflatbuffers::ComplexObject14FBST> complexobject{};
  ComplexObject13FBST() = default;
  ComplexObject13FBST(const ComplexObject13FBST &o);
  ComplexObject13FBST(ComplexObject13FBST&&) FLATBUFFERS_NOEXCEPT = default;
  ComplexObject13FBST &operator=(ComplexObject13FBST o) FLATBUFFERS_NOEXCEPT;
};

struct ComplexObject13FBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ComplexObject13FBST NativeTableType;
  typedef ComplexObject13FBSBuilder Builder;
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
  const complexobjectflatbuffers::ComplexObject14FBS *complexobject() const {
    return GetPointer<const complexobjectflatbuffers::ComplexObject14FBS *>(VT_COMPLEXOBJECT);
  }
  complexobjectflatbuffers::ComplexObject14FBS *mutable_complexobject() {
    return GetPointer<complexobjectflatbuffers::ComplexObject14FBS *>(VT_COMPLEXOBJECT);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VAR_STRING) &&
           verifier.VerifyString(var_string()) &&
           VerifyOffset(verifier, VT_COMPLEXOBJECT) &&
           verifier.VerifyTable(complexobject()) &&
           verifier.EndTable();
  }
  ComplexObject13FBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ComplexObject13FBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<ComplexObject13FBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject13FBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ComplexObject13FBSBuilder {
  typedef ComplexObject13FBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_var_string(flatbuffers::Offset<flatbuffers::String> var_string) {
    fbb_.AddOffset(ComplexObject13FBS::VT_VAR_STRING, var_string);
  }
  void add_complexobject(flatbuffers::Offset<complexobjectflatbuffers::ComplexObject14FBS> complexobject) {
    fbb_.AddOffset(ComplexObject13FBS::VT_COMPLEXOBJECT, complexobject);
  }
  explicit ComplexObject13FBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<ComplexObject13FBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ComplexObject13FBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<ComplexObject13FBS> CreateComplexObject13FBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> var_string = 0,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject14FBS> complexobject = 0) {
  ComplexObject13FBSBuilder builder_(_fbb);
  builder_.add_complexobject(complexobject);
  builder_.add_var_string(var_string);
  return builder_.Finish();
}

inline flatbuffers::Offset<ComplexObject13FBS> CreateComplexObject13FBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *var_string = nullptr,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject14FBS> complexobject = 0) {
  auto var_string__ = var_string ? _fbb.CreateString(var_string) : 0;
  return complexobjectflatbuffers::CreateComplexObject13FBS(
      _fbb,
      var_string__,
      complexobject);
}

flatbuffers::Offset<ComplexObject13FBS> CreateComplexObject13FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject13FBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline ComplexObject13FBST::ComplexObject13FBST(const ComplexObject13FBST &o)
      : var_string(o.var_string),
        complexobject((o.complexobject) ? new complexobjectflatbuffers::ComplexObject14FBST(*o.complexobject) : nullptr) {
}

inline ComplexObject13FBST &ComplexObject13FBST::operator=(ComplexObject13FBST o) FLATBUFFERS_NOEXCEPT {
  std::swap(var_string, o.var_string);
  std::swap(complexobject, o.complexobject);
  return *this;
}

inline ComplexObject13FBST *ComplexObject13FBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<ComplexObject13FBST>(new ComplexObject13FBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void ComplexObject13FBS::UnPackTo(ComplexObject13FBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = var_string(); if (_e) _o->var_string = _e->str(); }
  { auto _e = complexobject(); if (_e) { if(_o->complexobject) { _e->UnPackTo(_o->complexobject.get(), _resolver); } else { _o->complexobject = std::unique_ptr<complexobjectflatbuffers::ComplexObject14FBST>(_e->UnPack(_resolver)); } } else if (_o->complexobject) { _o->complexobject.reset(); } }
}

inline flatbuffers::Offset<ComplexObject13FBS> ComplexObject13FBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject13FBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateComplexObject13FBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<ComplexObject13FBS> CreateComplexObject13FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject13FBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ComplexObject13FBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _var_string = _o->var_string.empty() ? 0 : _fbb.CreateString(_o->var_string);
  auto _complexobject = _o->complexobject ? CreateComplexObject14FBS(_fbb, _o->complexobject.get(), _rehasher) : 0;
  return complexobjectflatbuffers::CreateComplexObject13FBS(
      _fbb,
      _var_string,
      _complexobject);
}

inline const complexobjectflatbuffers::ComplexObject13FBS *GetComplexObject13FBS(const void *buf) {
  return flatbuffers::GetRoot<complexobjectflatbuffers::ComplexObject13FBS>(buf);
}

inline const complexobjectflatbuffers::ComplexObject13FBS *GetSizePrefixedComplexObject13FBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<complexobjectflatbuffers::ComplexObject13FBS>(buf);
}

inline ComplexObject13FBS *GetMutableComplexObject13FBS(void *buf) {
  return flatbuffers::GetMutableRoot<ComplexObject13FBS>(buf);
}

inline complexobjectflatbuffers::ComplexObject13FBS *GetMutableSizePrefixedComplexObject13FBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<complexobjectflatbuffers::ComplexObject13FBS>(buf);
}

inline bool VerifyComplexObject13FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<complexobjectflatbuffers::ComplexObject13FBS>(nullptr);
}

inline bool VerifySizePrefixedComplexObject13FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<complexobjectflatbuffers::ComplexObject13FBS>(nullptr);
}

inline void FinishComplexObject13FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject13FBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedComplexObject13FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject13FBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject13FBST> UnPackComplexObject13FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject13FBST>(GetComplexObject13FBS(buf)->UnPack(res));
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject13FBST> UnPackSizePrefixedComplexObject13FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject13FBST>(GetSizePrefixedComplexObject13FBS(buf)->UnPack(res));
}

}  // namespace complexobjectflatbuffers

#endif  // FLATBUFFERS_GENERATED_COMPLEXOBJECT13_COMPLEXOBJECTFLATBUFFERS_H_
