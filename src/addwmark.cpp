#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    Mat image = imread("../test/logo.png", CV_LOAD_IMAGE_COLOR);
    return 0;
}
