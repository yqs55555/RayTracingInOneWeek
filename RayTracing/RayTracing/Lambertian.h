#pragma once
#include "Material.h"
#include "Vector3.h"

namespace YQS
{
	//兰伯特，漫反射材质
	class Lambertian : public Material
	{
	public:
		Lambertian(const Vector3& a)
			:albedo(a)
		{

		}

		virtual bool scatter(const Ray& ray_in, const Hit_record& rec, Vector3& attenuation, Ray& scatter) const
		{
			Vector3 target = rec.normal + random_in_unit_sphere();		//以碰撞点的为圆心构造一个半球，射出光线方向为这个半球的任意一个方向
			scatter = Ray(rec.p, target);		//生成散射后的新光线
			attenuation = albedo;				//反射系数即为此材质的albedo
			return true;
		}
		Vector3 albedo;
	};
}