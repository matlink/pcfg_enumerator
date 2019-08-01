#ifndef BASE_H
#define BASE_H

// i.e. L8, D4, S2
class Base: public std::pair<char, int> {
public:
	char type = this->first;
	int len = this->second;
};

inline std::ostream& operator<<(std::ostream& os, const Base& b){
	os << b.type << b.len;
	return os;
}
inline bool operator==(const Base &lhs, const Base &rhs){
	return lhs.type == rhs.type && lhs.len == rhs.len;
}
inline bool operator!=(const Base &lhs, const Base &rhs){
	return !(lhs==rhs);
}

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