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
	Structure structure;
	unordered_map<Base, int> nb_bases;
	unordered_map<Base, int>::const_iterator search;
	unsigned int w_ptr;
	for (string word; getline(learnstream, word);){
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
		dumpstream << rprob.second << " " << rprob.first << endl;
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
		dumpstream >> prob;
		dumpstream >> r;
		ruleprobs[r] = prob;
	}
	dumpstream.close();
}

const void debug(const long &nb, const int &pqsize, const int &found, const double &proba){
	cerr << nb << " " << pqsize << " " << found << " " << proba << endl;
}

unordered_map<string, int> &load_target(const string &filename){
	static unordered_map<string, int> occurrences;
	ifstream target(filename);
	for(string line; getline(target, line);){
		occurrences[line]++;
	}
	return occurrences;
}

const void Pcfg::enumerate(const string &target, const double &prob_limit, const int &max_att){
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
		for(const Base &b: sp.first){
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
	unordered_map<string, int> &occ = load_target(target);
	Preterm pt;
	Preterm newpt;
	long nb = 0;
	int found = 0;
	string word;
	debug(nb, pq.size(), found, pq.top().proba);
	while(pq.size()){
		pt = pq.top();
		pq.pop();
		cout << pt << endl;
		pt >> word;
		nb++;
		if (occ.find(word) != occ.end()) found += occ[word];
		if (nb%10000 == 0){
			debug(nb, pq.size(), found, pt.proba);
			found = 0;
		}
		if (max_att && nb > max_att) break;
		for(unsigned int pivot=pt.pivot; pivot < pt.ruleranks.size(); pivot++){
			newpt = Preterm(pt);
			newpt.pivot = pivot;
			if(newpt[pivot] && newpt.proba >= prob_limit){
				pq.push(newpt);
			}
		}
	}
	debug(nb, pq.size(), found, pt.proba);
}