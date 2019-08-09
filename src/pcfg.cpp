#include <fstream>
#include <iostream>
#include <functional>
#include <algorithm>
#include <queue>
#include "pcfg.hpp"
#include "preterm.hpp"

using namespace std;

const void Pcfg::learn(const string &filename){
	ifstream learnstream(filename);
	string word;
	Structure structure;
	unordered_map<Base, int> nb_bases;
	unordered_map<Base, int>::const_iterator search;
	unsigned int w_ptr;
	while (learnstream >> word){
		Structure structure(word);
		structprobs[structure]++;
		nb_structures++;
		w_ptr = 0;
		for(Base base: structure){
			string terminal = word.substr(w_ptr, base.len);
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

const void Pcfg::dump(const string &filename){
	ofstream dumpstream(filename);
	dumpstream << structprobs.size() << " " << ruleprobs.size() << endl;
	for(auto &sprob: structprobs){
		dumpstream << sprob.first << " " << sprob.second << endl;
	}
	for(auto &rprob: ruleprobs){
		dumpstream << rprob.first << " " << rprob.second << endl;
	}
	dumpstream.close();
}

const void Pcfg::load(const string &filename){
	ifstream dumpstream(filename);
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

const void Pcfg::enumerate(){
	priority_queue<Preterm> pq;
	multimap<double, Structure, greater<double>> ordered_structures = flip_map(structprobs);
	Ruledict ordered_rules;
	cerr << "Organizing rules ..." << endl;
	for(auto &ruleprob: ruleprobs){
		const Rule &r = ruleprob.first;
		double proba = ruleprob.second;
		ordered_rules[r.base].push_back(pair(r, proba));
	}

	for(auto &baseruleproba: ordered_rules){
		sort(baseruleproba.second.begin(), baseruleproba.second.end(), [](auto &left, auto &right) {
    		return left.second < right.second;
    		}
    	);
	}
	cerr << "Queue will be size " << ordered_structures.size() << endl;
	cerr << "Populating Queue ..." << endl;
	for(auto &sp: ordered_structures){
		const Structure &s = sp.second;
		double proba = sp.first;
		Preterm pt(proba, s, &ordered_rules);
		for(const Base &b: s){
			pt.proba *= ordered_rules[b][0].second;
			pt.ruleranks.push_back(0);
		}
		pq.push(pt);
	}
	cerr << "Generating candidates ..." << endl;
	Preterm pt;
	Preterm newpt;
	while(pq.size()){
		pt = pq.top();
		pq.pop();
		cout << pt << endl;
		for(unsigned int pivot=pt.pivot; pivot < pt.ruleranks.size(); pivot++){
			newpt = Preterm(pt);
			newpt.pivot = pivot;
			if(newpt[pivot]){
				pq.push(newpt);
			}
		}
	}
}