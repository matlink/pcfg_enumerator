#ifndef RULE_H
#define RULE_H

#include <utility>
#include <ostream>
#include <fstream>

#include "Simple.hpp"

// i.e. L8 -> password, ...
class Rule {
public:
	Simple base;
	std::string terminal;

	Rule() = default;
	Rule(const Simple &b, const std::string &t);

	friend std::ostream& operator<<(std::ostream& os, const Rule& r);
	friend std::ifstream& operator>>(std::ifstream& ifs, Rule& r);
	bool operator==(const Rule &lhs) const ;
	bool operator!=(const Rule &lhs) const ;
};


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