#include "rule.hpp"

Rule::Rule(const Simple &b, const std::string &t){
	base = b;
	terminal = t;
}

std::ostream& operator<<(std::ostream& os, const Rule& r){
	os << r.base << " " << r.terminal;
	return os;
}

std::ifstream& operator>>(std::ifstream& ifs, Rule& r){
	ifs >> r.base;
	getline(ifs, r.terminal);
	return ifs;
}

bool Rule::operator==(const Rule &lhs) const {
	return lhs.base == base && lhs.terminal == terminal;
}

bool Rule::operator!=(const Rule &lhs) const {
	return !(lhs == (*this));
}