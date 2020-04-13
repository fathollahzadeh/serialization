library(plyr)
require(stats)



dataj <- read.delim("data/Java_Results/readobjects/result_java_readobjects_4000000_1.txt", header=TRUE, sep="#")
datac <- read.delim("data/C_Results/readobjects/result_cpp_readobjects_4000000_1.txt", header=TRUE, sep="#")


dataj <- subset(dataj,seq=="true" & datatype=="TweetStatus")
datac <- subset(datac,seq=="true" & datatype=="TweetStatus")


data <- rbind(datac,dataj)

print(data)

#colors=c("darkblue", "green4") 
colors=c("darkgray", "gray87") 


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
#######     Plots       #########################
#################################################
pdf(file='Experiment_ReadObjects_Sequential_Bar.pdf', family="Helvetica")

par(mar = c(7, 4.5, 1, 0) + 0.1) 

max_y<-max(totaltime)+50
min_y<-min(totaltime)/3 #max(min(totaltime)-min(totaltime)/2,50)
#tick_list=c(min_y,0.3,0.6,1,2,3, 8,15, 25, 45,  80, 110, 200,370,570,800,1200,max_y)


p1 <- barplot(values, log="y", col=colors, ylim = c(min_y,  max(totaltime,na.rm = TRUE)+400), legend.text=TRUE, axes=FALSE)

z <-c(min_y,19,30,56,167,364,450,553,1045,max_y)
#z<-seq(min_y,max_y,(max_y-min_y)/10)

axis(2, las=1, at = z, labels=round(z, digits=0),  cex.axis = 1, font = 1)
#labs <- paste(min_y,names(totaltime), xnames)


text(x=p1, y=totaltime, font = 2, font.lab = 2, labels=round(totaltime, 1), pos=3, xpd=NA, cex=0.8)
#tm<-c(8,40,10,100,100,100,100,100,100,100)

text(x=p1[-2], y=totaltime[-2]-totaltime[-2]*0.3, font = 1, font.lab = 2, labels=round(cputime[-2], 1), pos=3, xpd=NA, cex=0.7)
text(x=p1, y=iotime-iotime*0.2, font = 1, font.lab = 2, labels=round(iotime, 1), pos=3, xpd=NA, cex=0.7)

#text(7, -1, cex=1.2, font=2, "External Sort of 3M Customer Objects")

#filesize<-c("(11 G)","(16 G)","(11 G)","(9.3 G)","(23 G)","(23 G)","(6.6 G)","(25 G)","(9.5 G)","(9.1 G)","(12 G)")
box()
text(x=p1-0.7,  y=min_y-3, xnames, xpd=NA, srt=45, pos=3,  cex=0.9)
#text(x=p1+0.2,  y=min_y-min(totaltime)-10, filesize, xpd=NA, srt=90, pos=3,  cex=0.8)

legend("topright", regions, cex = 1, fill = colors)
title(ylab = "Time (second)- log",  cex.lab = 1.2, line = 3.5, cex=1, font=2)
title(xlab = "Sequential Read Objects for 4M Tweets",  cex.lab = 1.2, line = 5, cex=1, font=2)

