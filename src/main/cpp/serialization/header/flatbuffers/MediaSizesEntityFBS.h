// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_MEDIASIZESENTITY_TWEETSTATUSFLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_MEDIASIZESENTITY_TWEETSTATUSFLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 22 &&
              FLATBUFFERS_VERSION_MINOR == 9 &&
              FLATBUFFERS_VERSION_REVISION == 29,
             "Non-compatible flatbuffers version included");

#include "SizeEntityFBS.h"

namespace tweetstatusflatbuffers {

struct MediaSizesEntityFBS;
struct MediaSizesEntityFBSBuilder;
struct MediaSizesEntityFBST;

struct MediaSizesEntityFBST : public flatbuffers::NativeTable {
  typedef MediaSizesEntityFBS TableType;
  std::unique_ptr<tweetstatusflatbuffers::SizeEntityFBST> thumb{};
  std::unique_ptr<tweetstatusflatbuffers::SizeEntityFBST> large{};
  std::unique_ptr<tweetstatusflatbuffers::SizeEntityFBST> medium{};
  std::unique_ptr<tweetstatusflatbuffers::SizeEntityFBST> small{};
  MediaSizesEntityFBST() = default;
  MediaSizesEntityFBST(const MediaSizesEntityFBST &o);
  MediaSizesEntityFBST(MediaSizesEntityFBST&&) FLATBUFFERS_NOEXCEPT = default;
  MediaSizesEntityFBST &operator=(MediaSizesEntityFBST o) FLATBUFFERS_NOEXCEPT;
};

struct MediaSizesEntityFBS FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef MediaSizesEntityFBST NativeTableType;
  typedef MediaSizesEntityFBSBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_THUMB = 4,
    VT_LARGE = 6,
    VT_MEDIUM = 8,
    VT_SMALL = 10
  };
  const tweetstatusflatbuffers::SizeEntityFBS *thumb() const {
    return GetPointer<const tweetstatusflatbuffers::SizeEntityFBS *>(VT_THUMB);
  }
  tweetstatusflatbuffers::SizeEntityFBS *mutable_thumb() {
    return GetPointer<tweetstatusflatbuffers::SizeEntityFBS *>(VT_THUMB);
  }
  const tweetstatusflatbuffers::SizeEntityFBS *large() const {
    return GetPointer<const tweetstatusflatbuffers::SizeEntityFBS *>(VT_LARGE);
  }
  tweetstatusflatbuffers::SizeEntityFBS *mutable_large() {
    return GetPointer<tweetstatusflatbuffers::SizeEntityFBS *>(VT_LARGE);
  }
  const tweetstatusflatbuffers::SizeEntityFBS *medium() const {
    return GetPointer<const tweetstatusflatbuffers::SizeEntityFBS *>(VT_MEDIUM);
  }
  tweetstatusflatbuffers::SizeEntityFBS *mutable_medium() {
    return GetPointer<tweetstatusflatbuffers::SizeEntityFBS *>(VT_MEDIUM);
  }
  const tweetstatusflatbuffers::SizeEntityFBS *small() const {
    return GetPointer<const tweetstatusflatbuffers::SizeEntityFBS *>(VT_SMALL);
  }
  tweetstatusflatbuffers::SizeEntityFBS *mutable_small() {
    return GetPointer<tweetstatusflatbuffers::SizeEntityFBS *>(VT_SMALL);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_THUMB) &&
           verifier.VerifyTable(thumb()) &&
           VerifyOffset(verifier, VT_LARGE) &&
           verifier.VerifyTable(large()) &&
           VerifyOffset(verifier, VT_MEDIUM) &&
           verifier.VerifyTable(medium()) &&
           VerifyOffset(verifier, VT_SMALL) &&
           verifier.VerifyTable(small()) &&
           verifier.EndTable();
  }
  MediaSizesEntityFBST *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(MediaSizesEntityFBST *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<MediaSizesEntityFBS> Pack(flatbuffers::FlatBufferBuilder &_fbb, const MediaSizesEntityFBST* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct MediaSizesEntityFBSBuilder {
  typedef MediaSizesEntityFBS Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_thumb(flatbuffers::Offset<tweetstatusflatbuffers::SizeEntityFBS> thumb) {
    fbb_.AddOffset(MediaSizesEntityFBS::VT_THUMB, thumb);
  }
  void add_large(flatbuffers::Offset<tweetstatusflatbuffers::SizeEntityFBS> large) {
    fbb_.AddOffset(MediaSizesEntityFBS::VT_LARGE, large);
  }
  void add_medium(flatbuffers::Offset<tweetstatusflatbuffers::SizeEntityFBS> medium) {
    fbb_.AddOffset(MediaSizesEntityFBS::VT_MEDIUM, medium);
  }
  void add_small(flatbuffers::Offset<tweetstatusflatbuffers::SizeEntityFBS> small) {
    fbb_.AddOffset(MediaSizesEntityFBS::VT_SMALL, small);
  }
  explicit MediaSizesEntityFBSBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<MediaSizesEntityFBS> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<MediaSizesEntityFBS>(end);
    return o;
  }
};

inline flatbuffers::Offset<MediaSizesEntityFBS> CreateMediaSizesEntityFBS(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::SizeEntityFBS> thumb = 0,
    flatbuffers::Offset<tweetstatusflatbuffers::SizeEntityFBS> large = 0,
    flatbuffers::Offset<tweetstatusflatbuffers::SizeEntityFBS> medium = 0,
    flatbuffers::Offset<tweetstatusflatbuffers::SizeEntityFBS> small = 0) {
  MediaSizesEntityFBSBuilder builder_(_fbb);
  builder_.add_small(small);
  builder_.add_medium(medium);
  builder_.add_large(large);
  builder_.add_thumb(thumb);
  return builder_.Finish();
}

flatbuffers::Offset<MediaSizesEntityFBS> CreateMediaSizesEntityFBS(flatbuffers::FlatBufferBuilder &_fbb, const MediaSizesEntityFBST *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline MediaSizesEntityFBST::MediaSizesEntityFBST(const MediaSizesEntityFBST &o)
      : thumb((o.thumb) ? new tweetstatusflatbuffers::SizeEntityFBST(*o.thumb) : nullptr),
        large((o.large) ? new tweetstatusflatbuffers::SizeEntityFBST(*o.large) : nullptr),
        medium((o.medium) ? new tweetstatusflatbuffers::SizeEntityFBST(*o.medium) : nullptr),
        small((o.small) ? new tweetstatusflatbuffers::SizeEntityFBST(*o.small) : nullptr) {
}

inline MediaSizesEntityFBST &MediaSizesEntityFBST::operator=(MediaSizesEntityFBST o) FLATBUFFERS_NOEXCEPT {
  std::swap(thumb, o.thumb);
  std::swap(large, o.large);
  std::swap(medium, o.medium);
  std::swap(small, o.small);
  return *this;
}

inline MediaSizesEntityFBST *MediaSizesEntityFBS::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<MediaSizesEntityFBST>(new MediaSizesEntityFBST());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void MediaSizesEntityFBS::UnPackTo(MediaSizesEntityFBST *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = thumb(); if (_e) { if(_o->thumb) { _e->UnPackTo(_o->thumb.get(), _resolver); } else { _o->thumb = std::unique_ptr<tweetstatusflatbuffers::SizeEntityFBST>(_e->UnPack(_resolver)); } } else if (_o->thumb) { _o->thumb.reset(); } }
  { auto _e = large(); if (_e) { if(_o->large) { _e->UnPackTo(_o->large.get(), _resolver); } else { _o->large = std::unique_ptr<tweetstatusflatbuffers::SizeEntityFBST>(_e->UnPack(_resolver)); } } else if (_o->large) { _o->large.reset(); } }
  { auto _e = medium(); if (_e) { if(_o->medium) { _e->UnPackTo(_o->medium.get(), _resolver); } else { _o->medium = std::unique_ptr<tweetstatusflatbuffers::SizeEntityFBST>(_e->UnPack(_resolver)); } } else if (_o->medium) { _o->medium.reset(); } }
  { auto _e = small(); if (_e) { if(_o->small) { _e->UnPackTo(_o->small.get(), _resolver); } else { _o->small = std::unique_ptr<tweetstatusflatbuffers::SizeEntityFBST>(_e->UnPack(_resolver)); } } else if (_o->small) { _o->small.reset(); } }
}

inline flatbuffers::Offset<MediaSizesEntityFBS> MediaSizesEntityFBS::Pack(flatbuffers::FlatBufferBuilder &_fbb, const MediaSizesEntityFBST* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateMediaSizesEntityFBS(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<MediaSizesEntityFBS> CreateMediaSizesEntityFBS(flatbuffers::FlatBufferBuilder &_fbb, const MediaSizesEntityFBST *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const MediaSizesEntityFBST* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _thumb = _o->thumb ? CreateSizeEntityFBS(_fbb, _o->thumb.get(), _rehasher) : 0;
  auto _large = _o->large ? CreateSizeEntityFBS(_fbb, _o->large.get(), _rehasher) : 0;
  auto _medium = _o->medium ? CreateSizeEntityFBS(_fbb, _o->medium.get(), _rehasher) : 0;
  auto _small = _o->small ? CreateSizeEntityFBS(_fbb, _o->small.get(), _rehasher) : 0;
  return tweetstatusflatbuffers::CreateMediaSizesEntityFBS(
      _fbb,
      _thumb,
      _large,
      _medium,
      _small);
}

inline const tweetstatusflatbuffers::MediaSizesEntityFBS *GetMediaSizesEntityFBS(const void *buf) {
  return flatbuffers::GetRoot<tweetstatusflatbuffers::MediaSizesEntityFBS>(buf);
}

inline const tweetstatusflatbuffers::MediaSizesEntityFBS *GetSizePrefixedMediaSizesEntityFBS(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<tweetstatusflatbuffers::MediaSizesEntityFBS>(buf);
}

inline MediaSizesEntityFBS *GetMutableMediaSizesEntityFBS(void *buf) {
  return flatbuffers::GetMutableRoot<MediaSizesEntityFBS>(buf);
}

inline tweetstatusflatbuffers::MediaSizesEntityFBS *GetMutableSizePrefixedMediaSizesEntityFBS(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<tweetstatusflatbuffers::MediaSizesEntityFBS>(buf);
}

inline bool VerifyMediaSizesEntityFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<tweetstatusflatbuffers::MediaSizesEntityFBS>(nullptr);
}

inline bool VerifySizePrefixedMediaSizesEntityFBSBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<tweetstatusflatbuffers::MediaSizesEntityFBS>(nullptr);
}

inline void FinishMediaSizesEntityFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::MediaSizesEntityFBS> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedMediaSizesEntityFBSBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tweetstatusflatbuffers::MediaSizesEntityFBS> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<tweetstatusflatbuffers::MediaSizesEntityFBST> UnPackMediaSizesEntityFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::MediaSizesEntityFBST>(GetMediaSizesEntityFBS(buf)->UnPack(res));
}

inline std::unique_ptr<tweetstatusflatbuffers::MediaSizesEntityFBST> UnPackSizePrefixedMediaSizesEntityFBS(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<tweetstatusflatbuffers::MediaSizesEntityFBST>(GetSizePrefixedMediaSizesEntityFBS(buf)->UnPack(res));
}

}  // namespace tweetstatusflatbuffers

#endif  // FLATBUFFERS_GENERATED_MEDIASIZESENTITY_TWEETSTATUSFLATBUFFERS_H_
