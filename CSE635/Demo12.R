#Prediction using k-means clustering
#Model in which there are a number of observation that could be clustered together
#The number of clusters will be dependent on the different levels of the dependent variable.
#Dimensionality of a dataset is the number of independent variables.
#Compute summary statistics of independent variable; dataset = iris
#Independent variables = iris[,-5]; 5th column is the dependent variable Species
#covariance square matrix with d by d. D is the dimension of the dataset 
#Summary statistics of the dataset includes:
#column means,column variance/std. deviation,and the correlation matrix
#The correlation matrix with diagonal element = 1 and the off diagonal elements 
#are the correlations coeeficents of two different variables
#Now we find the means and sd of each column
colMeans(iris[,-5])
c(sd(iris[,1]),sd(iris[,2]),sd(iris[,3]),sd(iris[,4]))
#Column 3 has the highest variability.
#Before doing clustering, we need to preprocess the data.
#Normalization or scaling is the first step
#The mean of the variables in the dataset has to be normalized to 0. The std. normalized to 1
#Use the scale command to normalize all numerical independent variables
Niris=scale(iris[,-5])
#scale guarantees that each column mean is 0.
colMeans(Niris)
c(sd(Niris[,1]),sd(Niris[,2]),sd(Niris[,3]),sd(Niris[,4]))
#It is obvious that scale transformation generates the Normalized data
#with zero means and unity standard deviations
#Now we are ready to perform kmeans clustering with number of clusters
#equals to the number of dependent variable levels
str(iris$Species)
m=kmeans(Niris, 3)
summary(m)
attributes(m)
p=m$cluster
table(p)
table(iris$Species)
c=table(p,iris$Species)
c
#ACCURACY
#Sometime the max value will not be in the diagonal so calculate the accuracy
#using the max function
ACC=(max(c[,1])+max(c[,2])+max(c[,3]))/sum(c)
ACC
#SENSITIVITY
SEN=cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))
SEN
#Now let's split the dataset in to training and testing subsets
#Training and Testing subsets 70/30 split
set.seed(497)
ind=sample(2,nrow(iris),replace = TRUE, prob = c(0.7, 0.3))
training=iris[ind == 1,]
testing=iris[ind == 2,]
nrow(training)
nrow(testing)
nrow(iris)
#Calculate the means of each column for the training dataset
mn=colMeans(training[,-5])
#Calculate the sd of  column for the training dataset
s=c(sd(training[,1]),sd(training[,2]),sd(training[,3]),sd(training[,4]))
#Create a covariance matrix
cv=cov(training[,-5])
mn
s
cv #the diagonals of this will not equal 1 because it is only a subset of the data.
Normalized_training=cbind((training[,1]-mn[1])/s[1],(training[,2]-mn[2])/s[2],(training[,3]-mn[3])/s[3],(training[,4]-mn[4])/s[4])
colMeans(Normalized_training)
cov(Normalized_training) # This has 1s along the diagonal, which means the std dev is 1
                         # off diagonal is between 1 and -1
#Then perform kmeans model using Normalized_training and k = 3
m=kmeans(Normalized_training,3)
p=m$cluster
table(p)
table(training$Species)
c=table(p,training$Species)
c
#ACCURACY
ACC_training=(max(c[,1])+max(c[,2])+max(c[,3]))/sum(c)
ACC_training
#SENSITIVITY
SEN_training=cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))
SEN_training
##The data that we have is just a collection of points
#Each row is the cluster with four coordinates
cntrs=m$centers
cntrs
#Training results are mn, s, and cntrs
#Now we are ready to do predictions using the testing subset
#First: Normalize testing subset using the training subset
Normalized_testing=cbind((testing[,1]-mn[1])/s[1],(testing[,2]-mn[2])/s[2],(testing[,3]-mn[3])/s[3],(testing[,4]-mn[4])/s[4])
colMeans(testing[,-5]) #The means are close to 0.
colMeans(Normalized_testing) 
cov(testing[,-5]) 
cov(Normalized_testing) # Now the covariances are close to 1. 
#Second: do row combined or rbind of Normalized_testing and cntrs, 
#then compute distances
#prediction is not done by a model, but through this rbind (row wise bind)
d=rbind(Normalized_testing,cntrs)
class(d)
nrow(d)
nrow(Normalized_testing)
ncol(d)
ncol(Normalized_testing)
#Look at the distances of the combined table. 
#It is a Cartesian difference function.
x=dist(d)
class(x)
x=as.matrix(x)
#Next we need to compute the distances between the three centers and each of testing records
y=x[45:47,1:44] #We get these numbers from the 44 data points of normalized testing
                #And the last 3 rows are the centers that we just appended to x.
                #The data in y will now have 3 rows with 44 columns.
#Go through each column and find the min and concat to df
p=which.min(y[,1]) #Now we get the min which will be our prediction.
for (i in 2:44) {p=c(p,which.min(y[,i]))}
length(p)
length(testing$Species)
table(p)
table(testing$Species)
c=table(p,testing$Species)
c
#ACCURACY
ACC_testing=(max(c[,1])+max(c[,2])+max(c[,3]))/sum(c)
ACC_testing
#SENSITIVITY
SEN_testing=cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))
SEN_testing
