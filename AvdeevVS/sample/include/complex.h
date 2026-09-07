#ifndef MAX
#define MAX 10000
#include <iostream>
using namespace std;

struct complex {
	float re;
	float im;

	complex(float , float );
	complex(const complex&);
	complex(const complex&&);
	complex operator+(const complex&);
	complex operator-(const complex&);
	complex operator*(const complex&);
	complex operator/(const complex&);
	bool operator==(const complex&) const;
	bool operator!=(const complex&) const;
	const complex& operator=(const complex&);
	complex& operator++();
	complex operator-();
	friend ostream& operator<<(ostream& out, const complex&);
};
#endif