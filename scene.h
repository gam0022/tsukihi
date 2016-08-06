#ifndef	_SCENE_H_
#define	_SCENE_H_

#include "constant.h"
#include "object.h"
#include "sphere.h"
#include "raymarching_sphere.h"
#include "raymarching_menger_sponge.h"
#include "intersection.h"

namespace edupt {

// レンダリングするシーンデータ
const Object* objects[] = {
	new Sphere(1e5, Vec( 1e5+1, 40.8, 81.6), Color(),      Color(0.75, 0.25, 0.25), REFLECTION_TYPE_DIFFUSE), // 左
	new Sphere(1e5, Vec(-1e5+99, 40.8, 81.6),Color(),      Color(0.25, 0.25, 0.75), REFLECTION_TYPE_DIFFUSE), // 右
	new Sphere(1e5, Vec(50, 40.8, 1e5),      Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 奥
	new Sphere(1e5, Vec(50, 40.8, -1e5+250), Color(),      Color(),                 REFLECTION_TYPE_DIFFUSE), // 手前
	new Sphere(1e5, Vec(50, 1e5, 81.6),      Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 床
	new Sphere(1e5, Vec(50, -1e5+81.6, 81.6),Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 天井
	new Sphere(20,Vec(65, 20, 20),           Color(),      Color(0.25, 0.75, 0.25), REFLECTION_TYPE_DIFFUSE), // 緑球
	new Sphere(16.5,Vec(27, 16.5, 47),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_SPECULAR), // 鏡
	new Sphere(16.5,Vec(77, 16.5, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_REFRACTION), //ガラス
	new Sphere(15.0,Vec(50.0, 90.0, 81.6),   Color(36,36,36), Color(),              REFLECTION_TYPE_SPECULAR), //照明
	//new RaymarchingSphere(Color(), Color(0.75, 0.25, 0.25), REFLECTION_TYPE_SPECULAR),
	new RaymarchingMengerSponge(Color(), Color(0.75, 0.25, 0.25), REFLECTION_TYPE_DIFFUSE),
};

// シーンとの交差判定関数
inline bool intersect_scene(const Ray &ray, Intersection *intersection) {
	const double n = 11;// sizeof(objects) / sizeof(Object);

	// 初期化
	intersection->hitpoint.distance = kINF;
	intersection->object_id  = -1;
	
	// 線形探索
	for (int i = 0; i < int(n); i ++) {
		Hitpoint hitpoint;
		if (objects[i]->intersect(ray, &hitpoint)) {
			if (hitpoint.distance < intersection->hitpoint.distance) {
				intersection->hitpoint = hitpoint;
				intersection->object_id = i;
			}
		}
	}

	return (intersection->object_id != -1);
}

};

#endif
