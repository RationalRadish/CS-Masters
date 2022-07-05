# There are two techniques to use to normalize data
# - mean/std deviation (this is like the scale function in R.)
# - min/max method 
# - The goal is to standardize the mean to 0 and the std. deviation to be 1

#Prediction using hclust clustering
#Compute summary statistics of independent variables; dataset = iris
#Independent variables = iris[,-5]; 5th column is the dependent variabile Species
colMeans(iris[,-5])
c(sd(iris[,1]),sd(iris[,2]),sd(iris[,3]),sd(iris[,4]))
#Use the scale command to normalize all numerical independent variables
Niris=scale(iris[,-5])
colMeans(Niris)
c(sd(Niris[,1]),sd(Niris[,2]),sd(Niris[,3]),sd(Niris[,4]))
#It is obvious that scale transformation generates the Normalized data
#with zero means and unity standard deviations
#Now we are ready to perform hclust clustering with number of clusters
#equals to the number of dependent variable levels
str(iris$Species)
#Hierarchical Clustering using Niris
#After standardization, then we use the distance function for the four variables
#distance function is used to build the vector quantization
d=dist(Niris)
class(d)
#Then perform hclust model using d
m=hclust(d, "ward.D2") #ward.D2 is a method of hclust
plot(m)
#Specify number of clusters to be three
rect.hclust(m,k=3,border = "Red")
#Predictions
clusters=cutree(m,3)
length(clusters)
table(clusters)
length(iris$Species)
table(iris$Species)
c=table(clusters,iris$Species)
c
#ACCURACY
ACC=(max(c[,1])+max(c[,2])+max(c[,3]))/sum(c)
ACC
#SENSITIVITY
SEN=cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))
SEN
##Now we just do the same as above but use the min/max method
#It results in a better predictive model
#Min/Max Normalization
Niris=cbind((iris[,1]-min(iris[,1]))/(max(iris[,1])-min(iris[,1])),(iris[,2]-min(iris[,2]))/(max(iris[,2])-min(iris[,2])),(iris[,3]-min(iris[,3]))/(max(iris[,3])-min(iris[,3])),(iris[,4]-min(iris[,4]))/(max(iris[,4])-min(iris[,4])))
d=dist(Niris)
m=hclust(d, "ward.D2")
plot(m)
rect.hclust(m, k=3,border = "Red")
clusters=cutree(m, 3)
c=table(clusters,iris$Species)
c
ACC=(max(c[,1])+max(c[,2])+max(c[,3]))/sum(c)
ACC
SEN=cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))
SEN
#Training and Testing subsets
set.seed(497)
ind=sample(2,nrow(iris),replace = TRUE, prob = c(0.7, 0.3))
training=iris[ind == 1,]
testing=iris[ind == 2,]
mn=colMeans(training[,-5])
s=c(sd(training[,1]),sd(training[,2]),sd(training[,3]),sd(training[,4]))
cv=cov(training[,-5])
mn
s
cv
nrow(training)
nrow(testing)
nrow(iris)
Normalized_training=cbind((training[,1]-mn[1])/s[1],(training[,2]-mn[2])/s[2],(training[,3]-mn[3])/s[3],(training[,4]-mn[4])/s[4])
colMeans(Normalized_training)
cov(Normalized_training)
#Perform hclust model using dist(Normalized_training) and k = 3
d=dist(Normalized_training)
m=hclust(d, "ward.D2")
plot(m)
rect.hclust(m,k=3,border = "Red")
clusters=cutree(m,3) # cut the tree down to the right number of clusters
length(clusters)
length(training$Species)
table(clusters)
table(training$Species)
c=table(clusters,training$Species)
c
#ACCURACY
ACC_training=(max(c[,1])+max(c[,2])+max(c[,3]))/sum(c)
ACC_training
#SENSITIVITY
SEN_training=cbind(c[,1]/sum(c[,1]),c[,2]/sum(c[,2]),c[,3]/sum(c[,3]))
SEN_training
#Please notice that hclust model does not compute the coordinates of the centers
#Therefore we have to do it
#we need to split the Normalized training into three subsets c1, c2, and c3
c1=Normalized_training[clusters == 1,]
c2=Normalized_training[clusters == 2,]
c3=Normalized_training[clusters == 3,]
nrow(c1)
nrow(c2)
nrow(c3)
cntrs=rbind(colMeans(c1),colMeans(c2),colMeans(c3))
cntrs
#Now we can do predictions using Normalized testing data
d=rbind(Normalized_testing,cntrs)
nrow(d)
nrow(Normalized_testing)
x=dist(d)
x=as.matrix(x)
y=x[45:47,1:44]
p=which.min(y[,1])
for (i in 2:44) {p=c(p,which.min(y[,i]))}
length(p)

