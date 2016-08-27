#ifndef	_VEC3_H_
#define	_VEC3_H_

#include <cmath>
#include <algorithm>

#include "math.h"
#include "vec2.h"

namespace tsukihi {

	struct Vec3 {
		double x, y, z;
		Vec3(const double x = 0, const double y = 0, const double z = 0) : x(x), y(y), z(z) {}

		inline Vec3 operator+(const Vec3 &b) const {
			return Vec3(x + b.x, y + b.y, z + b.z);
		}
		inline Vec3 operator-(const Vec3 &b) const {
			return Vec3(x - b.x, y - b.y, z - b.z);
		}
		inline Vec3 operator+(const double b) const {
			return Vec3(x + b, y + b, z + b);
		}
		inline Vec3 operator-(const double b) const {
			return Vec3(x - b, y - b, z - b);
		}
		inline Vec3 operator*(const double b) const {
			return Vec3(x * b, y * b, z * b);
		}
		inline Vec3 operator/(const double b) const {
			return Vec3(x / b, y / b, z / b);
		}

		inline Vec3 operator-() const {
			return Vec3(-x, -y, -z);
		}

		inline Vec3 operator+=(const Vec3 &b) {
			x += b.x;
			y += b.y;
			z += b.z;
			return *this;
		}
		inline Vec3 operator-=(const Vec3 &b) {
			x -= b.x;
			y -= b.y;
			z -= b.z;
			return *this;
		}
		inline Vec3 operator+=(const double b) {
			x += b;
			y += b;
			z += b;
			return *this;
		}
		inline Vec3 operator-=(const double b) {
			x -= b;
			y -= b;
			z -= b;
			return *this;
		}
		inline Vec3 operator*=(const double b) {
			x *= b;
			y *= b;
			z *= b;
			return *this;
		}
		inline Vec3 operator/=(const double b) {
			x /= b;
			y /= b;
			z /= b;
			return *this;
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
	inline Vec3 operator*(double f, const Vec3 &v) {
		return v * f;
	}

	inline Vec3 normalize(const Vec3 &v) {
		return v / v.length();
	}
	inline const Vec3 multiply(const Vec3 &v1, const Vec3 &v2) {
		return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}
	inline const double dot(const Vec3 &v1, const Vec3 &v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	inline const Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
		return Vec3(
			(v1.y * v2.z) - (v1.z * v2.y),
			(v1.z * v2.x) - (v1.x * v2.z),
			(v1.x * v2.y) - (v1.y * v2.x));
	}

	inline const Vec3 reflect(const Vec3& dir, const Vec3& normal) {
		return dir - dot(normal, dir) * normal * 2.0;
	}

	inline const Vec3 abs(const Vec3 &v) {
		return Vec3(std::abs(v.x), std::abs(v.y), std::abs(v.z));
	}
	inline const Vec3 max(const Vec3 &v, double b) {
		return Vec3(std::max(v.x, b), std::max(v.y, b), std::max(v.z, b));
	}
	inline const Vec3 mod(const Vec3 &v, double b) {
		return Vec3(mod(v.x, b), mod(v.y, b), mod(v.z, b));
	}
	inline const Vec3 clamp(const Vec3 &v, double a, double b) {
		return Vec3(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b));
	}
	inline double length(const Vec3 &v) {
		return v.length();
	}
};

#endif
