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
	const void learn(const std::string &filename);
	const void dump(const std::string &filename);
	const void load(const std::string &filename);
	const void enumerate();
};

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A, std::greater<double>> flip_map(const std::unordered_map<A,B> &src)
{
    std::multimap<B,A, std::greater<double>> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                   flip_pair<A,B>);
    return dst;
}

#endif