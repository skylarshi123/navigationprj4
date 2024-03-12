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
        
        m_segments[start].push_back(segments(startPoint, endPoint, nameOfStreet));
        m_segments[end].push_back(segments(endPoint, startPoint, nameOfStreet));
        
        //check to see if there are points of interest near geopoints
        //I need to be able to get the point of interest name and geopoint
        int numPointOfInterest;
        infile >> numPointOfInterest;
        infile.ignore(10000, '\n');
        if(numPointOfInterest != 0){
            GeoPoint midPoint = midpoint(startPoint, endPoint);
            string midPointName = midPoint.to_string();
            m_segments[midPointName].push_back(segments(midPoint, startPoint, nameOfStreet));
            m_segments[start].push_back(segments(startPoint, midPoint, nameOfStreet));
            m_segments[end].push_back(segments(endPoint, midPoint, nameOfStreet));
            m_segments[midPointName].push_back(segments(midPoint, endPoint, nameOfStreet));
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
                m_segments[midPointName].push_back(segments(midPoint, geopointAttraction, "a path"));
                m_segments[stringGeoPointAttraction].push_back(segments(geopointAttraction, midPoint, "a path"));
            }
        }
    }
    return true;
}
