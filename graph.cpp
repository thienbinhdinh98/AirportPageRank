#include "graph.h"
#include "airportData.h"
#include <limits.h>
using namespace std;

//builds adjacency matrix
Graph::Graph(){
    setup();
}

void Graph::setup() {
    airportData a;
    airports = a.parseAirportData("data/airports.dat");
    match = a.airportMatch(airports);
    routes = a.parseRouteData("data/routes.csv");

    adj_matrix = vector<vector<Edge *> >(airports.size());
    for (unsigned i = 0; i < airports.size(); i++) {
        adj_matrix[i] = vector<Edge *>(airports.size());
    }

    for (vector<Edge *> v: adj_matrix) {
		for (Edge* e: v) {
			e = NULL;
		}
	}
	
    // The first index of the adj_matrix is src_idx, while the second one is dest_idx
	for (map<int, map<int, Edge*> >::iterator it_outer = routes.begin(); it_outer != routes.end(); ++it_outer) {
		int src_idx = -1;
		int dest_idx = -1;
		
		// Get the src_idx
		map<int, int>::iterator it_match = match.find(it_outer->first);
		if (it_match != match.end()) {
            src_idx = match[it_outer->first];
		}
		
		// Get the dest_idx
		for (map<int, Edge*>::iterator it_inner = it_outer->second.begin(); it_inner != it_outer->second.end(); ++it_inner) {
			it_match = match.find(it_inner->first);
			if (it_match != match.end()) {
                dest_idx = match[it_inner->first];
			}
			
			// construct the element in the adj_matrix
			if (src_idx != -1 && dest_idx != -1) {
				adj_matrix[src_idx][dest_idx] = it_inner->second;

                // set the weight of each edge
                adj_matrix[src_idx][dest_idx]->setWeight(getWeight(airports[src_idx], airports[dest_idx]));
			}
		}
	}
}

double Graph::getWeight(Vertex src, Vertex dest){

    //using Haversine formula to calculate the distance between 2 points on round object(Earth)
    double distance = 0;
    double lat_src = src.getLatitude();
    double lon_src = src.getLongitude(); 
    double lat_dest = dest.getLatitude();
    double lon_dest = dest.getLongitude();
    
    double R = 6371000; //  average radius of Earth in meters
    double Pi = 3.1415926; //Pi number

    //convert to radian
    double rad_lat_src = lat_src * (Pi/180);
    double rad_lat_dest = lat_dest * (Pi/180);

    //Apply the formula
    double delta_phi = (lat_dest - lat_src) * (Pi/180);
    double delta_lambda = (lon_dest - lon_src) * (Pi/180);

    double temp1 = ( sin(delta_phi/2)*sin(delta_phi/2) ) + cos(rad_lat_src) * cos(rad_lat_dest) * (sin(delta_lambda/2) * sin(delta_lambda/2));
    double temp2 = 2 * atan2(sqrt(temp1), sqrt((1-temp1)));
    distance = R * temp2;
    return distance;
}

vector<int> Graph::BFS(int src_id){
    //there are 7698 vertices, initialized to be false
    vector<bool> visited(7698,false); //the visited vector should look like airports vector

    //initialize variables for BFS
    queue<int> q;
    vector<int> ans;
    //push the initial vertex's id in and mark as true
    int idx = match[src_id]; //find the index of the src_id in adj_matrix
    visited[idx] = true; //set the initial position to true
    q.push(idx); 
    ans.push_back(airports[idx].getID());
    int vis = 0; //vis will hold the id of the vertex
    while(!q.empty()){
        vis = q.front();
        for(unsigned i =0; i < visited.size(); i++){
            //Binh: I am asumming here that if the Edge do not exist, it is NULL, if it is, there is an Edge
            //do we have a default value for a not connected vertex, or is it just NULL?
            if(adj_matrix[vis][i] != NULL && (!visited[i])){
                //Push the node into the queue
                q.push(i);
                ans.push_back(airports[i].getID());
                //Set to true when visited
                visited[i] = true;
            }
        }
        q.pop();
    }
    return ans;
}

int Graph::minimumDistance(vector<int> distances, vector<bool> visited) {
    int min = INT_MAX, min_index;

    for (int i = 0; i < this->adj_matrix.size(); i++) {
        if (visited[this->match[i]] == false && distances[i] <= min) {
            min = distances[this->match[i]], min_index = i;
        }
    }
    return min_index;
}

double Graph::sumDistances(vector<int> distances) {
    double sum = 0.0;
    for (int i = 0; i < distances.size(); i++) {
        sum += distances[this->match[i]];
    }
    return sum;
}

vector<int> Graph::shortestPath(int id1, int id2){
    vector<int> distances;
    vector<bool> visited;
    vector<int> paths;
    paths.push_back(id1);

    for (int i = 0; i < this->adj_matrix.size(); i++) {
        distances.push_back(INT_MAX);
        visited.push_back(false);
    }

    //index of the source id
    distances[this->match[id1]] = 0;
    bool destNotFoundYet = true;
    for (int i = 0; i < this->adj_matrix.size(); i++) {
        int min = minimumDistance(distances, visited);
        visited[min] = true;
        if (destNotFoundYet) {
            for (int j = 0; j < this->adj_matrix.size() - 1; j++) {

                if (this->adj_matrix[min][j] != NULL && destNotFoundYet == true) {
                    if (this->adj_matrix[min][j]->getDest() != id2) {
                        if (!visited[j]  && distances[min] != INT_MAX 
                                && distances[min] + this->adj_matrix[min][j]->getEdgeWeight() < distances[j]) {

                       
                            distances[j] = distances[min] + this->adj_matrix[min][j]->getEdgeWeight(); 
                        }
                    } else {
                        if (i != j && this->adj_matrix[min][j] != NULL) {
                            int dest = this->adj_matrix[min][j]->getDest();
                            paths.push_back(dest);
                        }
                        destNotFoundYet = false;
                    }
                }
            }
        } else {
            break;
        }
    }
    return paths;

} 


/* return the vector of IDs of vertices with highest importance */
vector<int> Graph::pageRank(){
    // indices of vertices, with highest importance, in airports vector
    vector<int> indices_result;
    int max_num_edges = 0;

    // for every destination vertex
    for (unsigned j = 0; j < adj_matrix.size(); ++j) {
        int num_incident_edges = 0;

        // check every source vertex
        for (unsigned i = 0; i < adj_matrix.size(); ++i) {
            // if the edge exists
            if (adj_matrix[i][j] != NULL) {
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
        result.push_back(airports[idx].getID());
    }

    return result;
}