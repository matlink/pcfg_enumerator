#ifndef PCFG_H
#define PCFG_H

#include <string>
#include <unordered_map>
#include <vector>

#include "rule.hpp"
#include "structure.hpp"

class Pcfg{
private:
	int nb_structures = 0;
	std::unordered_map<Structure, double> structprobs;
	std::unordered_map<Rule, double> ruleprobs;
	const Structure parse(const std::string &word) const;
public:
	const void learn(const std::string &filename);
	const void dump(const std::string &filename);
	const void load(const std::string &filename);
};

#endif