
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

rustcount=10
cppcount=12
javacount=14

pdf(file='Experiment_External_Sort_CPU_IO_Bar_10M.pdf',height=2, width=3.5)

datajo = calulateMeanDataTimeBar("data/Java_Results/externalsort/10M_25/result_java_externalsort_",3 ,javacount)
dataco=calulateMeanDataTimeBar("data/C_Results/externalsort/10M_25/result_cpp_externalsort_",3 ,cppcount)
dataro=calulateMeanDataTimeBar("data/Rust_Results/externalsort/10M_25/result_rust_externalsort_",3 ,rustcount)

dataj <- subset(datajo,seq=="true"  & datatype=="TweetStatus")
datac <- subset(dataco,seq=="true" & datatype=="TweetStatus")
datar <- subset(dataro,seq=="true" & datatype=="TweetStatus")

data <- rbind(datac,dataj,datar)

#print(data)

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
rustJson <- subset(data, method=="Rust Json")
rustBincode <- subset(data, method=="Rust Bincode")
rustMessagePack <- subset(data, method=="Rust MessagePack")
rustBson <- subset(data, method=="Rust Bson")
rustFlexBuffers <- subset(data, method=="Rust FlexBuffers")


data <- rbind(cppInPlace,cppHandCoded,cppFlatBuf,cppProtoBuf,cppBoost,cppBson,rustMessagePack,rustBincode,rustJson,rustFlexBuffers,rustBson,javaJson,javaDefault,javaBson,javaKryo,javaProtoBuf,javaByteBuffer,javaFlatBuf)

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


valuestasksettrue <- matrix( c(iotimetasksettrue, cputimetasksettrue), nrow = 2, ncol = 18, byrow = TRUE)
valuestasksetfalse <- matrix( c(iotimetasksetfalse, cputimetasksetfalse), nrow = 2, ncol = 18, byrow = TRUE)

regions <- c("IO Time(taskset true)", "CPU Time(taskset true)","IO Time(taskset false)", "CPU Time(taskset false)")
xnamestasksettrue = datatasksettrue$method
xnamestasksetfalse = datatasksetfalse$method


#################################################
#######     Bar         #########################
#################################################


par(mar = c(1.5, 1.3, 0.1, 0.1)) 


max_y<-max(totaltimetasksettrue,totaltimetasksetfalse)
max_y<-max_y+max_y*0.1;
min_y<-min(iotimetasksettrue,iotimetasksetfalse)/1.3 

# draw bar plots
p1 <- barplot(valuestasksettrue, yaxs="i",xaxs="i", log="y", col=colorstasksettrue,xlim = c(-0.2, 54), ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y), legend.text=TRUE, axes=FALSE,border =colorstasksettrue , space=c(0.2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2))

p2 <- barplot(valuestasksetfalse,yaxs="i", xaxs="i",log="y", col=colorstasksetfalse,xlim = c(-0.2, 54), ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y), add=T,border =colorstasksetfalse, space=c(1.4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2),axes=FALSE)

p<-rbind(p1,p2)

# write y labels:
totaltime<-rbind(totaltimetasksettrue,totaltimetasksetfalse)
z<-rbind(totaltimetasksettrue,totaltimetasksetfalse,iotimetasksettrue,iotimetasksetfalse)
z<-z[sort.list(z)]
z <-c(min_y,z,max_y)
z<-calulateaxes(z,0.5)
axis(2, las=1, at = z, labels=round(z, digits=0),  cex.axis = 0.3, font = 1,lwd=0.5,mgp=c(5, .3, 0),tck = -0.02)

#write data inside of bar plots
iotime<-rbind(iotimetasksettrue,iotimetasksetfalse)
cputime<-rbind(cputimetasksettrue,cputimetasksetfalse)

text(x=p+0.05, y=totaltime-iotime*0.15, font = 2, font.lab = 2, labels=round(totaltime, 2), pos=3, xpd=NA, cex=0.25,srt=90)

text(x=p+0.27, y=totaltime-totaltime*0.5, font = 1, font.lab = 2, labels=round(cputime, 2), pos=3, xpd=NA, cex=0.25,srt=90)
##text(x=p[26]+0.2, y=totaltime[26]-totaltime[26]*0.25, font = 1, font.lab = 2, labels=round(cputime[26], 1), pos=3, xpd=NA, cex=0.45,srt=90)
text(x=p[c(-23,-24)]+0.27, y=iotime[c(-23,-24)]-iotime[c(-23,-24)]*0.45, font = 1, font.lab = 2, labels=round(iotime[c(-23,-24)], 2), pos=3, xpd=NA, cex=0.25,srt=90,col = "white")
box(lwd=0.5)

lines(x=p[1]-2, y=min_y-min_y/5.5,lwd = 1, col = "grey")
text(x=(p1+p2)/2+1.7,  y=min_y-0.17, xnamestasksettrue, xpd=NA, srt=30, pos=2, font=1, cex=0.3)

legend("topleft", regions, cex = 0.3, fill = regionscolors,lwd=0.5,box.lwd=0.3,col = regionscolors,border=regionscolors)


#title(xlab="Sequential Read Objects for 4M Tweets", col.lab=rgb(0,0.5,0),family="Helvetica",cex.lab = 0.5,line = 1.9)
title(ylab="Total Sort Time(minute) - log", col.lab="black",family="Helvetica",cex.lab = 0.4,line = 0.7)

par(xpd=TRUE)