#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"
#include <limits.h>
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "filler.h"
#include "solidColorPicker.h"
#include "imageTileColorPicker.h"
#include "quarterColorPicker.h"
#include "negativeBorderColorPicker.h"
#include "colorPicker.h"

using namespace std;
using namespace cs221util;

#define IMAGEDIR "images-original/"
#define SOLNIMGDIR "images-soln/"

#define FUNCTORTESTHEIGHT 300
#define FUNCTORTESTWIDTH 300
#define FUNCTORTESTFREQ 10
#define FUNCTORTESTX 40
#define FUNCTORTESTY 10
#define FUNCTORTESTRADIUS 45
#define FUNCTORTESTIMAGEW "images-original/white-300x300.png"
#define FUNCTORTESTIMAGEP "images-original/mr-300x300.png"

#define SOLIDX 60
#define SOLIDY 44
#define SOLIDTOLERANCE 0.05
#define SOLIDTESTIMAGE "images-original/krlkm-124x118.png"
#define SOLIDFRAMEFREQ 40

#define IMGTILEX 50 
#define IMGTILEY 331
#define IMGTILETOLERANCE 0.02
#define IMGTILETESTIMAGE "images-original/zt1-320x440.png"
#define IMGTILEOTHERIMAGE "images-original/krlkm-124x118.png"
#define IMGTILEFRAMEFREQ 620

#define QUARTERX 158
#define QUARTERY 307
#define QUARTERTOLERANCE 0.05
#define QUARTERTESTIMAGE "images-original/sbg-210x450.png"
#define QUARTERFRAMEFREQ 60

#define NEGBORDERX 203
#define NEGBORDERY 159
#define NEGBORDERTOLERANCE 0.1
#define NEGBORDERWIDTH 5
#define NEGBORDERTESTIMAGE "images-original/mr-300x300.png"
#define NEGBORDERFRAMEFREQ 180


PNG testColorPicker(ColorPicker& picker)
{
    PNG img;
    img.resize(FUNCTORTESTWIDTH, FUNCTORTESTHEIGHT);
    HSLAPixel px;

    for (int x = 0; x < FUNCTORTESTWIDTH; x++){
        for (int y = 0; y < FUNCTORTESTHEIGHT; y++){
            HSLAPixel* p = img.getPixel(x,y);
            PixelPoint pp(x, y, *p);
            *p = picker(pp);
        }
    }

    return img;
}

// TEST_CASE("colorPicker::basic solid","[weight=0][part=colorPicker]"){

//     cout << "Entered colorPicker::basic solid..." << endl;

//     HSLAPixel px(120, 1, 0.5, 1); // green
//     SolidColorPicker solidPicker(px);

//     PNG result = testColorPicker(solidPicker); result.convert();
//     result.writeToFile("images-output/solidColorPickerTest.png");
//     PNG expected; expected.readFromFile("images-soln/ex-solidColorPickerTest.png");
//     REQUIRE(result == expected);
    
//     cout << "Leaving colorPicker::basic solid..." << endl;
// }

// TEST_CASE("colorPicker::basic image tile","[weight=1][part=colorPicker]"){

//     cout << "Entered colorPicker::basic image tile..." << endl;

//     PNG imgtest, imgother;
//     imgtest.readFromFile(IMGTILETESTIMAGE);
//     imgother.readFromFile(IMGTILEOTHERIMAGE);

//     ImageTileColorPicker imgtilePicker(imgother);

//     PNG result = testColorPicker(imgtilePicker); result.convert();
//     result.writeToFile("images-output/imageTileColorPickerTest.png");
//     PNG expected; expected.readFromFile("images-soln/ex-imageTileColorPickerTest.png");
//     REQUIRE(result == expected);

//     cout << "Leaving colorPicker::basic image tile..." << endl;
// }

// TEST_CASE("colorPicker::basic quarter","[weight=1][part=colorPicker]"){
    
//     cout << "Entered colorPicker::basic quarter..." << endl;

//     PNG imgtest;
//     imgtest.readFromFile(FUNCTORTESTIMAGEP);

//     QuarterColorPicker quarterPicker(imgtest);

//     PNG result = testColorPicker(quarterPicker); result.convert();
//     result.writeToFile("images-output/quarterColorPickerTest.png");
//     PNG expected; expected.readFromFile("images-soln/ex-quarterColorPickerTest.png"); expected.convert();
//     REQUIRE(result == expected);

//     cout << "Leaving colorPicker::basic quarter..." << endl;
// }

TEST_CASE("colorPicker::basic negative border", "[weight=1][part=colorPicker]") {
  
    cout << "Entered colorPicker::basic negative border..." << endl;

    PNG imgtest;
    imgtest.readFromFile(FUNCTORTESTIMAGEW);
    PixelPoint p(NEGBORDERX, NEGBORDERY, *(imgtest.getPixel(NEGBORDERX, NEGBORDERY)));
    NegativeBorderColorPicker negborderPicker(imgtest, p, NEGBORDERWIDTH, NEGBORDERTOLERANCE);

    PNG result = testColorPicker(negborderPicker); result.convert();
    result.writeToFile("images-output/negativeBorderColorPickerTest.png");
    PNG expected; expected.readFromFile("images-soln/ex-negativeBorderColorPickerTest.png");
    REQUIRE(result == expected);

    cout << "Leaving colorPicker::basic negative border..." << endl;
}

// TEST_CASE("fill::basic solid dfs","[weight=1][part=fill]"){
    
//     cout << "Entered fill::basic solid dfs..." << endl;

//     HSLAPixel px(99, 0.4, 0.6, 1);
//     SolidColorPicker solidPicker(px);

//     filler::FillerConfig solidconfig;
//     solidconfig.img.readFromFile(SOLIDTESTIMAGE);
//     solidconfig.frameFreq = SOLIDFRAMEFREQ;
//     solidconfig.tolerance = SOLIDTOLERANCE;
//     solidconfig.seedpoint = PixelPoint(SOLIDX, SOLIDY, *solidconfig.img.getPixel(SOLIDX,SOLIDY));
//     solidconfig.picker = &solidPicker;

//     animation anim;
//     anim = filler::FillDFS(solidconfig);
//     PNG result = anim.write("images-output/dfssolid.gif");  result.convert();
//     result.writeToFile("images-output/dfssolid.png");

//     PNG expected; expected.readFromFile("images-soln/ex-dfssolid.png");
//     REQUIRE(result==expected);

//     cout << "Leaving fill::basic solid dfs..." << endl;
// }


// TEST_CASE("fill::basic solid bfs","[weight=1][part=fill]"){
    
//     cout << "Entered fill::basic solid bfs..." << endl;

//     HSLAPixel px(99, 0.4, 0.6, 1);
//     SolidColorPicker solidPicker(px);

//     filler::FillerConfig solidconfig;
//     solidconfig.img.readFromFile(SOLIDTESTIMAGE);
//     solidconfig.frameFreq = SOLIDFRAMEFREQ;
//     solidconfig.tolerance = SOLIDTOLERANCE;
//     solidconfig.seedpoint = PixelPoint(SOLIDX, SOLIDY, *solidconfig.img.getPixel(SOLIDX, SOLIDY));
//     solidconfig.picker = &solidPicker;

//     animation anim;
//     anim = filler::FillBFS(solidconfig);
//     PNG result = anim.write("images-output/bfssolid.gif"); result.convert();
//     result.writeToFile("images-output/bfssolid.png");

//     PNG expected; expected.readFromFile("images-soln/ex-bfssolid.png");
//     REQUIRE(result==expected);

//     cout << "Leaving fill::basic solid bfs..." << endl;
// }

// TEST_CASE("fill::basic image tile dfs", "[weight=1][part=fill]") {
    
//     cout << "Entered fill::basic image tile dfs..." << endl;

//     PNG imgtiletest, imgtileother;
//     imgtiletest.readFromFile(IMGTILETESTIMAGE);
//     imgtileother.readFromFile(IMGTILEOTHERIMAGE);
//     ImageTileColorPicker imgtilePicker(imgtileother);

//     filler::FillerConfig imgtileconfig;
//     imgtileconfig.img = imgtiletest;
//     imgtileconfig.frameFreq = IMGTILEFRAMEFREQ;
//     imgtileconfig.tolerance = IMGTILETOLERANCE;
//     imgtileconfig.seedpoint = PixelPoint(IMGTILEX, IMGTILEY, *imgtileconfig.img.getPixel(IMGTILEX, IMGTILEY));
//     imgtileconfig.picker = &imgtilePicker;

//     animation anim;
//     anim = filler::FillDFS(imgtileconfig);
//     PNG result = anim.write("images-output/dfsimagetile.gif"); result.convert();
//     result.writeToFile("images-output/dfsimagetile.png");

//     PNG expected; expected.readFromFile("images-soln/ex-dfsimagetile.png");
//     REQUIRE(result == expected);

//     cout << "Leaving fill::basic image tile dfs..." << endl;
// }

// TEST_CASE("fill::basic image tile bfs", "[weight=1][part=fill]") {
  
//     cout << "Entered fill::basic image tile bfs..." << endl;
  
//     PNG imgtiletest, imgtileother;
//     imgtiletest.readFromFile(IMGTILETESTIMAGE);
//     imgtileother.readFromFile(IMGTILEOTHERIMAGE);
//     ImageTileColorPicker imgtilePicker(imgtileother);

//     filler::FillerConfig imgtileconfig;
//     imgtileconfig.img = imgtiletest;
//     imgtileconfig.frameFreq = IMGTILEFRAMEFREQ;
//     imgtileconfig.tolerance = IMGTILETOLERANCE;
//     imgtileconfig.seedpoint = PixelPoint(IMGTILEX, IMGTILEY, *imgtileconfig.img.getPixel(IMGTILEX, IMGTILEY));
//     imgtileconfig.picker = &imgtilePicker;

//     animation anim;
//     anim = filler::FillBFS(imgtileconfig);
//     PNG result = anim.write("images-output/bfsimagetile.gif"); result.convert();
//     result.writeToFile("images-output/bfsimagetile.png");

//     PNG expected; expected.readFromFile("images-soln/ex-bfsimagetile.png");
//     REQUIRE(result == expected);

//     cout << "Leaving fill::basic image tile bfs..." << endl;
// }

// TEST_CASE("fill::basic quarter dfs","[weight=1][part=fill]"){
    
//     cout << "Entered fill::basic quarter dfs..." << endl;

//     PNG quartertest;
//     quartertest.readFromFile(QUARTERTESTIMAGE);
//     QuarterColorPicker quarterPicker(quartertest);

//     filler::FillerConfig quarterconfig;
//     quarterconfig.img = quartertest;
//     quarterconfig.frameFreq = QUARTERFRAMEFREQ;
//     quarterconfig.tolerance = QUARTERTOLERANCE;
//     quarterconfig.seedpoint = PixelPoint(QUARTERX, QUARTERY, *quarterconfig.img.getPixel(QUARTERX, QUARTERY));
//     quarterconfig.picker = &quarterPicker;

//     animation anim;
//     anim = filler::FillDFS(quarterconfig);
//     PNG result = anim.write("images-output/dfsquarter.gif"); result.convert();
//     result.writeToFile("images-output/dfsquarter.png");

//     PNG expected; expected.readFromFile("images-soln/ex-dfsquarter.png");
//     REQUIRE(result==expected);

//     cout << "Leaving fill::basic quarter dfs..." << endl;
// }

// TEST_CASE("fill::basic quarter bfs","[weight=1][part=fill]"){
    
//     cout << "Entered fill::basic quarter bfs..." << endl;

//     PNG quartertest;
//     quartertest.readFromFile(QUARTERTESTIMAGE);
//     QuarterColorPicker quarterPicker(quartertest);

//     filler::FillerConfig quarterconfig;
//     quarterconfig.img = quartertest;
//     quarterconfig.frameFreq = QUARTERFRAMEFREQ;
//     quarterconfig.tolerance = QUARTERTOLERANCE;
//     quarterconfig.seedpoint = PixelPoint(QUARTERX, QUARTERY, *quarterconfig.img.getPixel(QUARTERX, QUARTERY));
//     quarterconfig.picker = &quarterPicker;

//     animation anim;
//     anim = filler::FillBFS(quarterconfig);
//     PNG result = anim.write("images-output/bfsquarter.gif"); result.convert();
//     result.writeToFile("images-output/bfsquarter.png");

//     PNG expected; expected.readFromFile("images-soln/ex-bfsquarter.png");
//     REQUIRE(result == expected);

//     cout << "Leaving fill::basic quarter bfs..." << endl;
// }

TEST_CASE("fill::basic negative border dfs","[weight=1][part=fill]"){
  
    cout << "Entered fill::basic negative border dfs..." << endl;
  
    PNG imgtest;
    imgtest.readFromFile(NEGBORDERTESTIMAGE);
    PixelPoint p(NEGBORDERX, NEGBORDERY, *(imgtest.getPixel(NEGBORDERX, NEGBORDERY)));
    NegativeBorderColorPicker negborderPicker(imgtest, p, NEGBORDERWIDTH, NEGBORDERTOLERANCE);

    filler::FillerConfig negborderconfig;
    negborderconfig.img = imgtest;
    negborderconfig.frameFreq = NEGBORDERFRAMEFREQ;
    negborderconfig.tolerance = NEGBORDERTOLERANCE;
    negborderconfig.seedpoint = PixelPoint(NEGBORDERX, NEGBORDERY, *negborderconfig.img.getPixel(NEGBORDERX, NEGBORDERY));
    negborderconfig.picker = &negborderPicker;

    animation anim;
    anim = filler::FillDFS(negborderconfig);
    PNG result = anim.write("images-output/dfsnegativeborder.gif"); result.convert();
    result.writeToFile("images-output/dfsnegativeborder.png");

    PNG expected; expected.readFromFile("images-soln/ex-dfsnegativeborder.png");
    REQUIRE(result==expected);

    cout << "Leaving fill::basic negative border dfs..." << endl;
}

TEST_CASE("fill::basic negative border bfs","[weight=1][part=fill]"){
  
    cout << "Entered fill::basic negative border bfs..." << endl;
  
    PNG imgtest;
    imgtest.readFromFile(NEGBORDERTESTIMAGE);
    PixelPoint p(NEGBORDERX, NEGBORDERY, *(imgtest.getPixel(NEGBORDERX, NEGBORDERY)));
    NegativeBorderColorPicker negborderPicker(imgtest, p, NEGBORDERWIDTH, NEGBORDERTOLERANCE);

    filler::FillerConfig negborderconfig;
    negborderconfig.img = imgtest;
    negborderconfig.frameFreq = NEGBORDERFRAMEFREQ;
    negborderconfig.tolerance = NEGBORDERTOLERANCE;
    negborderconfig.seedpoint = PixelPoint(NEGBORDERX, NEGBORDERY, *negborderconfig.img.getPixel(NEGBORDERX, NEGBORDERY));
    negborderconfig.picker = &negborderPicker;

    animation anim;
    anim = filler::FillBFS(negborderconfig);
    PNG result = anim.write("images-output/bfsnegativeborder.gif"); result.convert();
    result.writeToFile("images-output/bfsnegativeborder.png");

    PNG expected; expected.readFromFile("images-soln/ex-bfsnegativeborder.png");
    REQUIRE(result == expected);

    cout << "Leaving fill::basic negative border bfs..." << endl;
}
