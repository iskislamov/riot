#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <ctime>
#include <string>

using namespace cv;
using namespace std;

class Binarization {
 public:
  size_t readImage(string path, bool show);
  void bradleyAlgo();
  void getResult(bool show);

 private:
  string path_;
  Mat inputImage_;
  Mat outputImage_;

  double greyConvertion(double R, double G, double B);
};
