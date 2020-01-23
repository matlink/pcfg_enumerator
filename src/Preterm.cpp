#include "Preterm.hpp"

Preterm::Preterm(const Preterm &pt) :
proba(pt.proba),
structure(pt.structure),
rule_ptrs(pt.rule_ptrs),
ordered_rules(pt.ordered_rules)
{}

Preterm::Preterm(double proba, const Structure &structure, Ruledict *ordered_rules) : 
proba(proba),
structure(structure),
ordered_rules(ordered_rules)
{}

bool Preterm::operator()(const uint pivot){
	uint rank = rule_ptrs[pivot];
	Simple &b = structure[pivot];
	if(rank+1 >= (*ordered_rules)[b].size()){
		return false;
	}
	proba /= (*ordered_rules)[b][rank+0].second;
	proba *= (*ordered_rules)[b][rank+1].second;
	rule_ptrs[pivot]++;
	return true;
}

std::ostream& operator<<(std::ostream& os, const Preterm& pt) {
	for(uint pivot=0; pivot < pt.structure.size(); pivot++){
		const Simple &b = pt.structure[pivot];
		uint rank = pt.rule_ptrs[pivot];
		Rule r = (*pt.ordered_rules)[b][rank].first;
		os << r.terminal;
	}
	return os;
}

std::string& operator>>(const Preterm& pt, std::string& word){
	word = "";
	for(uint pivot=0; pivot < pt.structure.size(); pivot++){
		const Simple &b = pt.structure[pivot];
		uint rank = pt.rule_ptrs[pivot];
		Rule r = (*pt.ordered_rules)[b][rank].first;
		word += r.terminal;
	}
	return word;
}

bool operator<(const Preterm &lhs, const Preterm &rhs) {
	return lhs.proba < rhs.proba;
}