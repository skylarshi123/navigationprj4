//#include <cstdio>
//#include <iomanip>
//#include <iostream>
//#include <map>
//#include <vector>
//#include "HashMap.h"
//
////#include "geodb.h"
////#include "router.h"
//#include "stops.h"
//#include "tourcmd.h"
//#include "geodb.h"
////#include "tour_generator.h"
//
//using namespace std;

//void print_tour(vector<TourCommand>& tcs)
//{
//    double total_dist = 0;
//    std::string direction;
//    double street_distance = 0;
//
//    cout << "Starting tour...\n";
//
//    for (size_t i = 0; i < tcs.size(); ++i)
//    {
//        if (tcs[i].get_command_type() == TourCommand::commentary)
//        {
//            cout << "Welcome to " << tcs[i].get_poi() << "!\n";
//            cout << tcs[i].get_commentary() << "\n";
//        }
//        else if (tcs[i].get_command_type() == TourCommand::turn)
//        {
//            cout << "Take a " << tcs[i].get_direction() << " turn on " << tcs[i].get_street() << endl;
//        }
//        else if (tcs[i].get_command_type() == TourCommand::proceed)
//        {
//            total_dist += tcs[i].get_distance();
//            if (direction.empty())
//                direction = tcs[i].get_direction();
//            street_distance += tcs[i].get_distance();
//            if (i+1 < tcs.size() && tcs[i+1].get_command_type() == TourCommand::proceed
//                && tcs[i+1].get_street() == tcs[i].get_street() && tcs[i].get_street() != "a path")
//            {
//                continue;
//            }
//
//            cout << "Proceed " << std::fixed << std::setprecision(3) << street_distance << " miles " << direction << " on " << tcs[i].get_street() << endl;
//            street_distance = 0;
//            direction.clear();
//        }
//    }
//
//    cout << "Your tour has finished!\n";
//    cout << "Total tour distance: " << std::fixed << std::setprecision(3) << total_dist << " miles\n";
//}

//int main(int argc, char *argv[])
//{
//    if (argc != 3)
//    {
//        cout << "usage: BruinTour mapdata.txt stops.txt\n";
//        return 1;
//    }
//
//    GeoDatabase geodb;
//    if (!geodb.load(argv[1]))
//    {
//        cout << "Unable to load map data: " << argv[1] << endl;
//        return 1;
//    }
//
//    Router router(geodb);
//    TourGenerator tg(geodb, router);
//
//    Stops stops;
//    if (!stops.load(argv[2]))
//    {
//        cout << "Unable to load tour data: " << argv[2] << endl;
//        return 1;
//    }
//
//    std::cout << "Routing...\n\n";
//
//    vector<TourCommand> tcs = tg.generate_tour(stops);
//    if (tcs.empty())
//        cout << "Unable to generate tour!\n";
//    else
//        print_tour(tcs);
//}


//int main() {
//    GeoDatabase g;
//
//    string lat = "34.0419265";
//    string long1 = "-118.5010322";
//    GeoPoint p1 = GeoPoint(lat, long1);
//    string p = p1.to_string();
//
//    vector<GeoPoint> points = g.get_connected_points(p1);
//
//    for (auto it : points)
//    {
//        cout << it.to_string() << endl; //should print geopoint
//    }
//
//    //test POI
//    std::string poi = "Thalians Mental Health Center";
//    GeoPoint point;
//    if (g.get_poi_location(poi, point)) {
//        std::cout << "Location of " << poi << ": " << point.to_string() << std::endl;
//    }
//
//    //test street
//    GeoPoint g1 = GeoPoint("34.0753246", "-118.3816632");
//    GeoPoint g2 = GeoPoint("34.0752704", "-118.3832229");
//    string t = g.get_street_name(g1, g1);
//
//    cout << t << endl;
//    
//
//
//    return 0;
//}

#include "router.h"
#include "geodb.h"
#include "geopoint.h"

#include <vector>
#include <iostream>

using namespace std;

int main() {
    GeoDatabase db;
    db.load("/Users/skylarshi/Desktop/navigationprj4/navigationprj4/mapdata.txt");
    Router router(db);
    GeoPoint pt1;
    GeoPoint pt2;
    db.get_poi_location("Diddy Riese", pt1);
    db.get_poi_location("Ami Sushi", pt2);
    vector<GeoPoint> route = router.route(pt1, pt2);

    for(const auto& point : route) {
        cerr << point.to_string() << endl;
    }

}
