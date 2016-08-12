#ifndef	_MATH_H_
#define	_MATH_H_

#include <cmath>
#include <algorithm>

namespace tukihi {
	template<class T>
	inline const T mod(T x, T y) {
		double a = std::fmod(x, y);
		return a > 0 ? a : a + y;
	}

	template<class T>
	inline const T clamp(T x, T l, T u) {
		if (x < l)
			return l;
		if (x > u)
			return u;
		return x;
	}

	template<class T>
	inline const T smoothstep(T edge0, T edge1, T x) {
		T t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
		return t * t * (3.0 - 2.0 * t);
	}
};

#endif