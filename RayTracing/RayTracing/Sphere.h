#pragma once

#include "Hitable.h"
namespace YQS
{
	//球形碰撞体
	class Sphere : public Hitable
	{
	public:

		Vector3 center;
		float radius;
		Material* mat_ptr;

		//center 球心坐标，r 球体半径，mat 球体材质
		Sphere(Vector3 center, float r, Material* mat)
			:center(center),radius(r), mat_ptr(mat)
		{
			
		}

		bool hit(const Ray& ray, float t_min, float t_max, Hit_record& rec) const override
		{
			/*
			 * 以下在求碰撞点，使用公式是射线的出发点O（已知）连接到碰撞点P（P=O + t * d）构成向量OP，P-C（球的球心）得到的向量的模长等于球的半径R，即dot（P-C，P-C）=R * R
			 * 得到式子dot(d,d)*t*t + 2*dot(d,OC)*t + dot(OC,OC) - R*R = 0
			 */
			Vector3 oc = ray.origin() - center;			
			float a = Vector3::dot(ray.direction(), ray.direction());
			float b = Vector3::dot(oc, ray.direction());
			float c = Vector3::dot(oc, oc) - radius * radius;
			float discriminant = b * b - a * c;		//求得这个一元二次方程的delta（等于常用式子b*b-4*a*c的1/4)
			if (discriminant > 0)		//如果解大于两个，即光线穿过了这个球，产生了两个交点
			{
				float temp = (-b - sqrt(discriminant)) / a;	//交点1，较小的那个解
				if (temp < t_max && temp > t_min)
				{
					rec.t = temp;
					rec.p = ray.point_at_parameter(rec.t);
					rec.normal = (rec.p - center) / radius;
					rec.mat_ptr = mat_ptr;
					return true;
				}
				return false;
				temp = (-b + sqrt(discriminant)) / a;		//交点2，较大的那个解，教程中存在，但是感觉没有存在的意义，故这里注释掉
				if (temp < t_max && temp > t_min)
				{
					rec.t = temp;
					rec.p = ray.point_at_parameter(rec.t);
					rec.normal = (rec.p - center) / radius;
					rec.mat_ptr = mat_ptr;
					return true;
				}
			}
			return false;
		}
	};
}