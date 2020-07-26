
#include "../Graph/graph.h"


int main(){

    Graph<char,float> *graph = new Graph<char, float>(false);

    // Adding nodes

    graph->addNode('A',1,1);

    graph->addNode('B',2,2);

    graph->addNode('C',3,3);

    graph->addNode('D',4,4);

    // Adding Edges
    graph->addEdge('A','C',3);

    graph->addEdge('A','B',3);

    graph->addEdge('B','C',3);

    graph->ImprimirGrafo();

   // cout << "Deleting B";
   // graph->deleteNode('B');
    graph->ImprimirGrafo();

    Node<char>* n1;
    Node<char>* n2;

    graph->getTwoClosestNodes(n1,n2,2,2);

//    graph->findNode('A')->setY(3);
    graph->Set();
    graph->deleteNodesAlone();
    graph->ImprimirGrafo();




}
