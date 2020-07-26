
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> // drawing shapes
#include <iostream>
#include "../GNG/graphDrawer.h"
#include "../Graph/graph.h"
#include "../PreProcessor/Preprocessor.h"



int preprocessorTest(){

    Preprocessor preprocessor;
    preprocessor.readImage("img2.jpg");
    preprocessor.run();

    Position<int>* positions = preprocessor.getBorderPoints();
    int n = preprocessor.getNumberPoints();
    for (int i = 0; i < preprocessor.getNumberPoints(); i++){
        cout << positions[i].x << " "<< positions[i].y << endl;

    }

    GraphDrawer<char,int> graphDrawer;

    graphDrawer.readFromFile("ResultImages/img2.jpg");


    for(int i = 0; i<n ;i++){
        graphDrawer.drawCircle(positions[i].y,positions[i].x);
    }
    graphDrawer.showImage();


    return 0;

}


int graphDrawerTest(){
    GraphDrawer<char,int> graphDrawer;

    graphDrawer.initialize();


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


int main( int argc, char** argv )
{
    preprocessorTest();
    return 0;
}
