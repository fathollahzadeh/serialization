//
// Created by saeed on 11/29/19.
//

#ifndef TWITTER_VIDEOENTITYIP_H
#define TWITTER_VIDEOENTITYIP_H

#include <iostream>
#include <vector>
#include "../../header/VariantEntity.h"
#include "../../header/VideoEntity.h"
#include "Object.h"
#include "VariantEntityIP.h"

using namespace std;

class VideoEntityIP: public Object {

private:
    vector<int> aspectRatio;
    int durationMillis;
    offset_ptr<VariantEntityIP> variants;
    int numOfVariantEntity;

public:
    VideoEntityIP();

    virtual ~VideoEntityIP();

    //In place object:
    VideoEntityIP(VideoEntity *videoEntity);

    void serialize(VideoEntity *videoEntity);

};


#endif //TWITTER_VIDEOENTITYIP_H
