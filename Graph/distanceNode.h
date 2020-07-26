#include "node.h"

template <typename N>
class DistanceNode {
public:
    DistanceNode() {};
    DistanceNode(N tag, double x, double y, double distance): tag(tag), x(x), y(y),distance(distance) {}
    N getTag () const { return tag; }
    double getX () const { return x; }
    double getY () const { return y; }
    Node<N> * getNode(){ return node;}
    void setNode(Node<N> * node){ this->node = node;}
    double getDistance () const {return distance;}
    void setX(double x) {this->x = x;}
    void setY(double y) {this->y = y;}
    bool operator < (const DistanceNode& other) const { return distance <= other.distance; }
    bool operator == (const DistanceNode& other) const { return tag == other.tag; }


private:
    Node<N> * node;
    N tag;
    double x;
    double y;
    double distance;
};
