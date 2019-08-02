#include "preterm.hpp"

Preterm::Preterm(double proba, const Structure &structure, Ruledict ordered_rules){
	this->proba = proba;
	this->structure = structure;
	this->ordered_rules = ordered_rules;
}

Preterm::Preterm(double proba, const Structure &structure, unsigned int pivot, Ruleranks ruleranks, Ruledict ordered_rules){
	this->proba = proba;
	this->structure = structure;
	this->pivot = pivot;
	this->ruleranks = ruleranks;
	this->ordered_rules = ordered_rules;
}

unsigned int Preterm::operator[](const unsigned int pivot){
	return ruleranks[pivot]++;
}

std::ostream& operator<<(std::ostream& os, const Preterm& pt){
	for(unsigned int pivot=0; pivot < pt.structure.size(); pivot++){
		// Base b = pt.structure[pivot];
		Base b;
		b.type = 'D';
		b.len = 8;
		// unsigned int rank = pt.ruleranks[pivot];
		auto terminal = pt.ordered_rules[b];
	}
	return os;
}

bool operator<(const Preterm &lhs, const Preterm &rhs){
	return lhs.proba < rhs.proba;
}