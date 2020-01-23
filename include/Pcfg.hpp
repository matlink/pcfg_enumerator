#ifndef PCFG_H
#define PCFG_H

#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <vector>

#include "Rule.hpp"
#include "Structure.hpp"

class Pcfg{
private:
	int nb_structures = 0;
	/**
	* @brief Mapping between Structures and their probability
	**/
	std::unordered_map<Structure, double> structprobs;
	/**
	* @brief Mapping between Rules and their probability
	**/
	std::unordered_map<Rule, double> ruleprobs;
public:
	/**
	* @brief Compute Structures and Rules probabilities of passwords of filename
	**/
	void learn(const std::string &filename);
	/**
	* @brief Writes probabilities to filename for further use by load()
	**/
	void dump(const std::string &filename) const;
	/**
	* @brief Loads probabilities from filename, written by dump()
	**/
	void load(const std::string &filename);
	/**
	* @brief launch the generation of candidates
	**/
	void enumerate(const double &prob_limit, const int &max_att) const;
};

#endif