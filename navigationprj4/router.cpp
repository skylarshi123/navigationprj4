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
using namespace std;

Router::Router(const GeoDatabaseBase& geo_db){
    geodatabase =  &geo_db;
}

Router::~Router(){}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const{
    unordered_map<string, GeoPoint> visited;
    queue<GeoPoint> to_visit;
    vector<GeoPoint> route;
    visited[pt1.to_string()] = pt1;
    to_visit.push(pt1);
    while (!to_visit.empty()){
        GeoPoint cur_vertex = to_visit.front();
        to_visit.pop();
        //do something with the cur_vertext
        if(cur_vertex.to_string() == pt2.to_string()) break;
        vector<GeoPoint> adjacent_vertices =  geodatabase->get_connected_points(cur_vertex);
        for(const GeoPoint& target_vertex: adjacent_vertices){
            if(!visited.contains(target_vertex.to_string())){
                visited[target_vertex.to_string()] = cur_vertex;
                to_visit.push(target_vertex);
            }
        }
    }
    route.push_back(pt2);
    string current = pt2.to_string();
    while(current != pt1.to_string()){
        auto it = visited.find(current);
        route.push_back(it->second);
        current = (it->second.to_string());
    }
    reverse(route.begin(), route.end());
    return route;
}

