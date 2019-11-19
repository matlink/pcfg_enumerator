#ifndef PCFG_H
#define PCFG_H

#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <vector>

#include "rule.hpp"
#include "structure.hpp"

class Pcfg{
private:
	int nb_structures = 0;
	std::unordered_map<Structure, double> structprobs;
	std::unordered_map<Rule, double> ruleprobs;
	void parse(const std::string &word, Structure &structure) const;
public:
	void learn(const std::string &filename);
	void dump(const std::string &filename) const;
	void load(const std::string &filename);
	void enumerate(const double &prob_limit, const int &max_att) const;
};

#endif