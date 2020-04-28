// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_PLACE_TWEETSTATUSFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_PLACE_TWEETSTATUSFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

#include "BoundingBoxCoordinateFBS.h"

namespace tweetstatusflatbuffers {

struct PlaceFBS;
struct PlaceFBSBuilder;
struct PlaceFBST;

struct PlaceFBST : public flatbuffers::NativeTable {
  typedef PlaceFBS TableType;
  std::string name;
  std::string country_code;
  std::string id;
  std::string country;
  std::string place_type;
  std::string url;
  std::string full_name;
  std::unique_ptr<tweetstatusflatbuffers::BoundingBoxCoordinateFBST> bounding_box;
  PlaceFBST() {
  }
};

struct PlaceFBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef PlaceFBST NativeTableType;
  typedef PlaceFBSBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_COUNTRY_CODE = 6,
    VT_ID = 8,
    VT_COUNTRY = 10,
    VT_PLACE_TYPE = 12,
    VT_URL = 14,
    VT_FULL_NAME = 16,
    VT_BOUNDING_BOX = 18
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  flatbuffers::String *mutable_name() {
    return GetPointer<flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::String *country_code() const {
    return GetPointer<const flatbuffers::String *>(VT_COUNTRY_CODE);
  }
  flatbuffers::String *mutable_country_code() {
    return GetPointer<flatbuffers::String *>(VT_COUNTRY_CODE);
  }
  const flatbuffers::String *id() const {
    return GetPointer<const flatbuffers::String *>(VT_ID);
  }
  flatbuffers::String *mutable_id() {
    return GetPointer<flatbuffers::String *>(VT_ID);
  }
  const flatbuffers::String *country() const {
    return GetPointer<const flatbuffers::String *>(VT_COUNTRY);
  }
  flatbuffers::String *mutable_country() {
    return GetPointer<flatbuffers::String *>(VT_COUNTRY);
  }
  const flatbuffers::String *place_type() const {
    return GetPointer<const flatbuffers::String *>(VT_PLACE_TYPE);
  }
  flatbuffers::String *mutable_place_type() {
    return GetPointer<flatbuffers::String *>(VT_PLACE_TYPE);
  }
  const flatbuffers::String *url() const {
    return GetPointer<const flatbuffers::String *>(VT_URL);
  }
  flatbuffers::String *mutable_url() {
    return GetPointer<flatbuffers::String *>(VT_URL);
  }
  const flatbuffers::String *full_name() const {
    return GetPointer<const flatbuffers::String *>(VT_FULL_NAME);
  }
  flatbuffers::String *mutable_full_name() {
    return GetPointer<flatbuffers::String *>(VT_FULL_NAME);
  }
  const tweetstatusflatbuffers::BoundingBoxCoordinateFBS *bounding_box() const {
    return GetPointer<const tweetstatusflatbuffers::BoundingBoxCoordinateFBS *>(VT_BOUNDING_BOX);
  }
  tweetstatusflatbuffers::BoundingBoxCoordinateFBS *mutable_bounding_box() {
    return GetPointer<tweetstatusflatbuffers::BoundingBoxCoordinateFBS *>(VT_BOUNDING_BOX);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_COUNTRY_CODE) &&
           verifier.VerifyString(country_code()) &&
           VerifyOffset(verifier, VT_ID) &&
           verifier.VerifyString(id()) &&
           VerifyOffset(verifier, VT_COUNTRY) &&
           verifier.VerifyString(country()) &&
           VerifyOffset(verifier, VT_PLACE_TYPE) &&
           verifier.VerifyString(place_type()) &&
           VerifyOffset(verifier, VT_URL) &&
           verifier.VerifyString(url()) &&
           VerifyOffset(verifier, VT_FULL_NAME) &&
           verifier.VerifyString(full_name()) &&
           VerifyOffset(verifier, VT_BOUNDING_BOX) &&
           verifier.VerifyTable(bounding_box()) &&
           verifier.EndTable();
  }
  PlaceFBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(PlaceFBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<PlaceFBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const PlaceFBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct PlaceFBSBuilder {
  typedef PlaceFBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(PlaceFBS::VT_NAME, name);
  }
  void add_country_code(flatbuffers::Offset<flatbuffers::String> country_code) {
    fbb_.AddOffset(PlaceFBS::VT_COUNTRY_CODE, country_code);
  }
  void add_id(flatbuffers::Offset<flatbuffers::String> id) {
    fbb_.AddOffset(PlaceFBS::VT_ID, id);
  }
  void add_country(flatbuffers::Offset<flatbuffers::String> country) {
    fbb_.AddOffset(PlaceFBS::VT_COUNTRY, country);
  }
  void add_place_type(flatbuffers::Offset<flatbuffers::String> place_type) {
    fbb_.AddOffset(PlaceFBS::VT_PLACE_TYPE, place_type);
  }
  void add_url(flatbuffers::Offset<flatbuffers::String> url) {
    fbb_.AddOffset(PlaceFBS::VT_URL, url);
  }
  void add_full_name(flatbuffers::Offset<flatbuffers::String> full_name) {
    fbb_.AddOffset(PlaceFBS::VT_FULL_NAME, full_name);
  }
  void add_bounding_box(flatbuffers::Offset<tweetstatusflatbuffers::BoundingBoxCoordinateFBS> bounding_box) {
    fbb_.AddOffset(PlaceFBS::VT_BOUNDING_BOX, bounding_box);
  }
  explicit PlaceFBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<PlaceFBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PlaceFBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<PlaceFBS> CreatePlaceFBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::String> country_code = 0,
    flatbuffers::Offset<flatbuffers::String> id = 0,
    flatbuffers::Offset<flatbuffers::String> country = 0,
    flatbuffers::Offset<flatbuffers::String> place_type = 0,
    flatbuffers::Offset<flatbuffers::String> url = 0,
    flatbuffers::Offset<flatbuffers::String> full_name = 0,
    flatbuffers::Offset<tweetstatusflatbuffers::BoundingBoxCoordinateFBS> bounding_box = 0) {
  PlaceFBSBuilder builder_(_fbb);
  builder_.add_bounding_box(bounding_box);
  builder_.add_full_name(full_name);
  builder_.add_url(url);
  builder_.add_place_type(place_type);
  builder_.add_country(country);
  builder_.add_id(id);
  builder_.add_country_code(country_code);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<PlaceFBS> CreatePlaceFBSDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const char *country_code = nullptr,
    const char *id = nullptr,
    const char *country = nullptr,
    const char *place_type = nullptr,
    const char *url = nullptr,
    const char *full_name = nullptr,
    flatbuffers::Offset<tweetstatusflatbuffers::BoundingBoxCoordinateFBS> bounding_box = 0) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto country_code__ = country_code ? _fbb.CreateString(country_code) : 0;
  auto id__ = id ? _fbb.CreateString(id) : 0;
  auto country__ = country ? _fbb.CreateString(country) : 0;
  auto place_type__ = place_type ? _fbb.CreateString(place_type) : 0;
  auto url__ = url ? _fbb.CreateString(url) : 0;
  auto full_name__ = full_name ? _fbb.CreateString(full_name) : 0;
  return tweetstatusflatbuffers::CreatePlaceFBS(
      _fbb,
      name__,
      country_code__,
      id__,
      country__,
      place_type__,
      url__,
      full_name__,
      bounding_box);
}

flatbuffers::Offset<PlaceFBS> CreatePlaceFBS(flatbuffers::FlatBufferBuilder &_fbb, const PlaceFBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline PlaceFBST *PlaceFBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  std::unique_ptr<tweetstatusflatbuffers::PlaceFBST> _o = std::unique_ptr<tweetstatusflatbuffers::PlaceFBST>(new PlaceFBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void PlaceFBS::UnPackTo(PlaceFBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = name(); if (_e) _o->name = _e->str(); }
  { auto _e = country_code(); if (_e) _o->country_code = _e->str(); }
  { auto _e = id(); if (_e) _o->id = _e->str(); }
  { auto _e = country(); if (_e) _o->country = _e->str(); }
  { auto _e = place_type(); if (_e) _o->place_type = _e->str(); }
  { auto _e = url(); if (_e) _o->url = _e->str(); }
  { auto _e = full_name(); if (_e) _o->full_name = _e->str(); }
  { auto _e = bounding_box(); if (_e) _o->bounding_box = std::unique_ptr<tweetstatusflatbuffers::BoundingBoxCoordinateFBST>(_e->UnPack(_resolver)); }
}

inline flatbuffers::Offset<PlaceFBS> PlaceFBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const PlaceFBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreatePlaceFBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<PlaceFBS> CreatePlaceFBS(flatbuffers::FlatBufferBuilder &_fbb, const PlaceFBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const PlaceFBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _name = _o->name.empty() ? 0 : _fbb.CreateString(_o->name);
  auto _country_code = _o->country_code.empty() ? 0 : _fbb.CreateString(_o->country_code);
  auto _id = _o->id.empty() ? 0 : _fbb.CreateString(_o->id);
  auto _country = _o->country.empty() ? 0 : _fbb.CreateString(_o->country);
  auto _place_type = _o->place_type.empty() ? 0 : _fbb.CreateString(_o->place_type);
  auto _url = _o->url.empty() ? 0 : _fbb.CreateString(_o->url);
  auto _full_name = _o->full_name.empty() ? 0 : _fbb.CreateString(_o->full_name);
  auto _bounding_box = _o->bounding_box ? CreateBoundingBoxCoordinateFBS(_fbb, _o->bounding_box.get(), _rehasher) : 0;
  return tweetstatusflatbuffers::CreatePlaceFBS(
      _fbb,
      _name,
      _country_code,
      _id,
      _country,
      _place_type,
      _url,
      _full_name,
      _bounding_box);
}

inline const tweetstatusflatbuffers::PlaceFBS *GetPlaceFBS(const void *buf) {
  return flatbuffers::GetRoot<tweetstatusflatbuffers::PlaceFBS>(buf);
}

inline const tweetstatusflatbuffers::PlaceFBS *GetSizePrefixedPlaceFBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<tweetstatusflatbuffers::PlaceFBS>(buf);
}

inline PlaceFBS *GetMutablePlaceFBS(void *buf) {
  return flatbuffers::GetMutableRoot<PlaceFBS>(buf);
}

inline bool VerifyPlaceFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<tweetstatusflatbuffers::PlaceFBS>(nullptr);
}

inline bool VerifySizePrefixedPlaceFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<tweetstatusflatbuffers::PlaceFBS>(nullptr);
}

inline void FinishPlaceFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::PlaceFBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedPlaceFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::PlaceFBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<tweetstatusflatbuffers::PlaceFBST> UnPackPlaceFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::PlaceFBST>(GetPlaceFBS(buf)->UnPack(res));
}

inline std::unique_ptr<tweetstatusflatbuffers::PlaceFBST> UnPackSizePrefixedPlaceFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::PlaceFBST>(GetSizePrefixedPlaceFBS(buf)->UnPack(res));
}

}  // namespace tweetstatusflatbuffers

#endif  // FLATBUFFERS_GENERATED_PLACE_TWEETSTATUSFLATBUFFERS_H_
