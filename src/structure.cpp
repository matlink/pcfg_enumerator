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
	std::vector<Base>::const_iterator it = s.begin();
	for(; it != s.end(); it++){
		os << (*it).type << (*it).len;
	}
	return os;
}

std::ifstream& operator>>(std::ifstream& ifs, Structure& s){
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