library(plyr)
require(stats)


pdf(file='Experiment_ReadObjects_Sequential_Memory.pdf', family="Helvetica",height=3.5, width=10)#,,

#par(mfrow=c(3,5),oma=c(0,0,0,0),mar=c(2.9,3,1.5,0.5))
m <- matrix(c(1,2),nrow = 1,ncol = 2,byrow = TRUE)

layout(mat = m,widths =c(0.8,0.2))

op <- par(mar = c(2,3,1,1))

size_g<-32
step_g<-8
rep_count<-5
memory_size<-size_g*1024
memory_step<-step_g*1024


max_y=rep_count*memory_size
min_y=0

max_x=15000
min_x=0

memory_labels<-sprintf("%s g",seq(0,size_g,step_g))
object_count_label<-c("1 M","2 M","3 M","4 M","5 M")
serialization_methods<-c("C++ HandCoded","C++ InPlace","C++ ProtoBuf","C++ Boost","C++ Bson","C++ FlatBuf","Java Default","Java Json+Gzip","Java Bson","Java ProtoBuf","Java Kryo","Java ByteBuffer","Java FlatBuf")

#memory_labels<-c(memory_labels,"")

y_labels<-rep(memory_labels[-1],rep_count)

y_labels<-c("0 g",y_labels)

plot(1, type="o", pch=1, lty=2,lwd=1, ylim=c(min_y, max_y),xlim = c(min_x,max_x), axes=FALSE, ann=FALSE, yaxs="i",xaxs="i")

tt<-seq(min_y,max_y,memory_step)


abline(h=c(memory_size,2*memory_size,3*memory_size,4*memory_size),col="gray",lwd=0.1)

#draw vertical lines
l<-seq(min_x,max_x,(max_x-min_x)/13)
abline(v=l,col="gray",lwd=0.1)



axis(side=4, at=seq(min_y,max_y,memory_step), labels=y_labels, las=2 ,cex.axis=0.4)

axis(side=2, at=c(memory_size,2*memory_size,3*memory_size,4*memory_size),col="gray",lwd=0.1,labels = FALSE)
axis(side=2, at=seq(16*1024,max_y,memory_size), labels=object_count_label, lwd.tick=0 ,cex.axis=0.6)

#axis(side=1, pos=0.0, lwd.ticks=1,cex.axis=0.6)

grid(nx = 40);
box()
