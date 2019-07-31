#include <fstream>
#include <iostream>
#include "pcfg.hpp"

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
}	

const void Pcfg::dump(const std::string &filename){
	std::ofstream dumpstream(filename);
	dumpstream << structprobs.size() << " " << ruleprobs.size() << std::endl;
	for(auto &sprob: structprobs){
		dumpstream << sprob.first << " " << sprob.second << std::endl;
	}
	for(auto &rprob: ruleprobs){
		dumpstream << rprob.first << " " << rprob.second << std::endl;
	}
	dumpstream.close();
}

const void Pcfg::load(const std::string &filename){
	std::ifstream dumpstream(filename);
	unsigned int nb_diff_structures;
	unsigned int nb_diff_terms;
	dumpstream >> nb_diff_structures >> nb_diff_terms;
	for(unsigned int i=0; i < nb_diff_structures; i++){
		Structure s;
		double prob;
		dumpstream >> s >> prob;
		structprobs[s] = prob;
	}
	for(unsigned int i=0; i < nb_diff_terms; i++){
		Rule r;
		double prob;
		dumpstream >> r >> prob;
		ruleprobs[r] = prob;
	}
	dumpstream.close();
}