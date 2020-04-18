library(plyr)
require(stats)



datajo <- read.delim("data/Java_Results/readobjects/result_java_readobjects_4000000_1.txt", header=TRUE, sep="#")
dataco <- read.delim("data/C_Results/readobjects/result_cpp_readobjects_4000000_1.txt", header=TRUE, sep="#")


dataj <- subset(datajo,seq=="true" & taskset=="true" & datatype=="TweetStatus")
datac <- subset(dataco,seq=="true" & taskset=="true" & datatype=="TweetStatus")


data <- rbind(datac,dataj)


#print(data)

#colors=c("darkblue", "green4") 
colors=c("gray83", "gray95") 


totaltime <- data$totaltime
iotime <- data$iotime
cputime <- totaltime - iotime
#print("--------------------------")
#print(totaltime)

values <- matrix( c(iotime, cputime), nrow = 2, ncol = 11, byrow = TRUE)
#values <- matrix(c(iotime, cputime), nrow = 2, ncol = 4, byrow = TRUE)
#values <- matrix(c(iotime, cputime))

#print(values)

regions <- c("IO Time", "CPU Time")
xnames = data$method#c("C++ HandCoded", "C++ InPlace","C++ Boost","C++ Protocol","C++ BSON","Java Default","Java JSON","Java BSON","Java Protocol","Java Kryo","Java ByteBuffer")


#################################################
#######     Bar         #########################
#################################################
pdf(file='Experiment_ReadObjects_Sequential_Bar_TaskSet.pdf', family="Helvetica")

old.par<-par(mfrow=c(1, 2), oma=c(1.2, 1.3, 0.0, 0.0),  pty="m")
par(mar = c(5, 2.5, 1, 0) + 0.1) 

max_y<-max(totaltime)
max_y<-max_y+max_y*0.1;
min_y<-min(totaltime)/3 #max(min(totaltime)-min(totaltime)/2,50)

p1 <- barplot(values, log="y", col=colors, ylim = c(min_y,  max(totaltime,na.rm = TRUE)+max_y/2.5), legend.text=TRUE, axes=FALSE)

z<-totaltime[sort.list(totaltime)]
z <-c(min_y,z[-6],max_y)

axis(2, las=1, at = z, labels=round(z, digits=0),  cex.axis = 0.7, font = 1)

text(x=p1, y=totaltime+totaltime*0.1, font = 2, font.lab = 2, labels=round(totaltime, 1), pos=3, xpd=NA, cex=0.7,srt=90)


text(x=p1[c(-1,-2)], y=totaltime[c(-1,-2)]-totaltime[c(-1,-2)]*0.18, font = 1, font.lab = 2, labels=round(cputime[c(-1,-2)], 1), pos=3, xpd=NA, cex=0.6,srt=90)
text(x=p1, y=iotime-iotime*0.18, font = 1, font.lab = 2, labels=round(iotime, 1), pos=3, xpd=NA, cex=0.6,srt=90)
box()
text(x=p1+0.1,  y=min_y-min_y/3, xnames, xpd=NA, srt=90, pos=3,  cex=0.6)
title(xlab = "Task Set is True",  cex.lab = 0.9, line = 4, cex=0.9, font=2)

##############################################################
##################                   #########################
##################      Next Bar     #########################
##################                   #########################
##############################################################

dataj <- subset(datajo,seq=="true" & taskset=="false" & datatype=="TweetStatus")
datac <- subset(dataco,seq=="true" & taskset=="false" & datatype=="TweetStatus")


data <- rbind(datac,dataj)

totaltime <- data$totaltime
iotime <- data$iotime
cputime <- totaltime - iotime
#print("--------------------------")
#print(totaltime)

values <- matrix( c(iotime, cputime), nrow = 2, ncol = 11, byrow = TRUE)

max_y<-max(totaltime)
max_y<-max_y+max_y*0.1;
min_y<-min(totaltime)/3 #max(min(totaltime)-min(totaltime)/2,50)
#tick_list=c(min_y,0.3,0.6,1,2,3, 8,15, 25, 45,  80, 110, 200,370,570,800,1200,max_y)


p1 <- barplot(values, log="y", col=colors, ylim = c(min_y,  max(totaltime,na.rm = TRUE)+max_y/2), legend.text=TRUE, axes=FALSE)

z<-totaltime[sort.list(totaltime)]
z <-c(min_y,z[c(-2,-3,-7,-8)],max_y)

axis(2, las=1, at = z, labels=round(z, digits=0),  cex.axis = 0.7, font = 1)
#labs <- paste(min_y,names(totaltime), xnames)


text(x=p1, y=totaltime+totaltime*0.1, font = 2, font.lab = 2, labels=round(totaltime, 1), pos=3, xpd=NA, cex=0.7,srt=90)

text(x=p1[c(-1,-2)], y=totaltime[c(-1,-2)]-totaltime[c(-1,-2)]*0.18, font = 1, font.lab = 2, labels=round(cputime[c(-1,-2)], 1), pos=3, xpd=NA, cex=0.6,srt=90)
text(x=p1, y=iotime-iotime*0.18, font = 1, font.lab = 2, labels=round(iotime, 1), pos=3, xpd=NA, cex=0.6,srt=90)

text(x=p1+0.1,  y=min_y-min_y/3.5, xnames, xpd=NA, srt=90, pos=3,  cex=0.6)

box()
legend("topright", regions, cex = 0.8, fill = colors)
#title(ylab = "Time (second)- log",  cex.lab = 1.2, line = 3.5, cex=1, font=2)
title(xlab = "Task Set is False",  cex.lab = 0.9, line = 4, cex=0.9, font=2)

mtext("Total Reading Time (sec) - log", outer = TRUE, cex = 1, font=0.7,side=2,family="Helvetica",line = -0.1, col=rgb(0,0.5,0) )
mtext("Sequential Read Objects for 4M Tweets", outer = TRUE, cex = 1, font=0.7,side=1,family="Helvetica" ,line = -0.1,col=rgb(0,0.5,0))

