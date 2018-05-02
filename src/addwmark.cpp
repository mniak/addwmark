#include <iostream>
#include <math.h>
#include <regex>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/program_options.hpp>

using namespace std;
using namespace cv;
namespace po = boost::program_options;

void addWatermark(Mat &image, Mat watermark, float alpha, Size wmPadding, Size wmMaxSize) {
    auto resizefac = min((float)wmMaxSize.width / watermark.size().width, (float)wmMaxSize.height / watermark.size().height);
    resize(watermark, watermark, Size(0,0), resizefac, resizefac);
    auto rect = Rect(image.size().width - watermark.size().width - wmPadding.width, 
                     image.size().height - watermark.size().height - wmPadding.height,
                     watermark.size().width, watermark.size().height);

    if (image.channels() == 3) 
        cvtColor(image, image, CV_BGR2BGRA, 4);
   
    int fromTo[] = {3,0, 3,1, 3,2, -1,3};
    mixChannels(&watermark, 1, &watermark, 1, fromTo, 4);
    
    addWeighted(watermark, alpha, image(rect), 1, 0.0, image(rect));
}
Size parseSize(string sizeStr) {
    auto rSize = regex("^(\\d+)x(\\d+)$");
    smatch match;
    if (regex_match(sizeStr, match, rSize)) {
        cout << "x=" << stoi(match[1].str()) << endl;
        cout << "y=" << stoi(match[2].str()) << endl;
    } else {
        return NULL;
    }
}
int main(int argc, char** argv) {
    float alpha;
    string max_sizeStr, paddingStr;

    auto desc = po::options_description("Program Options");
    desc.add_options()
        ("help", "Show help and usage info")
        ("alpha", po::value<float>(&alpha)->default_value(0.25), 
      "Alpha value for the watermark (float, betwen 0-1)")
        ("max-size", po::value<string>(&max_sizeStr)->default_value("300x200"),
      "Watermark maximum size")
        ("padding", po::value<string>(&paddingStr)->default_value("20x20"),
      "Watermark padding")
        ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);  


    auto watermark = imread("../test/logo.png", CV_LOAD_IMAGE_UNCHANGED);
    auto image = imread("../test/image.jpg", CV_LOAD_IMAGE_COLOR);

    if (vm.count("help")) {
        cout << desc << endl;
        return 1;
    }
    if (!watermark.data) {
        cout << "Could not load watermark file." << endl;
        return -2;
    }
    if (!image.data) {
        cout << "Could not load image file." << endl;
        return -2;
    }

    auto wmMaxSize = Size(300, 200);
    auto wmPadding = Size(20,20); 

    addWatermark(image, watermark, alpha, wmPadding, wmMaxSize); 

    return 0;
}
