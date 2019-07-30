#include <fstream>
#include <iostream>
#include "pcfg.hpp"

std::ostream& operator<<(std::ostream& os, const Structure& s){
	std::vector<Base>::const_iterator it = s.begin();
	for(; it != s.end(); it++){
		std::cout << (*it).first << (*it).second;
	}
	return os;
}

Structure Pcfg::parse(std::string word){
	Structure structure;
	char c;
	Base base;
	for(int i=0; i < word.length(); i++){
		c = word[i];
		if (c >= 'a' && c <= 'z') base.first = 'L';
		if (c >= 'A' && c <= 'Z') base.first = 'L';
		if (c >= '0' && c <= '9') base.first = 'D';
		else					  base.first = 'S';
		if (structure.size() == 0){
			base.second = 1;
			structure.push_back(base);
			continue;
		}
		if (base.first == structure.back().first){
			structure.back().second++;
			continue;
		}
		base.second = 1;
		structure.push_back(base);
	}
	return structure;
}

void Pcfg::learn(std::string filename){
	std::ifstream learnstream(filename);
	std::string word;
	Structure structure;
	while (learnstream >> word){
		structure = parse(word);
		structprobs[structure]++;
	}
	learnstream.close();
	std::unordered_map<Structure, double>::iterator it = structprobs.begin();
	while (it != structprobs.end()){
		std::cout << it->first << " " << it->second << std::endl;
		it++;
	}
}	