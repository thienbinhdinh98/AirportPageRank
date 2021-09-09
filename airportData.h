#pragma once
#include "edge.h"
#include "vertex.h"
#include <string>
#include <map>
#include <vector>

class airportData {
    public:
        /*
        * Takes in a string containing all the data in the airport data set and 
        * formats it in an easier way to use
        * @param fileData The string formed in the file_to_string function
        */
        std::map<int, std::map<int, Edge*> > parseRouteData(const std::string & filename);

        /*
        * Takes in a filename and returns a vector containing all of the vertices
        * which represent airports
        * @param filename The name of the file to be parsed
        */
        std::vector<Vertex> parseAirportData(const std::string &filename);

        /*
        * Takes in a vector of vertices and pairs the id to the index in the corresponding
        * vector
        * @param airports A vector of airport vertices
        */
        std::map<int, int> airportMatch(std::vector<Vertex> airports);
};
