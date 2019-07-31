#ifndef PCFG_H
#define PCFG_H

#include <string>
#include <unordered_map>
#include <vector>

// i.e. L8, D4, S2
typedef std::pair<char, int> Base;
// i.e. L8D4S2, ...
typedef std::vector<Base> Structure;
// i.e. L8 -> password, ...
typedef std::pair<Base, std::string> Rule;

// equality operators to store custom types in hashmaps.
inline bool operator==(const Base &lhs, const Base &rhs){
	return lhs.first == rhs.first && lhs.second == rhs.second;
}
inline bool operator!=(const Base &lhs, const Base &rhs){
	return !(lhs==rhs);
}
inline bool operator==(const Structure &lhs, const Structure &rhs){
	if (lhs.size() != rhs.size()) return false;
	for(unsigned int i=0; i < lhs.size(); i++){
		if(lhs[i] != rhs[i]) return false;
	}
	return true;
}
inline bool operator!=(const Structure &lhs, const Structure &rhs){
	return !(lhs == rhs);
}
inline bool operator==(const Rule &lhs, const Rule &rhs){
	return lhs.first == rhs.first && lhs.second == rhs.second;
}
inline bool operator!=(const Rule &lhs, const Rule &rhs){
	return !(lhs == rhs);
}

// Hash functions to store custom types in hashmaps.
namespace std {
	template<>
	struct hash<Base> : public unary_function<Base, size_t> {
		size_t operator()(const Base& b) const {
			return (hash<char>()(b.first)
				^ (hash<int>()(b.second)<<1) >> 1);
		}
	};
	template<>
	struct hash<Structure> : public unary_function<Structure, size_t> {
		size_t operator()(const Structure& s) const {
			size_t total = 0;
			unsigned short shift = 0;
			for(const Base &b: s){
				total ^= (hash<Base>()(b) << shift++);
			}
			return total;
		}
	};
	template<>
	struct hash<Rule> : public unary_function<Rule, size_t> {
		size_t operator()(const Rule& r) const {
			return (hash<char>()(r.first.first)
				^ (hash<int>()(r.first.second)<<1) >> 1)
				^ (hash<string>()(r.second) << 1);
		}
	};
}

class Pcfg{
private:
	std::unordered_map<Structure, double> structprobs;
	std::unordered_map<Rule, double> ruleprobs;
	const Structure parse(const std::string &word) const;
public:
	const void learn(const std::string &filename);
};

#endif