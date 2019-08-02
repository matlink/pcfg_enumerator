#ifndef PRETERM_H
#define PRETERM_H

#include <vector>
#include <unordered_map>

#include "structure.hpp"
#include "rule.hpp"

typedef std::vector<unsigned int> Ruleranks;
typedef std::unordered_map<Base, std::vector<std::pair<Rule, double>>> Ruledict;

class Preterm {
private:
	Ruledict ordered_rules;
public:
	Structure structure;
	double proba = 0;
	unsigned int pivot = 0;
	Ruleranks ruleranks;
	Preterm(double proba, const Structure &structure, const Ruledict &ordered_rules);
	Preterm(double proba, const Structure &structure, unsigned int pivot, Ruleranks ruleranks, const Ruledict &ordered_rules);
	Preterm(){};
	bool operator[](const unsigned int pivot);
	friend std::ostream& operator<<(std::ostream& os, Preterm& pt);
	friend bool operator<(const Preterm &lhd, const Preterm &rhs);
};

#endif