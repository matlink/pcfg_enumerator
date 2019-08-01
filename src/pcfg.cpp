#include <fstream>
#include <iostream>
#include "pcfg.hpp"

const void Pcfg::learn(const std::string &filename){
	std::ifstream learnstream(filename);
	std::string word;
	Structure structure;
	std::unordered_map<Base, int> nb_bases;
	std::unordered_map<Base, int>::const_iterator search;
	unsigned int w_ptr;
	while (learnstream >> word){
		Structure structure(word);
		structprobs[structure]++;
		nb_structures++;
		w_ptr = 0;
		for(Base base: structure){
			std::string terminal = word.substr(w_ptr, base.len);
			w_ptr += base.len;
			ruleprobs[Rule(base, terminal)]++;;
			nb_bases[base]++;
		}
	}
	learnstream.close();
	// compute probabilities
	for(auto &sprob: structprobs){
		sprob.second /= nb_structures;
	}
	for(auto &rprob: ruleprobs){
		Base b = rprob.first.base;
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