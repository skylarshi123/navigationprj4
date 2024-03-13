//
//  tour_generator.hpp
//  navigationprj4
//
//  Created by Skylar Shi on 3/13/24.
//

#ifndef tour_generator_hpp
#define tour_generator_hpp
#include "base_classes.h"
#include "geodb.h"

class TourGenerator: public TourGeneratorBase
{
public:
 TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
 virtual ~TourGenerator();
 virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
private:
    const GeoDatabaseBase* m_geodatabase;
    const RouterBase* m_routerbase;
};

#endif /* tour_generator_hpp */
