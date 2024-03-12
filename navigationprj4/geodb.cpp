//
//  geodb.cpp
//  navigationprj4
//
//  Created by Skylar Shi on 3/9/24.
//

#include "geodb.h"
#include "geopoint.h"
#include "geotools.h"
#include "HashMap.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

GeoDatabase::GeoDatabase(){
    
}

GeoDatabase::~GeoDatabase(){
}

bool GeoDatabase::load(const string& map_data_file){
    ifstream infile(map_data_file);
    if ( !infile )
    {
        cerr << "Error: Cannot open data.txt!" <<endl;
        return false;
    }
    string nameOfStreet;
    while(getline(infile, nameOfStreet)){
        string latitudeStart;
        string longitudeStart;
        string latitudeEnd;
        string longitudeEnd;
        infile >> latitudeStart >> longitudeStart >> latitudeEnd >> longitudeEnd;
        infile.ignore(10000, '\n');
        GeoPoint startPoint(latitudeStart, longitudeStart);
        GeoPoint endPoint(latitudeEnd, longitudeEnd);
        
        const string start =  startPoint.to_string();
        const string end = endPoint.to_string();
        //connecting all the starting and ending of the segments to each other
        m_connected[start].push_back(endPoint);
        m_connected[end].push_back(startPoint);
        //now add the street name
        m_streets[start+end] = nameOfStreet;
        
        //check to see if there are points of interest near geopoints
        //I need to be able to get the point of interest name and geopoint
        int numPointOfInterest;
        infile >> numPointOfInterest;
        infile.ignore(10000, '\n');
        if(numPointOfInterest != 0){
            GeoPoint midPoint = midpoint(startPoint, endPoint);
            string midPointName = midPoint.to_string();
            //connecting the starting and ending of the segments to the midpoint
            m_connected[start].push_back(midPoint);
            m_connected[end].push_back(midPoint);
            m_connected[midPointName].push_back(startPoint);
            m_connected[midPointName].push_back(endPoint);
            //note since we are concatenating, we have to search both directions to return the street name
            m_streets[start+midPointName] = nameOfStreet;
            m_streets[end+midPointName] = nameOfStreet;
            for (int i = 0; i<numPointOfInterest; i++){
                string pointOfInterestLine;
                getline(infile, pointOfInterestLine);
                size_t index = pointOfInterestLine.find('|');
                //get the name of the attraction
                string attractionName = pointOfInterestLine.substr(0, index);
                //get the geopoint
                string attractionGeoPoint = pointOfInterestLine.substr(index+1);
                size_t indexOfSpace = attractionGeoPoint.find(' ');
                string attractionLatitude = attractionGeoPoint.substr(0, indexOfSpace);
                string attractionLongitude = attractionGeoPoint.substr(indexOfSpace+1);
                GeoPoint geopointAttraction(attractionLatitude, attractionLongitude);
                string stringGeoPointAttraction = geopointAttraction.to_string();
                //add to hashmap
                m_connected[midPointName].push_back(geopointAttraction);
                m_connected[stringGeoPointAttraction].push_back(midPoint);
                m_pointsOfInterest[attractionName] = geopointAttraction;
                m_streets[midPointName+stringGeoPointAttraction] = "a path";
            }
        }
    }
    return true;
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const {
    const GeoPoint* pointOfInterest = m_pointsOfInterest.find(poi); //from the string it will get the value in the hashmap and store it in pointOfInterest (remember find returns the pointer to the found thing)
    if(pointOfInterest == nullptr) return false;
    else {
        point = *pointOfInterest; //dereference the pointer to return the actual geopoint
        return true;
    }
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint &pt) const {
    vector<GeoPoint> emptyVector; //in the case we find that none are connected, and thus returns a nullptr
    const vector<GeoPoint>* connectedPoints = m_connected.find(pt.to_string()); //because find will return a pointer to a vector
    if(connectedPoints == nullptr) return emptyVector;
    else return (*connectedPoints); //we want to return the vector, not the pointer to the vector
}

std::string GeoDatabase::get_street_name(const GeoPoint &pt1, const GeoPoint &pt2) const {
    string pointConcatenation = pt1.to_string() + pt2.to_string();
    const string* pointerStreetName = m_streets.find(pointConcatenation);
    if (pointerStreetName != nullptr) {
        return *pointerStreetName;
    }
    
    string pointConcatenation1 = pt2.to_string() + pt1.to_string();
    pointerStreetName = m_streets.find(pointConcatenation1);
    if (pointerStreetName != nullptr) {
        return *pointerStreetName;
    }
    
    return "";
}
