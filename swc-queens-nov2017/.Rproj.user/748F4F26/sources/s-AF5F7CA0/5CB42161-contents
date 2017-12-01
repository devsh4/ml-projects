library(ggplot2)
library(tidyverse)
library(gapminder)

gap <-  gapminder
str(gap)

#draw scatter plot by geom_point() to give point wise plots
ggplot(gap, aes(x=gdpPercap, y=lifeExp)) + geom_point()
ggplot(gap, aes(x=log10(gdpPercap), y=lifeExp)) + geom_point()

#with colour and legends
ggplot(gap, aes(x=gdpPercap, y=lifeExp, colour=continent)) + geom_point() + scale_x_log10()

#challenge
ggplot(gap, aes(x=year, y=lifeExp, colour=continent)) + geom_point()
#to give different shape to the plot
ggplot(gap, aes(x=year, y=lifeExp, group=year, colour=continent)) + geom_boxplot()
ggplot(gap, aes(x=continent, y=lifeExp)) + geom_boxplot()

#to create separate plots for each continent or subplot
ggplot(gap, aes(x=year, y=lifeExp, group=year)) + geom_boxplot() + facet_wrap(~continent)
ggsave('plot1.png')

#cool chart
ggplot(gap, aes(x=continent, y=lifeExp, fill=continent)) + geom_violin()
#change colors
ggplot(gap, aes(x=continent, y=lifeExp, fill=continent)) + geom_violin() + scale_fill_brewer()

#Change size and shape
ggplot(gap, aes(x=log10(gdpPercap), y=lifeExp, color=lifeExp)) + geom_point(size = 0.4)
#Add color gradient to the scale and modify background of the graph
ggplot(gap, aes(x=log10(gdpPercap), y=lifeExp, color=lifeExp)) + geom_point(shape = 4) +
       scale_color_gradient(low="red", high="darkorchid") + theme_classic()

#Challenge 2
#use adjust or alpha parameter of density() to get better graphs
ggplot(gap, aes(x=log10(gdpPercap), fill=continent)) + geom_density(alpha=0.3)
ggplot(gap, aes(x=log10(gdpPercap), fill=continent)) + geom_density(position='stack', aplha=0.3) + facet_wrap(~continent) + ggtitle("Test Graph")



