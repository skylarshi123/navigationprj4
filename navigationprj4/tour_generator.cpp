//
//  tour_generator.cpp
//  navigationprj4
//
//  Created by Skylar Shi on 3/13/24.
//

#include "tour_generator.h"
#include "stops.h"
#include "tourcmd.h"
#include <vector>
#include "geotools.h"

using namespace std;

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router){
    m_geodatabase = &geodb;
    m_routerbase = &router;
}

TourGenerator::~TourGenerator(){}

std::vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const{
    vector<TourCommand> tour_commands;
    int numStops = stops.size();
    for(int i = 0; i < numStops; i++){
        string stopName;
        string stopDescription;
        //returns empty vector if can't find, while also getting the info bc its passed in by reference
        if(!stops.get_poi_data(i, stopName, stopDescription)) return {};
        TourCommand commentaryCmd;
        commentaryCmd.init_commentary(stopName, stopDescription);
        tour_commands.push_back(commentaryCmd);
        GeoPoint currentStopPoint;
        if(i < numStops - 1){
            if(!m_geodatabase->get_poi_location(stopName, currentStopPoint)) return {};
        }
        
        string nextStopName;
        string nextStopDescription;
        if(!stops.get_poi_data(i+1, nextStopName, nextStopDescription)) return {};
        GeoPoint nextStopPoint;
        if(!m_geodatabase->get_poi_location(nextStopName, nextStopPoint)) return {};
        vector<GeoPoint> route = m_routerbase->route(currentStopPoint, nextStopPoint);
        if(route.empty()) return {};
        
        for(int j = 0; j < route.size() - 1; j++){
            GeoPoint p1 = route[j];
            GeoPoint p2 = route[j+1];
            
            string streetName = m_geodatabase->get_street_name(p1, p2);
            double distance = distance_earth_miles(p1, p2);
            string direction;
            if(angle_of_line(p1,p2)<22.5) direction = "east";
            else if(angle_of_line(p1,p2)<67.5) direction = "northeast";
            else if(angle_of_line(p1,p2)<112.5) direction = "north";
            else if(angle_of_line(p1,p2)<157.5) direction = "northwest";
            else if(angle_of_line(p1,p2)<202.5) direction = "west";
            else if(angle_of_line(p1,p2)<247.5) direction = "southwest";
            else if(angle_of_line(p1,p2)<292.5) direction = "south";
            else if(angle_of_line(p1,p2)<337.5) direction = "southeast";
            else direction = "east";

            TourCommand proceedCmd;
            proceedCmd.init_proceed(direction, streetName, distance, p1, p2);
            tour_commands.push_back(proceedCmd);
            
            if(j < route.size()-2){
                GeoPoint p3 = route[j+2];
                string streetNameNext = m_geodatabase->get_street_name(p2, p3);
                double angle = angle_of_turn(p1, p2, p3);
                
                if(streetName != streetNameNext && angle != 0) {
                    string turnDirection;
                    if(angle >= 1 && angle < 180) turnDirection = "left";
                    else turnDirection = "right";
                    TourCommand turnCmd;
                    turnCmd.init_turn(turnDirection, streetNameNext);
                    tour_commands.push_back(turnCmd);
                }
            }
        }
    }
    return tour_commands;
}
