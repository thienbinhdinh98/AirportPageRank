#pragma once
#include <string>
#include "vertex.h"

//inspire by https://web.stanford.edu/dept/cs_edu/cppdoc/Edge-class.html
class Edge {
    public:
        Edge(int s, int d);

        int getSource();
        
        int getDest();

        double calculateWeight(Vertex src, Vertex dest);

        void setWeight(double w);
        double getEdgeWeight();
    //ADD SOME OPERATOR < = != LATER
    private:
        int source;
        int destination;
        double weight;
};