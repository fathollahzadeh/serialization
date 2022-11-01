/*
* Copyright 2022 Saeed Fathollahzadeh. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef TWITTER_TWEETSTATUSPFLATBUFFERS_H
#define TWITTER_TWEETSTATUSPFLATBUFFERS_H

#include <TweetStatus.h>
#include "TweetStatusFBS.h"

using namespace tweetstatusflatbuffers;
class TweetStatusFlatBuffers: public RootData {

private:

    TweetStatusFBST *tweetStatusFbs;

    TweetStatus *tweetStatus;

    flatbuffers::Offset<TweetStatusFBS> addTOFlatBuffers(TweetStatus *tweetStatus,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<UserFBS> getUserBuilder(User *user, flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<AdditionalMediaInfoEntityFBS> getAdditionalMediaInfoEntityBuilder(AdditionalMediaInfoEntity *additionalMediaInfoEntity,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<BoundingBoxCoordinateFBS> getBoundingBoxCoordinateBuilder(BoundingBoxCoordinate *boundingBoxCoordinate,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<CoordinatesFBS> getCoordinatesBuilder(Coordinates *coordinates,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<EntitiesFBS> getEntitiesBuilder(Entities *entities,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<ExtendedTweetFBS> getExtendedTweetBuilder(ExtendedTweet *extendedTweet,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<ExtendedEntitiesFBS> getExtendedEntitiesBuilder(ExtendedEntities *extendedEntities,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<HashtagEntityFBS> getHashtagEntityBuilder(HashtagEntity *hashtagEntity,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<MediaEntityFBS> getMediaEntityBuilder(MediaEntity *mediaEntity,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<MediaSizesEntityFBS> getMediaSizesEntityBuilder(MediaSizesEntity *mediaSizesEntity,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<OptionEntityFBS> getOptionEntityBuilder(OptionEntity *optionEntity,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<PlaceFBS> getPlaceBuilder(Place *place,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<PollEntityFBS> getPollEntityBuilder(PollEntity *pollEntity,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<SizeEntityFBS> getSizeEntityBuilder(SizeEntity *sizeEntity,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<SymbolEntityFBS> getSymbolEntityBuilder(SymbolEntity *symbolEntity,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<URLEntityFBS> getURLEntityBuilder(URLEntity *urlEntity,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<UserMentionEntityFBS> getUserMentionEntityBuilder(UserMentionEntity *userMentionEntity,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<VariantEntityFBS> getVariantEntityBuilder(VariantEntity *variantEntity,flatbuffers::FlatBufferBuilder &builder);
    flatbuffers::Offset<VideoEntityFBS> getVideoEntityBuilder(VideoEntity *videoEntity,flatbuffers::FlatBufferBuilder &builder);


public:

    int objectsize=0;

    TweetStatusFlatBuffers();

    virtual ~TweetStatusFlatBuffers();

    // Create an flatbuffers object:
    TweetStatusFlatBuffers(TweetStatus *tweetStatus);

    //flatbuffers buffer serialization
    void serializeFlatBuffers(char *buffer, int &objectSize);

    //flatbuffers buffer serialization
    void serializeFlatBuffersIO(char *buffer, int &objectSize);

    //proto buffer de-serialization
    TweetStatusFlatBuffers* deserializeFlatBuffers(char *buffer, int &bytesRead);

    bool operator<(TweetStatusFlatBuffers &other);

};


#endif //TWITTER_TWEETSTATUSPFLATBUFFERS_H
