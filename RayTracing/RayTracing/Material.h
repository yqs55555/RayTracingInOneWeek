#pragma once
#include "Ray.h"
#include "Hitable.h"
#include "Random.h"

namespace YQS
{
	class Material
	{
	public:
		virtual bool scatter(const Ray& ray_in, const Hit_record& rec, Vector3& attrnation, Ray& scattered) const = 0;
	};

	inline Vector3 reflect(const Vector3& v, const Vector3& n)
	{
		return v - 2 * Vector3::dot(v, n) * n;
	}

	bool refract(const Vector3& v,const Vector3& n, float ni_over_nt, Vector3& refracted)
	{
		Vector3 uv = Vector3::unit_vector(v);
		float dt = Vector3::dot(uv, n);
		float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
		if(discriminant > 0)
		{
			refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
			return true;
		}
		return false;
	}

	float schlick(float cosine, float ref_idx)
	{
		float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
		r0 = r0 * r0;
		return (r0 + (1.0f - r0) * pow((1 - cosine), 5));
	}

	inline Vector3 random_in_unit_sphere()
	{
		Vector3 p;
		do
		{
			p = 2.0f * Vector3(drand48(), drand48(), drand48()) - Vector3(1, 1, 1);
		} while (p.squared_length() >= 1.0f);
		return p;
	}
}
