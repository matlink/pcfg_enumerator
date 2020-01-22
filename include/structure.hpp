#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>
#include <ostream>
#include <fstream>
#include <string>

#include "simple.hpp"

// i.e. L8D4S2, ...
class Structure: public std::vector<Simple> {
public:
	Structure() = default;
	Structure(const std::string &word);
	friend std::ostream& operator<<(std::ostream& os, const Structure& s);
	friend std::ifstream& operator>>(std::ifstream& ifs, Structure& s);
	bool operator==(const Structure &lhs) const;
	bool operator!=(const Structure &lhs) const;
};


// Hash functions to store custom types in hashmaps.
namespace std {
	template<>
	struct hash<Structure> : public unary_function<Structure, size_t> {
		size_t operator()(const Structure& s) const {
			size_t total = 0;
			unsigned short shift = 0;
			for(const Simple &b: s){
				total ^= (hash<Simple>()(b) << shift++);
			}
			return total;
		}
	};
}

#endif