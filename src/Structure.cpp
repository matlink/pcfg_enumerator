#include "Structure.hpp"

Structure::Structure(const std::string &word){
	Simple base;
	for(unsigned short i=0; i < word.length(); i++){
		if 		(word[i] >= 'a' && word[i] <= 'z')	base.type = 'L';
		else if (word[i] >= 'A' && word[i] <= 'Z') 	base.type = 'L';
		else if (word[i] >= '0' && word[i] <= '9') 	base.type = 'D';
		else					  					base.type = 'S';
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
	for(Simple i : s){
		os << i.type << " " << i.len << " ";
	}
	return os;
}

std::ifstream& operator>>(std::ifstream& ifs, Structure& s){
	uint size;
	ifs >> size;
	while(size--){
		Simple b;
		ifs >> b.type;
		ifs >> b.len;
		s.push_back(b);
	}
	return ifs;
}

// equality operators to store custom types in hashmaps.
bool Structure::operator==(const Structure &lhs) const {
	if (lhs.size() != size()) return false;
	for(uint i=0; i < lhs.size(); i++){
		if(lhs[i] != (*this)[i]) return false;
	}
	return true;
}

bool Structure::operator!=(const Structure &lhs) const {
	return !(lhs == (*this));
}