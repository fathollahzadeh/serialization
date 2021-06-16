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
      tspace<-space*20
    else if(j>listlength*0.25)
      tspace<-space*7
    else if(j>listlength*0.15)
      tspace<-space*2
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
rustcount=10*2

# load data for 5M objects write 
datajo = calulateMeanDataTimeBar("data/Java_Results/readobjects/result_java_readobjects_4000000_",3 , javacount)
dataco = calulateMeanDataTimeBar("data/C_Results/readobjects/result_cpp_readobjects_4000000_",3 , cppcount)
dataro = calulateMeanDataTimeBar("data/Rust_Results/readobjects2/result_rust_readobjects_4000000_",1 , rustcount)

dataj <- subset(datajo,seq=="false"  & datatype=="TweetStatus")
datac <- subset(dataco,seq=="false" & datatype=="TweetStatus")
datar <- subset(dataro,seq=="false" & datatype=="TweetStatus")

data <- rbind(datac,dataj,datar)

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


data <- rbind(cppHandCoded,cppProtoBuf,cppFlatBuf,cppInPlace,cppBoost,cppBson,rustBincode,rustMessagePack,rustFlexBuffers,rustJson,rustBson,javaFlatBuf,javaProtoBuf,javaKryo,javaByteBuffer,javaBson,javaJson,javaDefault)


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
pdf(file='Experiment_Rand_Read_CPU_IO_Bar.pdf',family="Helvetica",height=2, width=8)
par(mar = c(1.5, 2.3, 0.1, 0.1)) 

max_y<-max(totaltimetasksettrue,totaltimetasksetfalse)
max_y<-max_y+max_y*0.1;
min_y<-min(iotimetasksettrue,iotimetasksetfalse)/1.3 

# draw bar plots
p1 <- barplot(valuestasksettrue,log="y",,xaxs="i",  xlim = c(-0.2, 54),col=colorstasksettrue, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y*1.7), legend.text=TRUE, axes=FALSE,border =colorstasksettrue, space=c(0.2,1.85,1.85,1.85,1.85,1.85,3,1.85,1.85,1.85,1.85,3.5,1.85,1.85,1.85,1.85,1.85,1.85))

p2 <- barplot(valuestasksetfalse,log="y",,xaxs="i", xlim = c(-0.2, 54),col=colorstasksetfalse, ylim = c(min_y,  max(max_y,na.rm = TRUE)+max_y*1.7), add=T,border =colorstasksetfalse, space=c(1.4,1.85,1.85,1.85,1.85,1.85,3,1.85,1.85,1.85,1.85,3.5,1.85,1.85,1.85,1.85,1.85,1.85),axes=FALSE)

p<-rbind(p1,p2)


# write y labels:
totaltime<-rbind(totaltimetasksettrue,totaltimetasksetfalse)
z<-rbind(totaltimetasksettrue,totaltimetasksetfalse,iotimetasksettrue,iotimetasksetfalse)
z<-z[sort.list(z)]
z <-c(min_y,z,max_y)
z<-calulateaxes(z,2.5)
axis(2, las=1, at = z, labels=round(z, digits=0),cex=0.5,  cex.axis = 0.5, font = 1,lwd=0.5,mgp=c(3, .5, 0),tck = -0.03)

#write data inside of bar plots
iotime<-rbind(iotimetasksettrue,iotimetasksetfalse)
cputime<-rbind(cputimetasksettrue,cputimetasksetfalse)


text(x=p+0.20, y=totaltime+totaltime*0.2, font = 2, font.lab = 1, labels=round(totaltime, 1), pos=3, xpd=NA, cex=0.4,srt=90)

#text(x=p+0.22, y=totaltime-totaltime*0.55, font = 1, font.lab = 2, labels=round(cputime, 1), pos=3, xpd=NA, cex=0.4,srt=90,col = "black")
#text(x=p[c(1,2,24)], y=totaltime[c(1,2,24)]-totaltime[c(1,2,24)]*0.45, font = 1, font.lab = 2, labels=round(cputime[c(1,2,24)], 1), pos=3, xpd=NA, cex=0.4,srt=90,col = "black")
#text(x=p[c(5,6)], y=totaltime[c(5,6)]-totaltime[c(5,6)]*0.45, font = 1, font.lab = 2, labels=round(cputime[c(5,6)], 1), pos=3, xpd=NA, cex=0.4,srt=0,col = "black")

text(x=p[c(-15,-16)]+0.22, y=iotime[c(-15,-16)]-iotime[c(-15,-16)]*0.5, font = 1, font.lab = 2, labels=round(iotime[c(-15,-16)], 1), pos=3, xpd=NA, cex=0.4,srt=90,col = "white")
#text(x=p[c(3,4)], y=iotime[c(3,4)]-iotime[c(3,4)]*0.47, font = 1, font.lab = 2, labels=round(iotime[c(3,4)], 1), pos=3, xpd=NA, cex=0.3,srt=0,col = "white")
box(lwd=0.5)

#lines(x=p[1]-2, y=min_y-min_y/5.5,lwd = 1, col = "grey")
text(x=(p1+p2)/2+1,  y=9.5, xnamestasksettrue, xpd=NA, srt=18, pos=2, font=1, cex=0.5)

legend("topleft", regions, cex = 0.45, fill = regionscolors,lwd=0.5,box.lwd=0.5,col = regionscolors,border=regionscolors)

mtext("Random Read Time (minut) - log",  cex = 0.6, font=2,side=2,family="Helvetica",line =1.65, col="black" )
#mtext("Serialize Objects for 5M Tweets",  cex = 0.4, font=2,side=1,family="Helvetica" ,line = 1.3,col="black")


