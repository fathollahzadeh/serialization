
library(plyr)
# library(ggplot2)
# require(cowplot)


# function definition for calculating mean of data
calulateMeanDataTotaltime <- function(myfilename,nr, n){
  
  totaltime <- matrix(nrow= nr, ncol=n)
 
  # run for all 5 experiments 
  for(i in 1:nr){
    tfile = paste(myfilename, i,  sep = "")
    tfile <- paste(tfile, ".txt" , sep="")
    mydata <- read.delim(tfile, header=TRUE, sep="#")
    totaltime[i,] <-mydata[['totaltime']]- mydata[['iotime']]
  }
  
  finalTime <- vector() 
  
   for(j in 1:n){
      tmp<-0
      for(i in 1:nr){
        tmp= tmp+totaltime[i,j]   
      }
      tmp=tmp/nr
      finalTime[j] <- tmp
    }
    mydata$totaltime<-finalTime
  
  return(mydata)
}

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
    
    if(d<2){
      space<-0.10
      tspace<-space
    }
    else{
      space<-ts
     # space<-1.5
      if(j>listlength*0.75)
        tspace<-space*40
      else if(j>listlength*0.5)
        tspace<-space*15
      else if(j>listlength*0.25)
        tspace<-space*7
      else if(j>listlength*0.15)
        tspace<-space*1.5
      else
        tspace<-space
    }
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

# function for normalize y-axes data
drawPlot <- function(data,isseq,ts,hasshleg){
  #################################################
  #######  Data for Taskset=TRUE  #################
  #################################################
  
  # Java Defaul results
  javaDefault <- subset(data, language="ReadTimeJAVA",  method=="Java Default")
  javaDefaultV <- vector()
  javaDefaultV <-javaDefault[['totaltime']]
  
  # Java Json results 
  javaJson <- subset(data, language="ReadTimeJAVA",  method=="Java Json+Gzip")
  javaJsonV <- vector()
  javaJsonV <-javaJson[['totaltime']]
  
  # Java Bson results 
  javaBson <- subset(data, language="ReadTimeJAVA",  method=="Java Bson")
  javaBsonV <- vector()
  javaBsonV <-javaBson[['totaltime']]
  
  # Java ProtoBuf results 
  javaProtoBuf <- subset(data, language="ReadTimeJAVA", method=="Java ProtoBuf")
  javaProtoBufV <- vector()
  javaProtoBufV <-javaProtoBuf[['totaltime']]
  
  # Java Kryo results 
  javaKryo <- subset(data, language="ReadTimeJAVA",  method=="Java Kryo")
  javaKryoV <- vector()
  javaKryoV <-javaKryo[['totaltime']]
  
  # Java Byte Buffer results 
  javaByteBuffer <- subset(data, language="ReadTimeJAVA", method=="Java Byte Buffer")
  javaByteBufferV <- vector()
  javaByteBufferV <-javaByteBuffer[['totaltime']]
  
  # Java Byte Buffer results 
  javaFlatBuffer <- subset(data, language="ReadTimeJAVA",  method=="Java FlatBuffers")
  javaFlatBufferV <- vector()
  javaFlatBufferV <-javaFlatBuffer[['totaltime']]
  
  
  # C++  HANDCODED  results 
  cppHANDCODED <- subset(data, language="ReadTimeCPP",method=="C++ HandCoded")
  cppHANDCODEDV <- vector()
  cppHANDCODEDV <-cppHANDCODED[['totaltime']]
  
  # C++  PROTOBUF  results 
  cppPROTOBUF <- subset(data, language="ReadTimeCPP", method=="C++ ProtoBuf")
  cppPROTOBUFV <- vector()
  cppPROTOBUFV <-cppPROTOBUF[['totaltime']]
  
  
  # C++  INPLACE  results 
  cppINPLACE <- subset(data, language="ReadTimeCPP", method=="C++ inPlace")
  cppINPLACEV <- vector()
  cppINPLACEV <-cppINPLACE[['totaltime']]
  
  
  # C++  BOOST  results 
  cppBOOST <- subset(data, language="ReadTimeCPP", method=="C++ Boost")
  cppBOOSTV <- vector()
  cppBOOSTV <-cppBOOST[['totaltime']]
  
  # C++  BSON  results 
  cppBSON <- subset(data, language="ReadTimeCPP",  method=="C++ Bson")
  cppBSONV <- vector()
  cppBSONV <-cppBSON[['totaltime']]
  
  # C++  FlatBuffers  results 
  cppFLATBUF <- subset(data, language="ReadTimeCPP", method=="C++ FlatBuffers")
  cppFLATBUFV <- vector()
  cppFLATBUFV <-cppFLATBUF[['totaltime']]
  
  plot_colors <- c("red2", "blue1","green4", "saddlebrown","green", "lightseagreen", "deeppink3", "darkorange", "yellow1" , "gray8","midnightblue","chocolate4","maroon1")
  serialization_methods<-c("Java Default","Java Json+Gzip","Java BSON","Java ProtoBuf","Java Kryo","Java ByteBuffer","Java FlatBuffers","C++ Boost","C++ ProtoBuf",  "C++ HandCoded", "C++ InPlace","C++ BSON","C++ FlatBuffers")
  
  #################################################
  ######################   Plot ###################
  #################################################
 
  
  x <- c(1000000, 2000000,3000000,4000000,5000000)
  totaltimes=c(javaDefaultV[javaDefaultV!=0],javaJsonV[javaJsonV!=0],javaBsonV[javaBsonV!=0],javaProtoBufV[javaProtoBufV!=0],javaKryoV[javaKryoV!=0],
               javaByteBufferV[javaByteBufferV!=0],javaFlatBufferV[javaFlatBufferV!=0],cppHANDCODEDV[cppHANDCODEDV!=0],cppPROTOBUFV[cppPROTOBUFV!=0],
               cppINPLACEV[cppINPLACEV!=0],cppBOOSTV[cppBOOSTV!=0],cppBSONV[cppBSONV!=0],cppFLATBUFV[cppFLATBUFV!=0])  
  max_y<-max(totaltimes)
  max_y<-max_y+max_y*0.1;
  min_y<-min(totaltimes) 
  
  tick_list<-totaltimes[sort.list(totaltimes)]
  tick_list<-calulateaxes(tick_list,4)
  y_labels<- sprintf("%s",tick_list);
 
  javaDefaultV[javaDefaultV==0]<-max_y
  javaJsonV[javaJsonV==0]<-max_y
  javaBsonV[javaBsonV==0]<-max_y
  javaProtoBufV[javaProtoBufV==0]<-max_y
  javaKryoV[javaKryoV==0]<-max_y
  javaByteBufferV[javaByteBufferV==0]<-max_y
  javaFlatBufferV[javaFlatBufferV==0]<-max_y
  cppHANDCODEDV[cppHANDCODEDV==0]<-max_y
  cppPROTOBUFV[cppPROTOBUFV==0]<-max_y
  cppINPLACEV[cppINPLACEV==0]<-max_y
  cppBOOSTV[cppBOOSTV==0]<-max_y
  cppBSONV[cppBSONV==0]<-max_y
  cppFLATBUFV[cppFLATBUFV==0]<-max_y
  
  # Java Deafult
  plot(javaDefaultV, log="y", type="o",cex=0.5, pch=1, lty=2,lwd=0.5, ylim=c(min_y, max_y), axes=FALSE, ann=FALSE,col=plot_colors[1],  panel.first=abline(h= tick_list, v=c(1, 2, 3, 4,5), lty=3, col="gray"))
  
  # Make x axis using one to 5 labels
  axis(1, at=c(1, 2, 3, 4,5), labels=c("1M","2M","3M", "4M","5M"), las=2,cex.axis = 0.5 )
  
  # Make y axis with horizontal labels that display ticks at 
  axis(2, las=1, at = tick_list, labels=y_labels,cex.axis = 0.5)
  
  #lines for Json
  lines(javaJsonV , type="o", pch=2, lty=2,cex=0.5, col=plot_colors[2],lwd=0.5)
  
  #lines for Bson 
  lines(javaBsonV, type="o", pch=3, lty=2,cex=0.5, col=plot_colors[3],lwd=0.5)
  
  #lines for ProtoBuf
  lines(javaProtoBufV, type="o", pch=4, lty=2,cex=0.5, col=plot_colors[4],lwd=0.5)
  
  #lines for Kryo
  lines(javaKryoV, type="o", pch=5, lty=2,cex=0.5, col=plot_colors[5],lwd=0.5)
  
  #lines for ByteBuffer
  lines(javaByteBufferV, type="o", pch=6, lty=2,cex=0.5, col=plot_colors[6],lwd=0.5)
  
  #lines for Java flat buffers
  lines(javaFlatBufferV, type="o", pch=7, lty=2,cex=0.5, col=plot_colors[7],lwd=0.5)
  
  #lines for BOOST C++ 
  lines(cppBOOSTV, type="o", pch=8, lty=2,cex=0.5, col=plot_colors[8],lwd=0.5)
  
  #lines for PROTOBUF C++ 
  lines(cppPROTOBUFV, type="o", pch=9, lty=2,cex=0.5, col=plot_colors[9],lwd=0.5)
  
  #lines for HANDCODED C++ 
  lines(cppHANDCODEDV, type="o", pch=10, lty=2,cex=0.5, col=plot_colors[10],lwd=0.5)
  
  #lines for INPLACE C++ 
  lines(cppINPLACEV, type="o", pch=11, lty=2,cex=0.5, col=plot_colors[11],lwd=0.5)
  
  #lines for BSON C++ 
  lines(cppBSONV, type="o", pch=12, lty=2,cex=0.5, col=plot_colors[12],lwd=0.5)
  
  #lines for Faltbuffers C++ 
  lines(cppFLATBUFV, type="o", pch=13,cex=0.5, lty=2, col=plot_colors[13],lwd=0.5)
  
  xlb<-paste("Number of Objects(task set=", ts ,")", sep="")
  if(isseq){
    
    title(xlab=xlb, col.lab=rgb(0,0.5,0),family="Helvetica",cex.lab = 0.75,line = 1.5)
    title(ylab="Total Seqential Read Time (sec) - log", col.lab=rgb(0,0.5,0),family="Helvetica",cex.lab = 0.75,line = 2.5)
  }
  else{
    title(xlab=xlb, col.lab=rgb(0,0.5,0),family="Helvetica",cex.lab = 0.75,line = 1.5)
    title(ylab="Total Random Read Time (sec) - log", col.lab=rgb(0,0.5,0),family="Helvetica",cex.lab = 0.75,line = 2.5)
  }
  box()
  if(hasshleg){
    legend(3, 13, serialization_methods, cex=0.44,  col=plot_colors, pch=1:13, lty=2:2);
  }
}


cppcount=12*2
javacount=14*2

#Java Results
dataj1 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_1000000_",1 ,javacount)
dataj1$size <-1000000 

# load data for 2M objects read 
dataj2 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_2000000_",1 , javacount)
dataj2$size <-2000000 


# load data for 3M objects read 
dataj3 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_3000000_", 1 ,javacount)
dataj3$size <-3000000 


# load data for 4M objects read 
dataj4 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_4000000_",1 , javacount)
dataj4$size <-4000000


# load data for 5M objects read 
dataj5 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_4000000_",1 , javacount)
dataj5$totaltime<-0
dataj5$iotime<-0
dataj5$size <-5000000

# CPP Results 
##################################################################
# load data for 1M objects read 
datac1 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_1000000_",1 ,cppcount)
datac1$size <-1000000 

# load data for 2M objects read 
datac2 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_2000000_",1 , cppcount)
datac2$size <-2000000 


# load data for 3M objects read 
datac3 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_3000000_", 1 ,cppcount)
datac3$size <-3000000 

# load data for 4M objects read 
datac4 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_4000000_",1 , cppcount)
datac4$size <-4000000

# load data for 5M objects read 
datac5 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_5000000_",1 , cppcount)
datac5$size <-5000000


# bind the data frames together 
plotdata <- rbind(datac1,datac2,datac3,datac4,datac5,dataj1,dataj2,dataj3,dataj4,dataj5)

pdf(file='Experiment_ReadObjects.pdf',height=6, width=7)

m <- matrix(c(1,2,3,4,5,6),nrow = 2,ncol = 3,byrow = TRUE)
layout(mat = m,widths = c(0.26,0.23,0.51),heights = c(0.5,0.5))

par(mar = c(3.5,3.5,0,0.1))
drawPlot(subset(plotdata, taskset=="true" & seq=="true"),TRUE,"true",FALSE)
par(mar = c(3.5,2,0,0.1))
drawPlot(subset(plotdata, taskset=="false" & seq=="true"),TRUE,"false",TRUE)

#################################################
#######  Sequential Read Bar  ###################
#################################################

datajo = calulateMeanDataTimeBar("data/Java_Results/readobjects/result_java_readobjects_3000000_",1 ,javacount)
dataco=calulateMeanDataTimeBar("data/C_Results/readobjects/result_cpp_readobjects_3000000_",1 ,cppcount)

dataj <- subset(datajo,seq=="true"  & datatype=="TweetStatus")
datac <- subset(dataco,seq=="true" & datatype=="TweetStatus")

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

colorstasksettrue=c("Misty Rose", "Snow") 
colorstasksetfalse=c("darkseagreen1", "Honeydew") 

regionscolors<-c(colorstasksettrue[1],colorstasksettrue[2],colorstasksetfalse[1],colorstasksetfalse[2])

totaltimetasksettrue <- datatasksettrue$totaltime
iotimetasksettrue <- datatasksettrue$iotime
cputimetasksettrue <- totaltimetasksettrue - iotimetasksettrue

totaltimetasksetfalse <- datatasksetfalse$totaltime
iotimetasksetfalse <- datatasksetfalse$iotime
cputimetasksetfalse <- totaltimetasksetfalse - iotimetasksetfalse


valuestasksettrue <- matrix( c(iotimetasksettrue, cputimetasksettrue), nrow = 2, ncol = 13, byrow = TRUE)
valuestasksetfalse <- matrix( c(iotimetasksetfalse, cputimetasksetfalse), nrow = 2, ncol = 13, byrow = TRUE)

print(valuestasksettrue)


regions <- c("IO Time(taskset true)", "CPU Time(taskset true)","IO Time(taskset false)", "CPU Time(taskset false)")
xnamestasksettrue = datatasksettrue$method
xnamestasksetfalse = datatasksetfalse$method


#################################################
#######     Bar         #########################
#################################################

#old.par<-par(mfrow=c(1, 2), oma=c(1.2, 1.3, 0.0, 0.0),  pty="m")
#old.par<-par( oma=c(1.2, 1.3, 0.0, 0.0),  pty="m")
par(mar = c(4.5, 3.5, 0, 0)) 

max_y<-max(totaltimetasksettrue,totaltimetasksetfalse)
max_y<-max_y+max_y*0.1;
min_y<-min(iotimetasksettrue,iotimetasksetfalse)/1.3 

# draw bar plots
p1 <- barplot(valuestasksettrue, yaxs="i", log="y", col=colorstasksettrue, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y), legend.text=TRUE, axes=FALSE,border ="gray" , space=c(0.2,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5))

p2 <- barplot(valuestasksetfalse, log="y", col=colorstasksetfalse, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y), add=T,border ="gray", space=c(1.4,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5),axes=FALSE)

p<-rbind(p1,p2)

# write y labels:
totaltime<-rbind(totaltimetasksettrue,totaltimetasksetfalse)
z<-rbind(totaltimetasksettrue,totaltimetasksetfalse,iotimetasksettrue,iotimetasksetfalse)
z<-z[sort.list(z)]
z <-c(min_y,z,max_y)
z<-calulateaxes(z,4)
axis(2, las=1, at = z, labels=round(z, digits=0),  cex.axis = 0.5, font = 1)

#write data inside of bar plots
iotime<-rbind(iotimetasksettrue,iotimetasksetfalse)
cputime<-rbind(cputimetasksettrue,cputimetasksetfalse)

text(x=p, y=totaltime+totaltime*0.1, font = 2, font.lab = 2, labels=round(totaltime, 1), pos=3, xpd=NA, cex=0.5,srt=90)

text(x=p[c(-5,-6)]+0.27, y=totaltime[c(-5,-6)]-totaltime[c(-5,-6)]*0.3, font = 1, font.lab = 2, labels=round(cputime[c(-5,-6)], 1), pos=3, xpd=NA, cex=0.4,srt=90)
#text(x=p[26]+0.2, y=totaltime[26]-totaltime[26]*0.25, font = 1, font.lab = 2, labels=round(cputime[26], 1), pos=3, xpd=NA, cex=0.45,srt=90)
text(x=p+0.2, y=iotime-iotime*0.29, font = 1, font.lab = 2, labels=round(iotime, 1), pos=3, xpd=NA, cex=0.4,srt=90)
box()

lines(x=p[1]-2, y=min_y-min_y/5.5,lwd = 1, col = "grey")
text(x=(p1+p2)/2-2,  y=min_y-min_y/2.2, xnamestasksettrue, xpd=NA, srt=45, pos=3, font=1, cex=0.5)

legend("topright", regions, cex = 0.5, fill = regionscolors)


title(xlab="Sequential Read Objects for 3M Tweets", col.lab=rgb(0,0.5,0),family="Helvetica",cex.lab = 0.75,line = 2.5)
title(ylab="Total Seqential Read Time (sec) - log", col.lab=rgb(0,0.5,0),family="Helvetica",cex.lab = 0.75,line = 2)


#################################################
#######  Random Read Plot     ###################
#################################################
par(mar = c(3.5,3.5,0,0.1))
drawPlot(subset(plotdata, taskset=="true" & seq=="false"),FALSE,"true",FALSE)
par(mar = c(3.5,2,0,0.1))
drawPlot(subset(plotdata, taskset=="false" & seq=="false"),FALSE,"false",FALSE)

#################################################
#######  Sequential Read Bar  ###################
#################################################

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

colorstasksettrue=c("Misty Rose", "Snow") 
colorstasksetfalse=c("darkseagreen1", "Honeydew") 

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

par(mar = c(4.5, 3.5, 0, 0)) 

max_y<-max(totaltimetasksettrue,totaltimetasksetfalse)
max_y<-max_y+max_y*0.1;
min_y<-min(iotimetasksettrue,iotimetasksetfalse)/1.3 

# draw bar plots
p1 <- barplot(valuestasksettrue, yaxs="i", log="y", col=colorstasksettrue, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y), legend.text=TRUE, axes=FALSE,border ="gray" , space=c(0.2,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5))

p2 <- barplot(valuestasksetfalse, log="y", col=colorstasksetfalse, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y), add=T,border ="gray", space=c(1.4,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5),axes=FALSE)

p<-rbind(p1,p2)

# write y labels:
totaltime<-rbind(totaltimetasksettrue,totaltimetasksetfalse)
z<-rbind(totaltimetasksettrue,totaltimetasksetfalse,iotimetasksettrue,iotimetasksetfalse)
z<-z[sort.list(z)]
z <-c(min_y,z,max_y)
z<-calulateaxes(z,1.5)
axis(2, las=1, at = z, labels=round(z, digits=0),  cex.axis = 0.5, font = 1)

#write data inside of bar plots
iotime<-rbind(iotimetasksettrue,iotimetasksetfalse)
cputime<-rbind(cputimetasksettrue,cputimetasksetfalse)

text(x=p, y=totaltime+totaltime*0.1, font = 2, font.lab = 2, labels=round(totaltime, 1), pos=3, xpd=NA, cex=0.5,srt=90)

text(x=p[c(15,16,21,23)]+0.27, y=totaltime[c(15,16,21,23)]-totaltime[c(15,16,21,23)]*0.3, font = 1, font.lab = 2, labels=round(cputime[c(15,16,21,23)], 1), pos=3, xpd=NA, cex=0.4,srt=90)
#text(x=p[26]+0.2, y=totaltime[26]-totaltime[26]*0.25, font = 1, font.lab = 2, labels=round(cputime[26], 1), pos=3, xpd=NA, cex=0.45,srt=90)
text(x=p+0.2, y=iotime-iotime*0.27, font = 1, font.lab = 2, labels=round(iotime, 1), pos=3, xpd=NA, cex=0.4,srt=90)
box()

lines(x=p[1]-2, y=min_y-min_y/5.5,lwd = 1, col = "grey")
text(x=(p1+p2)/2-2,  y=min_y-min_y/2.5, xnamestasksettrue, xpd=NA, srt=45, pos=3, font=1, cex=0.5)

legend("topright", regions, cex = 0.5, fill = regionscolors)


title(xlab="Random Read Objects for 3M Tweets", col.lab=rgb(0,0.5,0),family="Helvetica",cex.lab = 0.75,line = 2.5)
title(ylab="Total Random Read Time (minut) - log", col.lab=rgb(0,0.5,0),family="Helvetica",cex.lab = 0.75,line = 2)

par(xpd=TRUE)