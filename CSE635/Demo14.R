require(neuralnet)
library(neuralnet)
#First Example: Prediction of Binary Dependent variable. Data set is infert
str(infert)
dim(infert)
#Select the significant independent variables
m=lm(case~. - case, data = infert)
summary(m)
#Selected ind. var = age,parity, induced, spontaneous, pooled.stratum
m=neuralnet(case~age+parity+induced+spontaneous+pooled.stratum,data = infert, hidden = 2,err.fct = "ce",linear.output = FALSE)
m$result.matrix
plot(m)
pred=predict(m,infert)
p=ifelse(pred[1] < 0.5, 0, 1)
for (i in 2:length(pred)) {p=c(p,ifelse(pred[i] < 0.5 , 0, 1))}
table(p)
table(infert$case)
c=table(p, infert$case)
c
ACC_infert=sum(diag(c))/sum(c)
ACC_infert
#Splitting dataset
set.seed(932)
ind=sample(2,nrow(infert),replace = TRUE, prob = c(0.7, 0.3))
training=infert[ind == 1,]
testing=infert[ind == 2,]
nn=neuralnet(case~age+parity+induced+spontaneous+pooled.stratum,data = training,hidden = 2,err.fct = "ce",linear.output = FALSE)
nn$result.matrix
plot(nn)
pred=predict(nn,training)
p=ifelse(pred[1] < 0.5, 0, 1)
for (i in 2:length(pred)) {p=c(p,ifelse(pred[i] < 0.5 , 0, 1))}
table(p)
table(training$case)
c=table(p, training$case)
c
ACC_training_infert=sum(diag(c))/sum(c)
ACC_training_infert
pred=predict(nn,testing)
p=ifelse(pred[1] < 0.5, 0, 1)
for (i in 2:length(pred)) {p=c(p,ifelse(pred[i] < 0.5 , 0, 1))}
table(p)
table(testing$case)
c=table(p, testing$case)
c
ACC_testing_infert=sum(diag(c))/sum(c)
ACC_testing_infert
#Second Example: Prediction of 3 levels  Dependent variable. Data set is iris
m=neuralnet(Species~Sepal.Length+Sepal.Width+Petal.Length+Petal.Width,data = iris,hidden = 2,err.fct = "ce",linear.output = FALSE)
m$result.matrix
plot(m)
pred=predict(m,iris) 
p=apply(pred, 1, which.max) #which column has the max probability value
table(p)
table(iris$Species)
c=table(p,iris$Species)
c
ACC_iris=sum(diag(c))/sum(c)
ACC_iris
#Splitting data set
set.seed(497)
ind=sample(2,nrow(iris),replace = TRUE, prob = c(0.7, 0.3))
training=iris[ind == 1,]
testing=iris[ind == 2,]
nn=neuralnet(Species~Sepal.Length+Sepal.Width+Petal.Length+Petal.Width,data = training,hidden = 2,err.fct = "ce",linear.output = FALSE)
plot(nn)
pred=predict(nn,training)
p=apply(pred, 1, which.max)
c=table(p,training$Species)
c
ACC_training_iris=sum(diag(c))/sum(c)
ACC_training_iris
pred=predict(nn,testing)
p=apply(pred, 1, which.max)
c=table(p,testing$Species)
c
ACC_testing_iris=sum(diag(c))/sum(c)
ACC_testing_iris
