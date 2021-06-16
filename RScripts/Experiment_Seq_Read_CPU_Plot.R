
library(plyr)
# library(ggplot2)
# require(cowplot)


# function definition for calculating mean of data
calulateMeanDataTotaltime <- function(myfilename,nr, n){
  
  totaltime <- matrix(nrow= nr, ncol=n)
  
  # run for all 3 experiments 
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
        tspace<-space*70
      else if(j>listlength*0.5)
        tspace<-space*50
      else if(j>listlength*0.25)
        tspace<-space*7
      else if(j>listlength*0.15)
        tspace<-space*3
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
  
  # Rust Json  results 
  rustJSON <- subset(data, language="ReadTimeRUST", method=="Rust Json")
  rustJSONV <- vector()
  rustJSONV <-rustJSON[['totaltime']]
  
  # Rust Json  results 
  rustBINCODE <- subset(data, language="ReadTimeRUST", method=="Rust Bincode")
  rustBINCODEV <- vector()
  rustBINCODEV <-rustBINCODE[['totaltime']]
  
  # Rust Json  results 
  rustMESSAGEPACK <- subset(data, language="ReadTimeRUST", method=="Rust MessagePack")
  rustMESSAGEPACKV <- vector()
  rustMESSAGEPACKV <-rustMESSAGEPACK[['totaltime']]
  
  # Rust Json  results 
  rustBSON <- subset(data, language="ReadTimeRUST", method=="Rust Bson")
  rustBSONV <- vector()
  rustBSONV <-rustBSON[['totaltime']]
  
  # Rust Json  results 
  rustFLEXBUFFERS <- subset(data, language="ReadTimeRUST", method=="Rust FlexBuffers")
  rustFLEXBUFFERSV <- vector()
  rustFLEXBUFFERSV <-rustFLEXBUFFERS[['totaltime']]
  
  
  
  
 # plot_colors <- c("red2", "blue1","green4", "saddlebrown","green", "lightseagreen", "deeppink3", "darkorange", "yellow1" , "gray8","midnightblue","chocolate4","maroon1","maroon1","maroon1","maroon1","maroon1","maroon1")
  plot_colors <- c("red4", "deeppink","brown2", "red4","red4", "darkorange", "gold", "blue4", "blue" , "dodgerblue1","dodgerblue4","cyan4","darkorchid4","green4","green4","black","green4","red")
  serialization_methods<-c("Java Default","Java Json+Gzip","Java Bson","Java ProtoBuf","Java Kryo","Java ByteBuffer","Java FlatBuffers","C++ Boost","C++ ProtoBuf",  "C++ HandCoded", "C++ InPlace","C++ Bson","C++ FlatBuffers","Rust Json","Rust Bincode","Rust MessagePack","Rust Bson","Rust FlexBuffers")
  pchs<-c(0,16,2,3,4,8,6,0,1,2,3,4,8,0,1,2,3,4)  
  
  #################################################
  ######################   Plot ###################
  #################################################
  
  
  #x <- c(1000000, 2000000,3000000,4000000,5000000)
  totaltimes=c(javaDefaultV[javaDefaultV!=0],javaJsonV[javaJsonV!=0],javaBsonV[javaBsonV!=0],javaProtoBufV[javaProtoBufV!=0],javaKryoV[javaKryoV!=0],
               javaByteBufferV[javaByteBufferV!=0],javaFlatBufferV[javaFlatBufferV!=0],cppHANDCODEDV[cppHANDCODEDV!=0],cppPROTOBUFV[cppPROTOBUFV!=0],
               cppINPLACEV[cppINPLACEV!=0],cppBOOSTV[cppBOOSTV!=0],cppBSONV[cppBSONV!=0],cppFLATBUFV[cppFLATBUFV!=0],rustJSONV[rustJSONV!=0],rustBINCODEV[rustBINCODEV!=0]
               ,rustMESSAGEPACKV[rustMESSAGEPACKV!=0],rustBSONV[rustBSONV!=0],rustFLEXBUFFERSV[rustFLEXBUFFERSV!=0])  
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
  rustJSONV[rustJSONV==0]<-NA
  rustBINCODEV[rustBINCODEV==0]<-NA
  rustMESSAGEPACKV[rustMESSAGEPACKV==0]<-NA
  rustBSONV[rustBSONV==0]<-NA
  rustFLEXBUFFERSV[rustFLEXBUFFERSV==0]<-NA
  
  #lines for Faltbuffers C++ 
  plot(na.omit(cppFLATBUFV), log="y", type="o",cex=0.5, pch=pchs[13], lty=2,lwd=0.5, ylim=c(min_y, max_y), axes=FALSE, ann=FALSE,col=plot_colors[13])
  
  if(ts=="false"){
    #abline(v=c(1, 2, 3, 4,5), lty=3, col="gray")
    
    for (t in tick_list)
      segments(1,t,5.2,t, lty=3, col="gray")
    
    for (t in c(1,2,3,4,5))
      segments(t,min_y,t,max_y+500, lty=3, col="gray")
  }
  else{
    abline(h=tick_list,v=c(1, 2, 3, 4,5), lty=3, col="gray")
  }
  
  pchsize=1.2
  lwdsize=0.5
  # Make x axis using one to 5 labels
  axis(1, at=c(1, 2, 3, 4,5), labels=c("1M","2M","3M", "4M","5M"), las=1,cex.axis = 1.4,mgp=c(3, 0.8, 0),tck = -0.03,lwd=1 )
  
  # Make y axis with horizontal labels that display ticks at 
  axis(2, las=1, at = tick_list, labels=y_labels,cex.axis = 1.4,mgp=c(3, .6, 0),tck = -0.03,lwd=lwdsize )
  
  #lines for Json
  lines(na.omit(javaJsonV) , type="o", pch=pchs[2], lty=2,cex=pchsize, col=plot_colors[2],lwd=lwdsize)
  
  #lines for Bson 
  lines(na.omit(javaBsonV), type="o", pch=pchs[3], lty=2,cex=pchsize, col=plot_colors[3],lwd=lwdsize)
  
  #lines for ProtoBuf
  lines(na.omit(javaProtoBufV), type="o", pch=pchs[4], lty=2,cex=pchsize, col=plot_colors[4],lwd=lwdsize)
  
  #lines for Kryo
  lines(na.omit(javaKryoV), type="o", pch=pchs[5], lty=2,cex=pchsize, col=plot_colors[5],lwd=lwdsize)
  
  #lines for ByteBuffer
  lines(na.omit(javaByteBufferV), type="o", pch=pchs[6], lty=2,cex=pchsize, col=plot_colors[6],lwd=lwdsize)
  
  #lines for Java flat buffers
  lines( na.omit(javaFlatBufferV), type="o", pch=pchs[7], lty=2,cex=pchsize, col=plot_colors[7],lwd=lwdsize)
  
  #lines for BOOST C++ 
  lines(na.omit(cppBOOSTV), type="o", pch=pchs[8], lty=2,cex=pchsize, col=plot_colors[8],lwd=lwdsize)
  
  #lines for PROTOBUF C++ 
  lines(na.omit(cppPROTOBUFV), type="o", pch=pchs[9], lty=2,cex=pchsize, col=plot_colors[9],lwd=lwdsize)
  
  #lines for HANDCODED C++ 
  lines(na.omit(cppHANDCODEDV), type="o", pch=pchs[10], lty=2,cex=pchsize, col=plot_colors[10],lwd=lwdsize)
  
  #lines for INPLACE C++ 
  lines(na.omit(cppINPLACEV), type="o", pch=pchs[11], lty=2,cex=pchsize, col=plot_colors[11],lwd=lwdsize)
  
  #lines for BSON C++ 
  lines(na.omit(cppBSONV), type="o", pch=pchs[12], lty=2,cex=pchsize, col=plot_colors[12],lwd=lwdsize)
  
  # Java Deafult
  lines(na.omit(javaDefaultV), type="o", pch=pchs[1],cex=pchsize, lty=2, col=plot_colors[1],lwd=lwdsize)
  
  #lines for Json Rust 
  lines(na.omit(rustJSONV), type="o", pch=pchs[14], lty=2,cex=pchsize, col=plot_colors[14],lwd=lwdsize)
  
  #lines for Bincode Rust 
  lines(na.omit(rustBINCODEV), type="o", pch=pchs[15], lty=2,cex=pchsize, col=plot_colors[15],lwd=lwdsize)
  
  #lines for MessagePack Rust 
  lines(na.omit(rustMESSAGEPACKV), type="o", pch=pchs[16], lty=2,cex=pchsize, col=plot_colors[16],lwd=lwdsize)
  
  #lines for Bson Rust 
  lines(na.omit(rustBSONV), type="o", pch=pchs[17], lty=2,cex=pchsize, col=plot_colors[17],lwd=lwdsize)
  
  #lines for FlexBuffers Rust 
  lines(na.omit(rustFLEXBUFFERSV), type="o", pch=pchs[18], lty=2,cex=pchsize, col=plot_colors[18],lwd=lwdsize)
  
  
  xlb<-paste("task set=", ts , sep="")
  title(xlab="Number of Objects", col.lab="black",family="Helvetica",cex.lab =1.4,line = 2.3,font=2)
  
  text(3, 2, xlb, cex=1.4)
  if(ts=="true"){
      title(ylab="Total Seqential Read Time (sec) - log", col.lab="black",family="Helvetica",cex.lab = 1.4,line = 2.7,font=2,las=1)
  }

 
  box(lwd=1)
 
   if(ts=="false"){
    legend("topright", inset=c(-0.59,0), serialization_methods, cex=1.1,  col=plot_colors, pch=pchs, text.font=1.2,title="Methods:",box.lty=0);
   # legend("topright", inset=c(-0.2,0), legend=c("A","B"), pch=c(1,3), title="Group")
    #legend(2.5, 10, serialization_methods[c(1:7)], cex=0.4,  col=plot_colors[c(1:7)], pch=1:7, lty=2:2,lwd=0.5,ncol=1,inset=c(-0.2,0));
  }
}


cppcount=12*2
javacount=14*2
rustcount=10*2

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
dataj4 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_4000000_",3, javacount)
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

# RUST Results 
##################################################################
# load data for 1M objects read 
datar1 = calulateMeanDataTotaltime("data/Rust_Results/readobjects2/result_rust_readobjects_1000000_",1 ,rustcount)
datar1$size <-1000000 

# load data for 2M objects read 
datar2 = calulateMeanDataTotaltime("data/Rust_Results/readobjects2/result_rust_readobjects_2000000_",1 , rustcount)
datar2$size <-2000000 


# load data for 3M objects read 
datar3 = calulateMeanDataTotaltime("data/Rust_Results/readobjects2/result_rust_readobjects_3000000_", 1 ,rustcount)
datar3$size <-3000000 

# load data for 4M objects read 
datar4 = calulateMeanDataTotaltime("data/Rust_Results/readobjects2/result_rust_readobjects_4000000_",1 , rustcount)
datar4$size <-4000000

# load data for 5M objects read 
datar5 = calulateMeanDataTotaltime("data/Rust_Results/readobjects2/result_rust_readobjects_5000000_",1 , rustcount)
datar5$size <-5000000


# bind the data frames together 
plotdata <- rbind(datac1,datac2,datac3,datac4,datac5,dataj1,dataj2,dataj3,dataj4,dataj5,datar1,datar2,datar3,datar4,datar5)
write.table(plotdata, file = "../Paper/latex/img/exp_read.csv", sep = ",",row.names = FALSE, col.names = TRUE)

pdf(file='Experiment_Seq_Read_CPU_Plot.pdf',height=8, width=10)

#old.par<-par(mfrow=c(1, 2),   pty="m")
#op <- par(mar = c(2.2,2.5,0,1),xpd=TRUE)

layout.matrix <- matrix(c(1, 2), nrow = 1, ncol = 2)
layout(mat = layout.matrix, widths = c(0.43, 0.57)) 

par(mar = c(3.5,4,0.1,1.2))
drawPlot(subset(plotdata, taskset=="true" & seq=="true"),TRUE,"true",FALSE)

par(mar = c(3.5,2.7,0.1,9.5),xpd=TRUE)
drawPlot(subset(plotdata, taskset=="false" & seq=="true"),TRUE,"false",FALSE)
par(xpd=TRUE)