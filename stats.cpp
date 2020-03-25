
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

    sumsqRed.at(0).at(0) = pow(im.getPixel(0, 0)->r, 2);
    sumsqGreen.at(0).at(0) = pow(im.getPixel(0, 0)->g, 2);
    sumsqBlue.at(0).at(0) = pow(im.getPixel(0, 0)->b, 2);

    for (int col = 1; col < im.width(); col++)
    {
        sumRed.at(0).at(col) = im.getPixel(col, 0)->r + sumRed.at(0).at(col - 1);
        sumGreen.at(0).at(col) = im.getPixel(col, 0)->g + sumGreen.at(0).at(col - 1);
        sumBlue.at(0).at(col) = im.getPixel(col, 0)->b + sumBlue.at(0).at(col - 1);

        sumsqRed.at(0).at(col) = pow(im.getPixel(col, 0)->r, 2) + sumsqRed.at(0).at(col - 1);
        sumsqGreen.at(0).at(col) = pow(im.getPixel(col, 0)->g, 2) + sumsqGreen.at(0).at(col - 1);
        sumsqBlue.at(0).at(col) = pow(im.getPixel(col, 0)->b, 2) + sumsqBlue.at(0).at(col - 1);
    }

    for (int row = 1; row < im.height(); row++)
    {
        sumRed.at(row).at(0) = im.getPixel(0, row)->r + sumRed.at(row - 1).at(0);
        sumGreen.at(row).at(0) = im.getPixel(0, row)->g + sumGreen.at(row - 1).at(0);
        sumBlue.at(row).at(0) = im.getPixel(0, row)->b + sumBlue.at(row - 1).at(0);

        sumsqRed.at(row).at(0) = pow(im.getPixel(0, row)->r, 2) + sumsqRed.at(row - 1).at(0);
        sumsqGreen.at(row).at(0) = pow(im.getPixel(0, row)->g, 2) + sumsqGreen.at(row - 1).at(0);
        sumsqBlue.at(row).at(0) = pow(im.getPixel(0, row)->b, 2) + sumsqBlue.at(row - 1).at(0);
    }

    for (int row = 1; row < im.height(); row++)
    {
        for (int col = 1; col < im.width(); col++)
        {
            sumRed.at(row).at(col) = im.getPixel(col, row)->r + sumRed.at(row).at(col - 1) + sumRed.at(row - 1).at(col) - sumRed.at(row - 1).at(col - 1);
            sumGreen.at(row).at(col) = im.getPixel(col, row)->g + sumGreen.at(row).at(col - 1) + sumGreen.at(row - 1).at(col) - sumGreen.at(row - 1).at(col - 1);
            sumBlue.at(row).at(col) = im.getPixel(col, row)->b + sumBlue.at(row).at(col - 1) + sumBlue.at(row - 1).at(col) - sumBlue.at(row - 1).at(col - 1);

            sumsqRed.at(row).at(col) = pow(im.getPixel(col, row)->r, 2) + sumsqRed.at(row).at(col - 1) + sumsqRed.at(row - 1).at(col) - sumsqRed.at(row - 1).at(col - 1);
            sumsqGreen.at(row).at(col) = pow(im.getPixel(col, row)->g, 2) + sumsqGreen.at(row).at(col - 1) + sumsqGreen.at(row - 1).at(col) - sumsqGreen.at(row - 1).at(col - 1);
            sumsqBlue.at(row).at(col) = pow(im.getPixel(col, row)->b, 2) + sumsqBlue.at(row).at(col - 1) + sumsqBlue.at(row - 1).at(col) - sumsqBlue.at(row - 1).at(col - 1);
        }
    }
}

long stats::getSum(char channel, pair<int, int> ul, pair<int, int> lr)
{

    // YOUR CODE HERE!!
    if (channel == 'r')
    {
        long res = sumRed.at(lr.second).at(lr.first);

        if (ul.second - 1 >= 0)
        {
            res = res - sumRed.at(ul.second - 1).at(lr.first);
        }
        if (ul.first - 1 >= 0)
        {
            res = res - sumRed.at(lr.second).at(ul.first - 1);
        }

        if (ul.second - 1 >= 0 && ul.first - 1 >= 0)
        {
            res = res + sumRed.at(ul.second - 1).at(ul.first - 1);
        }
        return res;
    }

    else if (channel == 'g')
    {
        long res = sumGreen.at(lr.second).at(lr.first);

        if (ul.second - 1 >= 0)
        {
            res = res - sumGreen.at(ul.second - 1).at(lr.first);
        }
        if (ul.first - 1 >= 0)
        {
            res = res - sumGreen.at(lr.second).at(ul.first - 1);
        }

        if (ul.second - 1 >= 0 && ul.first - 1 >= 0)
        {
            res = res + sumGreen.at(ul.second - 1).at(ul.first - 1);
        }
        return res;
    }

    else
    {
        long res = sumBlue.at(lr.second).at(lr.first);

        if (ul.second - 1 >= 0)
        {
            res = res - sumBlue.at(ul.second - 1).at(lr.first);
        }
        if (ul.first - 1 >= 0)
        {
            res = res - sumBlue.at(lr.second).at(ul.first - 1);
        }

        if (ul.second - 1 >= 0 && ul.first - 1 >= 0)
        {
            res = res + sumBlue.at(ul.second - 1).at(ul.first - 1);
        }
        return res;
    }
}

long stats::getSumSq(char channel, pair<int, int> ul, pair<int, int> lr)
{

    // YOUR CODE HERE!!
    if (channel == 'r')
    {
        long res = sumsqRed.at(lr.second).at(lr.first);

        if (ul.second - 1 >= 0)
        {
            res = res - sumsqRed.at(ul.second - 1).at(lr.first);
        }
        if (ul.first - 1 >= 0)
        {
            res = res - sumsqRed.at(lr.second).at(ul.first - 1);
        }

        if (ul.second - 1 >= 0 && ul.first - 1 >= 0)
        {
            res = res + sumsqRed.at(ul.second - 1).at(ul.first - 1);
        }
        return res;
    }

    else if (channel == 'g')
    {
        // std::cout << sumsqRed.size() << std::endl;
        // std::cout << sumsqGreen.size() << std::endl;
        // std::cout << sumsqBlue.size() << std::endl;
        long res = sumsqGreen.at(lr.second).at(lr.first);

        if (ul.second - 1 >= 0)
        {
            res = res - sumsqGreen.at(ul.second - 1).at(lr.first);
        }
        if (ul.first - 1 >= 0)
        {
            res = res - sumsqGreen.at(lr.second).at(ul.first - 1);
        }

        if (ul.second - 1 >= 0 && ul.first - 1 >= 0)
        {
            res = res + sumsqGreen.at(ul.second - 1).at(ul.first - 1);
        }
        return res;
    }

    else
    {
        long res = sumsqBlue.at(lr.second).at(lr.first);

        if (ul.second - 1 >= 0)
        {
            res = res - sumsqBlue.at(ul.second - 1).at(lr.first);
        }
        if (ul.first - 1 >= 0)
        {
            res = res - sumsqBlue.at(lr.second).at(ul.first - 1);
        }

        if (ul.second - 1 >= 0 && ul.first - 1 >= 0)
        {
            res = res + sumsqBlue.at(ul.second - 1).at(ul.first - 1);
        }
        return res;
    }
}

long stats::rectArea(pair<int, int> ul, pair<int, int> lr)
{

    // YOUR CODE HERE!!
    return (lr.first - ul.first + 1) * (lr.second - ul.second + 1);
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int, int> ul, pair<int, int> lr)
{

    // long redsq = getSumSq('r', ul, lr);
    // long greensq = getSumSq('g', ul, lr);
    // long bluesq = getSumSq('b', ul, lr);
    // long pow_thing = pow(getSum('r', ul, lr) + getSum('g', ul, lr) + getSum('b', ul, lr), 2);
    // std::cout << getSum('r', ul, lr) << std::endl;
    // std::cout << getSum('g', ul, lr) << std::endl;
    // std::cout << getSum('b', ul, lr) << std::endl;
    // long rect_area = rectArea(ul, lr);
    // std::cout << sumsqRed.size() << std::endl;
    // std::cout << sumsqGreen.size() << std::endl;
    // std::cout << sumsqBlue.size() << std::endl;
    long red_score = getSumSq('r', ul, lr) - pow(getSum('r', ul, lr), 2) / rectArea(ul, lr);
    long green_score = getSumSq('g', ul, lr) - pow(getSum('g', ul, lr), 2) / rectArea(ul, lr);
    long blue_score = getSumSq('b', ul, lr) - pow(getSum('b', ul, lr), 2) / rectArea(ul, lr);

    // YOUR CODE HERE!!
    return red_score + green_score + blue_score;
}

RGBAPixel stats::getAvg(pair<int, int> ul, pair<int, int> lr)
{

    // YOUR CODE HERE!!
    RGBAPixel res;
    res.r = getSum('r', ul, lr) / rectArea(ul, lr);
    res.g = getSum('g', ul, lr) / rectArea(ul, lr);
    res.b = getSum('b', ul, lr) / rectArea(ul, lr);
    return res;
}
