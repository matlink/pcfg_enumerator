#include <fstream>
#include <iostream>
#include "pcfg.hpp"

std::ostream& operator<<(std::ostream& os, const Base& b){
	os << b.first << b.second;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Structure& s){
	std::vector<Base>::const_iterator it = s.begin();
	for(; it != s.end(); it++){
		os << (*it).first << (*it).second;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const Rule& r){
	os << r.first << "->" << r.second;
	return os;
}

const Structure Pcfg::parse(const std::string &word) const{
	Structure structure;
	char c;
	Base base;
	for(unsigned short i=0; i < word.length(); i++){
		c = word[i];
		if 		(c >= 'a' && c <= 'z') 	base.first = 'L';
		else if (c >= 'A' && c <= 'Z') 	base.first = 'L';
		else if (c >= '0' && c <= '9') 	base.first = 'D';
		else					  		base.first = 'S';
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

const void Pcfg::learn(const std::string &filename){
	std::ifstream learnstream(filename);
	std::string word;
	Structure structure;
	int nb_structures = 0;
	std::unordered_map<Base, int> nb_bases;
	while (learnstream >> word){
		structure = parse(word);
		structprobs[structure]++;
		nb_structures++;
		int w_ptr = 0;
		int base_len;
		std::string terminal;
		for(Base base: structure){
			base_len = base.second;
			terminal = word.substr(w_ptr, base_len);
			w_ptr += base_len;
			ruleprobs[Rule(base,terminal)] += 1;
			std::unordered_map<Base, int>::const_iterator search = nb_bases.find(base);
			if(search == nb_bases.end()){
				nb_bases[base] = 0;
			}
			nb_bases[base]++;
		}
	}
	learnstream.close();
	// compute probabilities
	for(auto &sprob: structprobs){
		sprob.second /= nb_structures;
	}
	for(auto &rprob: ruleprobs){
		Base b = rprob.first.first;
		rprob.second /= nb_bases[b];
	}
	// std::unordered_map<Structure, double>::iterator it = structprobs.begin();
	// while (it != structprobs.end()){
	// 	std::cout << it->first << " " << it->second << std::endl;
	// 	it++;
	// }
	// std::unordered_map<Rule, double>::iterator it2 = ruleprobs.begin();
	// while (it2 != ruleprobs.end()){
	// 	std::cout << it2->first << " " << it2->second << std::endl;
	// 	it2++;
	// }
}	