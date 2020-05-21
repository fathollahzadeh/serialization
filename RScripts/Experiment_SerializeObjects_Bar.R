library(plyr)
require(stats)

# function definition for calculating mean of data 

calulateMeanDataTotaltime <- function(myfilename,nr, n){
  
  totaltime <- matrix(nrow= nr, ncol=n)
  
  # run for all 5 experiments 
  for(i in 1:nr){
    #       file = paste("data/java/resultJavaReadObjects_100_", i,  sep = "")
    file = paste(myfilename, i,  sep = "")
    file <- paste(file, ".txt" , sep="")
    mydata <- read.delim(file, header=TRUE, sep="#")
    totaltime[i,] <-mydata[['totaltime']]
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

# function for normalize y-axes data
calulateaxes <- function(data){
  
  resultdata <- vector() 
  resultdata[1]<-data[1];
  i<-1
  j<-1
  space<-1.5
  tspace<-space
  listlength<-length(data)
  for (d in data) {
    
    if(j>listlength*0.75)
      tspace<-space*217
    else if(j>listlength*0.5)
      tspace<-space*40
    else if(j>listlength*0.15)
      tspace<-space*10
    else if(j>listlength*0.05)
      tspace<-space*9
    
    j<-j+1
    
    if(d-resultdata[i]>tspace){
      i<-i+1
      resultdata[i]<-d
    }
  }
  
  return(resultdata)
}

# load data for 5M objects write 
datajo = calulateMeanDataTotaltime("data/Java_Results/writeobjects/result_java_writeobjects_5000000_",3 , 14)
dataco = calulateMeanDataTotaltime("data/C_Results/writeobjects/result_cpp_writeobjects_5000000_",3 , 12)

data <- rbind(dataco,datajo)

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


data <- rbind(cppHandCoded,cppInPlace,cppFlatBuf,cppProtoBuf,cppBoost,cppBson,javaJson,javaBson,javaDefault,javaProtoBuf,javaByteBuffer,javaFlatBuf,javaKryo)

datatasksettrue<-subset(data, taskset=="true")
datatasksetfalse<-subset(data, taskset=="false")

colorstasksettrue=c("gray5", "gray80")#c("Misty Rose", "Snow") 
colorstasksetfalse=c("gray30", "gray91") 

regionscolors<-c(colorstasksettrue[1],colorstasksettrue[2],colorstasksetfalse[1],colorstasksetfalse[2])

totaltimetasksettrue <- datatasksettrue$totaltime
iotimetasksettrue <- datatasksettrue$iotime
cputimetasksettrue <- totaltimetasksettrue - iotimetasksettrue

totaltimetasksetfalse <- datatasksetfalse$totaltime
iotimetasksetfalse <- datatasksetfalse$iotime
cputimetasksetfalse <- totaltimetasksetfalse - iotimetasksetfalse

valuestasksettrue <- matrix( c(iotimetasksettrue, cputimetasksettrue), nrow = 2, ncol = 13, byrow = TRUE)
valuestasksetfalse <- matrix( c(iotimetasksetfalse, cputimetasksetfalse), nrow = 2, ncol = 13, byrow = TRUE)


regions <- c("IO Time(taskset true)", "CPU Time(taskset true)","IO Time(taskset false)", "CPU Time(taskset false)")
xnamestasksettrue = datatasksettrue$method
xnamestasksetfalse = datatasksetfalse$method


#################################################
#######     Bar         #########################
#################################################
pdf(file='Experiment_SerializeObjects_Bar.pdf', family="Helvetica",height=2.5, width=3.5)

#old.par<-par(mfrow=c(1, 2), oma=c(1.2, 1.3, 0.0, 0.0),  pty="m")
#old.par<-par( oma=c(1.2, 1.3, 0.0, 0.0),  pty="m")
par(mar = c(1.8, 2.5, 0.1, 0.1)) 

max_y<-max(totaltimetasksettrue,totaltimetasksetfalse)
max_y<-max_y+max_y*0.1;
min_y<-min(iotimetasksettrue,iotimetasksetfalse)/1.3 

# draw bar plots
p1 <- barplot(valuestasksettrue,log="y",  col=colorstasksettrue, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y), legend.text=TRUE, axes=FALSE,border =colorstasksettrue, space=c(0.2,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5))

p2 <- barplot(valuestasksetfalse,log="y", col=colorstasksetfalse, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y), add=T,border =colorstasksetfalse, space=c(1.4,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5),axes=FALSE)

p<-rbind(p1,p2)


# write y labels:
totaltime<-rbind(totaltimetasksettrue,totaltimetasksetfalse)
z<-rbind(totaltimetasksettrue,totaltimetasksetfalse,iotimetasksettrue,iotimetasksetfalse)
z<-z[sort.list(z)]
z <-c(min_y,z,max_y)
z<-calulateaxes(z)
axis(2, las=1, at = z, labels=round(z, digits=0),cex=0.5,  cex.axis = 0.5, font = 1,lwd=0.5,mgp=c(3, .6, 0))

#write data inside of bar plots
iotime<-rbind(iotimetasksettrue,iotimetasksetfalse)
cputime<-rbind(cputimetasksettrue,cputimetasksetfalse)


text(x=p+0.25, y=totaltime+totaltime*0.12, font = 2, font.lab = 2, labels=round(totaltime, 1), pos=3, xpd=NA, cex=0.4,srt=90)

text(x=p[c(-2,-4)]+0.22, y=totaltime[c(-2,-4)]-totaltime[c(-2,-4)]*0.42, font = 1, font.lab = 2, labels=round(cputime[c(-2,-4)], 1), pos=3, xpd=NA, cex=0.37,srt=90,col = "black")
text(x=p[c(2,4)]+0.22, y=totaltime[c(2,4)]-totaltime[c(2,4)]*0.37, font = 1, font.lab = 2, labels=round(cputime[c(2,4)], 1), pos=3, xpd=NA, cex=0.37,srt=90,col = "black")

text(x=p[c(-8,-10,-14)]+0.2, y=iotime[c(-8,-10,-14)]-iotime[c(-8,-10,-14)]*0.43, font = 1, font.lab = 2, labels=round(iotime[c(-8,-10,-14)], 1), pos=3, xpd=NA, cex=0.35,srt=90,col = "white")
text(x=p[c(8,10,14)]+0.2, y=iotime[c(8,10,14)]-iotime[c(8,10,14)]*0.35, font = 1, font.lab = 2, labels=round(iotime[c(8,10,14)], 1), pos=3, xpd=NA, cex=0.27,srt=90,col = "white")
box(lwd=0.5)

#lines(x=p[1]-2, y=min_y-min_y/5.5,lwd = 1, col = "grey")
text(x=(p1+p2)/2+1.7,  y=13, xnamestasksettrue, xpd=NA, srt=30, pos=2, font=1, cex=0.43)

legend("topright", regions, cex = 0.4, fill = regionscolors,lwd=0.5,box.lwd=0.5,col = regionscolors,border=regionscolors)

mtext("Total Serialize Time (sec) - log",  cex = 0.7, font=2,side=2,family="Helvetica",line =1.8, col="black" )
#mtext("Serialize Objects for 5M Tweets",  cex = 0.4, font=2,side=1,family="Helvetica" ,line = 1.3,col="black")

