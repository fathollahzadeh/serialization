// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_COMPLEXOBJECT15_COMPLEXOBJECTFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_COMPLEXOBJECT15_COMPLEXOBJECTFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

#include "SimpleObjectFBS.h"

namespace complexobjectflatbuffers {

struct ComplexObject15FBS;
struct ComplexObject15FBSBuilder;
struct ComplexObject15FBST;

struct ComplexObject15FBST : public flatbuffers::NativeTable {
  typedef ComplexObject15FBS TableType;
  std::string var_string{};
  std::unique_ptr<complexobjectflatbuffers::SimpleObjectFBST> complexobject{};
  ComplexObject15FBST() = default;
  ComplexObject15FBST(const ComplexObject15FBST &o);
  ComplexObject15FBST(ComplexObject15FBST&&) FLATBUFFERS_NOEXCEPT = default;
  ComplexObject15FBST &operator=(ComplexObject15FBST o) FLATBUFFERS_NOEXCEPT;
};

struct ComplexObject15FBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ComplexObject15FBST NativeTableType;
  typedef ComplexObject15FBSBuilder Builder;
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
  const complexobjectflatbuffers::SimpleObjectFBS *complexobject() const {
    return GetPointer<const complexobjectflatbuffers::SimpleObjectFBS *>(VT_COMPLEXOBJECT);
  }
  complexobjectflatbuffers::SimpleObjectFBS *mutable_complexobject() {
    return GetPointer<complexobjectflatbuffers::SimpleObjectFBS *>(VT_COMPLEXOBJECT);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VAR_STRING) &&
           verifier.VerifyString(var_string()) &&
           VerifyOffset(verifier, VT_COMPLEXOBJECT) &&
           verifier.VerifyTable(complexobject()) &&
           verifier.EndTable();
  }
  ComplexObject15FBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ComplexObject15FBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<ComplexObject15FBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject15FBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ComplexObject15FBSBuilder {
  typedef ComplexObject15FBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_var_string(flatbuffers::Offset<flatbuffers::String> var_string) {
    fbb_.AddOffset(ComplexObject15FBS::VT_VAR_STRING, var_string);
  }
  void add_complexobject(flatbuffers::Offset<complexobjectflatbuffers::SimpleObjectFBS> complexobject) {
    fbb_.AddOffset(ComplexObject15FBS::VT_COMPLEXOBJECT, complexobject);
  }
  explicit ComplexObject15FBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<ComplexObject15FBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ComplexObject15FBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<ComplexObject15FBS> CreateComplexObject15FBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> var_string = 0,
    flatbuffers::Offset<complexobjectflatbuffers::SimpleObjectFBS> complexobject = 0) {
  ComplexObject15FBSBuilder builder_(_fbb);
  builder_.add_complexobject(complexobject);
  builder_.add_var_string(var_string);
  return builder_.Finish();
}

inline flatbuffers::Offset<ComplexObject15FBS> CreateComplexObject15FBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *var_string = nullptr,
    flatbuffers::Offset<complexobjectflatbuffers::SimpleObjectFBS> complexobject = 0) {
  auto var_string__ = var_string ? _fbb.CreateString(var_string) : 0;
  return complexobjectflatbuffers::CreateComplexObject15FBS(
      _fbb,
      var_string__,
      complexobject);
}

flatbuffers::Offset<ComplexObject15FBS> CreateComplexObject15FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject15FBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline ComplexObject15FBST::ComplexObject15FBST(const ComplexObject15FBST &o)
      : var_string(o.var_string),
        complexobject((o.complexobject) ? new complexobjectflatbuffers::SimpleObjectFBST(*o.complexobject) : nullptr) {
}

inline ComplexObject15FBST &ComplexObject15FBST::operator=(ComplexObject15FBST o) FLATBUFFERS_NOEXCEPT {
  std::swap(var_string, o.var_string);
  std::swap(complexobject, o.complexobject);
  return *this;
}

inline ComplexObject15FBST *ComplexObject15FBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<ComplexObject15FBST>(new ComplexObject15FBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void ComplexObject15FBS::UnPackTo(ComplexObject15FBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = var_string(); if (_e) _o->var_string = _e->str(); }
  { auto _e = complexobject(); if (_e) { if(_o->complexobject) { _e->UnPackTo(_o->complexobject.get(), _resolver); } else { _o->complexobject = std::unique_ptr<complexobjectflatbuffers::SimpleObjectFBST>(_e->UnPack(_resolver)); } } else if (_o->complexobject) { _o->complexobject.reset(); } }
}

inline flatbuffers::Offset<ComplexObject15FBS> ComplexObject15FBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject15FBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateComplexObject15FBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<ComplexObject15FBS> CreateComplexObject15FBS(flatbuffers::FlatBufferBuilder &_fbb, const ComplexObject15FBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ComplexObject15FBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _var_string = _o->var_string.empty() ? 0 : _fbb.CreateString(_o->var_string);
  auto _complexobject = _o->complexobject ? CreateSimpleObjectFBS(_fbb, _o->complexobject.get(), _rehasher) : 0;
  return complexobjectflatbuffers::CreateComplexObject15FBS(
      _fbb,
      _var_string,
      _complexobject);
}

inline const complexobjectflatbuffers::ComplexObject15FBS *GetComplexObject15FBS(const void *buf) {
  return flatbuffers::GetRoot<complexobjectflatbuffers::ComplexObject15FBS>(buf);
}

inline const complexobjectflatbuffers::ComplexObject15FBS *GetSizePrefixedComplexObject15FBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<complexobjectflatbuffers::ComplexObject15FBS>(buf);
}

inline ComplexObject15FBS *GetMutableComplexObject15FBS(void *buf) {
  return flatbuffers::GetMutableRoot<ComplexObject15FBS>(buf);
}

inline complexobjectflatbuffers::ComplexObject15FBS *GetMutableSizePrefixedComplexObject15FBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<complexobjectflatbuffers::ComplexObject15FBS>(buf);
}

inline bool VerifyComplexObject15FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<complexobjectflatbuffers::ComplexObject15FBS>(nullptr);
}

inline bool VerifySizePrefixedComplexObject15FBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<complexobjectflatbuffers::ComplexObject15FBS>(nullptr);
}

inline void FinishComplexObject15FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject15FBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedComplexObject15FBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<complexobjectflatbuffers::ComplexObject15FBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject15FBST> UnPackComplexObject15FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject15FBST>(GetComplexObject15FBS(buf)->UnPack(res));
}

inline std::unique_ptr<complexobjectflatbuffers::ComplexObject15FBST> UnPackSizePrefixedComplexObject15FBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<complexobjectflatbuffers::ComplexObject15FBST>(GetSizePrefixedComplexObject15FBS(buf)->UnPack(res));
}

}  // namespace complexobjectflatbuffers

#endif  // FLATBUFFERS_GENERATED_COMPLEXOBJECT15_COMPLEXOBJECTFLATBUFFERS_H_
