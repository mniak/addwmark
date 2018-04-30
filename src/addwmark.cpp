#include <iostream>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/program_options.hpp>

using namespace std;
using namespace cv;
namespace po = boost::program_options;

void addWatermark(Mat &image, Mat watermark, float alpha, Size wmPadding, Size wmMaxSize) {
    float resizefac = min((float)wmMaxSize.width / watermark.size().width, (float)wmMaxSize.height / watermark.size().height);
    resize(watermark, watermark, Size(0,0), resizefac, resizefac);
    Rect rect = Rect(image.size().width - watermark.size().width - wmPadding.width, 
                     image.size().height - watermark.size().height - wmPadding.height,
                     watermark.size().width, watermark.size().height);

    if (image.channels() == 3) 
        cvtColor(image, image, CV_BGR2BGRA, 4);
   
    int fromTo[] = {3,0, 3,1, 3,2, -1,3};
    mixChannels(&watermark, 1, &watermark, 1, fromTo, 4);
    
    addWeighted(watermark, alpha, image(rect), 1, 0.0, image(rect));
}
int main(int argc, char** argv) {
    po::options_description opts("Program Options");
    opts.add_options()
        ("help", "Show help and usage info")
        ("alpha", po::value<float>(), "Alpha value for the watermark (float, betwen 0-1)")
        ;

    Mat watermark = imread("../test/logo.png", CV_LOAD_IMAGE_UNCHANGED);
    Mat image = imread("../test/image.jpg", CV_LOAD_IMAGE_COLOR);

    if (!watermark.data) {
        cout << "Could not load watermark file." << endl;
        exit(-1);
    }
    if (!image.data) {
        cout << "Could not load image file." << endl;
        exit(-2);
    }

    Size wmMaxSize = Size(300, 200);
    Size wmPadding = Size(20,20); 
    float alpha = 0.25;

    addWatermark(image, watermark, alpha, wmPadding, wmMaxSize); 
    resize(image, image, Size(0,0), 0.7, 0.7);

    imshow("image", image);
    waitKey(0);
        
    return 0;
}
