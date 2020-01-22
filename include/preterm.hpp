#ifndef PRETERM_H
#define PRETERM_H

#include <vector>
#include <unordered_map>

#include "structure.hpp"
#include "rule.hpp"

typedef std::vector<uint> Ruleranks;
typedef std::unordered_map<Base, std::vector<std::pair<Rule, double>>> Ruledict;

class Preterm {
public:
	double proba = 0;
	unsigned int pivot = 0;
	Structure structure;
	Ruleranks ruleranks;
	Preterm(const Preterm &pt);
	Preterm(double proba, const Structure &structure, Ruledict *ordered_rules);
	Preterm() = default;
	bool operator[](const uint pivot);
	friend std::ostream& operator<<(std::ostream& os, const Preterm& pt);
	friend std::string& operator>>(const Preterm& pt, std::string& word);
	friend bool operator<(const Preterm &lhd, const Preterm &rhs);
private:
	Ruledict *ordered_rules;
};

#endif