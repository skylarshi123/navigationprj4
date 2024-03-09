//
//  HashMap.h
//  navigation
//
//  Created by Skylar Shi on 3/8/24.
//

#ifndef HashMap_h
#define HashMap_h
#include <vector>
#include <list>
#include <utility>
#include <string>
template <typename T>
class HashMap
{
public:
 HashMap(double max_load = 0.75); // constructor
 ~HashMap(); // destructor; deletes all of the items in the hashmap
 int size() const; // return the number of associations in the hashmap
 // The insert method associates one item (key) with another (value).
 // If no association currently exists with that key, this method inserts
 // a new association into the hashmap with that key/value pair. If there is
 // already an association with that key in the hashmap, then the item
 // associated with that key is replaced by the second parameter (value).
 // Thus, the hashmap must contain no duplicate keys.
 void insert(const std::string& key, const T& value);
 // Defines the bracket operator for HashMap, so you can use your map like this:
 // your_map["david"] = 2.99;
 // If the key does not exist in the hashmap, this will create a new entry in
 // the hashmap and map it to the default value of type T (0 for builtin types).
 // It returns a reference to the newly created value in the map.
 T& operator[](const std::string& key);
 // If no association exists with the given key, return nullptr; otherwise,
 // return a pointer to the value associated with that key. This pointer can be
 // used to examine that value within the map.
 const T* find(const std::string& key) const;
 // If no association exists with the given key, return nullptr; otherwise,
 // return a pointer to the value associated with that key. This pointer can be
 // used to examine that value or modify it directly within the map.
 T* find(const std::string& key) {
 const auto& hm = *this;
 return const_cast<T*>(hm.find(key));
 }
private:
    std::vector<std::list<std::pair<std::string, const T*>>> m_hashMap;
    int m_NumOfElements;
    int m_bucket;
    double m_max_load;
    int hashFunction(const std::string& key) const;
    void rehash();
};
template <typename T>
HashMap<T>::HashMap(double max_load){
    m_max_load = max_load;
    m_NumOfElements = 0;
    m_bucket = 10;
    m_hashMap.resize(10);
}
template <typename T>
int HashMap<T>::size() const{
    return m_NumOfElements;
}
template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value){
    m_NumOfElements++;
    if((double)m_NumOfElements/m_bucket > m_max_load){
        rehash();
    } //regular insertion
    //insert
    T* update = find(key);
    if(update != nullptr){
        *update = value;
        return;
    }
    int indexToInsert = hashFunction(key);
    m_hashMap[indexToInsert].push_back(std::make_pair(key, &value));
}

template <typename T>
void HashMap<T>::rehash(){
    m_bucket*=2;
    std::vector<std::list<std::pair<std::string, const T*>>> newHashMap;
    newHashMap.resize(m_bucket);
    
    for(auto it : m_hashMap)
    {
        for(auto p : it){
            //rehash string to get index
            int indexToInsert = hashFunction(p.first);
            newHashMap[indexToInsert].push_back(p);
        }
    }
    m_hashMap = newHashMap;
}

template <typename T>
int HashMap<T>::hashFunction(const std::string& key) const{
    size_t stringNumber = std::hash<std::string>()(key);
    int index = stringNumber % m_bucket;
    return index;
}

template <typename T>
HashMap<T>::~HashMap(){}

template <typename T>
const T* HashMap<T>::find(const std::string& key) const{
    int index = hashFunction(key);
    for( auto p : m_hashMap[index]){
        if (p.first == key) return p.second;
    }
    return nullptr;
}
#endif /* HashMap_h */
