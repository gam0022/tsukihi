#ifndef	_SCENE_H_
#define	_SCENE_H_

#include <vector>
#include <typeinfo>

#include "constant.h"
#include "intersection.h"

#include "object.h"
#include "sphere.h"
#include "raymarching_sphere.h"
#include "raymarching_menger_sponge.h"
#include "point_light.h"

namespace tukihi {

// カメラ位置

// 全体像
const Vec3 camera_position = Vec3(50.0, 52.0, 220.0);
const Vec3 camera_dir = normalize(Vec3(0.0, -0.04, -1.0));
const Vec3 camera_up = Vec3(0.0, 1.0, 0.0);

// 中身
//const Vec3 camera_position = Vec3(50, 60, 80);
//const Vec3 camera_dir      = normalize(Vec3(-0.1, -1.0, -0.01));
//const Vec3 camera_up       = Vec3(0.0, -1.0, 0.0);

// 斜め視点
//const Vec3 camera_position = Vec3(90.0, 78.0, 130.0);
//const Vec3 camera_dir = normalize(Vec3(-0.4, -0.5, -0.5));
//const Vec3 camera_up = Vec3(0.0, 1.0, 0.0);

// レンダリングするシーンデータ
Object* objects[] = {
	new Sphere(1e5, Vec3( 1e5+1, 40.8, 81.6), Color(),      Color(0.75, 0.25, 0.25), REFLECTION_TYPE_DIFFUSE), // 左
	new Sphere(1e5, Vec3(-1e5+99, 40.8, 81.6),Color(),      Color(0.25, 0.25, 0.75), REFLECTION_TYPE_DIFFUSE), // 右
	new Sphere(1e5, Vec3(50, 40.8, 1e5),      Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 奥
	new Sphere(1e5, Vec3(50, 40.8, -1e5+250), Color(),      Color(),                 REFLECTION_TYPE_DIFFUSE), // 手前
	new Sphere(1e5, Vec3(50, 1e5, 81.6),      Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 床
	new Sphere(1e5, Vec3(50, -1e5+81.6, 81.6),Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 天井

	new Sphere(1.0,Vec3(50.0, 90.0 - 10, 81.6),   Color(36,36,36), Color(),              REFLECTION_TYPE_SPECULAR), //照明
	new Sphere(1.0,Vec3(50.0, 20, 120),   Color(36,36,36), Color(),              REFLECTION_TYPE_SPECULAR), //照明

	//new Sphere(20,Vec(65, 20, 20),           Color(),       Color(0.99, 0.99, 0.99), REFLECTION_TYPE_SPECULAR), // 鏡
	//new Sphere(16.5,Vec(47, 16.5, 117),       Color(),      Color(0.99, 0.199, 0.99), REFLECTION_TYPE_REFRACTION), // ガラス
	//new Sphere(15,Vec(73, 15, 100),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_REFRACTION), //ガラス

	//new RaymarchingSphere(Color(), Color(0.75, 0.25, 0.25), REFLECTION_TYPE_SPECULAR),
	new RaymarchingMengerSponge(Color(), Color(0.25, 0.75, 0.25), REFLECTION_TYPE_DIFFUSE),
};

RaymarchingObject* raymarching_objects[] = {
	new RaymarchingMengerSponge(Color(), Color(0.5, 0.5, 0.5), REFLECTION_TYPE_DIFFUSE),
	nullptr
};

std::vector<PointLight*> lights;

void setup() {
	lights.push_back(new PointLight(1.0, Vec3(50.0, 90.0 - 10, 81.6), Color(255, 255, 255)));
	lights.push_back(new PointLight(1.0, Vec3(50.0, 20, 120.0), Color(255, 255, 255)));
}

// シーンとの交差判定関数
inline bool intersect_scene(const Ray &ray, Intersection *intersection) {
	// 初期化
	intersection->hitpoint.distance = kINF;
	intersection->object_id = -1;
	
	// 線形探索
	int i = 0;
	for (auto object : objects) {
		Hitpoint hitpoint;
		if (object->intersect(ray, &hitpoint)) {
			if (hitpoint.distance < intersection->hitpoint.distance) {
				intersection->hitpoint = hitpoint;
				intersection->object_id = i;
			}
		}
		i++;
	}

	return (intersection->object_id != -1);
}

inline double map(const Vec3 &position) {
	double min = std::numeric_limits<double>::max();
	for (int i = 0; raymarching_objects[i] != nullptr; i++) {
		min = std::min(min, raymarching_objects[i]->distanceFunction(position));
	}
	return min;
}

};

#endif
