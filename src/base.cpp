#include "base.hpp"

std::ostream& operator<<(std::ostream& os, const Base& b){
	os << b.type << " " << b.len;
	return os;
}

std::ifstream& operator>>(std::ifstream& ifs, Base& b){
	ifs >> b.type >> b.len;
	return ifs;
}

bool operator==(const Base &lhs, const Base &rhs){
	return lhs.type == rhs.type && lhs.len == rhs.len;
}

bool operator!=(const Base &lhs, const Base &rhs){
	return lhs.type != rhs.type || lhs.len != rhs.len;
}

Base::Base(char type, unsigned int len) : type(type), len(len){}