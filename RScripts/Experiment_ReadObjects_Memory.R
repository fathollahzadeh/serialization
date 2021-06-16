library(plyr)
require(stats)


#--------------------------------------------------------------

plot_colors <- c("blue","green","red","gold4");
regions <- c("Seq (taskset false)", "Seq (taskset true)","Rand (taskset false)", "Rand (taskset true)")
pdf(file='Experiment_ReadObjects_Memory.pdf', family="Helvetica",height=2, width=3.5)#

value <- matrix(nrow= 1, ncol=18)

#value <- matrix( c(iotimetasksettrue, cputimetasksettrue), nrow = 4, ncol = 13, byrow = TRUE)

methods<- vector() 

#CPP diagrams
j<-1
for (i in 1:6){

  txtmethod<-""
  if(i==1)
    txtmethod<-"C++ HandCoded"
  else if(i==2)
    txtmethod<-"C++ InPlace"
  else if(i==3)
    txtmethod<-"C++ Boost"
  else if(i==4)
    txtmethod<-"C++ ProtoBuf"
  else if(i==5)
    txtmethod<-"C++ Bson"
  else if(i==6)
    txtmethod<-"C++ FlatBuffers"
  
  summemory=0
  for (j in 1:3){
    datatasksetfalse_seq <-read.delim(paste("data/monitordata/mem__taskset_false_cppTwitterSequentialRead4000000", i,"_",j,".csv",  sep = ""), header=FALSE, sep=",")  
    summemory<-summemory+max(datatasksetfalse_seq[,3])
  }
  
  seq_ts_false<- summemory/3 
  
  value[1,i]<-seq_ts_false
  methods[i]<-txtmethod
}

#Rust diagrams
for (i in 1:5){
  
  txtmethod<-""
  if(i==1)
    txtmethod<-"Rust Json"
  else if(i==2)
    txtmethod<-"Rust Bincode"
  else if(i==3)
    txtmethod<-"Rust MessagePack"
  else if(i==4)
    txtmethod<-"Rust Bson"
  else if(i==5)
    txtmethod<-"Rust FlexBuffers"
 
  
  summemory=0
  for (j in 1:3){
    datatasksetfalse_seq <-read.delim(paste("data/monitordata2/mem__taskset_false_rustTwitterSequentialRead4000000", i,"_1.csv",  sep = ""), header=FALSE, sep=",")  
    summemory<-summemory+max(datatasksetfalse_seq[,3])
  }
  
  seq_ts_false<- summemory/3 
  
  value[1,i+6]<-seq_ts_false
  methods[i+6]<-txtmethod
}


#Java diagrams
for (i in 1:7){

    txtmethod<-""
  if(i==1)
    txtmethod<-"Java Default"
  else if(i==2)
    txtmethod<-"Java Json+Gzip"
  else if(i==3)
    txtmethod<-"Java Bson"
  else if(i==4)
    txtmethod<-"Java ProtoBuffer"
  else if(i==5)
    txtmethod<-"Java Kryo"
  else if(i==6)
    txtmethod<-"Java Byte Buffer"
  else if(i==7)
    txtmethod<-"Java FaltBuffers"
  
  summemory=0
  for (j in 1:2){
    datatasksetfalse_seq <-read.delim(paste("data/monitordata/mem__taskset_false_javaTwitterSequentialRead4000000", i,"_",j,".csv",  sep = ""), header=FALSE, sep=",")
    summemory<-summemory+max(datatasksetfalse_seq[,3])
  }
  seq_ts_false<- summemory/2
  
  value[1,i+11]<-seq_ts_false
  methods[i+11]<-txtmethod
}


sortvalue <- matrix(nrow= 1, ncol=18)
sortvalue[,1]<-value[,2]
sortvalue[,2]<-value[,6]
sortvalue[,3]<-value[,1]
sortvalue[,4]<-value[,3]
sortvalue[,5]<-value[,4]
sortvalue[,6]<-value[,5]

sortvalue[,7]<-value[,8]
sortvalue[,8]<-value[,9]
sortvalue[,9]<-value[,11]
sortvalue[,10]<-value[,7]
sortvalue[,11]<-value[,10]

sortvalue[,12]<-value[,17]
sortvalue[,13]<-value[,14]
sortvalue[,14]<-value[,13]
sortvalue[,15]<-value[,16]
sortvalue[,16]<-value[,12]
sortvalue[,17]<-value[,15]
sortvalue[,18]<-value[,18]

methods<-c(methods[2],methods[6],methods[1],methods[3],methods[4],methods[5],methods[8],methods[9],methods[11],methods[7],methods[10],methods[17],methods[14],methods[13],methods[16],methods[12],methods[15],methods[18])

par(mar = c(2.6, 1.7, 0.1, 0.1)) 
num_g_memory=32
y_labels_memory<- sprintf("%s",seq(10,num_g_memory,2))

p <- barplot(sortvalue-10*1024,density=25, ,xlim = c(-0.2, 54),yaxs="i",xaxs="i", ylim = c(10*1024,  36*1024),legend.text=TRUE, axes=FALSE,border ="gray67",beside = TRUE,offset = 10*1024,width=2, space=c(0.2,0.4,0.4,0.4,0.4,0.4,1.3,0.4,0.4,0.4,0.4,1.3,0.4,0.4,0.4,0.4,0.4,0.4))
axis(side=2, at=seq(10*1024,num_g_memory*1024,2*1024),labels=y_labels_memory,lwd.ticks=1,cex.axis=0.5,las=1,mgp=c(5, .4, 0),tck = -0.03)

abline(h= seq(10*1024,num_g_memory*1024,2*1024),lty=3, col="gray")

text(x=p+0.2, y=sortvalue+600, font = 2, font.lab = 2, labels=round(sortvalue/1024, 2), pos=3, xpd=NA, cex=0.4,srt=90)
#print(p)
text(x=p+1.7,  y=9600, methods, xpd=NA, srt=40, pos=2.1, font=1, cex=0.5)

mtext("Total Memory Used(gigabayte)", cex = 0.55, font=0.5,side=2,family="Helvetica",line = 1.1, col="black" )
#mtext("Read Objects for 4M Tweets",cex = 0.6, font=0.5,side=1,family="Helvetica" ,line = 2.3,col="black")

#regions <- c("Seq (taskset true)", "Seq (taskset false)","Rand (taskset true)", "Rand (taskset false)")
#legend("topleft", regions, cex = 0.5, fill = my_colors)
box()