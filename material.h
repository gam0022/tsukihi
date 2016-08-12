#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "vec3.h"

namespace tukihi {

typedef Vec3 Color;

enum ReflectionType {
	REFLECTION_TYPE_DIFFUSE,	// 完全拡散面。いわゆるLambertian面。
	REFLECTION_TYPE_SPECULAR,	// 理想的な鏡面。
	REFLECTION_TYPE_REFRACTION,	// 理想的なガラス的物質。

	REFLECTION_TYPE_FAKE,
};

const double kIor = 1.5; // 屈折率(Index of refraction)

};

#endif
