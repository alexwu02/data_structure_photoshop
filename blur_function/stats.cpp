/**
 * @file stats.cpp
 * @description implementation of Stats class used for fast computation of
 *              colour information from rectangular image regions
 *              CPSC 221 2023S PA3
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

#include "stats.h"

#define NUMBINS 36 // number of histogram bins

Stats::Stats(const PNG& im){
    // complete your implementation below
    sumHueX.resize(im.height());
    sumHueY.resize(im.height());
    sumSat.resize(im.height());
    sumLum.resize(im.height());
    hist.resize(im.height());

    for(unsigned int i = 0; i < im.height(); i++){
        sumHueX[i].resize(im.width());
        sumHueY[i].resize(im.width());
        sumSat[i].resize(im.width());
        sumLum[i].resize(im.width());

        for (unsigned int j= 0; j < im.width(); j++){
            sumHueX[i][j] = cos((im.getPixel(j, i)->h)* PI / 180.0);
            sumHueY[i][j] = sin((im.getPixel(j, i)->h)* PI / 180.0);
            sumSat[i][j] = im.getPixel(j, i)->s;
            sumLum[i][j] = im.getPixel(j, i)->l;

            if (i > 0){
                sumHueX[i][j] += sumHueX[i-1][j];
                sumHueY[i][j] += sumHueY[i-1][j];
                sumSat[i][j] += sumSat[i-1][j];
                sumLum[i][j] += sumLum[i-1][j];
            }

            if(j > 0){
                sumHueX[i][j] += sumHueX[i][j-1];
                sumHueY[i][j] += sumHueY[i][j-1];
                sumSat[i][j] += sumSat[i][j-1];
                sumLum[i][j] += sumLum[i][j-1];
            }

            if(i > 0 && j > 0){
                sumHueX[i][j] -= sumHueX[i-1][j-1];
                sumHueY[i][j] -= sumHueY[i-1][j-1];
                sumSat[i][j] -= sumSat[i-1][j-1];
                sumLum[i][j] -= sumLum[i-1][j-1];
            }
        }
    }

    for(unsigned int i = 0; i< im.height(); i++){
        hist[i].resize(im.width());
        for(unsigned int j = 0; j< im.width(); j++){
            hist[i][j].resize(NUMBINS);

            for(unsigned int k = 0; k < NUMBINS; k++){
                
                hist[i][j][k] = 0;
                if(i > 0){
                    hist[i][j][k] += hist[i-1][j][k];
                }
                if(j > 0){
                    hist[i][j][k] += hist[i][j-1][k];
                }
                if(i > 0 && j > 0){
                    hist[i][j][k] -= hist[i-1][j-1][k];
                }
                
                if(k*10 <= im.getPixel(j, i)->h 
                    && im.getPixel(j, i)->h < (k+1)*10){
                    hist[i][j][k] += 1;
                }  
            }
        }
    }

    
}

long Stats::RectArea(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr){
    // replace the stub below with your completed implementation
    return (lr.first - ul.first + 1)*(lr.second - ul.second + 1);
}

HSLAPixel Stats::GetAvg(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr){
    // replace the stub below with your completed implementation
    unsigned int x1 = ul.first;
    unsigned int y1 = ul.second;
    unsigned int x2 = lr.first;
    unsigned int y2 = lr.second;

    unsigned int totalPixels = (x2 - x1 + 1) * (y2 - y1 + 1);

    // Calculate the cumulative sums for the given rectangle
    double cumSumHueX = sumHueX[y2][x2] - (x1 > 0 ? sumHueX[y2][x1 - 1] : 0) - (y1 > 0 ? sumHueX[y1 - 1][x2] : 0) + ((x1 > 0 && y1 > 0) ? sumHueX[y1 - 1][x1 - 1] : 0);
    double cumSumHueY = sumHueY[y2][x2] - (x1 > 0 ? sumHueY[y2][x1 - 1] : 0) - (y1 > 0 ? sumHueY[y1 - 1][x2] : 0) + ((x1 > 0 && y1 > 0) ? sumHueY[y1 - 1][x1 - 1] : 0);
    double cumSumSat = sumSat[y2][x2] - (x1 > 0 ? sumSat[y2][x1 - 1] : 0) - (y1 > 0 ? sumSat[y1 - 1][x2] : 0) + ((x1 > 0 && y1 > 0) ? sumSat[y1 - 1][x1 - 1] : 0);
    double cumSumLum = sumLum[y2][x2] - (x1 > 0 ? sumLum[y2][x1 - 1] : 0) - (y1 > 0 ? sumLum[y1 - 1][x2] : 0) + ((x1 > 0 && y1 > 0) ? sumLum[y1 - 1][x1 - 1] : 0);

    // Calculate the average values
    double avgHue = atan2(cumSumHueY, cumSumHueX) * 180.0 / PI;
    if (avgHue < 0) {
        avgHue += 360.0;
    }
    double avgSat = cumSumSat / totalPixels;
    double avgLum = cumSumLum / totalPixels;

    // Create and return the average pixel
    return HSLAPixel(avgHue, avgSat, avgLum, 1.0);


}

double Stats::Entropy(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr){

    vector<unsigned int> distribution;
    distribution.resize(NUMBINS);

    double entropy = 0.0;

    long area = RectArea(ul, lr);


    for(unsigned int i = 0; i < NUMBINS; i++){
        distribution[i] = hist[lr.second][lr.first][i];

        if(ul.second > 0){
            distribution[i] -= hist[ul.second-1][lr.first][i];
        }
        if(ul.first > 0){
            distribution[i] -= hist[lr.second][ul.first-1][i];
        }
        if(ul.second>0 && ul.first>0){
            distribution[i] += hist[ul.second-1][ul.first-1][i];
        }
    }


    for (unsigned int i = 0; i < NUMBINS; i++)
    {
        if (distribution[i] > 0)
            entropy += ((double)distribution[i] / (double)area) * log2((double)distribution[i] / (double)area);
    }
    return -1 * entropy;
}
    

    /**
    *  Complete your implementation below.
    *  Using private member hist, assemble the distribution over the
    *  given rectangle defined by points ul, and lr into variable distribution.
    *  You will use distribution to compute the entropy over the rectangle.
    *  if any bin in the distribution has frequency 0, then do not add that 
    *  term to the entropy total. see .h file for more details.
    */

    /* your code should include the following lines (or something similar):
        if (distribution[i] > 0 ) 
            entropy += ((double) distribution[i]/(double) area) 
                                    * log2((double) distribution[i]/(double) area);
    */
    
    


/**
 * Add your private Stats function implementations below
 */
