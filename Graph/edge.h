#ifndef EDGE_H
#define EDGE_H

#include <utility>
#include "node.h"

template <typename N, typename E>
class Edge {
public:
    Edge () {}
    Edge (N from, N to, E weight): from(from), to(to), weight(weight) {
        this->age = 0;
    }
    E getWeight () const { return weight; }
    N getFrom () const { return from; }
    N getTo () const { return to; }
    int getAge() {return age;}
    void setAge(int age){ this->age = age;}
    std::pair <N, N> getNodes () const { return {from, to}; }
    bool operator < (const Edge& other) const {
        if (weight != other.weight) return weight < other.weight;
        if (from != other.from) return from < other.from;
        return to < other.to;
    }
    bool operator == (const Edge& other) const {
        return  from == other.from and to == other.to;
    }


private:
    E weight;
    N from;
    N to;
    int age;
};

#endif