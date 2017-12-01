#comments
print('Our script works')

dataset = read.csv('cats.csv')

#to determine what is the class
class(dataset)

#to get structure
str(dataset)

#to access columns (works like a vector)
dataset$weight <- dataset$weight + 10

#change datatype
dataset$likes_string <- as.logical(dataset$likes_string)

#print data by paste function
paste('the cat is', dataset$coat)

#declare vector and index starts from 1 not 0
test <- c(3,2,1,6)
test[2]

#accessing  vector
test[length(test)]
test[1:3] <-  10
test > 8
test[test > 7]

#working with NA 
bad_values <-  c(NA, 4,8,3,2,1)
mean(bad_values)

#removing na 
is.na(bad_values)
!is.na(bad_values)
#one way
bad_values <-  bad_values[!is.na(bad_values)]
mean(bad_values)
#second way
mean(bad_values, na.rm = TRUE)
bad_values

#Lists, can have multiple data types 
demo_list <- list(1, TRUE, "words", 1:4, list(1))
demo_list

#Matrices
mat <-  matrix(1:16, nrow = 4, ncol = 4)
mat
mat[1,]
mat[3,3]
mat*2












