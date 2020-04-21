library(plyr)
require(stats)

datajo <- read.delim("data/Java_Results/readobjects/result_java_readobjects_5000000_1.txt", header=TRUE, sep="#")
dataco <- read.delim("data/C_Results/readobjects/result_cpp_readobjects_5000000_1.txt", header=TRUE, sep="#")


dataj <- subset(datajo,seq=="false"  & datatype=="TweetStatus")
datac <- subset(dataco,seq=="false" & datatype=="TweetStatus")


data <- rbind(datac,dataj)

javaDefault <- subset(data, method=="Java Default")
javaJson <- subset(data, method=="Java Json")
javaBson <- subset(data, method=="Java Bson")
javaKryo <- subset(data, method=="Java Kryo")
javaByteBuffer <- subset(data, method=="Java Byte Buffer")
javaProtoBuf <- subset(data, method=="Java ProtoBuf")
cppHandCoded <- subset(data, method=="C++ HandCoded")
cppInPlace <- subset(data, method=="C++ inPlace")
cppBoost <- subset(data, method=="C++ Boost")
cppProtoBuf <- subset(data, method=="C++ ProtoBuf")
cppBson <- subset(data, method=="C++ Bson")

data <- rbind(cppHandCoded,cppInPlace,cppBoost,cppProtoBuf,cppBson,javaDefault,javaJson,javaBson,javaKryo,javaByteBuffer,javaProtoBuf)

datatasksettrue<-subset(data, taskset=="true")
datatasksetfalse<-subset(data, taskset=="false")

#print(data)

#xlabel<-data$method
#xlabel<-xlabel[duplicated(xlabel),]
#xlabel<-data$method
#xlabel<-distinct(xlabel)
#print(xlabel)

#colors=c("darkblue", "green4") 
colorstasksettrue=c("Misty Rose", "Snow") 
colorstasksetfalse=c("darkseagreen1", "Honeydew") 

regionscolors<-c(colorstasksettrue[1],colorstasksettrue[2],colorstasksetfalse[1],colorstasksetfalse[2])

totaltimetasksettrue <- datatasksettrue$totaltime/60
iotimetasksettrue <- datatasksettrue$iotime/60
cputimetasksettrue <- totaltimetasksettrue - iotimetasksettrue

totaltimetasksetfalse <- datatasksetfalse$totaltime/60
iotimetasksetfalse <- datatasksetfalse$iotime/60
cputimetasksetfalse <- totaltimetasksetfalse - iotimetasksetfalse

#print("--------------------------")
#print(totaltime)

valuestasksettrue <- matrix( c(iotimetasksettrue, cputimetasksettrue), nrow = 2, ncol = 11, byrow = TRUE)
valuestasksetfalse <- matrix( c(iotimetasksetfalse, cputimetasksetfalse), nrow = 2, ncol = 11, byrow = TRUE)
#values <- matrix(c(iotime, cputime), nrow = 2, ncol = 4, byrow = TRUE)
#values <- matrix(c(iotime, cputime))

#print(values)

regions <- c("IO Time(taskset true)", "CPU Time(taskset true)","IO Time(taskset false)", "CPU Time(taskset false)")
xnamestasksettrue = datatasksettrue$method
xnamestasksetfalse = datatasksetfalse$method


#################################################
#######     Bar         #########################
#################################################
pdf(file='Experiment_ReadObjects_Random_Bar_TaskSet.pdf', family="Helvetica")

#old.par<-par(mfrow=c(1, 2), oma=c(1.2, 1.3, 0.0, 0.0),  pty="m")
old.par<-par( oma=c(1.2, 1.3, 0.0, 0.0),  pty="m")
par(mar = c(4.5, 3.5, 1, 0) + 0.1) 

max_y<-max(totaltimetasksettrue,totaltimetasksetfalse)
max_y<-max_y+max_y*0.1;
min_y<-min(totaltimetasksettrue,totaltimetasksetfalse)/3 

# draw bar plots
p1 <- barplot(valuestasksettrue, log="y", col=colorstasksettrue, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y/2.5), legend.text=TRUE, axes=FALSE,border ="gray" , space=c(0.2,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5))

p2 <- barplot(valuestasksetfalse, log="y", col=colorstasksetfalse, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y/2.5), add=T,border ="gray", space=c(1.4,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5),axes=FALSE)

p<-rbind(p1,p2)

# write y labels:
totaltime<-rbind(totaltimetasksettrue,totaltimetasksetfalse)
z<-totaltime[sort.list(totaltime)]
z <-c(min_y,z[c(-3,-4,-5,-7,-8,-9,-12,-13,-14,-17,-18)],max_y)
axis(2, las=1, at = z, labels=round(z, digits=0),  cex.axis = 0.7, font = 1)

#write data inside of bar plots
iotime<-rbind(iotimetasksettrue,iotimetasksetfalse)
cputime<-rbind(cputimetasksettrue,cputimetasksetfalse)

text(x=p, y=totaltime+totaltime*0.1, font = 2, font.lab = 2, labels=round(totaltime, 1), pos=3, xpd=NA, cex=0.7,srt=90)

text(x=p[c(-1,-2,-3,-4)]+0.2, y=totaltime[c(-1,-2,-3,-4)]-totaltime[c(-1,-2,-3,-4)]*0.15, font = 1, font.lab = 2, labels=round(cputime[c(-1,-2,-3,-4)], 1), pos=3, xpd=NA, cex=0.6,srt=90)
text(x=p+0.2, y=iotime-iotime*0.18, font = 1, font.lab = 2, labels=round(iotime, 1), pos=3, xpd=NA, cex=0.6,srt=90)
box()

lines(x=p[1]-2, y=min_y-min_y/5.5,lwd = 1, col = "grey")
text(x=(p1+p2)/2-2,  y=min_y-min_y/3.4, xnamestasksettrue, xpd=NA, srt=45, pos=3, font=1, cex=0.7)

legend("topleft", regions, cex = 0.8, fill = regionscolors)

mtext("Total Reading Time (minut) - log", outer = TRUE, cex = 1, font=0.7,side=2,family="Helvetica",line = -0.1, col=rgb(0,0.5,0) )
mtext("Random Read Objects for 5M Tweets", outer = TRUE, cex = 1, font=0.7,side=1,family="Helvetica" ,line = -0.1,col=rgb(0,0.5,0))

