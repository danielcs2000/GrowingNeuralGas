#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> // drawing shapes
#include <iostream>
#include "../GNG/graphDrawer.h"
#include "../Graph/graph.h"



int graphDrawerTest(){
    GraphDrawer<char,int> graphDrawer;

    graphDrawer.readFromFile("ResultImages/img1.jpg");


    graphDrawer.drawLine(40,100,200,300);
    graphDrawer.drawCircle(40,100);
    graphDrawer.drawCircle(200,300);


    graphDrawer.showImage();
    Graph<char,int> *graph = new Graph<char, int>(false);

    // Adding nodes
    graph->addNode('A',300,100);
    graph->addNode('B',100,300);
    graph->addNode('C',100,100);
    graph->addNode('D',300,300);

    // Adding Edges
    graph->addEdge('A','C',3);
    graph->addEdge('A','B',3);
    graph->addEdge('A','D',3);
    graph->ImprimirGrafo();

    graphDrawer.removeDrawings();

    graphDrawer.drawGraph(graph);
    graphDrawer.showImage();

    return 0;

}

int uniqueColors(){
    cv::Mat img;
    img = cv::imread("ResultImages/img1.jpg");

    cout << img.cols << " "<< img.rows<< endl;
    for (int y = 0; y < 3*img.cols; y++)
    {
        for (int x = 0; x < img.rows; x++) {

            if(img.at<uchar>(x, y)>60)
            {
                img.at<uchar>(x, y) = 255;
            } else{
                img.at<uchar>(x, y) = 0;
            }
        }
    }



    cv::namedWindow( "After", cv::WINDOW_AUTOSIZE );
    cv::imshow("After",img);
    cv::waitKey(0);


}


int main(){
   // graphDrawerTest();
   uniqueColors();
}