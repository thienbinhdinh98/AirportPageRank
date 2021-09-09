#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../cs225/catch/catch.hpp"

#include "../edge.h"
#include "../graph.h"
#include "../vertex.h"
#include "../airportData.h"

using namespace std;

airportData a;

/* The codes are copied from graph.cpp to test pageRank. */
vector<int> pageRank(vector<vector<Edge *> > & matrix, vector<Vertex> & airports_vec){
    // indices of vertices, with highest importance, in airports vector
    vector<int> indices_result;
    int max_num_edges = 0;

    // for every destination vertex
    for (unsigned j = 0; j < matrix.size(); ++j) {
        int num_incident_edges = 0;

        // check every source vertex
        for (unsigned i = 0; i < matrix.size(); ++i) {
            // if the edge exists
            if (matrix[i][j] != NULL) {
                ++num_incident_edges;
            }
        }
        
        if (num_incident_edges > max_num_edges) {
            max_num_edges = num_incident_edges;
            
            vector<int> tmp;
            tmp.push_back(j);
            indices_result = tmp;
        } else if (num_incident_edges == max_num_edges) {
            indices_result.push_back(j);
        }
    }

    // the vector of IDs of all vertices with highest importance
    vector<int> result;
    for (int idx: indices_result) {
        result.push_back(airports_vec[idx].getID());
    }

    return result;
}

//code copied from Graph class to test with smaller data
vector<int> BFStest(int src_id, vector<vector<Edge *> > & matrix){
    //there are 7698 vertices, initialized to be false
    vector<bool> visited(4,false); //the visited vector should look like airports vector

    //initialize variables for BFS
    queue<int> q;
    vector<int> ans;
    //push the initial vertex's id in and mark as true
    visited[src_id] = true; //set the initial position to true
    q.push(src_id); 
    ans.push_back(src_id);
    int vis = 0; //vis will hold the id of the vertex
    while(!q.empty()){
        vis = q.front();
        for(unsigned i =0; i < visited.size(); i++){
            //Binh: I am asumming here that if the Edge do not exist, it is NULL, if it is, there is an Edge
            //do we have a default value for a not connected vertex, or is it just NULL?
            if(matrix[vis][i] != NULL && (!visited[i])){
                //Push the node into the queue
                q.push(i);
                ans.push_back(i);
                //Set to true when visited
                visited[i] = true;
            }
        }
        q.pop();
    }
    return ans;
}

TEST_CASE("Sanity check") {
  string temp = "test";
  REQUIRE( temp == "test" );
}

TEST_CASE("Test parse route") {
  std::string dataFile = "routes.csv";
	auto result = a.parseRouteData("tests/../data/routes.csv");
  long long count = 0;
	for (auto i: result) {
		for (auto j: i.second) {
			count++;
		}
	}
  REQUIRE(result.size() == 3315);
  REQUIRE(count == 37273);
}

TEST_CASE("Test parse airport") {
  std::string dataFile = "tests/../data/airports.csv";
  vector<Vertex> result = a.parseAirportData(dataFile);
  REQUIRE(result.size() == 7698);
  REQUIRE(result[0].getID() == 1);
  REQUIRE(result[7697].getID() == 14110);
}

TEST_CASE("Test simple BFS"){
  Vertex A(1, "A", 0, 0, "A", "A");
  Vertex B(2, "B", 0, 0, "B", "B");
  Vertex C(3, "C", 0, 0, "C", "C");
  Vertex D(4, "D", 0, 0, "D", "D");
  Edge * ab = new Edge(1, 2);
  Edge * bc = new Edge(2, 3);
  Edge * cd = new Edge(3, 4);
  vector<Vertex> airports;
  airports.push_back(A);
  airports.push_back(B);
  airports.push_back(C); 
  airports.push_back(D);
  vector<vector<Edge *> > adj_matrix(airports.size());
  for (unsigned i = 0; i < adj_matrix.size(); ++i) {
    adj_matrix[i] = vector<Edge *>(airports.size());
  }
  for (vector<Edge *> v: adj_matrix) {
		for (Edge* e: v) {
			e = NULL;
		}
	}
  adj_matrix[0][1] = ab;
  adj_matrix[1][2] = bc;
  adj_matrix[2][3] = cd;
  vector<int> result = BFStest(1, adj_matrix);
  REQUIRE(result[0] ==  1);
  REQUIRE(result[1] ==  2);
  REQUIRE(result[2] ==  3);

}

TEST_CASE("Test BFS"){
  Graph * graph = new Graph();
	vector<int> temp1 = graph->BFS(1);
	vector<int> temp2 = graph->BFS(5430);
  vector<int> temp3 = graph->BFS(11922);
  REQUIRE(temp1.size() == 3166);
  REQUIRE(temp2.size() == 3166);
  REQUIRE(temp3.size() == 3166);
}


TEST_CASE("Test pageRank") {
  /* 
  A(id:1) ---> B(id:2)
  ^ ^
  |   -
  |     -
  |        -
  |           -
  C(id:3) ---> D(id:4)

  0 1 0 0
  0 0 0 0
  1 0 0 1
  1 0 0 0
  */

  // initialize vertices and edges
  Vertex A(1, "A", 0, 0, "A", "A");
  Vertex B(2, "B", 0, 0, "B", "B");
  Vertex C(3, "C", 0, 0, "C", "C");
  Vertex D(4, "D", 0, 0, "D", "D");
  Edge * ab = new Edge(1, 2);
  Edge * ca = new Edge(3, 1);
  Edge * da = new Edge(4, 1);
  Edge * cd = new Edge(3, 4);
  // initialize parameters for pageRank function
  vector<Vertex> airports;
  airports.push_back(A);
  airports.push_back(B);
  airports.push_back(C); 
  airports.push_back(D);
  vector<vector<Edge *> > adj_matrix(airports.size());
  for (unsigned i = 0; i < adj_matrix.size(); ++i) {
    adj_matrix[i] = vector<Edge *>(airports.size());
  }
  for (vector<Edge *> v: adj_matrix) {
		for (Edge* e: v) {
			e = NULL;
		}
	}
  adj_matrix[0][1] = ab;
  adj_matrix[2][0] = ca;
  adj_matrix[3][0] = da;
  adj_matrix[2][3] = cd;

  vector<int> result = pageRank(adj_matrix, airports);
  REQUIRE(result.size() == 1);
  vector<int> sol = {1};
  REQUIRE(result == sol);
}


// Test cases for Dijkstras
TEST_CASE("Testing Dijkstras - simple") {
  /* 
  A(id:1) ---> B(id:2)
  ^ ^
  |   -
  |     -
  |        -
  |           -
  C(id:3) ---> D(id:4)

  0 1 0 0
  0 0 0 0
  1 0 0 1
  1 0 0 0
  */
  Graph *g = new Graph(); 
  // initialize vertices and edges
  Vertex A(1, "A", 0, 0, "A", "A");
  Vertex B(2, "B", 0, 0, "B", "B");
  Vertex C(3, "C", 0, 0, "C", "C");
  Vertex D(4, "D", 0, 0, "D", "D");
  Edge * ab = new Edge(1, 2);
  Edge * ca = new Edge(3, 1);
  Edge * da = new Edge(4, 1);
  Edge * cd = new Edge(3, 4);
  vector<Vertex> airports;
  g->airports.push_back(A);
  g->airports.push_back(B);
  g->airports.push_back(C); 
  g->airports.push_back(D);
  g->adj_matrix.resize(airports.size());
  for (int i = 0; i < g->adj_matrix.size(); ++i) {
    g->adj_matrix[i] = vector<Edge *>(airports.size());
  }
  for (vector<Edge *> v: g->adj_matrix) {
    for (Edge* e: v) {
      e = NULL;
    }
  }
  g->adj_matrix[0][1] = ab;
  g->adj_matrix[2][0] = ca;
  g->adj_matrix[3][0] = da;
  g->adj_matrix[2][3] = cd; 

  vector<int> solution = {1,3,4};
  vector<int> results = g->shortestPath(1, 4); 
  REQUIRE(solution == results);
}