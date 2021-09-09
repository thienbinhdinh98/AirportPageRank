#pragma once

#include <map>
#include <vector>
#include <cmath>
#include "vertex.h"
#include "edge.h"
#include <queue>
//reference for the idea: https://www.tutorialspoint.com/cplusplus-program-to-implement-adjacency-matrix
//https://www.geeksforgeeks.org/graph-and-its-representations/
using namespace std;

class Graph {
    public:
        /**
         * Default constructor
         */ 
        Graph();

        /**
         * Do a BFS on the whole graph
         * @param src_id the starting position to start searching
         * @return a vector of airport Id
         */ 
        vector<int> BFS(int src_id);
        
        /**
         * Do a BFS on the graph where it will stops
         * @param src_id the starting position to start searching
         * @param dest_id the ending position of the search
         * @return a vector of airport Id
         */ 
        vector<int> BFS(int src_id, int dest_id);
        
        /**
         * Using Dijkstra's Algorithm to find the shortest path
         * @param src_id
         * @param dest_id
         */ 
        vector<int> shortestPath(int src_id, int dest_id);

        vector<int> pageRank(/*emptyfor now*/);

        void InsertEdge();
        

        int getMatchsize(){
            return match.size();
        }

        int getRoutesSize(){
            return routes.size();
        }

        int getAdjMatrixSize(){
            return adj_matrix.size();
        }

        int getAirportsSize(){
            return airports.size();
        }
        vector<Vertex> airports;
        // K: airport id
        // V: index of the airport in the above airports vector
        map<int, int> match;

        // src_id -> map<dest_id, Edge>
        map<int , map<int, Edge*> > routes;

        //hold edge information
        vector<vector<Edge *> > adj_matrix;

        void setup();
        
        /* calculate the distance between two vertices */
        double getWeight(Vertex src, Vertex dest);

        //dont know why these vectors are not green in VScode, maybe lagging for me
        //helper functions
        //helper to find the index where the minimum distance occurs
        int minimumDistance(vector<int> distances, vector<bool> visited);
        //helper to find the total distance between two locations
        double sumDistances(vector<int> distances);
};
