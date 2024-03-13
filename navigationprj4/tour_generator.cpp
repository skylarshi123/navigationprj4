//
//  tour_generator.cpp
//  navigationprj4
//
//  Created by Skylar Shi on 3/13/24.
//

#include "tour_generator.h"

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router){
    m_geodatabase = &geodb;
    m_routerbase = &router;
}

TourGenerator::~TourGenerator(){}

std::vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const{
    return std::vector<TourCommand>();
}
