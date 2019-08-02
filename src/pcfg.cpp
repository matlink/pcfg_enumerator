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
	unordered_map<Base, multimap<double, Rule, greater<double>>> ordered_rules_map;
	for(auto &ruleprob: ruleprobs){
		Rule r = ruleprob.first;
		double proba = ruleprob.second;
		ordered_rules_map[r.base].insert(pair(proba,r));
	}
	Ruledict ordered_rules;
	for(auto &orm: ordered_rules_map){
		Base b = orm.first;
		for(auto &ruleprob: orm.second){
			ordered_rules[b].push_back(flip_pair(ruleprob));
		}
	}
	for(auto &sp: ordered_structures){
		Structure &s = sp.second;
		double proba = sp.first;
		Preterm pt(proba, s, ordered_rules);
		for(Base &b: s){
			pair<Rule, double> &first_rule_prob = ordered_rules[b][0];
			pt.proba *= first_rule_prob.second;
			pt.ruleranks.push_back(0);
		}
		pq.push(pt);
	}
	Preterm pt;
	while(pq.size()){
		pt = pq.top();
		pq.pop();
		cout << pt << endl;
		for(unsigned int pivot=pt.pivot; pivot < pt.ruleranks.size(); pivot++){
			pt[pivot];
			pq.push(pt);
		}
	}
}