

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../GNG/config.h"

#include <iostream>




class Preprocessor{
private:
    cv::Mat imput;
    cv::Mat result;

    // Sobel params
    int ddepth = CV_16S;
    int delta = 0;
    int scale = 1;

    int numberPoints ;

    Position<int> * positionsBorder;

    std::string imputName;

public:
    Preprocessor(){};
    ~Preprocessor(){
        delete [] positionsBorder;
    };
    void run(){
        //resizeImage();
        //grayScale();
        sobelMask();
        normalizeImage();
        saveResult();
    }

    int readImage(std::string ImageFile){


        std::string dirImages = "ImputImages/" + ImageFile;

        cout << "Reading from " + dirImages << endl;
        imput = cv::imread(dirImages);


        if(!imput.data ) {
            std::cout <<  "Could not open or find the image" << std::endl ;
            return -1;
        }
        imputName = ImageFile;
        imput.copyTo(result);
        return 0;
    }

    void resizeImage(){
        cout << "Resizing image..." << endl;

        cv::resize(result, result, cv::Size(WITH,HEIGHT));
    }

    void grayScale(){
        cout << "Converting to grayscale..." << endl;

        cv::cvtColor(result,result, CV_BGR2GRAY);
    }

    void sobelMask(){
        grayScale();

        //to reduce the noise
        cv::GaussianBlur(result,result,cv::Size(3,3),0,0, cv::BORDER_DEFAULT);

        //showResult();
        // Genereta grad_x grad_y
        cv::Mat grad_x, grad_y;
        cv::Mat abs_grad_x, abs_grad_y;

        //Gradient X

        cv::Sobel(result,grad_x,ddepth,1,0,3,scale,delta, cv::BORDER_DEFAULT);
        cv::convertScaleAbs(grad_x,abs_grad_x);

        // Gradient y

        cv::Sobel(result,grad_y,ddepth,0,1,3,scale,delta, cv::BORDER_DEFAULT);
        cv::convertScaleAbs(grad_y,abs_grad_y);

        cout << "llegué"<<endl;


        cv::addWeighted(abs_grad_x, 0.5,abs_grad_y, 0.5, 0 , result);

    }

    void showResult(){
        cv::namedWindow("showResult", CV_WINDOW_AUTOSIZE);
        cv::imshow("showResult", result);
        cv::waitKey(0);
    }

    void normalizeImage(){
        for (int y = 0; y < result.cols; y++)
        {
            for (int x = 0; x < result.rows; x++) {

                if(result.at<uchar>(x, y)>60)
                {
                    result.at<uchar>(x, y) = 255;
                } else{
                    result.at<uchar>(x, y) = 0;
                }
            }
        }

    }

    Position<int> * getBorderPoints(){
        int n = 0;
        for (int x = 0; x < result.cols; x++)
        {
            for (int y = 0; y < result.rows; y++) {

                if(result.at<uchar>(y, x)==255)
                    n += 1;
            }
        }
        numberPoints = n;

        positionsBorder = new Position<int>[n];

        int i = 0;
        for (int x = 0; x < result.cols; x++)
        {
            for (int y = 0; y < result.rows; y++) {

                if(result.at<uchar>(y, x)==255){
                    Position<int> position = {x,y};
                    positionsBorder[i] = position;
                    i += 1;
                }


            }
        }
        return positionsBorder;

    }



    int getNumberPoints(){
        return numberPoints;
    }


    void saveResult(){

        std::string resultName ="ResultImages/" +imputName;
        cout << "Saving Result in " + resultName<< endl;
        cv::imwrite(resultName,result );
    }

};