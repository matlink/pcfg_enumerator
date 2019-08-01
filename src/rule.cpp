#include "rule.hpp"

Rule::Rule(const Base &b, const std::string &t){
	base = b;
	terminal = t;
}

std::ostream& operator<<(std::ostream& os, const Rule& r){
	os << r.base << "->" << r.terminal;
	return os;
}

std::ifstream& operator>>(std::ifstream& ifs, Rule& r){
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

bool Rule::operator==(const Rule &lhs){
	return lhs.base == base && lhs.terminal == terminal;
}

bool Rule::operator!=(const Rule &lhs){
	return !(lhs == (*this));
}