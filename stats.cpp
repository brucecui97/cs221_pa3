
#include "stats.h"

stats::stats(PNG & im){

// YOUR CODE HERE!!
sumRed = std::vector<std::vector<long>> (im.height(),std::vector<long>(im.width(),-1));
sumGreen= std::vector<std::vector<long>> (im.height(),std::vector<long>(im.width(),-1));
sumBlue = std::vector<std::vector<long>> (im.height(),std::vector<long>(im.width(),-1));
sumsqRed = std::vector<std::vector<long>> (im.height(),std::vector<long>(im.width(),-1));
sumsqGreen = std::vector<std::vector<long>> (im.height(),std::vector<long>(im.width(),-1));
sumsqBlue = std::vector<std::vector<long>> (im.height(),std::vector<long>(im.width(),-1));
}

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

}

long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
return (lr.first-ul.first+1) * (lr.second-ul.second+1);

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

}
		
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

}
