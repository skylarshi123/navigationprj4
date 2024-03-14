//
//  router.cpp
//  navigationprj4
//
//  Created by Skylar Shi on 3/11/24.
//

#include "router.h"
#include <unordered_map>
#include <queue>
#include <vector>
#include "geotools.h"
using namespace std;

Router::Router(const GeoDatabaseBase& geo_db){
    geodatabase =  &geo_db;
}

Router::~Router(){}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const{
    unordered_map<string, double> distance;
    unordered_map<string, GeoPoint> storedRoute;
    unordered_map<string, bool> isOptimizedVertex;
    priority_queue<pair<double, GeoPoint>, vector<pair<double, GeoPoint>>, CompareDistance> to_visit;
    distance[pt1.to_string()] = 0;
    to_visit.push(make_pair(0, pt1));
    while (!to_visit.empty()){
        GeoPoint cur_vertex = to_visit.top().second;
        to_visit.pop();
        string cur_vertex_string = cur_vertex.to_string();
        isOptimizedVertex[cur_vertex_string] = true;
        //do something with the cur_vertext, in this case before we pop it off, it would have been given the optimized distance
        if(cur_vertex.to_string() == pt2.to_string()) break;
        vector<GeoPoint> adjacent_vertices =  geodatabase->get_connected_points(cur_vertex);
        for(const GeoPoint& target_vertex: adjacent_vertices){
            string target_vertex_string = target_vertex.to_string();
            if(isOptimizedVertex[target_vertex_string]){
                continue;
            }
            if(!distance.count(target_vertex_string)) distance[target_vertex_string] = 99999999;
            double lengthOfEdge = distance_earth_miles(cur_vertex, target_vertex);
            double competingDistance = distance[cur_vertex_string]+lengthOfEdge;
            if(distance[target_vertex_string] > competingDistance){
                distance[target_vertex_string] = competingDistance;
                storedRoute[target_vertex_string] = cur_vertex;
                to_visit.push(make_pair(distance[target_vertex_string], target_vertex));
            }
        }
    }
    vector<GeoPoint> route;
    route.push_back(pt2);
    string current = pt2.to_string();

    while (current != pt1.to_string()) {
        auto it = storedRoute.find(current);
        if (it != storedRoute.end()) {
            route.push_back(it->second);
            current = it->second.to_string();
        } else {
            break;  // No path found
        }
    }

    reverse(route.begin(), route.end());
    return route;
}

