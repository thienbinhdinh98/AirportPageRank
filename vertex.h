#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using std::string;

class Vertex {
    public:
        /**
         * Default constructor
         */ 
        Vertex();

        /**
         * Construct new vertex
         * @param id airport id
         * @param name airport name
         * @param latitude latitude of the airport
         * @param longtitude longtitude of the airport
         * @param IATA_code IATA code of the airport
         * @param ICAO_code ICAO code of the airport, maybe BLANK if airport does not have this code
         */ 
        Vertex(int id, string name, double latitude, double longtitude, string IATA_code, string ICAO_code);

        /**
         * Operator = (equal) to see if 2 vertex are the same
         * @param other other to Vertex object to compare with
         * @return true if two vertices are equal, else false
         */ 
        bool operator==(const Vertex& other);

        /**
         * Operator != (not equal) to see if 2 vertex are the same or not
         * @param lhs left hand side object to be compared
         * @param rhs right hand side object to be compared
         * @return true if two vertices are NOT equal, else false
         */ 
        bool operator!=(const Vertex& rhs);

        /**
         * get Name
         * @return airport name
         */ 
        string getName();

        /**
         * get airport ID
         * @return airport id
         */ 
        int getID();

        /**
         * get airport IATA code
         * @return airport IATA code 
         */ 
        string getIATA();

        /**
         * get airport ICAO
         * @return airport ICAO
         */ 
        string getICAO();

        /**
         * get airport latituide
         * @return airport latitude
         */ 
        float getLatitude();

        /**
         * get airport longtitude
         * @return airport longtitude
         */ 
        float getLongitude();
        
       
    private:
        int id_;
        string name_;
        double latitude_;
        double longtitude_;
        string IATA_code_;
        string ICAO_code_;
        
};