//
//  router.hpp
//  navigationprj4
//
//  Created by Skylar Shi on 3/11/24.
//
#include "geodb.h"
#include "base_classes.h"
#include "unordered_map"
#include <algorithm>
class Router: public RouterBase
{
public:
 Router(const GeoDatabaseBase& geo_db);
 virtual ~Router();
 virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
    const GeoDatabaseBase* geodatabase;
    struct CompareDistance {
        bool operator()(const std::pair<double, GeoPoint>& left, const std::pair<double, GeoPoint>& right) const {
            return left.first > right.first;
        }
    };
};

