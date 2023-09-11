#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "stats.h"
#include "imgtree.h"

using namespace std;
using namespace cs221util;

TEST_CASE("Stats::basic RectArea","[weight=1][part=stats]"){

    PNG data; data.resize(2,2);

    Stats s(data);
    pair<unsigned int, unsigned int> ul(0,0);
    pair<unsigned int, unsigned int> lr(1,1);
    long result = s.RectArea(ul,lr);

    REQUIRE(result == 4);
    
}

TEST_CASE("Stats::basic getAvg","[weight=1][part=stats]"){
    PNG data; data.resize(2,2);
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j++){
            HSLAPixel * p = data.getPixel(i,j);
            p->h = 135*j + i * 90;
            p->s = 1.0;
            p->l = 0.5;
            p->a = 1.0;
        }
    }
    Stats s(data);
    pair<unsigned int, unsigned int> ul(0,0);
    pair<unsigned int, unsigned int> lr(1,1);
    HSLAPixel result = s.GetAvg(ul,lr);
    HSLAPixel expected(112.5,1.0, 0.5);

    REQUIRE(result == expected);
}

TEST_CASE("Stats::basic entropy","[weight=1][part=stats]"){
    PNG data; data.resize(2,2);
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j++){
            HSLAPixel * p = data.getPixel(i,j);
            p->h = 135*j + i * 90;
            p->s = 1.0;
            p->l = 0.5;
            p->a = 1.0;
        }
    }
    Stats s(data);
    pair<unsigned int, unsigned int> ul(0,0);
    pair<unsigned int, unsigned int> lr(1,1);
    long result = s.Entropy(ul,lr); // simple implicit cast for exact equality testing with known integer value

    REQUIRE(result == 2);
}

TEST_CASE("ImgTree::basic ctor render","[weight=1][part=ImgTree]"){
    PNG img;
    img.readFromFile("images-original/tri-640x426.png");
     cout << "Read1" << endl;

    ImgTree t1(img);
    cout << "Constructed1" << endl;
    PNG out = t1.Render();
     cout << "Rendered1" << endl;
    REQUIRE(out==img);
}

TEST_CASE("ImgTree::basic copy","[weight=1][part=ImgTree]"){
    PNG img;
    img.readFromFile("images-original/tri-640x426.png");
     cout << "Read2" << endl;
    ImgTree t1(img);
     cout << "Constructed2" << endl;
    ImgTree t1copy(t1);
     cout << "Copied2" << endl;
    PNG out = t1copy.Render();
    cout << "Render2" << endl;
    REQUIRE(out==img);
}

TEST_CASE("ImgTree::basic prune","[weight=1][part=ImgTree]"){
    PNG img;
    img.readFromFile("images-original/tri-640x426.png");
    cout << "Read3" << endl;
    ImgTree t1(img);
    cout << "Constructed3" << endl;
    PNG prePrune = t1.Render();
    cout << "Render3" << endl;
    t1.Prune(0.05);
    cout << "Prune3" << endl;
    PNG result = t1.Render();
    cout << "Render3" << endl;
    PNG expected; expected.readFromFile("images-soln/ex-tri-prune005.png");
    cout << "Read3" << endl;
    REQUIRE(expected==result);
}

