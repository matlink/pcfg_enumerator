#ifndef BASE_H
#define BASE_H

#include <utility>
#include <ostream>
#include <fstream>

#define uint unsigned int
#define uchar unsigned char

// i.e. L8, D4, S2
class Base {
public:
	char type;
	uint len;

	Base(const char& type, const uint& len);
	Base() = default;

	friend std::ostream& operator<<(std::ostream& os, const Base& b);
	friend std::ifstream& operator>>(std::ifstream& ifs, Base& b);
	friend bool operator==(const Base &lhs, const Base &rhs);
	friend bool operator!=(const Base &lhs, const Base &rhs);
};

namespace std {
	template<>
	struct hash<Base> : public unary_function<Base, size_t> {
		size_t operator()(const Base& b) const {
			return (hash<char>()(b.type)
				^ (hash<int>()(b.len)<<1) >> 1);
		}
	};
}

#endif