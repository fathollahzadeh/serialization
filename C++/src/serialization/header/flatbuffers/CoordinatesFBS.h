// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_COORDINATES_TWEETSTATUSFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_COORDINATES_TWEETSTATUSFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

namespace tweetstatusflatbuffers {

struct CoordinatesFBS;
struct CoordinatesFBSBuilder;
struct CoordinatesFBST;

struct CoordinatesFBST : public flatbuffers::NativeTable {
  typedef CoordinatesFBS TableType;
  std::string type;
  std::vector<double> coordinates;
  CoordinatesFBST() {
  }
};

struct CoordinatesFBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef CoordinatesFBST NativeTableType;
  typedef CoordinatesFBSBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TYPE = 4,
    VT_COORDINATES = 6
  };
  const flatbuffers::String *type() const {
    return GetPointer<const flatbuffers::String *>(VT_TYPE);
  }
  flatbuffers::String *mutable_type() {
    return GetPointer<flatbuffers::String *>(VT_TYPE);
  }
  const flatbuffers::Vector<double> *coordinates() const {
    return GetPointer<const flatbuffers::Vector<double> *>(VT_COORDINATES);
  }
  flatbuffers::Vector<double> *mutable_coordinates() {
    return GetPointer<flatbuffers::Vector<double> *>(VT_COORDINATES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_TYPE) &&
           verifier.VerifyString(type()) &&
           VerifyOffset(verifier, VT_COORDINATES) &&
           verifier.VerifyVector(coordinates()) &&
           verifier.EndTable();
  }
  CoordinatesFBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(CoordinatesFBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<CoordinatesFBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const CoordinatesFBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct CoordinatesFBSBuilder {
  typedef CoordinatesFBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(flatbuffers::Offset<flatbuffers::String> type) {
    fbb_.AddOffset(CoordinatesFBS::VT_TYPE, type);
  }
  void add_coordinates(flatbuffers::Offset<flatbuffers::Vector<double>> coordinates) {
    fbb_.AddOffset(CoordinatesFBS::VT_COORDINATES, coordinates);
  }
  explicit CoordinatesFBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<CoordinatesFBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<CoordinatesFBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<CoordinatesFBS> CreateCoordinatesFBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> type = 0,
    flatbuffers::Offset<flatbuffers::Vector<double>> coordinates = 0) {
  CoordinatesFBSBuilder builder_(_fbb);
  builder_.add_coordinates(coordinates);
  builder_.add_type(type);
  return builder_.Finish();
}

inline flatbuffers::Offset<CoordinatesFBS> CreateCoordinatesFBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *type = nullptr,
    const std::vector<double> *coordinates = nullptr) {
  auto type__ = type ? _fbb.CreateString(type) : 0;
  auto coordinates__ = coordinates ? _fbb.CreateVector<double>(*coordinates) : 0;
  return tweetstatusflatbuffers::CreateCoordinatesFBS(
      _fbb,
      type__,
      coordinates__);
}

flatbuffers::Offset<CoordinatesFBS> CreateCoordinatesFBS(flatbuffers::FlatBufferBuilder &_fbb, const CoordinatesFBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline CoordinatesFBST *CoordinatesFBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  std::unique_ptr<tweetstatusflatbuffers::CoordinatesFBST> _o = std::unique_ptr<tweetstatusflatbuffers::CoordinatesFBST>(new CoordinatesFBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void CoordinatesFBS::UnPackTo(CoordinatesFBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = type(); if (_e) _o->type = _e->str(); }
  { auto _e = coordinates(); if (_e) { _o->coordinates.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->coordinates[_i] = _e->Get(_i); } } }
}

inline flatbuffers::Offset<CoordinatesFBS> CoordinatesFBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const CoordinatesFBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateCoordinatesFBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<CoordinatesFBS> CreateCoordinatesFBS(flatbuffers::FlatBufferBuilder &_fbb, const CoordinatesFBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const CoordinatesFBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _type = _o->type.empty() ? 0 : _fbb.CreateString(_o->type);
  auto _coordinates = _o->coordinates.size() ? _fbb.CreateVector(_o->coordinates) : 0;
  return tweetstatusflatbuffers::CreateCoordinatesFBS(
      _fbb,
      _type,
      _coordinates);
}

inline const tweetstatusflatbuffers::CoordinatesFBS *GetCoordinatesFBS(const void *buf) {
  return flatbuffers::GetRoot<tweetstatusflatbuffers::CoordinatesFBS>(buf);
}

inline const tweetstatusflatbuffers::CoordinatesFBS *GetSizePrefixedCoordinatesFBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<tweetstatusflatbuffers::CoordinatesFBS>(buf);
}

inline CoordinatesFBS *GetMutableCoordinatesFBS(void *buf) {
  return flatbuffers::GetMutableRoot<CoordinatesFBS>(buf);
}

inline bool VerifyCoordinatesFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<tweetstatusflatbuffers::CoordinatesFBS>(nullptr);
}

inline bool VerifySizePrefixedCoordinatesFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<tweetstatusflatbuffers::CoordinatesFBS>(nullptr);
}

inline void FinishCoordinatesFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::CoordinatesFBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedCoordinatesFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::CoordinatesFBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<tweetstatusflatbuffers::CoordinatesFBST> UnPackCoordinatesFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::CoordinatesFBST>(GetCoordinatesFBS(buf)->UnPack(res));
}

inline std::unique_ptr<tweetstatusflatbuffers::CoordinatesFBST> UnPackSizePrefixedCoordinatesFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::CoordinatesFBST>(GetSizePrefixedCoordinatesFBS(buf)->UnPack(res));
}

}  // namespace tweetstatusflatbuffers

#endif  // FLATBUFFERS_GENERATED_COORDINATES_TWEETSTATUSFLATBUFFERS_H_
