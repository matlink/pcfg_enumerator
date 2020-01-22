#include <fstream>
#include <iostream>
#include <functional>
#include <algorithm>
#include <queue>
#include "pcfg.hpp"
#include "preterm.hpp"

using namespace std;

void Pcfg::learn(const string &filename){
	ifstream learnstream(filename);
	Structure structure;
	unordered_map<Simple, int> nb_bases;
	unordered_map<Simple, int>::const_iterator search;
	uint w_ptr;
	for (string word; getline(learnstream, word);){
		Structure structure(word);
		structprobs[structure]++;
		nb_structures++;
		w_ptr = 0;
		for(Simple base: structure){
			string terminal = word.substr(w_ptr, base.len);
			w_ptr += base.len;
			ruleprobs[Rule(base, terminal)]++;
			nb_bases[base]++;
		}
	}
	learnstream.close();
	// compute probabilities
	for(auto &sprob: structprobs){
		sprob.second /= nb_structures;
	}
	for(auto &rprob: ruleprobs){
		Simple b = rprob.first.base;
		rprob.second /= nb_bases[b];
	}
}	

void Pcfg::dump(const string &filename) const {
	ofstream dumpstream(filename);
	dumpstream << structprobs.size() << " " << ruleprobs.size() << endl;
	for(auto &sprob: structprobs){
		dumpstream << sprob.first << " " << sprob.second << endl;
	}
	for(auto &rprob: ruleprobs){
		dumpstream << rprob.second << " " << rprob.first << endl;
	}
	dumpstream.close();
}

void Pcfg::load(const string &filename){
	ifstream dumpstream(filename);
	uint nb_diff_structures;
	uint nb_diff_terms;
	dumpstream >> nb_diff_structures >> nb_diff_terms;
	for(uint i=0; i < nb_diff_structures; i++){
		Structure s;
		double prob;
		dumpstream >> s >> prob;
		structprobs[s] = prob;
	}
	for(uint i=0; i < nb_diff_terms; i++){
		Rule r;
		double prob;
		dumpstream >> prob;
		dumpstream >> r;
		ruleprobs[r] = prob;
	}
	dumpstream.close();
}

void Pcfg::enumerate(const double &prob_limit, const int &max_att) const {
	priority_queue<Preterm> pq;
	Ruledict ordered_rules;

	for(auto &ruleprob: ruleprobs){
		const Rule &r = ruleprob.first;
		double proba = ruleprob.second;
		ordered_rules[r.base].push_back(pair<Rule, double>(r, proba));
	}

	for(auto &baseruleproba: ordered_rules){
		sort(baseruleproba.second.begin(), baseruleproba.second.end(), [](auto &left, auto &right) {
			return left.second > right.second;
    		}
    	);
	}
	for(auto &sp: structprobs){
		Preterm pt(sp.second, sp.first, &ordered_rules);
		for(const Simple &b: sp.first){
			pt.proba *= ordered_rules[b][0].second;
			pt.ruleranks.push_back(0);
		}
		if (pt.proba >= prob_limit){
			pq.push(pt);
		}
	}
	if (pq.size() == 0){
		cerr << "Empty queue, threshold to high!" << endl;
		return;
	}
	Preterm pt;
	Preterm newpt;
	long nb = 0;

	while(pq.size()){
		pt = pq.top();
		pq.pop();
		cout << pt << endl;
		nb++;
		if (max_att && nb > max_att) break;

		for(uint pivot=pt.pivot; pivot < pt.ruleranks.size(); pivot++){
			newpt = Preterm(pt);
			newpt.pivot = pivot;
			if(newpt[pivot] && newpt.proba >= prob_limit){
				pq.push(newpt);
			}
		}
	}
}