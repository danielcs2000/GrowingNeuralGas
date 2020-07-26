#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <typeinfo>
#include "node.h"
#include "edge.h"
#include "distanceNode.h"
#include <unordered_map>

using namespace std;

template <typename N, typename E>
class Graph {
public:
    typedef Graph <N, E> self;
    typedef Node <N> node;
    typedef Edge <N, E> edge;
    typedef DistanceNode<N> distanceNode;

    Graph (bool is_directed): is_directed(is_directed), negativeWeight(false) {}

    ~Graph () {
        for(auto item: nodeList){
            delete item;
        }

        nodeList.clear();

        for (auto item: edgeList){
            delete item;
        }

        edgeList.clear();
        adjList.clear();
        adjList_Trans.clear();
    }

    bool addNode (N tag, double x, double y) {
        if (findNode(tag)) return false;
        for (auto n: nodeList ){
            if ( n -> getX() == x && n -> getY() == y) return false;
        }

        node * newNode = new node(tag,x,y);
        set <N> AdjNodes;
        adjList.insert({newNode->getTag(), AdjNodes});
        adjList_Trans.insert({newNode->getTag(), AdjNodes});
        nodeList.insert(newNode);
        return true;
    }

    void deleteNodesAlone(){
        for (node * node: nodeList){
            auto itSetNode = adjList.find(node->getTag());

            if(itSetNode->second.size() == 0)
                deleteNode(node->getTag());
        }
    }

    bool deleteNode (N tag) {
        if (!findNode(tag)) return false;
        auto node = adjList.find(tag);
        auto itMap = adjList.find(tag);
        for (auto itSet : node -> second){
            deleteEdge(tag,itSet);
            itMap = adjList.find(itSet);
            itMap->second.erase(tag);
        }


        //Eliminando de la lista de adyacencia
        adjList.erase(tag);

        //Eliminando de la lista de nodos
        for (auto i = nodeList.begin(); i != nodeList.end(); i++){
            if ( (*i) -> getTag() == tag) {
                nodeList.erase(i);
            }
        }

        //Eliminando de la lista de aristas



        node = adjList_Trans.find(tag);
        for (auto i : node -> second){
            itMap = adjList.find(i);
            itMap->second.erase(tag);
        }
        adjList_Trans.erase(tag);
        return true;
    }

    bool addEdge (N from, N to, E weight) {
        if(findEdge(from,to))
            return false;
        if(from == to)
            return false;
        if (weight < 0) negativeWeight = true;
        edge* newEdge1 = new edge(from,to,weight);
        edgeList.insert(newEdge1);
        adjList[from].insert(to);
        adjList_Trans[to].insert(from);
        if(!is_directed){
            //edge * newEdge2 = new edge(to,from,weight);
           // edgeList.insert(newEdge2);
            adjList[to].insert(from);
            adjList_Trans[from].insert(to);
        }
        return true;
    }

    bool deleteEdge (N from, N to) {
        if(!findEdge(from,to) or !findEdge (to, from))
            return false;
        if(is_directed) {
            adjList[from].erase(to);
            adjList_Trans[to].erase(from);


            auto itr = edgeList.begin();
            while (itr != edgeList.end()){

                if((*itr)->getNodes().first==from and (*itr)->getNodes().second==to){
                    edgeList.erase(itr);
                }
                itr++;
            }

        } else{
            adjList[from].erase(to);
            adjList[to].erase(from);
            adjList_Trans[from].erase(to);
            adjList_Trans[to].erase(from);

            auto itr = edgeList.begin();
            while (itr != edgeList.end()){
                edge * ed = *itr;
                if((*itr)->getNodes().first==from and (*itr)->getNodes().second==to){
                    edgeList.erase(itr);
                }
                if((*itr)->getNodes().first==to and (*itr)->getNodes().second==from){
                    edgeList.erase(itr);
                }
                itr++;
            }
        }
        return true;
    }

    node* findNode (N tag) {
        for ( auto it_set : nodeList){
            if (it_set->getTag() == tag){
                return it_set;
            }
        }
        return nullptr;
    }

    void Set(){
        for ( auto it_set : nodeList){
            it_set->setX(10);
        }
    }

    node * findNodeMaxError(){
        float max_error = -1;
        node * max_node ;
        for ( auto it_set : nodeList){
            if (it_set->getError() > max_error){
                max_error = it_set->getError();
                max_node = it_set;
            }
        }
        return max_node;
    }


    edge* findEdge (N from, N to) {
        for (auto ed : edgeList){
            if((ed->getNodes().first==from and ed->getNodes().second==to) or (ed->getNodes().first==to and ed->getNodes().second==from)){
                return ed;
            }
        }

        return nullptr;
    }

    double getSquareDistance (N from, N to){
        node* from_ = findNode(from);
        node* to_ = findNode(to);

        return (from_->getX() - to_->getX())*(from_->getX() - to_->getX()) + (from_->getY() - to_->getY())*(from_->getY() - to_->getY());
    }

    void getTwoClosestNodes(node *&n1, node *&n2,int x,int y){
        //to store nodes with distance
        set<distanceNode> nodesWithDistance;

        for (node * n:nodeList){
            double distance = (x - n->getX())*(x - n->getX()) + (y- n->getY())*(y- n->getY());
            distanceNode distanceNode1 = distanceNode(n->getTag(),n->getX(),n->getY(),distance);
            distanceNode1.setNode(n);
            nodesWithDistance.insert(distanceNode1);
        }

        int i = 1;

        for (distanceNode n: nodesWithDistance){
            if(i==1)
            {
               // n1.setX(n.getX());
               // n1.setY(n.getY());
               // n1.setTag(n.getTag());
               n1 = n.getNode();
            } else if (i == 2){
                //n2.setX(n.getX());
                //n2.setY(n.getY());
                //n2.setTag(n.getTag());
                n2 = n.getNode();
            } else{
                break;
            }
            i +=1;

        }

    }


    vector<node *> findAllNeighbors(N tag){
        node * current = findNode(tag);
        vector<node *> neighbors;


        auto itMap = adjList.find(tag);
        for (auto itSet : itMap -> second){
            neighbors.push_back(findNode(itSet));
        }
        return neighbors;
    }


    int getOutDegree (N tag){
        if (!findNode(tag)) throw "The node doesn't belong to the graph";
        auto node = adjList.find(tag);
        int outDegree = node -> second.size();
        return outDegree;
    }

    int getInDegree(N tag){
        if (!findNode(tag)) throw "The node doesn't belong to the graph";
        auto node = adjList_Trans.find(tag);
        int inDegree = node -> second.size();
        return inDegree;
    }

    map <N, int> BFS (N source) {
        if (!findNode(source)) throw "The node does not belong to the graph";
        map <N, int > d;
        N s = source;
        queue<N> cola;
        set<N> used;
        cola.push(s);
        used.insert(s);
        d[s] = 0;
        while (!cola.empty()) {
            N v = cola.front();
            cola.pop();
            for (N u : adjList[v]) {
                if (!used.count(u)) {
                    used.insert(u);
                    cola.push(u);
                    d[u] = d[v] + 1;
                }
            }
        }

        return std::move(d);
    }

    map <N, pair <int, int>> DFS (N source) {
        if (!findNode(source)) throw "The node does not belong to the graph";
        map <N, pair <int, int>> ret;
        map <N, int> time_in;
        map <N, int> time_out;
        map <N, int> color;
        int timer = 0;
        dfsRec(source, time_in, time_out, color, timer);
        for (auto pp: time_in) {
            ret[pp.first] = {time_in[pp.first], time_out[pp.first]};
        }
        return ret;
    }

    int getPosNode (N node) {
        int pos = 0;
        for (auto it : adjList) {
            if (it.first == node) break;
            pos++;
        }
        return pos;
    }

    N getTag (int temp) {
        int count = 0;
        for (auto it : adjList) {
            if (count == temp ) return it.first;
            count++;
        }
    }

    bool isDirected () const { return is_directed; }
    void setDensityParameter (double density) const { denseParameter = density; }
    int getNumberOfNodes () const { return nodeList.size(); }
    int getNumberOfEdges () const { return edgeList.size(); }
    set <node*> getNodeList () const { return nodeList; }
    set <edge *> getEdgeList ()  { return edgeList; }
    double getInfinity () const { return INF; }
    bool haveNegativeWeight () const { return negativeWeight; }

    void ImprimirGrafo(){

        //cout << "Is directed" << endl;
        //cout << is_directed << endl;
        cout << "Imprimiendo nodos" << endl;
        for(auto i:nodeList){
            cout << i->getTag() << " ("<< i->getX() <<", " << i->getY()<< " )"<< endl;
        }
        cout << endl;
        cout << "Imprimiendo aristas" << endl;
        for(auto i:edgeList){
            cout << i->getNodes().first <<" "<< i->getNodes().second<< " "  << i->getWeight() << endl;;
        }
        cout << endl;

        cout << "Imprimiendo la lista de adyacencia" << endl;
        for (auto it = adjList.begin();it != adjList.end();it++){
            cout << it->first<< " ";
            for (auto i: it->second){
                cout << i <<" ";
            }
            cout << endl;
        }

    }

private:

    const double denseParameter = 0.5;
    set <node *> nodeList;
    set <edge *> edgeList;
    map <N, set <N>> adjList;
    map <N, set <N>> adjList_Trans;
    bool is_directed;
    const double INF = 1e17;
    bool negativeWeight;

};

#endif