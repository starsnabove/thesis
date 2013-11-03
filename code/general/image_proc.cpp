#include "../general/image_proc.h"


/* Img_Processor constructor
 * img)dir is the directory that the image is stored at
 */
Img_Processor::Img_Processor(string img_dir) {

    img = imread(img_dir.c_str(), CV_LOAD_IMAGE_COLOR);

    if (!img.data) {
        // TODO print error message stating could not open image
        cerr << "image did not load in Img_processor init\n";
        exit(1);
    }

    //smooth image using gaussian kernel
    GaussianBlur(img, img, Size(3, 3), 0, 0, BORDER_DEFAULT);

    //change image to HSV color format
    cvtColor(img, imgHSV, CV_BGR2HSV);

}

/* Thresholds the image around red and obtains the contours & centres
 * of the masses that those contours develop
 */
void Img_Processor::find_red(void) {

    //Threshold image around red
    inRange(imgHSV, REDLB, REDUB, imgred);

    //find red contours
    findContours(imgred, redcontours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

    drawContours(imgred, redcontours, -1, Scalar::all(255), CV_FILLED);

    vector<Moments> redmoments(redcontours.size() );
    for (int i = 0; i < redcontours.size(); ++i) {
        redmoments[i] = moments(redcontours.size(), false);
        /*if (! redmoments[i] ) {
            //TODO I believe this is bad so should perhaps stop
        }*/
    }

    for (int i = 0; i < redcontours.size(); ++i) {
        redcentres.push_back(Point2f(redmoments[i].m10 / redmoments[i].m00, 
                redmoments[i].m01 / redmoments[i].m00));
    }
}

/* Thresholds the image around blue and obtains the contours & centres
 * of the masses that those contours develop
 */
void Img_Processor::find_blue(void) {

    inRange(imgHSV, BLUELB, BLUEUB, imgblue);

    findContours(imgblue, bluecontours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

    drawContours(imgblue, bluecontours, -1, Scalar::all(255), CV_FILLED);

    vector<Moments> bluemoments(bluecontours.size() );
    for (int i = 0; i < bluecontours.size(); ++i) {
        bluemoments[i] = moments(bluecontours.size(), false);
        /*if (! bluemoments[i] ) {
            //TODO I believe this is bad so should perhaps stop
        }*/
    }

    for (int i = 0; i < bluecontours.size(); ++i) {
        bluecentres.push_back(Point2f(bluemoments[i].m10 / bluemoments[i].m00,
                bluemoments[i].m01 / bluemoments[i].m00));
    }

}

/* Thresholds the image around yellow and obtains the contours & centres
 * of the masses that those contours develop
 */
void Img_Processor::find_yellow(void) {

    vector<Vec4i> hierarchy;

    inRange(imgHSV, YELLOWLB, YELLOWUB, imgyellow);

//    findContours(imgyellow, yellowcontours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    findContours(imgyellow, yellowcontours, hierarchy, CV_RETR_TREE, 
            CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    drawContours(imgyellow, yellowcontours, -1, Scalar::all(255), CV_FILLED);

    vector<Moments> yellowmoments(yellowcontours.size() );
    for (int i = 0; i < yellowcontours.size(); ++i) {
        yellowmoments[i] = moments(yellowcontours.size(), false);
        /*if (! yellowmoments[i] ) {
            //TODO I believe this is bad so should perhaps stop
        }*/
    }

    for (int i = 0; i < yellowcontours.size(); ++i) {
        cout << "yel mom:" << yellowmoments[i].m10 << ',';
        cout << yellowmoments[i].m00 << ',' << yellowmoments[i].m01 << endl;
        yellowcentres.push_back(Point2f(yellowmoments[i].m10 / \
                yellowmoments[i].m00,
                yellowmoments[i].m01 / yellowmoments[i].m00));
    }
}

/* Returns the centres of the red masses detected
 */
vector<Point2f> Img_Processor::get_red_centres(void) {

    return redcentres;

}


/* Returns the centres of the blue masses detected
 */
vector<Point2f> Img_Processor::get_blue_centres(void) {

    return bluecentres;

}


/* Returns the centres of the yellow masses detected
 */
vector<Point2f> Img_Processor::get_yellow_centres(void) {

    return yellowcentres;

}

/* Returns the red contours detected
 */
vector<vector<Point> > Img_Processor::get_red_contours(void) {

    return redcontours;

}


/* Returns the blue contours detected
 */
vector<vector<Point> > Img_Processor::get_blue_contours(void) {

    return bluecontours;

}


/* Returns the yellow contours detected
 */
vector<vector<Point> > Img_Processor::get_yellow_contours(void) {

    return yellowcontours;

}

/* Returns the original Image loaded from the file
 */
Mat Img_Processor::get_original_img(void) {

    return img;

}

/* Returns the image after converted to HSV color format
 */
Mat Img_Processor::get_HSV_img(void) {

    return imgHSV;

}

/* Returns an image thresholded for red
 */
Mat Img_Processor::get_red_img(void) {

    return imgred;

}


/* Returns an image thresholded for blue
 */
Mat Img_Processor::get_blue_img(void) {

    return imgblue;

}


/* Returns an image thresholded for yellow
 */
Mat Img_Processor::get_yellow_img(void) {

    return imgyellow;

}

/* Saves the HSV image to the given location
 */
void Img_Processor::save_HSV_img(string dir) {

    try {
        imwrite(dir, imgHSV);
    }
    catch (const std::exception& ex) {
        //TODO error message cannot save imgHSV
    }
}

/* Saves the img thresholded for red
 */
void Img_Processor::save_red_img(string dir) {

    try {
        imwrite(dir, imgred);
    }
    catch (const std::exception& ex) {
        //TODO error message saving red
    }
}


/* Saves the img thresholded for blue
 */
void Img_Processor::save_blue_img(string dir) {

    try {
        imwrite(dir, imgblue);
    }
    catch (const std::exception& ex) {
        //TODO error message saving blue
    }
}
/* Saves the img thresholded for yellow
 */
void Img_Processor::save_yellow_img(string dir) {

    try {
        imwrite(dir, imgyellow);
    }
    catch (const std::exception& ex) {
        //TODO error message saving green
    }
}


int main(int argc, char ** argv) {

    Img_Processor proc("/home/starsnabove/Desktop/test.jpg");

    proc.find_red();
    proc.find_blue();
    proc.find_yellow();

    proc.save_blue_img("/home/starsnabove/Desktop/t_b.jpg");
    proc.save_red_img("/home/starsnabove/Desktop/t_r.jpg");
    proc.save_yellow_img("/home/starsnabove/Desktop/t_y.jpg");

    for (int i = 0; i < proc.get_blue_centres().size(); ++i) {
        cout << proc.get_blue_centres()[i] <<endl;
    }
    return 0;
}
