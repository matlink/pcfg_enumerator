#ifndef PRETERM_H
#define PRETERM_H

#include <vector>
#include <unordered_map>

#include "Structure.hpp"
#include "Rule.hpp"

/**
* @brief Contains pointers to the next rule to apply, for each simple base of the structure
**/
typedef std::vector<uint> RulePtrs;
/**
* @brief Maps simple bases to a list of rules with their associated probability
**/
typedef std::unordered_map<Simple, std::vector<std::pair<Rule, double>>> Ruledict;

// Elements of the priority queue
class Preterm {
public:
	double proba = 0;
	unsigned int pivot = 0;
	Structure structure;
	RulePtrs rule_ptrs;
	Preterm(const Preterm &pt);
	Preterm(double proba, const Structure &structure, Ruledict& ordered_rules);
	Preterm& operator=(const Preterm&);
	bool operator()(const uint pivot);
	friend std::ostream& operator<<(std::ostream& os, const Preterm& pt);
	friend std::string& operator>>(const Preterm& pt, std::string& word);
	friend bool operator<(const Preterm &lhd, const Preterm &rhs);
private:
	Ruledict& ordered_rules;
};

#endif