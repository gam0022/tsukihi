#ifndef	_VEC2_H_
#define	_VEC2_H_

#include <cmath>
#include <algorithm>

#include "math.h"

namespace tsukihi {

	struct Vec2 {
		double x, y;
		Vec2(const double x = 0, const double y = 0) : x(x), y(y) {}
		inline Vec2 operator+(const Vec2 &b) const {
			return Vec2(x + b.x, y + b.y);
		}
		inline Vec2 operator-(const Vec2 &b) const {
			return Vec2(x - b.x, y - b.y);
		}
		inline Vec2 operator*(const double b) const {
			return Vec2(x * b, y * b);
		}
		inline Vec2 operator+(const double b) const {
			return Vec2(x + b, y + b);
		}
		inline Vec2 operator-(const double b) const {
			return Vec2(x - b, y - b);
		}
		inline Vec2 operator/(const double b) const {
			return Vec2(x / b, y / b);
		}
		inline const double length_squared() const {
			return x*x + y*y;
		}
		inline const double length() const {
			return sqrt(length_squared());
		}
	};
	inline Vec2 operator*(double f, const Vec2 &v) {
		return v * f;
	}
	inline Vec2 normalize(const Vec2 &v) {
		return v * (1.0 / v.length());
	}
	inline const Vec2 multiply(const Vec2 &v1, const Vec2 &v2) {
		return Vec2(v1.x * v2.x, v1.y * v2.y);
	}
	inline const double dot(const Vec2 &v1, const Vec2 &v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	inline const double cross(const Vec2 &v1, const Vec2 &v2) {
		return v1.x * v2.y - v2.x * v1.y;
	}
	inline const Vec2 abs(const Vec2 &v) {
		return Vec2(std::abs(v.x), std::abs(v.y));
	}
	inline const Vec2 max(const Vec2 &v, double b) {
		return Vec2(std::max(v.x, b), std::max(v.y, b));
	}
	inline const Vec2 mod(const Vec2 &v, double b) {
		return Vec2(mod(v.x, b), mod(v.y, b));
	}
};

#endif
