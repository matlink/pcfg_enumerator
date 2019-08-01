#ifndef RULE_H
#define RULE_H

#include <utility>
#include <ostream>
#include <fstream>

#include "base.hpp"

// i.e. L8 -> password, ...
class Rule: public std::pair<Base, std::string> {
public:
	Base base = first;
	std::string terminal = second;

	Rule(){};
	Rule(const Base &b, const std::string &t);
};

inline std::ostream& operator<<(std::ostream& os, const Rule& r){
	os << r.base << "->" << r.terminal;
	return os;
}
inline std::ifstream& operator>>(std::ifstream& ifs, Rule& r){
	std::string line;
	ifs >> line;
	Base b;
	b.type = line[0];
	unsigned int lptr = 1;
	while(line[lptr] <= '9' && line[lptr] >= '0'){
		lptr++;
	}
	b.len = std::stoi(line.substr(1,lptr-1));
	r.base = b;
	r.terminal = line.substr(lptr+2);
	return ifs;
}
inline bool operator==(const Rule &lhs, const Rule &rhs){
	return lhs.base == rhs.base && lhs.terminal == rhs.terminal;
}
inline bool operator!=(const Rule &lhs, const Rule &rhs){
	return !(lhs == rhs);
}


// Hash functions to store custom types in hashmaps.
namespace std {
	template<>
	struct hash<Rule> : public unary_function<Rule, size_t> {
		size_t operator()(const Rule& r) const {
			return (hash<char>()(r.base.type)
				^ (hash<int>()(r.base.len)<<1) >> 1)
				^ (hash<string>()(r.terminal) << 1);
		}
	};
}

#endif