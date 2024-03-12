//
//  router.hpp
//  navigationprj4
//
//  Created by Skylar Shi on 3/11/24.
//

#ifndef router_hpp
#define router_hpp

class Router: public RouterBase
{
public:
 Router(const GeoDatabaseBase& geo_db);
 virtual ~Router();
 virtual std::vector<GeoPoint> route(const GeoPoint& pt1,
 const GeoPoint& pt2) const;
};
#endif /* router_hpp */
