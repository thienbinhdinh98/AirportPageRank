#include "edge.h"
#include <cmath>
#include <iostream>
#include <limits.h>
using namespace std;

Edge::Edge(int s, int d){
    source = s;
    destination = d;
    weight = INT_MAX;
}

int Edge::getSource(){
    return source;
}

int Edge::getDest(){
    return destination;
}

double Edge::calculateWeight(Vertex src, Vertex dest){

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

void Edge::setWeight(double w){
    weight = w;
}

double Edge::getEdgeWeight(){
    return weight;
}