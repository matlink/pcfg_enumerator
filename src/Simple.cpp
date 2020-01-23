#include "Simple.hpp"

std::ostream& operator<<(std::ostream& os, const Simple& b){
	os << b.type << " " << b.len;
	return os;
}

std::ifstream& operator>>(std::ifstream& ifs, Simple& b){
	ifs >> b.type >> b.len;
	return ifs;
}

bool operator==(const Simple &lhs, const Simple &rhs){
	return lhs.type == rhs.type && lhs.len == rhs.len;
}

bool operator!=(const Simple &lhs, const Simple &rhs){
	return lhs.type != rhs.type || lhs.len != rhs.len;
}

Simple::Simple(const char& type, const uint& len) : type(type), len(len){}