// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_BOUNDINGBOXCOORDINATE_TWEETSTATUSFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_BOUNDINGBOXCOORDINATE_TWEETSTATUSFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

namespace tweetstatusflatbuffers {

struct BoundingBoxCoordinateFBS;
struct BoundingBoxCoordinateFBSBuilder;
struct BoundingBoxCoordinateFBST;

struct DoubleList1;
struct DoubleList1Builder;
struct DoubleList1T;

struct DoubleList2;
struct DoubleList2Builder;
struct DoubleList2T;

struct BoundingBoxCoordinateFBST : public flatbuffers::NativeTable {
  typedef BoundingBoxCoordinateFBS TableType;
  std::string type{};
  std::vector<std::unique_ptr<tweetstatusflatbuffers::DoubleList1T>> coordinates{};
  BoundingBoxCoordinateFBST() = default;
  BoundingBoxCoordinateFBST(const BoundingBoxCoordinateFBST &o);
  BoundingBoxCoordinateFBST(BoundingBoxCoordinateFBST&&) FLATBUFFERS_NOEXCEPT = default;
  BoundingBoxCoordinateFBST &operator=(BoundingBoxCoordinateFBST o) FLATBUFFERS_NOEXCEPT;
};

struct BoundingBoxCoordinateFBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef BoundingBoxCoordinateFBST NativeTableType;
  typedef BoundingBoxCoordinateFBSBuilder Builder;
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
  const flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList1>> *coordinates() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList1>> *>(VT_COORDINATES);
  }
  flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList1>> *mutable_coordinates() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList1>> *>(VT_COORDINATES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_TYPE) &&
           verifier.VerifyString(type()) &&
           VerifyOffset(verifier, VT_COORDINATES) &&
           verifier.VerifyVector(coordinates()) &&
           verifier.VerifyVectorOfTables(coordinates()) &&
           verifier.EndTable();
  }
  BoundingBoxCoordinateFBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(BoundingBoxCoordinateFBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<BoundingBoxCoordinateFBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const BoundingBoxCoordinateFBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct BoundingBoxCoordinateFBSBuilder {
  typedef BoundingBoxCoordinateFBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(flatbuffers::Offset<flatbuffers::String> type) {
    fbb_.AddOffset(BoundingBoxCoordinateFBS::VT_TYPE, type);
  }
  void add_coordinates(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList1>>> coordinates) {
    fbb_.AddOffset(BoundingBoxCoordinateFBS::VT_COORDINATES, coordinates);
  }
  explicit BoundingBoxCoordinateFBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<BoundingBoxCoordinateFBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<BoundingBoxCoordinateFBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<BoundingBoxCoordinateFBS> CreateBoundingBoxCoordinateFBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> type = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList1>>> coordinates = 0) {
  BoundingBoxCoordinateFBSBuilder builder_(_fbb);
  builder_.add_coordinates(coordinates);
  builder_.add_type(type);
  return builder_.Finish();
}

inline flatbuffers::Offset<BoundingBoxCoordinateFBS> CreateBoundingBoxCoordinateFBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *type = nullptr,
    const std::vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList1>> *coordinates = nullptr) {
  auto type__ = type ? _fbb.CreateString(type) : 0;
  auto coordinates__ = coordinates ? _fbb.CreateVector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList1>>(*coordinates) : 0;
  return tweetstatusflatbuffers::CreateBoundingBoxCoordinateFBS(
      _fbb,
      type__,
      coordinates__);
}

flatbuffers::Offset<BoundingBoxCoordinateFBS> CreateBoundingBoxCoordinateFBS(flatbuffers::FlatBufferBuilder &_fbb, const BoundingBoxCoordinateFBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct DoubleList1T : public flatbuffers::NativeTable {
  typedef DoubleList1 TableType;
  std::vector<std::unique_ptr<tweetstatusflatbuffers::DoubleList2T>> values{};
  DoubleList1T() = default;
  DoubleList1T(const DoubleList1T &o);
  DoubleList1T(DoubleList1T&&) FLATBUFFERS_NOEXCEPT = default;
  DoubleList1T &operator=(DoubleList1T o) FLATBUFFERS_NOEXCEPT;
};

struct DoubleList1 FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef DoubleList1T NativeTableType;
  typedef DoubleList1Builder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_VALUES = 4
  };
  const flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList2>> *values() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList2>> *>(VT_VALUES);
  }
  flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList2>> *mutable_values() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList2>> *>(VT_VALUES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VALUES) &&
           verifier.VerifyVector(values()) &&
           verifier.VerifyVectorOfTables(values()) &&
           verifier.EndTable();
  }
  DoubleList1T *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(DoubleList1T *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<DoubleList1> Pack(flatbuffers::FlatBufferBuilder &_fbb, const DoubleList1T* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct DoubleList1Builder {
  typedef DoubleList1 Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_values(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList2>>> values) {
    fbb_.AddOffset(DoubleList1::VT_VALUES, values);
  }
  explicit DoubleList1Builder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<DoubleList1> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<DoubleList1>(end);
    return o;
  }
};

inline flatbuffers::Offset<DoubleList1> CreateDoubleList1(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList2>>> values = 0) {
  DoubleList1Builder builder_(_fbb);
  builder_.add_values(values);
  return builder_.Finish();
}

inline flatbuffers::Offset<DoubleList1> CreateDoubleList1Direct(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList2>> *values = nullptr) {
  auto values__ = values ? _fbb.CreateVector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList2>>(*values) : 0;
  return tweetstatusflatbuffers::CreateDoubleList1(
      _fbb,
      values__);
}

flatbuffers::Offset<DoubleList1> CreateDoubleList1(flatbuffers::FlatBufferBuilder &_fbb, const DoubleList1T *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct DoubleList2T : public flatbuffers::NativeTable {
  typedef DoubleList2 TableType;
  std::vector<double> values{};
};

struct DoubleList2 FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef DoubleList2T NativeTableType;
  typedef DoubleList2Builder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_VALUES = 4
  };
  const flatbuffers::Vector<double> *values() const {
    return GetPointer<const flatbuffers::Vector<double> *>(VT_VALUES);
  }
  flatbuffers::Vector<double> *mutable_values() {
    return GetPointer<flatbuffers::Vector<double> *>(VT_VALUES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VALUES) &&
           verifier.VerifyVector(values()) &&
           verifier.EndTable();
  }
  DoubleList2T *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(DoubleList2T *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<DoubleList2> Pack(flatbuffers::FlatBufferBuilder &_fbb, const DoubleList2T* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct DoubleList2Builder {
  typedef DoubleList2 Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_values(flatbuffers::Offset<flatbuffers::Vector<double>> values) {
    fbb_.AddOffset(DoubleList2::VT_VALUES, values);
  }
  explicit DoubleList2Builder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<DoubleList2> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<DoubleList2>(end);
    return o;
  }
};

inline flatbuffers::Offset<DoubleList2> CreateDoubleList2(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<double>> values = 0) {
  DoubleList2Builder builder_(_fbb);
  builder_.add_values(values);
  return builder_.Finish();
}

inline flatbuffers::Offset<DoubleList2> CreateDoubleList2Direct(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<double> *values = nullptr) {
  auto values__ = values ? _fbb.CreateVector<double>(*values) : 0;
  return tweetstatusflatbuffers::CreateDoubleList2(
      _fbb,
      values__);
}

flatbuffers::Offset<DoubleList2> CreateDoubleList2(flatbuffers::FlatBufferBuilder &_fbb, const DoubleList2T *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline BoundingBoxCoordinateFBST::BoundingBoxCoordinateFBST(const BoundingBoxCoordinateFBST &o)
      : type(o.type) {
  coordinates.reserve(o.coordinates.size());
  for (const auto &coordinates_ : o.coordinates) { coordinates.emplace_back((coordinates_) ? new tweetstatusflatbuffers::DoubleList1T(*coordinates_) : nullptr); }
}

inline BoundingBoxCoordinateFBST &BoundingBoxCoordinateFBST::operator=(BoundingBoxCoordinateFBST o) FLATBUFFERS_NOEXCEPT {
  std::swap(type, o.type);
  std::swap(coordinates, o.coordinates);
  return *this;
}

inline BoundingBoxCoordinateFBST *BoundingBoxCoordinateFBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<BoundingBoxCoordinateFBST>(new BoundingBoxCoordinateFBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void BoundingBoxCoordinateFBS::UnPackTo(BoundingBoxCoordinateFBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = type(); if (_e) _o->type = _e->str(); }
  { auto _e = coordinates(); if (_e) { _o->coordinates.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { if(_o->coordinates[_i]) { _e->Get(_i)->UnPackTo(_o->coordinates[_i].get(), _resolver); } else { _o->coordinates[_i] = std::unique_ptr<tweetstatusflatbuffers::DoubleList1T>(_e->Get(_i)->UnPack(_resolver)); }; } } else { _o->coordinates.resize(0); } }
}

inline flatbuffers::Offset<BoundingBoxCoordinateFBS> BoundingBoxCoordinateFBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const BoundingBoxCoordinateFBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateBoundingBoxCoordinateFBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<BoundingBoxCoordinateFBS> CreateBoundingBoxCoordinateFBS(flatbuffers::FlatBufferBuilder &_fbb, const BoundingBoxCoordinateFBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const BoundingBoxCoordinateFBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _type = _o->type.empty() ? 0 : _fbb.CreateString(_o->type);
  auto _coordinates = _o->coordinates.size() ? _fbb.CreateVector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList1>> (_o->coordinates.size(), [](size_t i, _VectorArgs *__va) { return CreateDoubleList1(*__va->__fbb, __va->__o->coordinates[i].get(), __va->__rehasher); }, &_va ) : 0;
  return tweetstatusflatbuffers::CreateBoundingBoxCoordinateFBS(
      _fbb,
      _type,
      _coordinates);
}

inline DoubleList1T::DoubleList1T(const DoubleList1T &o) {
  values.reserve(o.values.size());
  for (const auto &values_ : o.values) { values.emplace_back((values_) ? new tweetstatusflatbuffers::DoubleList2T(*values_) : nullptr); }
}

inline DoubleList1T &DoubleList1T::operator=(DoubleList1T o) FLATBUFFERS_NOEXCEPT {
  std::swap(values, o.values);
  return *this;
}

inline DoubleList1T *DoubleList1::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<DoubleList1T>(new DoubleList1T());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void DoubleList1::UnPackTo(DoubleList1T *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = values(); if (_e) { _o->values.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { if(_o->values[_i]) { _e->Get(_i)->UnPackTo(_o->values[_i].get(), _resolver); } else { _o->values[_i] = std::unique_ptr<tweetstatusflatbuffers::DoubleList2T>(_e->Get(_i)->UnPack(_resolver)); }; } } else { _o->values.resize(0); } }
}

inline flatbuffers::Offset<DoubleList1> DoubleList1::Pack(flatbuffers::FlatBufferBuilder &_fbb, const DoubleList1T* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateDoubleList1(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<DoubleList1> CreateDoubleList1(flatbuffers::FlatBufferBuilder &_fbb, const DoubleList1T *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const DoubleList1T* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _values = _o->values.size() ? _fbb.CreateVector<flatbuffers::Offset<tweetstatusflatbuffers::DoubleList2>> (_o->values.size(), [](size_t i, _VectorArgs *__va) { return CreateDoubleList2(*__va->__fbb, __va->__o->values[i].get(), __va->__rehasher); }, &_va ) : 0;
  return tweetstatusflatbuffers::CreateDoubleList1(
      _fbb,
      _values);
}

inline DoubleList2T *DoubleList2::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<DoubleList2T>(new DoubleList2T());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void DoubleList2::UnPackTo(DoubleList2T *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = values(); if (_e) { _o->values.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->values[_i] = _e->Get(_i); } } else { _o->values.resize(0); } }
}

inline flatbuffers::Offset<DoubleList2> DoubleList2::Pack(flatbuffers::FlatBufferBuilder &_fbb, const DoubleList2T* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateDoubleList2(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<DoubleList2> CreateDoubleList2(flatbuffers::FlatBufferBuilder &_fbb, const DoubleList2T *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const DoubleList2T* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _values = _o->values.size() ? _fbb.CreateVector(_o->values) : 0;
  return tweetstatusflatbuffers::CreateDoubleList2(
      _fbb,
      _values);
}

inline const tweetstatusflatbuffers::BoundingBoxCoordinateFBS *GetBoundingBoxCoordinateFBS(const void *buf) {
  return flatbuffers::GetRoot<tweetstatusflatbuffers::BoundingBoxCoordinateFBS>(buf);
}

inline const tweetstatusflatbuffers::BoundingBoxCoordinateFBS *GetSizePrefixedBoundingBoxCoordinateFBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<tweetstatusflatbuffers::BoundingBoxCoordinateFBS>(buf);
}

inline BoundingBoxCoordinateFBS *GetMutableBoundingBoxCoordinateFBS(void *buf) {
  return flatbuffers::GetMutableRoot<BoundingBoxCoordinateFBS>(buf);
}

inline tweetstatusflatbuffers::BoundingBoxCoordinateFBS *GetMutableSizePrefixedBoundingBoxCoordinateFBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<tweetstatusflatbuffers::BoundingBoxCoordinateFBS>(buf);
}

inline bool VerifyBoundingBoxCoordinateFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<tweetstatusflatbuffers::BoundingBoxCoordinateFBS>(nullptr);
}

inline bool VerifySizePrefixedBoundingBoxCoordinateFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<tweetstatusflatbuffers::BoundingBoxCoordinateFBS>(nullptr);
}

inline void FinishBoundingBoxCoordinateFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::BoundingBoxCoordinateFBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedBoundingBoxCoordinateFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::BoundingBoxCoordinateFBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<tweetstatusflatbuffers::BoundingBoxCoordinateFBST> UnPackBoundingBoxCoordinateFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::BoundingBoxCoordinateFBST>(GetBoundingBoxCoordinateFBS(buf)->UnPack(res));
}

inline std::unique_ptr<tweetstatusflatbuffers::BoundingBoxCoordinateFBST> UnPackSizePrefixedBoundingBoxCoordinateFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::BoundingBoxCoordinateFBST>(GetSizePrefixedBoundingBoxCoordinateFBS(buf)->UnPack(res));
}

}  // namespace tweetstatusflatbuffers

#endif  // FLATBUFFERS_GENERATED_BOUNDINGBOXCOORDINATE_TWEETSTATUSFLATBUFFERS_H_
