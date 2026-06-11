#include <iostream>
#include <map>
#include <string>

int main() {
    // 1. Create a map: Key is int, Value is string
    std::map<int, std::string> error_map;

    // 2. Insert multiple DIFFERENT keys with the EXACT SAME value
    error_map[400] = "/generic_error.html";
    error_map[403] = "/generic_error.html";
    error_map[404] = "/generic_error.html";
    
    // Insert a different key with a different value
    error_map[500] = "/server_crash.html";

    // 3. Print the map to prove how it stores them
    std::cout << "Contents of the map (automatically sorted by key):" << std::endl;
    
    // C++98 iteration (no 'auto' allowed)
    for (std::map<int, std::string>::const_iterator it = error_map.begin(); 
         it != error_map.end(); 
         ++it) {
        std::cout << "Key: " << it->first 
                  << "  ->  Value: " << it->second << std::endl;
    }

    // 4. Prove that looking up a specific key works perfectly
    std::cout << "\nLooking up key 403..." << std::endl;
    std::map<int, std::string>::const_iterator search = error_map.find(403);
    
    if (search != error_map.end()) {
        std::cout << "Found it! The path is: " << search->second << std::endl;
    }

    return 0;
}