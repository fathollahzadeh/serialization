
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
        tspace<-space*75
      else if(j>listlength*0.5)
        tspace<-space*30
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
  
  
  #x <- c(1000000, 2000000,3000000,4000000,5000000)
  totaltimes=c(javaDefaultV[javaDefaultV!=0],javaJsonV[javaJsonV!=0],javaBsonV[javaBsonV!=0],javaProtoBufV[javaProtoBufV!=0],javaKryoV[javaKryoV!=0],
               javaByteBufferV[javaByteBufferV!=0],javaFlatBufferV[javaFlatBufferV!=0],cppHANDCODEDV[cppHANDCODEDV!=0],cppPROTOBUFV[cppPROTOBUFV!=0],
               cppINPLACEV[cppINPLACEV!=0],cppBOOSTV[cppBOOSTV!=0],cppBSONV[cppBSONV!=0],cppFLATBUFV[cppFLATBUFV!=0])  
  max_y<-max(totaltimes)
  max_y<-max_y+max_y*0.1;
  min_y<-min(totaltimes) 
  
  tick_list<-totaltimes[sort.list(totaltimes)]
  tick_list<-calulateaxes(tick_list,3.5)
  y_labels<- sprintf("%s",tick_list);
  
  javaDefaultV[javaDefaultV==0]<-NA
  javaJsonV[javaJsonV==0]<-NA
  javaBsonV[javaBsonV==0]<-NA
  javaProtoBufV[javaProtoBufV==0]<-NA
  javaKryoV[javaKryoV==0]<-NA
  javaByteBufferV[javaByteBufferV==0]<-NA
  javaFlatBufferV[javaFlatBufferV==0]<-NA
  cppHANDCODEDV[cppHANDCODEDV==0]<-NA
  cppPROTOBUFV[cppPROTOBUFV==0]<-NA
  cppINPLACEV[cppINPLACEV==0]<-NA
  cppBOOSTV[cppBOOSTV==0]<-NA
  cppBSONV[cppBSONV==0]<-NA
  cppFLATBUFV[cppFLATBUFV==0]<-NA
  
  
  #lines for Faltbuffers C++ 
  plot(na.omit(cppFLATBUFV), log="y", type="o",cex=0.5, pch=13, lty=2,lwd=0.5, ylim=c(min_y, max_y), axes=FALSE, ann=FALSE,col=plot_colors[13],  panel.first=abline(h= tick_list, v=c(1, 2, 3, 4,5), lty=3, col="gray"))
  
  # Make x axis using one to 5 labels
  axis(1, at=c(1, 2, 3, 4,5), labels=c("1M","2M","3M", "4M","5M"), las=1,cex.axis = 0.6 ,mgp=c(3, .6, 0))
  
  # Make y axis with horizontal labels that display ticks at 
  axis(2, las=1, at = tick_list, labels=y_labels,cex.axis = 0.6)
  
  #lines for Json
  lines(na.omit(javaJsonV) , type="o", pch=2, lty=2,cex=0.5, col=plot_colors[2],lwd=0.5)
  
  #lines for Bson 
  lines(na.omit(javaBsonV), type="o", pch=3, lty=2,cex=0.5, col=plot_colors[3],lwd=0.5)
  
  #lines for ProtoBuf
  lines(na.omit(javaProtoBufV), type="o", pch=4, lty=2,cex=0.5, col=plot_colors[4],lwd=0.5)
  
  #lines for Kryo
  lines(na.omit(javaKryoV), type="o", pch=5, lty=2,cex=0.5, col=plot_colors[5],lwd=0.5)
  
  #lines for ByteBuffer
  lines(na.omit(javaByteBufferV), type="o", pch=6, lty=2,cex=0.5, col=plot_colors[6],lwd=0.5)
  
  #lines for Java flat buffers
  lines( na.omit(javaFlatBufferV), type="o", pch=7, lty=2,cex=0.5, col=plot_colors[7],lwd=0.5)
  
  #lines for BOOST C++ 
  lines(na.omit(cppBOOSTV), type="o", pch=8, lty=2,cex=0.5, col=plot_colors[8],lwd=0.5)
  
  #lines for PROTOBUF C++ 
  lines(na.omit(cppPROTOBUFV), type="o", pch=9, lty=2,cex=0.5, col=plot_colors[9],lwd=0.5)
  
  #lines for HANDCODED C++ 
  lines(na.omit(cppHANDCODEDV), type="o", pch=10, lty=2,cex=0.5, col=plot_colors[10],lwd=0.5)
  
  #lines for INPLACE C++ 
  lines(na.omit(cppINPLACEV), type="o", pch=11, lty=2,cex=0.5, col=plot_colors[11],lwd=0.5)
  
  #lines for BSON C++ 
  lines(na.omit(cppBSONV), type="o", pch=12, lty=2,cex=0.5, col=plot_colors[12],lwd=0.5)
  
  # Java Deafult
  lines(na.omit(javaDefaultV), type="o", pch=1,cex=0.5, lty=2, col=plot_colors[1],lwd=0.5)
  
 
  xlb<-paste("Number of Objects(task set=", ts ,")", sep="")
  title(xlab=xlb, col.lab="black",family="Helvetica",cex.lab = 0.6,line = 1.3,font=2)
    
    if(ts=="true"){
      title(ylab="Total Random Read Time (sec) - log", col.lab="black",family="Helvetica",cex.lab = 0.7,line =1.85,font=2)
    }
  
  box()
  
  if(ts=="true"){
    legend(1.6, 14, serialization_methods[c(8:13)], cex=0.33,  col=plot_colors[c(8:13)], pch=8:13, lty=2:2,lwd=0.5,ncol=2);
  }
  else{
    legend(1.7, 17.5, serialization_methods[c(1:7)], cex=0.33,  col=plot_colors[c(1:7)], pch=1:7, lty=2:2,lwd=0.5,ncol=2);
  }
}


cppcount=12*2
javacount=14*2

#Java Results
dataj1 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_1000000_",3 ,javacount)
dataj1$size <-1000000 

# load data for 2M objects read 
dataj2 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_2000000_",3 , javacount)
dataj2$size <-2000000 


# load data for 3M objects read 
dataj3 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_3000000_", 3 ,javacount)
dataj3$size <-3000000 


# load data for 4M objects read 
dataj4 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_4000000_",3 , javacount)
dataj4$size <-4000000


# load data for 5M objects read 
dataj5 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_5000000_",3 , javacount)
dataj5$size <-5000000

# CPP Results 
##################################################################
# load data for 1M objects read 
datac1 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_1000000_",3 ,cppcount)
datac1$size <-1000000 

# load data for 2M objects read 
datac2 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_2000000_",3 , cppcount)
datac2$size <-2000000 


# load data for 3M objects read 
datac3 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_3000000_", 3 ,cppcount)
datac3$size <-3000000 

# load data for 4M objects read 
datac4 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_4000000_",3 , cppcount)
datac4$size <-4000000

# load data for 5M objects read 
datac5 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_5000000_",3 , cppcount)
datac5$size <-5000000


# bind the data frames together 
plotdata <- rbind(datac1,datac2,datac3,datac4,datac5,dataj1,dataj2,dataj3,dataj4,dataj5)

pdf(file='Experiment_Rand_Read_CPU_Plot.pdf',height=3, width=4)

old.par<-par(mfrow=c(1, 2),   pty="m")
op <- par(mar = c(2.2,2.5,0,0.1))

drawPlot(subset(plotdata, taskset=="true" & seq=="false"),FALSE,"true",TRUE)
drawPlot(subset(plotdata, taskset=="false" & seq=="false"),FALSE,"false",TRUE)
par(xpd=TRUE)