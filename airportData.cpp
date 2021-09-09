#include "airportData.h"
#include "edge.h"
#include "vertex.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

std::map<int, std::map<int, Edge*> > airportData::parseRouteData(const std::string & filename) {
	//TODO
	std::map<int, std::map<int, Edge*> > result;
	std::ifstream myfile(filename);

	if (myfile.good()) {
		std::string line;
		while(std::getline(myfile, line)) {
			std::stringstream ss(line);
			std::string substr;
			std::vector<std::string> line_vec;
			
			while(ss.good()) {
				std::getline(ss, substr, ',');
				line_vec.push_back(substr);
			}
			
			// std::stringstream ss_0(line_vec[0]);
			// int src_id = 0;
			// ss_0 >> src_id;
			int src_id = std::atoi(line_vec[0].c_str());
			int dest_id = std::atoi(line_vec[1].c_str());
			Edge* e = new Edge(src_id, dest_id);
			std::map<int, Edge*> innerMap;
			innerMap[dest_id] = e;
			if (result.find(src_id) == result.end()) {
				result[src_id] = innerMap;
			} else {
				result[src_id][dest_id] = e;
			}
		}
		
	}
	return result;
}


std::vector<Vertex> airportData::parseAirportData(const std::string &filename) {
	std::vector<Vertex> out;
	std::ifstream myfile(filename);

	if (myfile.good()) {
		std::string line;
		while(std::getline(myfile, line)) {
			std::stringstream ss(line);
			std::string substr;
			std::vector<std::string> line_vec;
			
			while(ss.good()) {
				std::getline(ss, substr, ',');
				line_vec.push_back(substr);
			}
			
			//latitude and longitude at indexes 6 and 7 respectively
			double latitude = std::atof(line_vec[6].c_str());

			double longitude = std::atof(line_vec[7].c_str());

			//airport id at index 0
			
			int airportID = std::atoi(line_vec[0].c_str());
				
			//IATA code at index 4
			// int IATAcode = std::atoi(line_vec[4].c_str());
			std::string IATAcode = line_vec[4];
			//ICAO code at index 5
			// int ICAOcode = std::atoi(line_vec[5].c_str());
			std::string ICAOcode = line_vec[5];
			//name at index 1
			// std::string name = std::atoi(line_vec[1].c_str());
			std::string name = line_vec[1];
			Vertex v(airportID, name, latitude, longitude, IATAcode, ICAOcode);
			//push vertex to out vector
			out.push_back(v);
		}
	}
	return out;
}

std::map<int, int> airportData::airportMatch(std::vector<Vertex> airports) {
	//id -> index in vector
	std::map<int, int> out;	

	for (unsigned i = 0; i < airports.size(); i++) {
		out[airports[i].getID()] = i;
	}

	return out;
}