#ifndef TWITTER_MEDIASIZESENTITYIP_H
#define TWITTER_MEDIASIZESENTITYIP_H

#include "SizeEntity.h"
#include "MediaSizesEntity.h"
#include "Object.h"
#include "SizeEntityIP.h"

class MediaSizesEntityIP: public Object {

private:
    offset_ptr <SizeEntityIP>thumb;
    bool  hasThumb;
    offset_ptr <SizeEntityIP>large;
    bool  hasLarge;
    offset_ptr <SizeEntityIP>medium;
    bool hasMedium;
    offset_ptr <SizeEntityIP>small;
    bool hasSmall;

public:

    MediaSizesEntityIP();

    virtual ~MediaSizesEntityIP();

    //In place serialization:
    MediaSizesEntityIP(MediaSizesEntity *mediaSizesEntity);

    void serialize(MediaSizesEntity *mediaSizesEntity);
};


#endif //TWITTER_MEDIASIZESENTITYIP_H
