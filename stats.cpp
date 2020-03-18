
#include "stats.h"

stats::stats(PNG &im)
{

    // YOUR CODE HERE!!
    sumRed = std::vector<std::vector<long>>(im.height(), std::vector<long>(im.width(), -1));
    sumGreen = std::vector<std::vector<long>>(im.height(), std::vector<long>(im.width(), -1));
    sumBlue = std::vector<std::vector<long>>(im.height(), std::vector<long>(im.width(), -1));
    sumsqRed = std::vector<std::vector<long>>(im.height(), std::vector<long>(im.width(), -1));
    sumsqGreen = std::vector<std::vector<long>>(im.height(), std::vector<long>(im.width(), -1));
    sumsqBlue = std::vector<std::vector<long>>(im.height(), std::vector<long>(im.width(), -1));

    sumRed.at(0).at(0) = im.getPixel(0, 0)->r;
    sumGreen.at(0).at(0) = im.getPixel(0, 0)->g;
    sumBlue.at(0).at(0) = im.getPixel(0, 0)->b;

    for (int col = 1; col < im.width(); col++)
    {
        sumRed.at(0).at(col) = im.getPixel(col, 0)->r + im.getPixel(col - 1, 0)->r;
        sumGreen.at(0).at(col) = im.getPixel(col, 0)->g + im.getPixel(col - 1, 0)->g;
        sumBlue.at(0).at(col) = im.getPixel(col, 0)->b + im.getPixel(col - 1, 0)->b;
    }

    for (int row = 1; row < im.height(); row++)
    {
        sumRed.at(row).at(0) = im.getPixel(0, row)->r + im.getPixel(0, row - 1)->r;
        sumGreen.at(row).at(0) = im.getPixel(0, row)->g + im.getPixel(0, row - 1)->g;
        sumBlue.at(row).at(0) = im.getPixel(0, row)->b + im.getPixel(0, row - 1)->b;
    }

    for (int row = 1; row < im.height(); row++)
    {
        for (int col = 1; col < im.width(); col++)
        {
            sumRed.at(row).at(col) = im.getPixel(col, row)->r + sumRed.at(row).at(col - 1) + sumRed.at(row - 1).at(col) - sumRed.at(row - 1).at(col - 1);
            sumGreen.at(row).at(col) = im.getPixel(col, row)->g + sumGreen.at(row).at(col - 1) + sumGreen.at(row - 1).at(col) - sumGreen.at(row - 1).at(col - 1);
            sumBlue.at(row).at(col) = im.getPixel(col, row)->b + sumBlue.at(row).at(col - 1) + sumBlue.at(row - 1).at(col) - sumBlue.at(row - 1).at(col - 1);
        }
    }
}

long stats::getSum(char channel, pair<int, int> ul, pair<int, int> lr)
{

    // YOUR CODE HERE!!
    if (channel == 'r')
    {
       long res = sumRed.at(lr.second).at(lr.first);

       if (ul.second-1>=0){
           res = res - sumRed.at(ul.second-1).at(lr.first);
       }
       if (ul.first-1>=0){
           res = res - sumRed.at(lr.second).at(ul.first-1);
       }

       if (ul.second-1>=0 && ul.first-1>=0){
           res = res + sumRed.at(ul.second-1).at(ul.first-1);
       }
       return res;
    }

    else if (channel == 'g')
    {
       long res = sumGreen.at(lr.second).at(lr.first);

       if (ul.second-1>=0){
           res = res - sumGreen.at(ul.second-1).at(lr.first);
       }
       if (ul.first-1>=0){
           res = res - sumGreen.at(lr.second).at(ul.first-1);
       }

       if (ul.second-1>=0 && ul.first-1>=0){
           res = res + sumGreen.at(ul.second-1).at(ul.first-1);
       }
       return res;
    }

    else 
    {
       long res = sumBlue.at(lr.second).at(lr.first);

       if (ul.second-1>=0){
           res = res - sumBlue.at(ul.second-1).at(lr.first);
       }
       if (ul.first-1>=0){
           res = res - sumBlue.at(lr.second).at(ul.first-1);
       }

       if (ul.second-1>=0 && ul.first-1>=0){
           res = res + sumBlue.at(ul.second-1).at(ul.first-1);
       }
       return res;
    }
}

long stats::getSumSq(char channel, pair<int, int> ul, pair<int, int> lr)
{

    // YOUR CODE HERE!!
}

long stats::rectArea(pair<int, int> ul, pair<int, int> lr)
{

    // YOUR CODE HERE!!
    return (lr.first - ul.first + 1) * (lr.second - ul.second + 1);
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int, int> ul, pair<int, int> lr)
{

    // YOUR CODE HERE!!
}

RGBAPixel stats::getAvg(pair<int, int> ul, pair<int, int> lr)
{

    // YOUR CODE HERE!!
    RGBAPixel res;
    res.r = getSum('r',ul,lr)/rectArea(ul,lr);
    res.g = getSum('g',ul,lr)/rectArea(ul,lr);
    res.b = getSum('b',ul,lr)/rectArea(ul,lr);
    return res;
}
