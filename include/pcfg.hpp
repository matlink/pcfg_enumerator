#ifndef PCFG_H
#define PCFG_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

// i.e. L8, D4, S2
typedef std::pair<char, int> Base;
// i.e. L8D4S2, ...
typedef std::vector<Base> Structure;
// i.e. L8 -> password, ...
typedef std::pair<Base, std::string> Rule;

inline std::ostream& operator<<(std::ostream& os, const Base& b){
	os << b.first << b.second;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const Structure& s){
	std::vector<Base>::const_iterator it = s.begin();
	for(; it != s.end(); it++){
		os << (*it).first << (*it).second;
	}
	return os;
}

inline std::ifstream& operator>>(std::ifstream& ifs, Structure& s){
	std::string line;
	ifs >> line;
	unsigned int lptr = 0;
	while(lptr < line.length()){
		Base b;
		b.first = line[lptr++];
		unsigned int nptr = 0;
		while(line[lptr+nptr] <= '9' && line[lptr+nptr] >= '0' && lptr+nptr < line.length()){
			nptr++;
		}
		b.second = std::stoi(line.substr(lptr,nptr));
		lptr += nptr;
		s.push_back(b);
	}
	return ifs;
}

inline std::ostream& operator<<(std::ostream& os, const Rule& r){
	os << r.first << "->" << r.second;
	return os;
}

inline std::ifstream& operator>>(std::ifstream& ifs, Rule& r){
	std::string line;
	ifs >> line;
	Base b;
	b.first = line[0];
	unsigned int lptr = 1;
	while(line[lptr] <= '9' && line[lptr] >= '0'){
		lptr++;
	}
	b.second = std::stoi(line.substr(1,lptr-1));
	r.first = b;
	r.second = line.substr(lptr+2);
	return ifs;
}

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