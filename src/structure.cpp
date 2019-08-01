#include "structure.hpp"

Structure::Structure(const std::string &word){
	char c;
	Base base;
	for(unsigned short i=0; i < word.length(); i++){
		c = word[i];
		if 		(c >= 'a' && c <= 'z')	base.type = 'L';
		else if (c >= 'A' && c <= 'Z') 	base.type = 'L';
		else if (c >= '0' && c <= '9') 	base.type = 'D';
		else					  		base.type = 'S';
		if (size() && base.type == back().type){
			back().len++;
			continue;
		}
		base.len = 1;
		push_back(base);
	}
}

std::ostream& operator<<(std::ostream& os, const Structure& s){
	os << s.size() << " ";
	std::vector<Base>::const_iterator it = s.begin();
	for(; it != s.end(); it++){
		os << (*it).type << " " << (*it).len << " ";
	}
	return os;
}

std::ifstream& operator>>(std::ifstream& ifs, Structure& s){
	unsigned int size;
	ifs >> size;
	while(size--){
		Base b;
		ifs >> b.type;
		ifs >> b.len;
		s.push_back(b);
	}
	return ifs;
}

// equality operators to store custom types in hashmaps.
bool Structure::operator==(const Structure &lhs){
	if (lhs.size() != size()) return false;
	for(unsigned int i=0; i < lhs.size(); i++){
		if(lhs[i] != (*this)[i]) return false;
	}
	return true;
}

bool Structure::operator!=(const Structure &lhs){
	return !(lhs == (*this));
}