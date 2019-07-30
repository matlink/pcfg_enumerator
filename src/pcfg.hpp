#ifndef PCFG_H
#define PCFG_H

#include <string>
#include <unordered_map>
#include <vector>

typedef std::pair<char, int> Base;
typedef std::vector<Base> Structure;

namespace std {
	template<>
	struct hash<Structure> : public unary_function<Structure, size_t> {
		size_t operator()(const Structure& s) const {
			Structure::const_iterator it = s.begin();
			int total = 0;
			for(; it != s.end(); it++){
				total += (*it).first + (*it).second;
			}
			return total;
		}
	};
}

class Pcfg{
private:
	std::unordered_map<Structure, double> structprobs;
	Structure parse(std::string word);
public:
	void learn(std::string filename);
};

#endif