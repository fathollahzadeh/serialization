library(plyr)
require(stats)

# function for clean data
cleandata <- function(data){
  
  max_value<-max(data)
  i<-1
  listlength<-length(data)
  finalindex<-1
  for(i in listlength:1){
    if(i!=1 && data[i]==max_value){
      finalindex<-i
      break()
      
    }
  }
  return(data)
}

plot_colors <- c("blue","green","red","gold4");
regions <- c("Seq (taskset false)", "Seq (taskset true)","Rand (taskset false)", "Rand (taskset true)")
pdf(file='Experiment_ReadObjects_Sequential_RAM.pdf', family="Helvetica",height=3, width=7)

#par(mfrow=c(3,5),oma=c(0,0,0,0),mar=c(2.9,3,1.5,0.5))
m <- matrix(c(1,2,3,4,5,6,7,8,9,10,11,12,13,14),nrow = 2,ncol = 7,byrow = TRUE)

layout(mat = m,heights = c(0.5,0.5))

# Hand Coded 

#CPP diagrams
for (i in 1:5){
  par(mar = c(3,1,1,1))
  
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
    txtmethod<-"C++ BSON"
  else if(i==6)
    txtmethod<-"C++ FlatBuffers"
  
  
  datatasksetfalse_seq <-read.delim(paste("data/C_Results/monitordata/mem__taskset_false_cppTwitterSequentialRead4000000", i,"_1.csv",  sep = ""), header=FALSE, sep=",")
  datatasksettrue_seq <-read.delim(paste("data/C_Results/monitordata/mem__taskset_true_cppTwitterSequentialRead4000000", i,"_1.csv",  sep = ""), header=FALSE, sep=",")
  datatasksetfalse_rand <-read.delim(paste("data/C_Results/monitordata/mem__taskset_false_cppTwitterRandomRead4000000", i,"_1.csv",  sep = ""), header=FALSE, sep=",")
  datatasksettrue_rand <-read.delim(paste("data/C_Results/monitordata/mem__taskset_true_cppTwitterRandomRead4000000", i,"_1.csv",  sep = ""), header=FALSE, sep=",")
  
  max_y<-datatasksetfalse_seq[1,2]
  max_y<-max_y;
  min_y<-0
  
  
  seq_ts_true<- cleandata(datatasksettrue_seq[,3])
  seq_ts_false<-cleandata(datatasksetfalse_seq[,3])
  rand_ts_true<-cleandata(datatasksettrue_rand[,3])
  rand_ts_false<-cleandata(datatasksetfalse_rand[,3])
  
  
  max_length<-max(length(seq_ts_true),length(seq_ts_false),length(rand_ts_true),length(rand_ts_false))
  min_length<-min(length(seq_ts_true),length(seq_ts_false),length(rand_ts_true),length(rand_ts_false))
  
  tempvector <- rep(0, max_length-min_length)
  
  needzero<-max(1,max_length-length(seq_ts_true))
  seq_ts_true<-c(seq_ts_true,tempvector[1:needzero])
  
  needzero<-max(1,max_length-length(seq_ts_false))
  seq_ts_false<-c(seq_ts_false,tempvector[1:needzero])
  
  needzero<-max(1,max_length-length(rand_ts_true))
  rand_ts_true<-c(rand_ts_true,tempvector[1:needzero])
  
  needzero<-max(1,max_length-length(rand_ts_false))
  rand_ts_false<-c(rand_ts_false,tempvector[1:needzero])
  
  
  num_g_memory=round((max_y/1024)+0.5);
  y_labels_memory<- sprintf("%s",seq(0,num_g_memory,4));
  
  
  
  
  plot(seq_ts_true,type = "S",log="x", col = plot_colors[1], xlab = "", ylab = "", main = "",lwd=1,pch=15,ylim=c(0,max_y),xaxs="i", yaxs="i",frame.plot = FALSE,axes = FALSE);
  
  axis(side=2, at=seq(min_y,num_g_memory*1024,4*1024), labels=y_labels_memory, las=2 ,cex.axis=0.6)
  axis(side=1, pos=0.0, lwd.ticks=1,cex.axis=0.6)
  
  #grid(nx = 10);
  
  #lines(seq_ts_false, type = "S", col = plot_colors[2],lwd=1)
  lines(rand_ts_true, type = "S", col = plot_colors[3],lwd=1)
  #lines(rand_ts_false, type = "S", col = plot_colors[4],lwd=1)
  
  
  
  text(max_length/3, (num_g_memory-3)*1024, txtmethod, cex=0.6)
  
  #title(ylab="Memory Load(Gigabyte)", line=2, cex.lab=0.6)
  #title(xlab="Time(second)", line=2, cex.lab=0.6)
  
  box()
}


plot(1, type = "n", axes=FALSE, xlab="", ylab="")
legend(x = "top",inset = 0, legend = regions, col=plot_colors, lwd=1, cex=0.7, horiz = FALSE)


#------------------------------