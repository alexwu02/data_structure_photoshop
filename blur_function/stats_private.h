/**
 * @file stats_private.h
 * @description student declarations of private functions
 *              for Stats, CPSC 221 2023S PA3
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

// begin your declarations below

vector<unsigned int> buildHist(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr)
{
   
    unsigned int ul_x = ul.first;
    unsigned int lr_x = lr.first;
    unsigned int ul_y = ul.second;
    unsigned int lr_y = lr.second;

    vector<unsigned int> toReturn = hist[lr_x][lr_y];

    for (unsigned int i = 0; i < 36; i++)
    {
        unsigned int bin = 0; //if ul_x and ul_y ==0
        if (ul_x == 0 && ul_y == 0)
        {
            bin = hist[lr_x][lr_y][i];
        }
        else if (ul_x != 0 && ul_y == 0)
        {
            bin = hist[lr_x][lr_y][i] - hist[ul_x - 1][lr_y][i];
        }
        else if (ul_x == 0 && ul_y != 0)
        {
            bin = hist[lr_x][lr_y][i] - hist[lr_x][ul_y - 1][i];
        }
        else if (ul_x != 0 && ul_y != 0)
        {
            bin = hist[lr_x][lr_y][i] - hist[lr_x][ul_y - 1][i] - hist[ul_x - 1][lr_y][i] + hist[ul_x - 1][ul_y - 1][i];
        }
        toReturn[i] = bin;
    }

    return toReturn;
}
