//
// Created by daniel on 7/17/20.
//

#ifndef GNGPROYECT__GRAPHDRAWER_H
#define GNGPROYECT__GRAPHDRAWER_H



#include "../Graph/graph.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> // drawing shapes

#include "config.h"
#include <iostream>

template <typename N, typename E>
class GraphDrawer{
private:
    // contains the original image
    cv::Mat image;
    int WITH_;
    int HEIGH_;

    // contains the drawings
    cv::Mat result;

    cv::VideoWriter * videoWriter;

    std::string fileName;

public:
    GraphDrawer(){
    };

    cv::Mat getResult(){
        return result;
    }

    void readFromFile(std::string fileName){

        this->fileName = fileName;
        std::string filePath = "ResultImages/" + fileName;
        image = cv::imread(filePath);
        image.copyTo(result);


        this->WITH_ = image.cols;
        this->HEIGH_ = image.rows;
    }


    void drawGraph(Graph<N,E> *graph){
        set<Edge<N,E> *> edgeList= graph->getEdgeList();
        set<Node<N> *> nodeList = graph->getNodeList();

        for (Edge<N,E>* edge: edgeList){
            auto nodes = edge->getNodes();
            auto tag_node_1 = nodes.first;
            auto tag_node_2 = nodes.second;

            Node<N> *node_1 = graph->findNode(tag_node_1);
            Node<N> *node_2 = graph->findNode(tag_node_2);

            drawLine(node_1->getX(),node_1->getY(),node_2->getX(), node_2->getY());
        }

        for (Node<N> *node: nodeList){
            int x = (int) node->getX();
            int y = (int) node->getY();
            drawCircle(x,y);
        }

    }

    void drawCircleColor(int x, int y, cv::Scalar circleColor){
        cv::Point circleCenter(x,y);
        cv::circle(result, circleCenter, circleRadio, circleColor, CV_FILLED);
    }

    void drawCircle(int x, int y){
        cv::Point circleCenter(x,y);
        cv::circle(result, circleCenter, circleRadio, circleColor, CV_FILLED);
    }

    void drawLine(int x_1, int y_1, int x_2, int y_2){
        cv::Point p1(x_1,y_1), p2(x_2,y_2);
        cv::line(result, p1, p2, lineColor, lineThickness);
    }

    void removeDrawings(){
        image.copyTo(result);
    }


    bool initializeVideoWriter(){
        int framesPerSec = 10;
        std::string videoPath = "ResultVideos/"+ fileName + ".avi";

        cv::Size frame_size(this->WITH_, this->HEIGH_);

        videoWriter = new cv::VideoWriter(videoPath,cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                framesPerSec, frame_size, true);


        if (videoWriter->isOpened())
            return true;
        return false;
    }

    void writeFrame(cv::Mat frame){

        videoWriter->write(frame);

    }

    void releaseVideo(){
        videoWriter->release();
    }

    void setImageFile(string ImageFile){

    }

    void showImage(){
        cv::namedWindow( "Growing Neural Gas", cv::WINDOW_AUTOSIZE );
        cv::imshow( "Growing Neural Gas", result );
        cv::waitKey(0);

    }

};
#endif //GNGPROYECT__GRAPHDRAWER_H
