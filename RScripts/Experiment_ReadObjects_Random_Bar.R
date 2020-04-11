library(plyr)
require(stats)



dataj <- read.delim("data/Java_Results/readobjects/result_java_readobjects_4000000_1.txt", header=TRUE, sep="#")
datac <- read.delim("data/C_Results/readobjects/result_cpp_readobjects_4000000_1.txt", header=TRUE, sep="#")


dataj <- subset(dataj,seq=="false" & datatype=="TweetStatus")
datac <- subset(datac,seq=="false" & datatype=="TweetStatus")


data <- rbind(datac,dataj)

#print(data)

colors=c("darkblue", "green4") 

totaltime <- data$totaltime/60
iotime <- data$iotime/60
cputime <- totaltime - iotime
#print("--------------------------")
#print(totaltime)

values <- matrix( c(iotime, cputime), nrow = 2, ncol = 11, byrow = TRUE)
#values <- matrix(c(iotime, cputime), nrow = 2, ncol = 4, byrow = TRUE)
#values <- matrix(c(iotime, cputime))

#print(values)

regions <- c("IO Time", "CPU Time")
xnames = c("C++ HandCoded", "C++ InPlace","C++ BSON","C++ Protocol","C++ Boost","Java Default","Java JSON","Java BSON","Java Protocol","Java Kryo","Java ByteBuffer")


#################################################
#######     Plots       #########################
#################################################
pdf(file='Experiment_ReadObjects_Random_Bar.pdf', family="Helvetica")

par(mar = c(7, 4, 1, 0) + 0.1) 

max_y<-max(totaltime)+2
min_y<-5#max(min(totaltime)-1,1)
#tick_list=c(min_y,0.3,0.6,1,2,3, 8,15, 25, 45,  80, 110, 200,370,570,800,1200,max_y)


p1 <- barplot(values, log="y", col=colors, ylim = c(min_y,  max(totaltime,na.rm = TRUE)+150), legend.text=TRUE, axes=FALSE)

z <-c(5,7,15,30,45,60,75,90,120,150,180,210)
#print(z)

axis(2, las=1, at = z, labels=round(z, digits=1),  cex.axis = 1, font = 1)
labs <- paste(names(totaltime), xnames)


text(x=p1, y=totaltime, font = 1, font.lab = 2, labels=round(totaltime, 1), pos=3, xpd=NA, cex=0.8)

#text(7, -1, cex=1.2, font=2, "External Sort of 3M Customer Objects")
box()
text(x=p1-0.7,  y=3, labs, xpd=NA, srt=45, pos=3,  cex=1)
legend("topleft", regions, cex = 1, fill = colors)
title(ylab = "Time (minuts)- log",  cex.lab = 1.2, line = 2.5, cex=1, font=1,col.lab=rgb(0,0.5,0))
title(xlab = "Random Read Objects for 4M Tweets",  cex.lab = 1.2, line = 5.3, cex=1, font=1,col.lab=rgb(0,0.5,0))

