library(plyr)
require(stats)

#data <- read.delim("data/Java/externalsort/result_Java_externalsort_1.txt", header=TRUE, sep="#")
datac <- read.delim("data/C_Results/externalsort/result_cpp_externalsort_1.txt", header=TRUE, sep="#")




# data <- read.delim("data/java/externalSort/final3/loging.log_Lineitem_final", header=TRUE, sep="#")
#data <- subset(data,  datatype=="TweetStatus")
#data <- data[c(-6)]

datac <- subset(datac, datatype=="TweetStatus")

# print(data)
# print (datac)

data <- rbind(datac)

print(data)

# Colors JSON, JAVA Default,  BSON , Protocol Buffer, ByteBuffer, KRYO
# colors=c("darkred", "green", "blue", "red", "blue1", "green4") 
# colors=c("darkred", "green4") 
# colors=c("green4", "darkblue") 
colors=c("darkblue", "green4") 

totaltime <- data$totaltime/3600
iotime <- data$iotime/3600
cputime <- totaltime - iotime
print("--------------------------")
print(totaltime)


values <- matrix(c(iotime, cputime), nrow = 2, ncol = 4, byrow = TRUE)
# values <- matrix(c(iotime, cputime))

print(values)

regions <- c("IO Time", "CPU Time")

#xnames = c("Java JSON GZIP",  "Java Default" , "Java BSON" , "Java Protocol", "Java ByteBuffer", "Java Kryo", "C++ HandCoded", "C++ InPlace", "C++ Protocol", "C++ Boost")
xnames = c( "C++ HandCoded", "C++ InPlace",  "C++ Boost","C++ Protocol")

#################################################
#######     Plots       #########################
#################################################
pdf(file='Experiment_ExternalSort.pdf', family="Helvetica")

par(mar = c(7, 6, 1, 0) + 0.1) 

p1 <- barplot(values, log="y", col=colors, ylim = c(0.1,  max(totaltime,na.rm = TRUE)+200), legend.text=TRUE, axes=FALSE)
# p1 <- barplot(values, log="y", col=colors, ylim = c(0.1,  max(totaltime,na.rm = TRUE)+2), legend.text=TRUE, beside=TRUE, axes=FALSE)
#z <- c(0.1, 0.5,2, 5,  15)
z <- c(0.1,5,10,20,40,70,110,170)

# Writes the label of x-axis 
axis(2, las=1, at = z, labels=round(z, digits=1),  cex.axis = 1, font = 1)
print(paste(names(totaltime), xnames))
labs <-paste(names(totaltime), xnames)

# writes the 
text(x=p1, y=totaltime,  font = 1, font.lab = 8, labels=round(totaltime, 1), pos=3, xpd=NA, cex=1)

text(7, 9, cex=1.4, font=2, "External Sort of 10M Objects")
box()
text(x=p1-0.5,  y=0.03, labs, xpd=NA, srt=45, pos=3,  cex=1)
legend("topleft", regions, cex = 1, fill = colors)
title(ylab = "Time (minuts)- log",  cex.lab = 2, line = 3.3, cex=2, font=2)

