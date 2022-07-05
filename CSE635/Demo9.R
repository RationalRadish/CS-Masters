d=read.csv("cheese.txt",sep="\t",header=TRUE) 
head(d)
str(d)
p1=d$FREQ/52
p1=matrix(p1,nrow = 9,ncol = 4)
p1
#Ranking D>A>C>B based on the initial probabilities (or maximal probabilities)
#Then we compute the average of each column using the dot product
#This is the average grade people gave for each type. 
average_a = sum((1:9) * p1[,1])
average_b = sum((1:9) * p1[,2])
average_c = sum((1:9) * p1[,3])
average_d = sum((1:9) * p1[,4])
#order based on comparing grade averages = highest average (7.42 ) that belongs to D.
# This is followed by A, followed by C, followed by B.

#Method 3 is to look at the variances to find out which one of these distributions has the
#highest variance or std. dev

#Method 4 is to look at the entropy to find out which one has the smallest. 

#First model is polr which is in MASS library
library(MASS)
d$Y=as.factor(d$Y) #Response variable has to be changed to categorical variable.
m=polr(d$Y ~ d$Type, weights = d$FREQ) #weights are the probabilities.
summary(m)
#In order to find the probabilites from the fitted results we must do
fitted_values <-  m$fitted.values
# m$fitted.values[1,9] <- probability that A received a grade of 9
# every grade has 9 rows alloted to it. So rows 1-9 are grade A. Rows 10 - 18 are B.
# The column values are the likelihood of receiving the result so [1,1] gives the
# likelihood of cheese A receiving a rank of 1.
library(nnet)
m=multinom(d$Y ~ d$Type, weights = d$FREQ)
