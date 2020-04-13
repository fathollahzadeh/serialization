
library(extrafont);
loadfonts();

data <- read.delim("data/DataOverview/tweet.txt", header=TRUE, sep="#")


pdf("Data_Overview.pdf", height=3.5, width=7.5,family="Helvetica");
#pdf(file='Data_Overview.pdf',height=3.5, width=4.5,family="Helvetica")
par(mfrow=c(2,7),mar=c(2.9,3,1.5,0.5),oma = c(0.9, 0.8, 0, 0))



#------------
# Tweets
#------------
mTweets<-mean(data$Tweets)
sdTweets<-sqrt(var(data$Tweets))
hist(data$Tweets, density=20, prob=TRUE, main="tweets",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=mTweets, sd=sdTweets), add=TRUE,col="blue")

musers<-mean(data$users)
sdusers<-sqrt(var(data$users))
hist(data$users, density=20, prob=TRUE, main="users",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=musers, sd=sdusers), add=TRUE,col="blue")

filtered_data<-data[data[, "coordinates"] >0,]
data_coordinates=filtered_data$coordinates
mcoordinates<-mean(data_coordinates)
sdcoordinates<-sqrt(var(data_coordinates))
hist(data_coordinates, density=20, prob=TRUE, main="coordinates",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=mcoordinates, sd=sdcoordinates), add=TRUE,col="blue")

filtered_data<-data[data[, "place"] >0,]
data_place=filtered_data$place
mplace<-mean(data_place)
sdplace<-sqrt(var(data_place))
hist(data_place, density=20, prob=TRUE, main="place",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=mplace, sd=sdplace), add=TRUE,col="blue")

filtered_data<-data[data[, "quoted_status"] >0,]
data_quoted_status=filtered_data$quoted_status
mquoted_status<-mean(data_quoted_status)
sdquoted_status<-sqrt(var(data_quoted_status))
hist(data_quoted_status, density=20, prob=TRUE, main="quoted_status",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=mquoted_status, sd=sdquoted_status), add=TRUE,col="blue")

filtered_data<-data[data[, "retweeted_status"] >0,]
data_retweeted_status=filtered_data$retweeted_status
mretweeted_status<-mean(data_retweeted_status)
sdretweeted_status<-sqrt(var(data_retweeted_status))
hist(data_retweeted_status, density=20, prob=TRUE, main="retweeted_status",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=mretweeted_status, sd=sdretweeted_status), add=TRUE,col="blue")

filtered_data<-data[data[, "entities"] >0,]
data_entities=filtered_data$entities
mentities<-mean(data_entities)
sdentities<-sqrt(var(data_entities))
hist(data_entities, density=20, prob=TRUE, main="entities",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=mentities, sd=sdentities), add=TRUE,col="blue")

filtered_data<-data[data[, "extended_entities"] >0,]
data_extended_entities=filtered_data$extended_entities
mextended_entities<-mean(data_extended_entities)
sdextended_entities<-sqrt(var(data_extended_entities))
hist(data_extended_entities, density=20, prob=TRUE, main="extended_entities",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=mextended_entities, sd=sdextended_entities), add=TRUE,col="blue")


#------------
# Entities
#------------
data_hashtags <- read.delim("data/DataOverview/hashtags.txt", header=TRUE, sep="#")
data_hashtags <-data_hashtags$hashtags
mhashtags<-mean(data_hashtags)
sdhashtags<-sqrt(var(data_hashtags))
hist(data_hashtags, density=20, prob=TRUE, main="hashtags",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=mhashtags, sd=sdhashtags), add=TRUE,col="blue")

data_media <- read.delim("data/DataOverview/media.txt", header=TRUE, sep="#")
data_media <-data_media$medias
mmedia<-mean(data_media)
sdmedia<-sqrt(var(data_media))
hist(data_media, density=20, prob=TRUE, main="media",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=mmedia, sd=sdmedia), add=TRUE,col="blue")

data_urls <- read.delim("data/DataOverview/urls.txt", header=TRUE, sep="#")
data_urls <-data_urls$urls
murls<-mean(data_urls)
sdurls<-sqrt(var(data_urls))
hist(data_urls, density=20, prob=TRUE, main="urls",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=murls, sd=sdurls), add=TRUE,col="blue")

data_user_mentions <- read.delim("data/DataOverview/user_mentions.txt", header=TRUE, sep="#")
data_user_mentions <-data_user_mentions$user_mentions
muser_mentions<-mean(data_user_mentions)
sduser_mentions<-sqrt(var(data_user_mentions))
hist(data_user_mentions, density=20, prob=TRUE, main="user_mentions",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=muser_mentions, sd=sduser_mentions), add=TRUE,col="blue")

data_symbols <- read.delim("data/DataOverview/symbols.txt", header=TRUE, sep="#")
data_symbols <-data_symbols$symbols
msymbols<-mean(data_symbols)
sdsymbols<-sqrt(var(data_symbols))
hist(data_symbols, density=20, prob=TRUE, main="symbols",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=msymbols, sd=sdsymbols), add=TRUE,col="blue")


# Media entity

data_media_entity <- read.delim("data/DataOverview/media_entity.txt", header=TRUE, sep="#")
data_media_entity <-data_media_entity$sizes
mmedia_entity<-mean(data_media_entity)
sdmedia_entity<-sqrt(var(data_media_entity))
hist(data_media_entity, density=20, prob=TRUE, main="sizes",cex.main=0.7,lwd=1,pch=150,xaxs="i", yaxs="i",cex.axis=0.6,las=2,col =rgb(0.1,0.1,0.1,0.5))
curve(dnorm(x, mean=mmedia_entity, sd=sdmedia_entity), add=TRUE,col="blue")

mtext("Dencity", outer = TRUE, cex = 0.6, font=0.7,side=2,family="Helvetica" )
mtext("Number od Data", outer = TRUE, cex = 0.6, font=0.7,side=1,family="Helvetica" )

# media sizes entity
data_media_size_entity <- read.delim("data/DataOverview/media_size_entity.txt", header=TRUE, sep="#")


# print avg and count values:

print(sprintf("avg tweet= %s", mTweets))
print(sprintf("tweet count=%s",length(data$Tweets)))

print(sprintf("avg users= %s", musers))
print(sprintf("users count=%s",length(data$users)))

print(sprintf("avg coordinates= %s", mcoordinates))
print(sprintf("coordinates count=%s",length(data_coordinates)))

print(sprintf("avg place= %s", mplace))
print(sprintf("place count=%s",length(data_place)))

print(sprintf("avg quoted_status= %s", mquoted_status))
print(sprintf("quoted_status count=%s",length(data_quoted_status)))

print(sprintf("avg retweeted_status= %s", mretweeted_status))
print(sprintf("tweet retweeted_status=%s",length(data_retweeted_status)))

print(sprintf("avg entities= %s", mentities))
print(sprintf("entities count=%s",length(data_entities)))

print(sprintf("avg extended_entities= %s", mextended_entities))
print(sprintf("extended_entities count=%s",length(data_extended_entities)))

# entities objects
print(sprintf("avg hashtags= %s", mhashtags))
print(sprintf("hashtags count=%s",length(data_hashtags)))

print(sprintf("avg media= %s", mmedia))
print(sprintf("media count=%s",length(data_media)))

print(sprintf("avg urls= %s", murls))
print(sprintf("urls count=%s",length(data_urls)))

print(sprintf("avg user_mentions= %s", muser_mentions))
print(sprintf("user_mentions count=%s",length(data_user_mentions)))

print(sprintf("avg symbols= %s", msymbols))
print(sprintf("symbols count=%s",length(data_symbols)))

# media entity
print(sprintf("avg sizes= %s", mmedia_entity))
print(sprintf("sizes count=%s",length(data_media_entity)))

#media sizes entity


mthumb<-mean(data_media_size_entity$thumb)
print(sprintf("avg thumb= %s", mthumb))
print(sprintf("thumb count=%s",length(data_media_size_entity$thumb)))


mlarge<-mean(data_media_size_entity$large)
print(sprintf("avg large= %s", mlarge))
print(sprintf("large count=%s",length(data_media_size_entity$large)))


mmedium<-mean(data_media_size_entity$medium)
print(sprintf("avg medium= %s", mmedium))
print(sprintf("medium count=%s",length(data_media_size_entity$medium)))


msmall<-mean(data_media_size_entity$small)
print(sprintf("avg small= %s", msmall))
print(sprintf("small count=%s",length(data_media_size_entity$small)))


print(sprintf("avg size entity= %s", mmedia_entity))
print(sprintf("size entity count=%s",length(data_media_entity)))










