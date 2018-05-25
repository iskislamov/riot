#include "Binarization.h"
#include <algorithm>

#define SIZE_AREA 16
#define T 0.15

size_t Binarization::readImage(string path, bool show) {
  path_ = path;
  inputImage_ = imread(path_, CV_LOAD_IMAGE_COLOR);
  if (inputImage_.empty()) {
    cout << "Failed at inputing image" << std::endl;
    exit(-1);
  }

  outputImage_ = inputImage_;

  if (show) {
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", inputImage_);
    waitKey(0);
  }

  return inputImage_.total() / 1000000;
}

void Binarization::bradleyAlgo() {
  int width = inputImage_.size().width;
  int height = inputImage_.size().height;

  int* integralImage = new int[height * width * sizeof(int)];

  int sum = 0;
  int index;

  for (int i = 0; i < width; ++i) {
    sum = 0;
    for (int j = 0; j < height; ++j) {
      Vec3b color = inputImage_.at<Vec3b>(j, i);

      sum += greyConvertion(color.val[0], color.val[1], color.val[2]);
      index = j * width + i;
      if (i != 0) {
        integral_image[index] = integral_image[index - 1] + sum;
      } else {
        integral_image[index] = sum;
      }
    }
  }

  int size = width / SIZE_AREA;
  int count = 0;
  int x1, y1, x2, y2;
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      x1 = max(i - size, 0);
      x2 = min(i + size, width - 1);
      y1 = max(j - size, 0);
      y2 = min(j + size, height - 1);

      count = (x2 - x1) * (y2 - y1);

      sum = integral_image[y2 * width + x2] - integral_image[y1 * width + x2] -
            integral_image[y2 * width + x1] + integral_image[y1 * width + x1];

      Vec3b color = inputImage_.at<Vec3b>(j, i);
      if (greyConvertion(color.val[0], color.val[1], color.val[2]) * count <
          sum * (1.0 - T)) {
        outputImage_.at<Vec3b>(j, i)[0] = 0;
        outputImage_.at<Vec3b>(j, i)[1] = 0;
        outputImage_.at<Vec3b>(j, i)[2] = 0;
      } else {
        outputImage_.at<Vec3b>(j, i)[0] = 255;
        outputImage_.at<Vec3b>(j, i)[1] = 255;
        outputImage_.at<Vec3b>(j, i)[2] = 255;
      }
    }
  }

  delete[] integral_image;
}

double Binarization::greyConvertion(double R, double G, double B) {
  return 0.2125 * R + 0.7154 * G + 0.0721 * B;
}

void Binarization::getResult(bool show) {
  string path;
  for (size_t i = 0; i < path_.size() - 4; ++i) {
    path += path_[i];
  }
  path += " res.jpg";
  imwrite(path, outputImage_);

  if (show) {
    namedWindow("Display window 2", WINDOW_AUTOSIZE);
    imshow("Display window 2", outputImage_);
    waitKey(0);
  }
}
