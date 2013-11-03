#ifndef __IMAGE_PROC_H_INCLUDED__
#define __IMAGE_PROC_H_INCLUDED__

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/opengl_interop.hpp"
#include "opencv2/contrib/contrib.hpp"
#include <iostream>
#include <exception>
#include <vector>

using namespace cv;
using namespace std;


static const Scalar REDLB = cvScalar(170, 140, 220);
static const Scalar REDUB = cvScalar(160, 180, 245);
static const Scalar BLUELB = cvScalar(90, 165, 230);
static const Scalar BLUEUB = cvScalar(100, 205, 255);
static const Scalar YELLOWLB = cvScalar(25, 15, 230); //yellow atm
static const Scalar YELLOWUB = cvScalar(35, 50, 255);


class Img_Processor {

    public:
        Img_Processor(string);
        void find_red(void);
        void find_blue(void);
        void find_yellow(void);
        vector<Point2f> get_red_centres(void);
        vector<Point2f> get_blue_centres(void);
        vector<Point2f> get_yellow_centres(void);

        vector<vector<Point> > get_red_contours(void);
        vector<vector<Point> > get_blue_contours(void);
        vector<vector<Point> > get_yellow_contours(void);

        Mat get_original_img(void);
        Mat get_HSV_img(void);
        Mat get_red_img(void);
        Mat get_blue_img(void);
        Mat get_yellow_img(void);

        void save_HSV_img(string);
        void save_red_img(string);
        void save_blue_img(string);
        void save_yellow_img(string);

    private:
            Mat img;
            Mat imgHSV;
            Mat imgred; // img thresholded for red
            Mat imgblue; // img thresholded for blue
            Mat imgyellow; // img tresholded for green

            vector<vector<Point> > redcontours;
            vector<vector<Point> > bluecontours;
            vector<vector<Point> > yellowcontours;

            vector<Point2f> redcentres;
            vector<Point2f> bluecentres;
            vector<Point2f> yellowcentres;


};

#endif
