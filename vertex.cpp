#include "vertex.h"

Vertex::Vertex(){
    id_ = -1; //This airport does not connect to any, default -1
    name_ = "";
    latitude_ = 0;
    longtitude_ = 0;
    IATA_code_ = "";
    ICAO_code_ = "";
}

Vertex::Vertex(int id, string name, double latitude, double longtitude, string IATA_code, string ICAO_code){
    id_ = id; //This airport does not connect to any, default -1
    name_ = name;
    latitude_ = latitude;
    longtitude_ = longtitude;
    IATA_code_ = IATA_code;
    ICAO_code_ = ICAO_code;
}

bool Vertex::operator==(const Vertex& other){
    if(this->id_ == other.id_){
        return true;
    }
    return false;
}

bool Vertex::operator!=(const Vertex& rhs ){
    if(this->id_ == rhs.id_){
        return false;
    }
    return true;
}

string Vertex::getName(){
    return name_;
}

int Vertex::getID(){
    return id_;
}

string Vertex::getIATA(){
    return IATA_code_;
}

string Vertex::getICAO(){
    return ICAO_code_;
}

float Vertex::getLatitude(){
    return latitude_;
}

float Vertex::getLongitude(){
    return longtitude_;
}     