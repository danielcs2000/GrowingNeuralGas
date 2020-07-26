#include "../Graph/graph.h"
#include "config.h"
#include <ctime>
#include <stdlib.h>
#include "graphDrawer.h"

class GNG {

private:

    Graph<int,int> *graph;
    GraphDrawer<int,int> graphDrawer;

    Position<int> *data;
    int n; //number of elements in data;

    double eps_n;
    double eps_b;
    int max_age;
    int lambda;
    double alpha;
    double beta;
    int max_nodes;
    int imput_signals;
    int count; // for tag nodes




    // for random imput
    int p;
    int rand_count;

public:
    GNG(Position<int>* data, int n){

        this->eps_b = EPS_B;
        this->eps_n = EPS_N;
        this-> max_age= MAX_AGE;
        this-> lambda = LAMBDA;
        this-> alpha = ALPHA;
        this-> beta = BETA;
        this-> max_nodes = MAX_NODES;



        this->graph = new Graph<int,int>(false);
        this->data = data;
        this->imput_signals = 0;
        this->n = n;

        this->count = 0; //it has the tag if a new node is inserted


    //    srand(time(NULL));

        //for ramdom imput

        if (n>12721)
            this->p = 12721;
        else
            this->p = 14741;

        this->rand_count = 1;



        // initialize the graph
        Position<int> ran =  getRandomData();
        graph->addNode(count,ran.x,ran.y);
        count++;
        Position<int> ran2 = getRandomData();
        graph->addNode(count,ran2.x,ran2.y);
        count++;
        graph->addEdge(0,1,0);


    }

    void setGraphDrawer(GraphDrawer<int,int> graphDrawer){
        this -> graphDrawer = graphDrawer;
    }

    void getNewPositionWinner(Position<int> &newPos, Position<int> winner, Position<int> current){

        int dist_x = current.x - winner.x;
        int dist_y = current.y - winner.y;

        double delta_x = eps_b*dist_x;
        double delta_y = eps_b*dist_y;


        newPos.x = winner.x + delta_x +0.5;
        newPos.y = winner.y + delta_y + 0.5;
    }

    Position<int>  getRandomData(){

        int random =  (p*rand_count)%n;

        rand_count ++;
        return data[random];
    }


    void getNewPositionWinnerNeighbor(Position<int> &newPos, Position<int> winner_neighbor, Position<int> current){

        int dist_x = current.x - winner_neighbor.x;
        int dist_y = current.y - winner_neighbor.y;

        double delta_x = eps_n*dist_x;

        double delta_y = eps_n*dist_y;

        newPos.x = winner_neighbor.x + delta_x +0.5;
        newPos.y = winner_neighbor.y + delta_y +0.5;

    }

    void getAveragePosition(Position<int> &avgPos, Position<int> a, Position<int> b){
        avgPos.x = (a.x + b.x)/2;
        avgPos.y = (a.y + b.y)/2;
    }

    void updateWinner(int x, int y){
        //color winner 1
        cv::Scalar color(0,0,255);

        //color winner 2
        cv::Scalar color2(0,255,255);

        cv::Scalar color3(255,0,0);

        // color new Pos winner 1

        // color new Pos winner 2


      //  graphDrawer.drawCircleColor(x,y,color2);

        Node<int> * winner1;
        Node<int> * winner2;

        //graph->ImprimirGrafo();
        //find the two nierest nodes to the input position
        graph->getTwoClosestNodes(winner1,winner2,x,y);

        graphDrawer.drawCircleColor(winner1->getX(),winner1->getY(),color);

        graphDrawer.drawCircleColor(winner2->getX(),winner2->getY(),color2);


        // Error of Winner_n1
        double error1 = (winner1->getX() - x)*(winner1->getX() - x) + (winner1->getY() - y)*(winner1->getY() - y);

        // find the new error
        double current_error = winner1->getError();
        double new_error = current_error + error1;

        //Update the new error
        winner1->setError(new_error);

        // move the winner towards current node

        Position<int> current = {x,y};
        Position<int> winnerPos = {(int)winner1->getX(),(int)winner1->getY()};

        Position<int> newPosWinner;



        getNewPositionWinner(newPosWinner, winnerPos, current);

        graphDrawer.drawCircleColor(newPosWinner.x,newPosWinner.y,color);


        winner1->setX(newPosWinner.x);
        winner1->setY(newPosWinner.y);

        vector<Node<int> *> neighbors = graph->findAllNeighbors(winner1->getTag());

        // Update all neighbors position and all edges emanating from winner1

        for (auto node: neighbors){
            Position<int> newPosNeighbor;
            Position<int> currentNeighborPos = {(int)node->getX(),(int)node->getY()};
            Position<int> curr = {x,y};

            // calculate new Position of neighbor
            getNewPositionWinnerNeighbor(newPosNeighbor, currentNeighborPos,curr);

            // set the new position
            node->setX(newPosNeighbor.x);
            node->setY(newPosNeighbor.y);
            graphDrawer.drawCircleColor(node->getX(),node->getY(),color3);
            //update the edges
            auto neighborEdge =  graph->findEdge(node->getTag(),winner1->getTag());

            int currentAge = neighborEdge->getAge();

            int newAge = currentAge + 1;
            neighborEdge->setAge(newAge);

            neighborEdge =  graph->findEdge(node->getTag(),winner1->getTag());
            int updatedAge = neighborEdge->getAge();

        }
        //graphDrawer.showImage();


        // if winner 1 and winner 2 are connected update their edges to 0

        auto edgeWin1_Win2 = graph->findEdge(winner1->getTag(),winner2->getTag());

        if(edgeWin1_Win2){
            edgeWin1_Win2->setAge(0);
        }else{
            graph->addEdge(winner1->getTag(),winner2->getTag(),0);
        }

        // if there are edges more than maximun allowed age, remove them

        auto edgeList = graph->getEdgeList();

        for (auto edge: edgeList){
            if (edge->getAge() > max_age )
                graph->deleteEdge(edge->getFrom(),edge->getTo());
        }

        // if this results in nodes having no emanating edges, remove them as well
        graph->deleteNodesAlone();

    }


    void train(int max_iterations){
        graphDrawer.initializeVideoWriter();
        cout << "Starting gng training..."<< endl;
        for (int i = 1; i <= max_iterations; i++)
        {
            cout<< endl << "Iteration " << i<<" ..."<<  endl;


            Position<int> input = getRandomData();


            updateWinner(input.x, input.y);
            graphDrawer.removeDrawings();

            if(i%8==0){
                graphDrawer.drawGraph(graph);
                //graphDrawer.drawCircle(input.x,input.y);
             //   graphDrawer.showImage();
                graphDrawer.writeFrame(graphDrawer.getResult());

            }


            // if number of input signal generated so far
                if(i%lambda == 0 and graph->getNumberOfNodes() <= max_nodes){

                    // find the node with largest error

                    auto max_error_node = graph->findNodeMaxError();

                    // find the neighbor of the node just found with largest error

                    vector<Node<int>*> neighbors = graph->findAllNeighbors(max_error_node->getTag());

                    double max = -1;
                    Node<int> * max_neighbor_error_node ;
                    for ( auto node : neighbors){
                        if (node->getError() > max){
                            max = node->getError();
                            max_neighbor_error_node = node;
                        }
                    }
                    // max_neighbor_error_node has the max error

                    // inster a new node half way between these two

                    Position<int> newNodePos;
                    Position<int> a = {(int)max_error_node->getX(),(int)max_error_node->getY()};
                    Position<int> b = {(int)max_neighbor_error_node->getX(),(int)max_neighbor_error_node->getY()};

                    getAveragePosition(newNodePos, a,b);

                    int newTag = count;
                    graph->addNode(newTag,newNodePos.x,newNodePos.y);
                    count ++;
                    //delete the edge between the two nodes
                    graph->deleteEdge(max_error_node->getTag(),max_neighbor_error_node->getTag());

                    // insert edges between the new node and the other two

                    graph->addEdge(newTag,max_error_node->getTag(),0);
                    graph->addEdge(newTag,max_neighbor_error_node->getTag(), 0);



                    //decrease errir variable of other two nodes

                    //for node 1
                    auto node_max_error = graph->findNode(max_error_node->getTag());
                    double new_error = node_max_error->getError()*alpha;
                    node_max_error->setError(new_error);

                    //for node 2
                    auto node_second_error = graph->findNode(max_neighbor_error_node->getTag());
                    double new_error_second = node_second_error->getError()*alpha;
                    node_second_error->setError(new_error_second);

                    //initialize the error variable of the new node with max_error
                    graph->findNode(newTag)->setError(new_error);

                }


                // decrease all error variables

                auto allNodes = graph->getNodeList();

                for (auto node: allNodes){
                    double oldError = node->getError();
                    double newError = oldError - beta*oldError;
                    node->setError(newError);
                }


        }
        graphDrawer.releaseVideo();

    }




};