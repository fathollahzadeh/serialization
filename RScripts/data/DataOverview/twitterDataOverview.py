
import json

tweet_file = open('tweet.txt', 'a')
place_file = open('place.txt', 'a')
entities_object_count_file=open('entities_object_count.txt', 'a')

hashtags_file=open('hashtags.txt', 'a')
media_file=open('media.txt', 'a')
urls_file=open('urls.txt', 'a')
user_mentions_file=open('user_mentions.txt', 'a')
symbols_file=open('symbols.txt', 'a')
polls_file=open('polls.txt', 'a')
media_entity_file=open('media_entity.txt', 'a')
poll_entity_object_count_file=open('poll_entity_object_count.txt', 'a')
media_size_entity_file=open('media_size_entity.txt', 'a')
video_entity_count_file=open('video_entity_count.txt', 'a')
variant_entity_file=open('variant_entity.txt', 'a')

tweet_file.write("Tweets#users#coordinates#place#quoted_status#retweeted_status#entities#extended_entities \n")
place_file.write("bounding_box \n")
entities_object_count_file.write("hashtags#media#urls#user_mentions#symbols#polls\n")
hashtags_file.write("hashtags\n")
media_file.write("medias\n")
urls_file.write("urls\n")
user_mentions_file.write("user_mentions\n")
symbols_file.write("symbols\n")
polls_file.write("polls\n")
media_entity_file.write("sizes#video_info#additional_media_info\n")
poll_entity_object_count_file.write("options\n")
media_size_entity_file.write("thumb#large#medium#small\n")
video_entity_count_file.write("variants\n")
variant_entity_file.write("variants \n")



with open('/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/tweets_1M_rows.txt') as f:
    for line in f:
        tweet=json.loads(line)

        # Tweet Object
        tweetsLength = len(json.dumps(tweet))
        usersLength = len(json.dumps(tweet["user"]))
        coordinatesLength = 0
        if tweet['coordinates'] is not None:
            coordinatesLength=len(json.dumps(tweet["coordinates"]))

        placeLength = 0

        # place nested objects:
        bounding_boxLength=0
        if tweet['place'] is not None:
            placeLength = len(json.dumps(tweet["place"]))
            if tweet['place'].get('bounding_box'):
                if tweet['place']['bounding_box'] is not None:
                    bounding_boxLength=len(json.dumps(tweet['place']['bounding_box']))

        quoted_statusLength = 0
        if tweet.get('quoted_status'):
            if  tweet['quoted_status'] is not None:
                quoted_statusLength = len(json.dumps(tweet["quoted_status"]))

        retweeted_statusLength = 0
        if tweet.get('retweeted_status'):
            if tweet['retweeted_status'] is not None:
             retweeted_statusLength = len(json.dumps(tweet["retweeted_status"]))

        entitiesLength = 0
        if tweet['entities'] is not None:
            entitiesLength = len(json.dumps(tweet["entities"]))
            # entities nested objects:
            hashtagsCount=0
            mediaCount=0
            urlsCount=0
            user_mentionsCount=0
            symbolsCount=0
            pollsCount=0

           # get hashtags list and calc each object size:
            if tweet['entities'].get("hashtags") :
                hashtagsCount=len(tweet['entities']["hashtags"])
                for hashtag in tweet['entities']["hashtags"]:
                    hashtags_file.write(str(len(json.dumps(hashtag)))+"\n")

            # get media list and calc each object size:
            if tweet['entities'].get("media") :
                mediaCount=len(tweet['entities']["media"])
                for media in tweet['entities']["media"]:
                    media_file.write(str(len(json.dumps(media)))+"\n")
                    # media entity nested objects:
                    for media_entity in tweet['entities']["media"]:
                        sizesLength=0
                        if media_entity.get("sizes"):
                            if media_entity["sizes"] is not None:
                                sizesLength=len(json.dumps(media_entity["sizes"]))
                                thumbLength=0
                                largeLength=0
                                mediumLength=0
                                smallLength=0

                                if media_entity["sizes"]["thumb"] is not None:
                                    thumbLength=len(json.dumps(media_entity["sizes"]["thumb"]))

                                if media_entity["sizes"]["large"] is not None:
                                    largeLength=len(json.dumps(media_entity["sizes"]["large"]))

                                if media_entity["sizes"]["medium"] is not None:
                                    mediumLength=len(json.dumps(media_entity["sizes"]["medium"]))

                                if media_entity["sizes"]["small"] is not None:
                                    smallLength=len(json.dumps(media_entity["sizes"]["small"]))
                                media_size_entity_file.write(str(thumbLength)+"#"+str(largeLength)+"#"+str(mediumLength)+"#"+str(smallLength)+"\n")


                        video_infoLength=0
                        if media_entity.get("video_info"):
                            if media_entity["video_info"] is not None:
                                video_infoLength=len(json.dumps(media_entity["video_info"]))
                                variantsCount=0
                                if media_entity["video_info"].get("variants"):
                                    variantsCount=len(media_entity["video_info"]["variants"])
                                    video_entity_count_file.write(str(variantsCount)+"\n")
                                    for variant in media_entity["video_info"]["variants"]:
                                        variant_entity_file.write(len(json.dumps(media_entity["video_info"]["variants"])))

                        additional_media_infoLength=0
                        if media_entity.get("additional_media_info"):
                            if media_entity["additional_media_info"] is not None:
                                additional_media_infoLength=len(json.dumps(media_entity["additional_media_info"]))
                        media_entity_file.write(str(sizesLength)+"#"+str(video_infoLength)+"#"+str(additional_media_infoLength)+"\n")


            # get urls list and calc each object size:
            if tweet['entities'].get("urls") :
                urlsCount=len(tweet['entities']["urls"])
                for url in tweet['entities']["urls"]:
                    urls_file.write(str(len(json.dumps(url)))+"\n")

            # get user_mentions list and calc each object size:
            if tweet['entities'].get("user_mentions") :
                user_mentionsCount=len(tweet['entities']["user_mentions"])
                for user_mention in tweet['entities']["user_mentions"]:
                    user_mentions_file.write(str(len(json.dumps(user_mention)))+"\n")

            # get symbols list and calc each object size:
            if tweet['entities'].get("symbols") :
                symbolsCount=len(tweet['entities']["symbols"])
                for symbol in tweet['entities']["symbols"]:
                    symbols_file.write(str(len(json.dumps(symbol)))+"\n")

            # get polls list and calc each object size:
            if tweet['entities'].get(" polls") :
                pollsCount=len(tweet['entities'][" polls"])
                for poll in tweet['entities']["polls"]:
                    polls_file.write(str(len(json.dumps(poll)))+"\n")
                    for poll_entity in poll:
                        optionsCount = 0
                        if poll_entity.get("options"):
                            if poll_entity["options"] is not None:
                                optionsCount = len(poll_entity["options"])
                        poll_entity_object_count_file.write(str(optionsCount)+"\n")

        extended_entitiesLength = 0
        if tweet.get('extended_entities'):
            if tweet['extended_entities'] is not None:
             extended_entitiesLength = len(json.dumps(tweet["extended_entities"]))

        #tweet log:
        tweetLog=str(tweetsLength)+"#"+str(usersLength)+"#"+str(coordinatesLength)+"#"+str(placeLength)+"#"+str(quoted_statusLength)+"#"+str(retweeted_statusLength)+"#"+str(entitiesLength)+"#"+str(extended_entitiesLength)+"\n"
        tweet_file.write(tweetLog)

        #place log:
        if bounding_boxLength>0:
            placeLog=str(bounding_boxLength)+"\n"
            place_file.write(placeLog)

        # entities object count log:
        entitiesObjectCountLog=str(hashtagsCount)+"#"+str(mediaCount)+"#"+str(urlsCount)+"#"+str(user_mentionsCount)+"#"+str(symbolsCount)+"#"+str(pollsCount)+"\n"
        if entitiesObjectCountLog!="0#0#0#0#0#0\n":
            entities_object_count_file.write(entitiesObjectCountLog)
        #print(tweetLog)

tweet_file.close()
place_file.close()
entities_object_count_file.close()
hashtags_file.close()
media_file.close()
urls_file.close()
user_mentions_file.close()
symbols_file.close()
polls_file.close()
media_entity_file.close()
media_size_entity_file.close()
video_entity_count_file.close()
variant_entity_file.close()