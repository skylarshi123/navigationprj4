//
//  geodb.hpp
//  navigationprj4
//
//  Created by Skylar Shi on 3/9/24.
//

#ifndef geodb_hpp
#define geodb_hpp
#include "base_classes.h"
#include "HashMap.h"
#include <vector>
class GeoDatabase: public GeoDatabaseBase
{
public:
 GeoDatabase();
 virtual ~GeoDatabase();
 virtual bool load(const std::string& map_data_file);
 virtual bool get_poi_location(const std::string& poi,
 GeoPoint& point) const;
 virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt)
 const;
 virtual std::string get_street_name(const GeoPoint& pt1,
 const GeoPoint& pt2) const;
private:
    HashMap<GeoPoint> m_pointsOfInterest;
    HashMap<std::vector<GeoPoint>> m_connected;
    HashMap<std::string> m_streets;
};
#endif /* geodb_hpp */
