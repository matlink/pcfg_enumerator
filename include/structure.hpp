#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>
#include <ostream>
#include <fstream>

#include "base.hpp"

// i.e. L8D4S2, ...
class Structure: public std::vector<Base> {
public:
	Structure(){};
	Structure(const std::string &word);
};

inline std::ostream& operator<<(std::ostream& os, const Structure& s){
	std::vector<Base>::const_iterator it = s.begin();
	for(; it != s.end(); it++){
		os << (*it).type << (*it).len;
	}
	return os;
}

inline std::ifstream& operator>>(std::ifstream& ifs, Structure& s){
	std::string line;
	ifs >> line;
	unsigned int lptr = 0;
	while(lptr < line.length()){
		Base b;
		b.type = line[lptr++];
		unsigned int nptr = 0;
		while(line[lptr+nptr] <= '9' && line[lptr+nptr] >= '0' && lptr+nptr < line.length()){
			nptr++;
		}
		b.len = std::stoi(line.substr(lptr,nptr));
		lptr += nptr;
		s.push_back(b);
	}
	return ifs;
}

// equality operators to store custom types in hashmaps.
inline bool operator==(const Structure &lhs, const Structure &rhs){
	if (lhs.size() != rhs.size()) return false;
	for(unsigned int i=0; i < lhs.size(); i++){
		if(lhs[i] != rhs[i]) return false;
	}
	return true;
}
inline bool operator!=(const Structure &lhs, const Structure &rhs){
	return !(lhs == rhs);
}

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