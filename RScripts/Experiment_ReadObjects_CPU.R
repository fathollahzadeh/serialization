
library(plyr)
# library(ggplot2)
# require(cowplot)


# function definition for calculating mean of data 

calulateMeanDataTotaltime <- function(myfilename,nr, n){
  
  totaltime <- matrix(nrow= nr, ncol=n)
  
  # run for all 5 experiments 
  for(i in 1:nr){
    #       file = paste("data/java/resultJavaReadObjects_100_", i,  sep = "")
    file = paste(myfilename, i,  sep = "")
    file <- paste(file, ".txt" , sep="")
    mydata <- read.delim(file, header=TRUE, sep="#")
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
  
  # print("This is before replacing")
  # print(mydata)
  mydata$totaltime<-finalTime
  return(mydata)
}


#Java Results
dataj1 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_1000000_",1 ,12)
dataj1$size <-1000000 

# load data for 2M objects read 
dataj2 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_2000000_",1 , 12)
dataj2$size <-2000000 


# load data for 3M objects read 
dataj3 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_3000000_", 1 ,12)
dataj3$size <-3000000 

# load data for 4M objects read 
dataj4 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_4000000_",1 , 12)
dataj4$size <-4000000

# load data for 5M objects read 
dataj5 = calulateMeanDataTotaltime("data/Java_Results/readobjects/result_java_readobjects_5000000_",1 , 12)
dataj5$size <-5000000


# CPP Results 
##################################################################
# load data for 1M objects read 
datac1 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_1000000_",1 ,8)
datac1$size <-1000000 

# load data for 2M objects read 
datac2 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_2000000_",1 , 8)
datac2$size <-2000000 


# load data for 3M objects read 
datac3 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_3000000_", 1 ,8)
datac3$size <-3000000 

# load data for 4M objects read 
datac4 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_4000000_",1 , 8)
datac4$size <-4000000

# load data for 5M objects read 
datac5 = calulateMeanDataTotaltime("data/C_Results/readobjects/result_cpp_readobjects_5000000_",1 , 8)
datac5$size <-5000000


# bind the data frames together 
data <- rbind(datac1,datac2,datac3,datac4,datac5,dataj1,dataj2,dataj3,dataj4,dataj5)

##################################################################
##################################################################
# Java Defaul results 
javaDefaultSeq <- subset(data, language="ReadTimeJAVA", seq=="true" & method=="Java Default")
javaDefaultSeqV <- vector()
javaDefaultSeqV <-javaDefaultSeq[['totaltime']]

javaDefault <- subset(data, language="ReadTimeJAVA", seq=="false" & method=="Java Default")
javaDefaultV <- vector()
javaDefaultV <-javaDefault[['totaltime']]

# Java Json results 
javaJsonSeq <- subset(data, language="ReadTimeJAVA", seq=="true" & method=="Java Json")
javaJsonSeqV <- vector()
javaJsonSeqV <-javaJsonSeq[['totaltime']]

javaJson <- subset(data, language="ReadTimeJAVA", seq=="false" & method=="Java Json")
javaJsonV <- vector()
javaJsonV <-javaJson[['totaltime']]

# Java Bson results 
javaBsonSeq <- subset(data, language="ReadTimeJAVA", seq=="true" & method=="Java Bson")
javaBsonSeqV <- vector()
javaBsonSeqV <-javaBsonSeq[['totaltime']]

javaBson <- subset(data, language="ReadTimeJAVA", seq=="false" & method=="Java Bson")
javaBsonV <- vector()
javaBsonV <-javaBson[['totaltime']]

# Java ProtoBuf results 
javaProtoBufSeq <- subset(data, language="ReadTimeJAVA", seq=="true" & method=="Java ProtoBuf")
javaProtoBufSeqV <- vector()
javaProtoBufSeqV <-javaProtoBufSeq[['totaltime']]

javaProtoBuf <- subset(data, language="ReadTimeJAVA", seq=="false" & method=="Java ProtoBuf")
javaProtoBufV <- vector()
javaProtoBufV <-javaProtoBuf[['totaltime']]

# Java Kryo results 
javaKryoSeq <- subset(data, language="ReadTimeJAVA", seq=="true" & method=="Java Kryo")
javaKryoSeqV <- vector()
javaKryoSeqV <-javaKryoSeq[['totaltime']]

javaKryo <- subset(data, language="ReadTimeJAVA", seq=="false" & method=="Java Kryo")
javaKryoV <- vector()
javaKryoV <-javaKryo[['totaltime']]

# Java Byte Buffer results 
javaByteBufferSeq <- subset(data, language="ReadTimeJAVA", seq=="true" & method=="Java Byte Buffer")
javaByteBufferSeqV <- vector()
javaByteBufferSeqV <-javaByteBufferSeq[['totaltime']]

javaByteBuffer <- subset(data, language="ReadTimeJAVA", seq=="false" & method=="Java Byte Buffer")
javaByteBufferV <- vector()
javaByteBufferV <-javaByteBuffer[['totaltime']]


# C++  HANDCODED  results 
cppHANDCODEDSeq <- subset(data, language="ReadTimeCPP", seq=="true" & method=="HANDCODED")
cppHANDCODEDSeqV <- vector()
cppHANDCODEDSeqV <-cppHANDCODEDSeq[['totaltime']]

cppHANDCODED <- subset(data, language="ReadTimeCPP",seq=="false" & method=="HANDCODED")
cppHANDCODEDV <- vector()
cppHANDCODEDV <-cppHANDCODED[['totaltime']]

# C++  PROTOBUF  results 
cppPROTOBUFSeq <- subset(data, language="ReadTimeCPP", seq=="true" & method=="PROTOBUF")
cppPROTOBUFSeqV <- vector()
cppPROTOBUFSeqV <-cppPROTOBUFSeq[['totaltime']]

cppPROTOBUF <- subset(data, language="ReadTimeCPP", seq=="false" & method=="PROTOBUF")
cppPROTOBUFV <- vector()
cppPROTOBUFV <-cppPROTOBUF[['totaltime']]


# C++  INPLACE  results 
cppINPLACESeq <- subset(data, language="ReadTimeCPP",  seq=="true" & method=="INPLACE")
cppINPLACESeqV <- vector()
cppINPLACESeqV <- cppINPLACESeq[['totaltime']]

cppINPLACE <- subset(data, language="ReadTimeCPP", seq=="false" & method=="INPLACE")
cppINPLACEV <- vector()
cppINPLACEV <-cppINPLACE[['totaltime']]


# C++  BOOST  results 
cppBOOSTSeq <- subset(data, language="ReadTimeCPP", seq=="true" & method=="BOOST")
cppBOOSTSeqV <- vector()
cppBOOSTSeqV <-cppBOOSTSeq[['totaltime']]

cppBOOST <- subset(data, language="ReadTimeCPP", seq=="false" & method=="BOOST")
cppBOOSTV <- vector()
cppBOOSTV <-cppBOOST[['totaltime']]


plot_colors <- c("red2", "blue1","green4", "saddlebrown","green", "lightseagreen", "deeppink3", "darkorange", "yellow1" , "gray8")
serialization_methods<-c("Java Default","Java JSON","Java BSON","Java Protocol","Java Kryo","Java ByteBuffer","C++ Boost","C++ Protocol",  "C++ HandCoded", "C++ InPlace")

#################################################
#######     Plots       #########################
#################################################
pdf(file='Experiment_ReadObjects_CPU.pdf')

# old.par <- par(mfrow=c(1, 2))
old.par<-par(mfrow=c(1, 2), oma=c(1.2, 1.3, 0.0, 0.0),  pty="m")

#mar=c(2.9,3,1.5,0.5),oma = c(0.9, 0.8, 0, 0)
op <- par(mar = c(3.5,3.5,0,0.1))
#op <- par(mar = c(4, 4, 0.1, 0.1))

#par(mfrow=c(1,2),mar=c(2.9,3,1.5,0.5),oma = c(0, 0, 0, 0))

# op <- par(mar = c(4,6,0.2,0.2) + 0.1)
# par(mar=c(4, 4, 1, 1))
# par(oma=c(0, 0, 0, 0))

x <- c(1000000, 2000000,3000000,4000000,5000000)
max_y<-14000
min_y<-0.1
tick_list=c(min_y,0.3,0.6,1,2,3, 8,15, 25, 45,  80, 110, 200,370,570,800,1300,4000,8000,max_y)

y_labels<- sprintf("%s",tick_list);

# Java Deafult
plot(javaDefaultSeqV, log="y", type="o", pch=1, lty=2,lwd=1, ylim=c(min_y, max_y), axes=FALSE, ann=FALSE,col=plot_colors[1],  panel.first=abline(h= tick_list, v=c(1, 2, 3, 4,5), lty=3, col="gray"))

# Make x axis using one to 5 labels
axis(1, at=c(1, 2, 3, 4,5), labels=c("1M","2M","3M", "4M","5M"), las=2 )

# Make y axis with horizontal labels that display ticks at 
axis(2, las=1, at = tick_list, labels=y_labels)

#lines for Json
lines(javaJsonSeqV , type="o", pch=2, lty=2, col=plot_colors[2])

#lines for Bson 
lines(javaBsonSeqV, type="o", pch=3, lty=2, col=plot_colors[3])

#lines for ProtoBuf
lines(javaProtoBufSeqV, type="o", pch=4, lty=2, col=plot_colors[4])

#lines for Kryo
lines(javaKryoSeqV, type="o", pch=5, lty=2, col=plot_colors[5])

#lines for ByteBuffer
lines(javaByteBufferSeqV, type="o", pch=6, lty=2, col=plot_colors[6])

#lines for BOOST C++ 
lines(cppBOOSTSeqV, type="o", pch=7, lty=2, col=plot_colors[7])

#lines for PROTOBUF C++ 
lines(cppPROTOBUFSeqV, type="o", pch=8, lty=2, col=plot_colors[8])

#lines for HANDCODED C++ 
lines(cppHANDCODEDSeqV, type="o", pch=9, lty=2, col=plot_colors[9])

#lines for INPLACE C++ 
print(cppINPLACESeqV)
lines(cppINPLACESeqV, type="o", pch=10, lty=2, col=plot_colors[10])


#title(xlab="Number of Objects", col.lab=rgb(0,0.5,0))
#title(ylab="Total Reading Time (sec) - log ", col.lab=rgb(0,0.5,0),cex=1)
text(3, 4000, "Sequential", cex=1.3)

box()
#par(xpd=TRUE)
legend(3, 16, serialization_methods, cex=0.65,  col=plot_colors, pch=1:10, lty=2:2);
##############################################################
##################                   #########################
##################      Next Plot    #########################
##################                   #########################
##############################################################
#op <- par(oma=c(0.1, 0.1, 0.0, 0.0))#par(mar = c(4, 4, 0.1, 0.1))

#x <- c(1000000, 2000000,3000000,4000000,5000000)
#max_y<-14000
#min_y<-0.5
#tick_list<-c(min_y,3, 8,15, 25, 45,  80, 110, 200,370,570,800,1300,4000,8000,max_y)

y_labels<- sprintf("%s",tick_list);

# Java Deafult
plot(javaDefaultV, log="y", type="o", pch=1, lty=2,lwd=1, ylim=c(min_y, max_y),col=plot_colors[1], axes=FALSE, ann=FALSE,cex.axis=0.6, panel.first=abline(h= tick_list, v=c(1, 2, 3, 4,5), lty=3, col="gray"))

# Make x axis using one to 5 labels
axis(1, at=c(1, 2, 3, 4,5), labels=c("1M","2M","3M", "4M", "5M"), las=2 )

# Make y axis with horizontal labels that display ticks at 
axis(2, las=1, at = tick_list, labels=y_labels)

#lines for Json
lines(javaJsonV , type="o", pch=2, lty=2, col=plot_colors[2])

#lines for Bson 
lines(javaBsonV, type="o", pch=3, lty=2, col=plot_colors[3])

#lines for ProtoBuf
lines(javaProtoBufV, type="o", pch=4, lty=2, col=plot_colors[4])

#lines for Kryo
lines(javaKryoV, type="o", pch=5, lty=2, col=plot_colors[5])

#lines for ByteBuffer
lines(javaByteBufferV, type="o", pch=6, lty=2, col=plot_colors[6])

#lines for BOOST C++ 
lines(cppBOOSTV, type="o", pch=7, lty=2, col=plot_colors[7])

#lines for PROTOBUF C++ 
lines(cppPROTOBUFV, type="o", pch=8, lty=2, col=plot_colors[8])

#lines for HANDCODED C++ 
lines(cppHANDCODEDV, type="o", pch=9, lty=2, col=plot_colors[9])

#lines for INPLACE C++ 
lines(cppINPLACEV, type="o", pch=10, lty=2, col=plot_colors[10])


#title(xlab="Number of Objects", col.lab=rgb(0,0.5,0))
#title(ylab="Total Reading Time (sec) - log ", col.lab=rgb(0,0.5,0))
text(3, 8, "Random", cex=1.3)

mtext("Total Reading Time (sec) - log", outer = TRUE, cex = 1, font=0.7,side=2,family="Helvetica",line = -0.5, col=rgb(0,0.5,0) )
mtext("Number of Objects", outer = TRUE, cex = 1, font=0.7,side=1,family="Helvetica" ,line = -1,col=rgb(0,0.5,0))
# Create box around plot
box()

par(old.par)
par(xpd=TRUE)


#legend(3.5, 2, c("C++ Boost","C++ Protocol",  "C++ HandCoded", "C++ InPlace"), cex=0.9,  col=c( "violet",  "deepskyblue" , "blue3","orange"), pch=2:11, lty=2:2);
# par(xpd=TRUE)


