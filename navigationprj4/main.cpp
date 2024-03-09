#include "HashMap.h" // Assuming the header file name is HashMap.h
#include <iostream>
#include <string>

int main() {
    HashMap<int> map(0.75); // Create a HashMap instance for storing int values
    
    // Insert some key-value pairs
    map.insert("one", 1);
    map.insert("two", 2);
    map.insert("three", 3);
    map.insert("four", 4);

    // Attempt to retrieve and print some values
//    const int* one = map.find("one");
//    if (one != nullptr) {
//        std::cout << "one = " << *one << std::endl;
//    }
//
//    const int* three = map.find("three");
//    if (three != nullptr) {
//        std::cout << "three = " << *three << std::endl;
//    }

    // Demonstrate rehashing by adding more elements
    std::cout << "Current size before rehashing: " << map.size() << std::endl;
    for (int i = 5; i <= 20; ++i) {
        map.insert("key" + std::to_string(i), i);
    }
    std::cout << "Current size after rehashing: " << map.size() << std::endl;

    // Try to find a value that does not exist
//    const int* missing = map.find("missing");
//    if (missing == nullptr) {
//        std::cout << "missing = not found" << std::endl;
//    }

    return 0;
}
