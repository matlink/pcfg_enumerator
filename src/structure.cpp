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