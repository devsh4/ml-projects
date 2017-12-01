#like pandas in python
library(gapminder)

#dataframe
gap <-  gapminder

#like python, get first 5 or last 5 rows 
head(gap)
tail(gap)
#to get dimensions of the dataframe
nrow(gap)
ncol(gap)
dim(gap)
colnames(gap)
str(gap)

#return unique rows
unique(gap$country)
#returns true or false in rows
gap$country[gap$country == "Canada"]
canada <- gap[gap$country == "Canada",]

#stack or merge dataframes
#stacks dataframes one on top of another
double_canada <- rbind(canada, canada)
#stacks dataframes side by side
test_canada <- cbind(canada, canada)

#to get all columns 
#print(canada, width = Inf)
canada$gdp <- canada$gdp * canada$gdpPercap

one <- c(1,2,3,4,5)
two <- c(1,6,9,12,5)

#to check if one vector has some values similar to another vector
one %in% two
