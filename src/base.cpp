#include "base.hpp"

std::ostream& operator<<(std::ostream& os, const Base& b){
	os << b.type << " " << b.len;
	return os;
}

std::ifstream& operator>>(std::ifstream& ifs, Base& b){
	ifs >> b.type >> b.len;
	return ifs;
}

bool Base::operator==(const Base &lhs){
	return lhs.type == type && lhs.len == len;
}

bool Base::operator!=(const Base &lhs){
	return !(lhs == (*this));
}

Base::Base(char type, unsigned int len){
	this->type = type;
	this->len = len;
}