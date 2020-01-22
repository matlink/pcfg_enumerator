#ifndef SIMPLE_H
#define SIMPLE_H

#include <utility>
#include <ostream>
#include <fstream>

#define uint unsigned int
#define uchar unsigned char

// i.e. L8, D4, S2
class Simple {
public:
	char type;
	uint len;

	Simple(const char& type, const uint& len);
	Simple() = default;

	friend std::ostream& operator<<(std::ostream& os, const Simple& b);
	friend std::ifstream& operator>>(std::ifstream& ifs, Simple& b);
	friend bool operator==(const Simple &lhs, const Simple &rhs);
	friend bool operator!=(const Simple &lhs, const Simple &rhs);
};

namespace std {
	template<>
	struct hash<Simple> : public unary_function<Simple, size_t> {
		size_t operator()(const Simple& b) const {
			return (hash<char>()(b.type)
				^ (hash<int>()(b.len)<<1) >> 1);
		}
	};
}

#endif