
library(extrafont);
loadfonts();

# 8 figures arranged in 2 rows and 4 columns
data <- read.delim("/home/saeed/Documents/Projects/1-Research/GitHub/serialization/Java/bin/benchmark/result_data_sd.txt", header=TRUE, sep="#")


pdf("Data_Overview.pdf", height=5, width=9,family="Helvetica");
#pdf(file='Data_Overview.pdf',height=3.5, width=4.5,family="Helvetica")
par(mfrow=c(2,4),oma=c(0,0,0,0),mar=c(2.9,3,1.5,0.5))
#Row########
#------------
# Tweets
#------------
mTweets<-mean(data$Tweets)
sdTweets<-sqrt(var(data$Tweets))
hist(data$Tweets, density=20, prob=TRUE, main="tweets",cex.main=0.7,lwd=1,pch=15,xaxs="i", yaxs="i")
curve(dnorm(x, mean=mTweets, sd=sdTweets), add=TRUE)

musers<-mean(data$users)
sdusers<-sqrt(var(data$users))
hist(data$users, density=20, prob=TRUE, main="users",cex.main=0.7,lwd=1,pch=15,xaxs="i", yaxs="i")
curve(dnorm(x, mean=musers, sd=sdusers), add=TRUE)

filtered_data<-data[data[, "coordinates"] >0,]
data_coordinates=filtered_data$coordinates
mcoordinates<-mean(data_coordinates)
sdcoordinates<-sqrt(var(data_coordinates))
hist(data_coordinates, density=20, prob=TRUE, main="coordinates",cex.main=0.7,lwd=1,pch=15,xaxs="i", yaxs="i")
curve(dnorm(x, mean=mcoordinates, sd=sdcoordinates), add=TRUE)

filtered_data<-data[data[, "place"] >0,]
data_place=filtered_data$place
mplace<-mean(data_place)
sdplace<-sqrt(var(data_place))
hist(data_place, density=20, prob=TRUE, main="place",cex.main=0.7,lwd=1,pch=15,xaxs="i", yaxs="i")
curve(dnorm(x, mean=mplace, sd=sdplace), add=TRUE)

filtered_data<-data[data[, "quoted_status"] >0,]
data_quoted_status=filtered_data$quoted_status
mquoted_status<-mean(data_quoted_status)
sdquoted_status<-sqrt(var(data_quoted_status))
hist(data_quoted_status, density=20, prob=TRUE, main="quoted_status",cex.main=0.7,lwd=1,pch=15,xaxs="i", yaxs="i")
curve(dnorm(x, mean=mquoted_status, sd=sdquoted_status), add=TRUE)

filtered_data<-data[data[, "retweeted_status"] >0,]
data_retweeted_status=filtered_data$retweeted_status
mretweeted_status<-mean(data_retweeted_status)
sdretweeted_status<-sqrt(var(data_retweeted_status))
hist(data_retweeted_status, density=20, prob=TRUE, main="retweeted_status",cex.main=0.7,lwd=1,pch=15,xaxs="i", yaxs="i")
curve(dnorm(x, mean=mretweeted_status, sd=sdretweeted_status), add=TRUE)

filtered_data<-data[data[, "entities"] >0,]
data_entities=filtered_data$entities
mentities<-mean(data_entities)
sdentities<-sqrt(var(data_entities))
hist(data_entities, density=20, prob=TRUE, main="entities",cex.main=0.7,lwd=1,pch=15,xaxs="i", yaxs="i")
curve(dnorm(x, mean=mentities, sd=sdentities), add=TRUE)

filtered_data<-data[data[, "extended_entities"] >0,]
data_extended_entities=filtered_data$extended_entities
mextended_entities<-mean(data_extended_entities)
sdextended_entities<-sqrt(var(data_extended_entities))
hist(data_extended_entities, density=20, prob=TRUE, main="extended_entities",cex.main=0.7,lwd=1,pch=15,xaxs="i", yaxs="i")
curve(dnorm(x, mean=mextended_entities, sd=sdextended_entities), add=TRUE)






