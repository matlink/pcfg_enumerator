#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>
#include <ostream>
#include <fstream>
#include <string>

#include "base.hpp"

// i.e. L8D4S2, ...
class Structure: public std::vector<Base> {
public:
	Structure(){};
	Structure(const std::string &word);
	friend std::ostream& operator<<(std::ostream& os, const Structure& s);
	friend std::ifstream& operator>>(std::ifstream& ifs, Structure& s);
	bool operator==(const Structure &lhs);
	bool operator!=(const Structure &lhs);
};


// Hash functions to store custom types in hashmaps.
namespace std {
	template<>
	struct hash<Structure> : public unary_function<Structure, size_t> {
		size_t operator()(const Structure& s) const {
			size_t total = 0;
			unsigned short shift = 0;
			for(const Base &b: s){
				total ^= (hash<Base>()(b) << shift++);
			}
			return total;
		}
	};
}

#endif