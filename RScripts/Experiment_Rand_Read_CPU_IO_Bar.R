
library(plyr)

calulateMeanDataTimeBar <- function(myfilename,nr, n){
  
  totaltime <- matrix(nrow= nr, ncol=n)
  iotime <- matrix(nrow= nr, ncol=n)
  
  # run for all 5 experiments 
  for(i in 1:nr){
    tfile = paste(myfilename, i,  sep = "")
    tfile <- paste(tfile, ".txt" , sep="")
    mydata <- read.delim(tfile, header=TRUE, sep="#")
    totaltime[i,] <-mydata[['totaltime']]
    iotime[i,] <-mydata[['iotime']]
  }
  
  finalTotalTime <- vector()
  finalIOTime <- vector()
  
  for(j in 1:n){
    tmptotaltime<-0
    tmpiotime<-0
    for(i in 1:nr){
      tmptotaltime= tmptotaltime+totaltime[i,j]   
      tmpiotime= tmpiotime+iotime[i,j] 
    }
    tmptotaltime=tmptotaltime/nr
    tmpiotime=tmpiotime/nr
    
    finalTotalTime[j] <- tmptotaltime
    finalIOTime[j] <- tmpiotime
  }
  mydata$totaltime<-finalTotalTime
  mydata$iotime<-finalIOTime
  
  return(mydata)
}

# function for normalize y-axes data
calulateaxes <- function(data,ts){
  
  resultdata <- vector() 
  resultdata[1]<-round(data[1],2)
  i<-1
  j<-1
  
  listlength<-length(data)
  for (d in data) {
    
    space<-ts
    # space<-1.5
    if(j>listlength*0.75)
      tspace<-space*50
    else if(j>listlength*0.5)
      tspace<-space*15
    else if(j>listlength*0.25)
      tspace<-space*7
    else if(j>listlength*0.15)
      tspace<-space*1.5
    else
      tspace<-space*3
    
    j<-j+1
    
    if(d-resultdata[i]>tspace){
      i<-i+1
      if(d>1)
        resultdata[i]<-round(d)
      else
        resultdata[i]<-round(d,2)
    }
  }
  
  return(resultdata)
}

cppcount=12*2
javacount=14*2

pdf(file='Experiment_Rand_Read_CPU_IO_Bar.pdf',height=3, width=4)

datajo = calulateMeanDataTimeBar("data/Java_Results/readobjects/result_java_readobjects_4000000_",3 ,javacount)
dataco=calulateMeanDataTimeBar("data/C_Results/readobjects/result_cpp_readobjects_4000000_",3 ,cppcount)

dataj <- subset(datajo,seq=="false"  & datatype=="TweetStatus")
datac <- subset(dataco,seq=="false" & datatype=="TweetStatus")

data <- rbind(datac,dataj)

javaDefault <- subset(data, method=="Java Default")
javaJson <- subset(data, method=="Java Json+Gzip")
javaBson <- subset(data, method=="Java Bson")
javaKryo <- subset(data, method=="Java Kryo")
javaByteBuffer <- subset(data, method=="Java Byte Buffer")
javaProtoBuf <- subset(data, method=="Java ProtoBuf")
javaFlatBuf <- subset(data, method=="Java FlatBuffers")
cppHandCoded <- subset(data, method=="C++ HandCoded")
cppInPlace <- subset(data, method=="C++ inPlace")
cppBoost <- subset(data, method=="C++ Boost")
cppProtoBuf <- subset(data, method=="C++ ProtoBuf")
cppBson <- subset(data, method=="C++ Bson")
cppFlatBuf <- subset(data, method=="C++ FlatBuffers")


data <- rbind(cppHandCoded,cppProtoBuf,cppInPlace,cppFlatBuf,cppBoost,cppBson,javaDefault,javaJson,javaBson,javaByteBuffer,javaProtoBuf,javaKryo,javaFlatBuf)

datatasksettrue<-subset(data, taskset=="true")
datatasksetfalse<-subset(data, taskset=="false")

colorstasksettrue=c("gray5", "gray80")#c("Misty Rose", "Snow") 
colorstasksetfalse=c("gray30", "gray91") 

regionscolors<-c(colorstasksettrue[1],colorstasksettrue[2],colorstasksetfalse[1],colorstasksetfalse[2])

totaltimetasksettrue <- datatasksettrue$totaltime/60
iotimetasksettrue <- datatasksettrue$iotime/60
cputimetasksettrue <- totaltimetasksettrue - iotimetasksettrue

totaltimetasksetfalse <- datatasksetfalse$totaltime/60
iotimetasksetfalse <- datatasksetfalse$iotime/60
cputimetasksetfalse <- totaltimetasksetfalse - iotimetasksetfalse


valuestasksettrue <- matrix( c(iotimetasksettrue, cputimetasksettrue), nrow = 2, ncol = 13, byrow = TRUE)
valuestasksetfalse <- matrix( c(iotimetasksetfalse, cputimetasksetfalse), nrow = 2, ncol = 13, byrow = TRUE)

regions <- c("IO Time(taskset true)", "CPU Time(taskset true)","IO Time(taskset false)", "CPU Time(taskset false)")
xnamestasksettrue = datatasksettrue$method
xnamestasksetfalse = datatasksetfalse$method


#################################################
#######     Bar         #########################
#################################################

#old.par<-par(mfrow=c(1, 2), oma=c(1.2, 1.3, 0.0, 0.0),  pty="m")
#old.par<-par( oma=c(1.2, 1.3, 0.0, 0.0),  pty="m")
par(mar = c(1.8, 2.5, 0.1, 0.1)) 

max_y<-max(totaltimetasksettrue,totaltimetasksetfalse)
max_y<-max_y+max_y*0.1;
min_y<-min(iotimetasksettrue,iotimetasksetfalse)/1.3 

# draw bar plots
p1 <- barplot(valuestasksettrue, yaxs="i", log="y", col=colorstasksettrue, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y*1.5), legend.text=TRUE, axes=FALSE,border =colorstasksettrue , space=c(0.2,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5))

p2 <- barplot(valuestasksetfalse,yaxs="i", log="y", col=colorstasksetfalse, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y*1.5), add=T,border =colorstasksettrue, space=c(1.4,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5),axes=FALSE)

p<-rbind(p1,p2)

# write y labels:
totaltime<-rbind(totaltimetasksettrue,totaltimetasksetfalse)
z<-rbind(totaltimetasksettrue,totaltimetasksetfalse,iotimetasksettrue,iotimetasksetfalse)
z<-z[sort.list(z)]
z <-c(min_y,z,max_y)
z<-calulateaxes(z,1.2)
axis(2, las=1, at = z, labels=round(z, digits=0),  cex.axis = 0.5, font = 1,mgp=c(3, .6, 0))

#write data inside of bar plots
iotime<-rbind(iotimetasksettrue,iotimetasksetfalse)
cputime<-rbind(cputimetasksettrue,cputimetasksetfalse)

text(x=p+0.2, y=totaltime+totaltime*0.1, font = 2, font.lab = 2, labels=round(totaltime, 1), pos=3, xpd=NA, cex=0.35,srt=90)

#text(x=p[c(-5,-6)]+0.27, y=totaltime[c(-5,-6)]-totaltime[c(-5,-6)]*0.34, font = 1, font.lab = 2, labels=round(cputime[c(-5,-6)], 1), pos=3, xpd=NA, cex=0.3,srt=90)
#text(x=p[26]+0.2, y=totaltime[26]-totaltime[26]*0.25, font = 1, font.lab = 2, labels=round(cputime[26], 1), pos=3, xpd=NA, cex=0.45,srt=90)
text(x=p+0.2, y=iotime-iotime*0.29, font = 1, font.lab = 2, labels=round(iotime, 1), pos=3, xpd=NA, cex=0.3,srt=90,col = "white")
box()

lines(x=p[1]-2, y=min_y-min_y/5.5,lwd = 1, col = "grey")
text(x=(p1+p2)/2+1.7,  y=min_y-1, xnamestasksettrue, xpd=NA, srt=30, pos=2, font=1, cex=0.4)

legend("topleft", regions, cex = 0.4, fill = regionscolors,col = regionscolors,border=regionscolors,box.lwd=0.5)


#title(xlab="Random Read Objects for 4M Tweets", col.lab=rgb(0,0.5,0),family="Helvetica",cex.lab = 0.5,line = 1.9)
title(ylab="Total Random Read Time (minut) - log", col.lab="black",family="Helvetica",cex.lab = 0.6,line = 1.9)

par(xpd=TRUE)