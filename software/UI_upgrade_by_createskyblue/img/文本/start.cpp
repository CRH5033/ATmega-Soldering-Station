#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
    char default_prefix[] = "image";
    char* prefix = default_prefix;
    if (argc >= 3)
        prefix = argv[2];

    Mat img = imread(argv[2]);
    Mat channels[3];
    split(img, channels);
    // cv::imshow("image", channels[0]);
    printf("const PROGMEM uint8_t %s[] = {", prefix);

    int Abyte, Check, count = 0, countI = 1;
    for (int i = 0; i < channels[0].cols * channels[0].rows; i++) {
        if (!channels[0].at<uchar>(i))
            Abyte |= 1;
        if (count == 7) {
            if (countI % 4 == 0) {
                Abyte >>= 4;
                Abyte <<= 4;
                i -= 4;
            }
            printf("0x%02x,", Abyte);
            countI++;
            Abyte = 0;
            count = 0;
        } else {
            count++;
            Abyte <<= 1;
        }
    }
    if (count == 4) {
        Abyte <<= 3;
        printf("0x%02x,", Abyte);
    }
    printf("};\n");

    return 0;
}