#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include "HashMap.h"

//#include "geodb.h"
//#include "router.h"
#include "stops.h"
#include "tourcmd.h"
//#include "tour_generator.h"

using namespace std;

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

int main()
{
    HashMap<int> map(0.75); // Create a HashMap instance for storing int values

    // Insert some key-value pairs
    int n1 = 1, n2 = 2, n3 = 3, n4 = 4;
    map.insert("one", n1);
    map.insert("two", n2);
    map.insert("three", n3);
    map.insert("four", n4);
    std::cout << *map.find("one") << std::endl;
   // map.insert("one", 2); not update yet
    std::cout << *map.find("three") << std::endl;

    // // Attempt to retrieve and print some values
    // const int* one = map.find("one");
    // if (one != nullptr) {
    //     std::cout << "one = " << *one << std::endl;
    // }
    //
    // const int* three = map.find("three");
    // if (three != nullptr) {
    //     std::cout << "three = " << *three << std::endl;
    // }
    //
    // // Demonstrate rehashing by adding more elements
    // std::cout << "Current size before rehashing: " << map.size() << std::endl;
    // for (int i = 5; i <= 20; ++i) {
    //     map.insert("key" + std::to_string(i), i);
    // }
    // std::cout << "Current size after rehashing: " << map.size() << std::endl;
    //
    // // Try to find a value that does not exist
    // const int* missing = map.find("missing");
    // if (missing == nullptr) {
    //     std::cout << "missing = not found" << std::endl;
    // }


    return 0;
}
