d=read.csv("CTG.txt", sep = "\t", header = TRUE)
drops <- c("X","X.1", "X.2")
d <- d[ , !(names(d) %in% drops)]
nrow(d)
ncol(d)
summary(d)

#First set the seed so we get reproducible results
set.seed(854)
#Split dataset d
ind=sample(2,nrow(d),replace = TRUE, prob = c(0.8, 0.2))
train=d[ind == 1,]
test=d[ind == 2,]
nrow(train)
nrow(test)
nrow(d)
#NSP LEVELS 1 = Normal, 2 = Suspect, 3 = pathological
## Use the lm model to find the significant variables using all of the independent variables
#Use the training data for this exercise.
m=lm(NSP~.,data = train,  na.action=na.exclude)
summary(m)
#Run the model again without the non significant variables
m=lm(NSP~.-LB-AC-UC-DS-MSTV-MLTV-Width-Min-Max-Nmax-Mode-Mean-Median-Variance-Tendency-SUSP-CLASS,data = train)
summary(m)
y=m$fitted.values
plot(y)
p=ifelse(y < 1.5, 1, ifelse(y < 2.5, 2, 3)) #discretize the input into formal buckets
                                            # the buckets based on visual of data. Just set a level

length(p)
length(train$NSP)
c=table(p,train$NSP) #confusion table for the training data
c
#accuracy
sum(diag(c))/sum(c)
#sensitivity
#Divide the confusion entries by the columns for sensitivity
#Each column/Sum(each column)
cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))
#You can use the test data set with trained lm model
y=predict(m,test)
#quantize the values again into 3 buckets based on viz of data
p=ifelse(y < 1.5, 1, ifelse(y < 2.5, 2, 3))
length(p)
length(test$NSP)
#Confusion matrix
c=table(p,test$NSP)
c
#accuracy
sum(diag(c))/sum(c)
#sensitivity
cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))
#ordinal prediction or proportional ordinal logistic regression
#We must change the variable to be ordinal for the classification task
d$NSP=as.ordered(d$NSP)
library(MASS)
#Split dataset d
ind=sample(2,nrow(d),replace = TRUE, prob = c(0.8, 0.2))
train=d[ind == 1,]
test=d[ind == 2,]
m1=polr(NSP~FM+DL+DP+ASTV+ALTV+Nzeros+A+B+C+D+AD+DE+LD+FS, data = train, Hess = TRUE)
summary(m1)
p=predict(m1,train)
length(train$NSP)
length(p)
c=table(p,train$NSP)
c
#accuracy
sum(diag(c))/sum(c)
#sensitivity
cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))
p=predict(m1,test)
length(test$NSP)
length(p)
c=table(p,test$NSP)
c
#accuracy
sum(diag(c))/sum(c)
#sensitivity
cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))
#Compute p value of the coefficients 
#Testing of hypothesis that these coefficients are significant
(ctable = coef(summary(m1)))
pb=pnorm(abs(ctable[,"t value"]), lower.tail = FALSE)*2
(ctable = cbind(ctable, "p value" = pb))
#Now we run the multinomial model.
#Change the Y dependent variable to a factor.
d$NSP=as.factor(d$NSP)
library(nnet)
m2=multinom(NSP~FM+DL+DP+ASTV+ALTV+Nzeros+A+B+C+D+AD+DE+LD+FS, data = train)
summary(m2)
p=predict(m2,train)
length(p)
length(train$NSP)
c=table(p,train$NSP)
c
#accuracy
sum(diag(c))/sum(c)
#sensitivity
cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))
p=predict(m2,test)
length(p)
length(test$NSP)
c=table(p,test$NSP)
c
#accuracy
sum(diag(c))/sum(c)
#sensitivity
cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))

