#include "preterm.hpp"

Preterm::Preterm(const Preterm &pt){
	this->proba = pt.proba;
	this->structure = pt.structure;
	this->ordered_rules = pt.ordered_rules;
	this->pivot = pt.pivot;
	this->ruleranks = pt.ruleranks;
}

Preterm::Preterm(double proba, const Structure &structure, const Ruledict &ordered_rules){
	this->proba = proba;
	this->structure = structure;
	this->ordered_rules = ordered_rules;
}

Preterm::Preterm(double proba, const Structure &structure, unsigned int pivot, Ruleranks ruleranks, const Ruledict &ordered_rules){
	this->proba = proba;
	this->structure = structure;
	this->pivot = pivot;
	this->ruleranks = ruleranks;
	this->ordered_rules = ordered_rules;
}

bool Preterm::operator[](const unsigned int pivot){
	unsigned int rank = ruleranks[pivot];
	Base &b = structure[pivot];
	if(rank+1 >= ordered_rules[b].size()){
		return false;
	}
	double old_proba = ordered_rules[b][rank+0].second;
	double new_proba = ordered_rules[b][rank+1].second;
	proba *=  new_proba / old_proba;
	ruleranks[pivot]++;
	return true;
}

std::ostream& operator<<(std::ostream& os, Preterm& pt){
	// os << pt.structure;
	for(unsigned int pivot=0; pivot < pt.structure.size(); pivot++){
		const Base &b = pt.structure[pivot];
		// os << b << " ";
		unsigned int rank = pt.ruleranks[pivot];
		Rule r = pt.ordered_rules[b][rank].first;
		// os << r << " ";
		os << r.terminal;
	}
	return os;
}

bool operator<(const Preterm &lhs, const Preterm &rhs){
	return lhs.proba < rhs.proba;
}