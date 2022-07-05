head(iris)
nrow(iris)
ncol(iris)
str(iris)
#set the seed to be constant in order to have the same split in every time
set.seed(978)
ind=sample(2,nrow(iris),replace = TRUE, prob = c(0.8,0.2))
training = iris[ind == 1,]
testing = iris[ind == 2,]
nrow(iris)
nrow(training)
nrow(testing)
#Linear model using training dataset
#Encode Species (categorical variable) into levels 0, 1, 2 based on value
y=ifelse(training$Species=="setosa",0,(ifelse(training$Species=="versicolor",1,2)))
table(y)
#Now we notice that Y has the same distribution as the independent variables.
#Linear Model so each one of these independent variables are numerical
m1=lm(y~training$Sepal.Length+training$Sepal.Width+training$Petal.Length+training$Petal.Width)
#Now we should look at the SSE, Rsquared, and Pvalues of the independent variables
summary(m1)
# Create a variable called yhat that is the line of predicted values
yh=m1$fitted.values
#Now plot yhat
plot(yh)
# We notice that Yhat creates clusters, even though we are using numerical data.
#Now we need to quantize yh into three levels
#Quantize is another way of saying buckets
mx=max(yh)
mn=min(yh)
s=(mx-mn)/3 # This is the step size
t1=mn+s # group 1
t2=mx-s # group 2
p=ifelse(yh < t1, 0,(ifelse(yh < t2,1,2))) #if/else logic to create 3 groups based on yhat.
t=table(y,p) # confusion matrix
t
ACC=sum(diag(t))/sum(t)
ACC
c=m1$coefficients
c
#Now we do prdiction using testing dataset. Let's start by building matrix X
X=cbind(rep(1,nrow(testing)),testing[,-5]) #Lefthand column for 1s and then the values of the 
                                           #independent variables
head(X)
class(X)
X=as.matrix(X)
#The following matrix multiplication computes the response of m1 using testing dataset
c=as.matrix(c) # c is a matrix of coefficient values from the earlier linear model
yh=X%*%c # matrix multiplication. This will give us yhat using the testing dataset.
plot(yh) #now repeat the process we did for the training data set for the testing dataset
mx=max(yh) #quantization process 
mn=min(yh) 
s=(mx-mn)/3
t1=mn+s
t2=mx-s
p=ifelse(yh < t1, 0,(ifelse(yh < t2,1,2))) #predictors
t=table(testing$Species,p) #confusion table of the testing dataset
t
ACC=sum(diag(t))/sum(t)
ACC
library(nnet)
m=multinom(Species~.,data = training) #multinomial is part of the neural network library
                                      #multinomial model means we don't need to encode the 
                                      #variable
p=predict(m) #predictors
t=table(training$Species,p) #confusion table
t
sum(diag(t))/sum(t) #accuracy of the training set
c=coefficients(m) # we need to extract the coefficients for evaluation
c #the two rows correspond to the second and third flower. The first flower is in the intercept.
#Now we do prediction using testing dataset. set start by building matrix X
X=cbind(rep(1,nrow(testing)),testing[,-5]) #Same as the linear model. We need a matrix of
                                          # the independent variable observations with a column
                                         # of 1s on the LFH
head(X)
str(X)
class(X)
X=as.matrix(X)
#Let's compute the response of testing using coeff. c
Y=X%*%t(c) #These are the logit values which are the log of the odds. Now we need to 
           #calculate the probabilities. That means we need to get the inverse of the log.
# In this step, we are multiplying the matrix of independent variables with 1s * 
# transposed vector of the fitted coefficent values.
head(Y)
Y=exp(Y) # This is why we need to use the exp function for the Y value.
head(Y)  # Now we have the predicted odds relative to the probability of the first species
         # Next we need to convert the odds into probability. 
        #Do 1/1+each of the Y columns
pb=cbind(1/(1+Y[,1]+Y[,2]),Y[,1]/(1+Y[,1]+Y[,2]),Y[,2]/(1+Y[,1]+Y[,2]))
#every row now adds up to 1. For instance, row 1 shows the probability of 
# belonging to the first species
head(pb)
#predicted species type corresponds to the index of maximum prob
p=which.max(pb[1,])
for (i in 2:nrow(testing)) {p=c(p, which.max(pb[i,]))} #find the maximum for the testing
                                                      #rows in the data.
p
t=table(testing$Species,p)
t
sum(diag(t))/sum(t)
