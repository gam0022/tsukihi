#ifndef	_VEC_H_
#define	_VEC_H_

#include <cmath>
#include <algorithm>

#include "math.h"
#include "vec2.h"

namespace edupt {

struct Vec {
	double x, y, z;
	     Vec(const double x = 0, const double y = 0, const double z = 0) : x(x), y(y), z(z) {}
	inline Vec operator+(const Vec &b) const {
		return Vec(x + b.x, y + b.y, z + b.z);
	}
	inline Vec operator-(const Vec &b) const {
		return Vec(x - b.x, y - b.y, z - b.z);
	}
	inline Vec operator+(const double b) const {
		return Vec(x + b, y + b, z + b);
	}
	inline Vec operator-(const double b) const {
		return Vec(x - b, y - b, z - b);
	}
	inline Vec operator*(const double b) const {
		return Vec(x * b, y * b, z * b);
	}
	inline Vec operator/(const double b) const {
		return Vec(x / b, y / b, z / b);
	}
	inline const double length_squared() const { 
		return x*x + y*y + z*z; 
	}
	inline const double length() const { 
		return sqrt(length_squared()); 
	}

	inline const Vec2 xy() const {
		return Vec2(x, y);
	}
	inline const Vec2 yz() const {
		return Vec2(y, z);
	}
	inline const Vec2 zx() const {
		return Vec2(z, x);
	}
};
inline Vec operator*(double f, const Vec &v) { 
	return v * f; 
}
inline Vec normalize(const Vec &v) {
	return v * (1.0 / v.length()); 
}
inline const Vec multiply(const Vec &v1, const Vec &v2) {
	return Vec(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
inline const double dot(const Vec &v1, const Vec &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
inline const Vec cross(const Vec &v1, const Vec &v2) {
	return Vec(
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x));
}
inline const Vec abs(const Vec &v) {
	return Vec(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}
inline const Vec max(const Vec &v, double b) {
	return Vec(std::max(v.x, b), std::max(v.y, b), std::max(v.z, b));
}
inline const Vec mod(const Vec &v, double b) {
	return Vec(mod(v.x, b), mod(v.y, b), mod(v.z, b));
}
};

#endif
