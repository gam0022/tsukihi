#ifndef	_VEC4_H_
#define	_VEC4_H_

#include <cmath>
#include <algorithm>

#include "math.h"
#include "vec2.h"
#include "vec3.h"

namespace tsukihi {

	struct Vec4 {
		double x, y, z, w;
		Vec4(const double x = 0, const double y = 0, const double z = 0, const double w = 0) : x(x), y(y), z(z), w(w) {}

		inline Vec4 operator+(const Vec4 &b) const {
			return Vec4(x + b.x, y + b.y, z + b.z, w + b.w);
		}
		inline Vec4 operator-(const Vec4 &b) const {
			return Vec4(x - b.x, y - b.y, z - b.z, w - b.w);
		}
		inline Vec4 operator+(const double b) const {
			return Vec4(x + b, y + b, z + b, w + b);
		}
		inline Vec4 operator-(const double b) const {
			return Vec4(x - b, y - b, z - b, w - b);
		}
		inline Vec4 operator*(const double b) const {
			return Vec4(x * b, y * b, z * b, w * b);
		}
		inline Vec4 operator/(const double b) const {
			return Vec4(x / b, y / b, z / b, w / b);
		}

		inline Vec4 operator-() const {
			return Vec4(-x, -y, -z, -w);
		}

		inline Vec4 operator+=(const Vec4 &b) {
			x += b.x;
			y += b.y;
			z += b.z;
			w += b.w;
			return *this;
		}
		inline Vec4 operator-=(const Vec4 &b) {
			x -= b.x;
			y -= b.y;
			z -= b.z;
			w -= b.w;
			return *this;
		}
		inline Vec4 operator+=(const double b) {
			x += b;
			y += b;
			z += b;
			w += b;
			return *this;
		}
		inline Vec4 operator-=(const double b) {
			x -= b;
			y -= b;
			z -= b;
			w -= b;
			return *this;
		}
		inline Vec4 operator*=(const double b) {
			x *= b;
			y *= b;
			z *= b;
			w *= b;
			return *this;
		}
		inline Vec4 operator/=(const double b) {
			x /= b;
			y /= b;
			z /= b;
			w /= b;
			return *this;
		}

		inline const double length_squared() const {
			return x*x + y*y + z*z + w*w;
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
		inline const Vec2 zw() const {
			return Vec2(z, w);
		}
		inline const Vec2 wx() const {
			return Vec2(w, x);
		}
		inline const Vec3 xyz() const {
			return Vec3(x, y, z);
		}
		inline const void set_xyz(const Vec3 &b) {
			x = b.x;
			y = b.y;
			z = b.z;
		}
	};
	inline Vec4 operator*(double f, const Vec4 &v) {
		return v * f;
	}

	inline Vec4 normalize(const Vec4 &v) {
		return v / v.length();
	}
	inline const Vec4 multiply(const Vec4 &v1, const Vec4 &v2) {
		return Vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
	}
	inline const double dot(const Vec4 &v1, const Vec4 &v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}
	//inline const Vec4 cross(const Vec4 &v1, const Vec4 &v2) {
	//	return Vec4(
	//		(v1.y * v2.z) - (v1.z * v2.y),
	//		(v1.z * v2.x) - (v1.x * v2.z),
	//		(v1.x * v2.y) - (v1.y * v2.x));
	//}

	inline const Vec4 reflect(const Vec4& dir, const Vec4& normal) {
		return dir - dot(normal, dir) * normal * 2.0;
	}

	inline const Vec4 abs(const Vec4 &v) {
		return Vec4(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w));
	}
	inline const Vec4 max(const Vec4 &v, double b) {
		return Vec4(std::max(v.x, b), std::max(v.y, b), std::max(v.z, b), std::max(v.w, b));
	}
	inline const Vec4 mod(const Vec4 &v, double b) {
		return Vec4(mod(v.x, b), mod(v.y, b), mod(v.z, b), mod(v.w, b));
	}
	inline const Vec4 clamp(const Vec4 &v, double a, double b) {
		return Vec4(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b), clamp(v.w, a, b));
	}
	inline double length(const Vec4 &v) {
		return v.length();
	}
};

#endif