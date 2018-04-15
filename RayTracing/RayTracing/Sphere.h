#pragma once

#include "Hitable.h"
namespace YQS
{
	class Sphere : public Hitable
	{
	public:
		Sphere(Vector3 center, float r, Material* mat)
			:center(center),radius(r), mat_ptr(mat)
		{
			
		}

		bool hit(const Ray& ray, float t_min, float t_max, Hit_record& rec) const override
		{
			Vector3 oc = ray.origin() - center;
			float a = Vector3::dot(ray.direction(), ray.direction());
			float b = Vector3::dot(oc, ray.direction());
			float c = Vector3::dot(oc, oc) - radius * radius;
			float discriminant = b * b - a * c;
			if (discriminant > 0)
			{
				float temp = (-b - sqrt(discriminant)) / a;
				if (temp < t_max && temp > t_min)
				{
					rec.t = temp;
					rec.p = ray.point_at_parameter(rec.t);
					rec.normal = (rec.p - center) / radius;
					rec.mat_ptr = mat_ptr;
					return true;
				}
				temp = (-b + sqrt(discriminant)) / a;
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
		Vector3 center;
		float radius;
		Material* mat_ptr;
	};
}