#include <iostream>
#include "airportData.h"
#include "graph.h"
#include <vector>
#include "vertex.h"
#include <string>
using namespace std;

int main () {
	int id1, id2;
	cout<<" Enter in the starting airport ID: "<<endl;
	cin>>id1;
	cout<<" Enter in the destination airport ID: "<<endl;
	cin>>id2;
	Graph *graph = new Graph();

	/*** For Dijkstras ***/
	vector<int> paths = graph->shortestPath(id1,id2);	
	if (paths.size() == 1) {
		cout<<" there are not routes from: "<<id1<<" to: "<<id2<<endl;
	} else {
		cout<<" the airport ID path you will need to take from "<<id1<<" to "<<id2<<" is: "<<endl;
		for (int i = 0; i < paths.size(); i++) {
			cout<<paths[i]<<" -> ";
		}
	}

	/*** For Pagerank **/
	vector<int> pr = graph->pageRank();

	cout<<" most important airport "<<endl;
	for (int i = 0; i < pr.size(); i++) {
		cout<<pr[i]<<endl;
	}


	/*** For BFS ***/
	vector<int> bfs = graph->BFS(id1);

	std::ofstream testBFS;
	testBFS.open("BFSresult.txt");
	int count = 0;
	for(auto x: bfs){
		count++;
		testBFS<< x << " -> ";
		if (count % 10 == 0) {
			testBFS<<"\n";
		}
	}
	testBFS.close();	

}
