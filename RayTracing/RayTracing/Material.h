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
	//反射 v:入射光线 n:法线
	inline Vector3 reflect(const Vector3& v, const Vector3& n)
	{
		return v - 2 * Vector3::dot(v, n) * n;
	}

	//折射 v:入射光线 n:法线 ni_over_nt折射率 refracted折射光线
	bool refract(const Vector3& v,const Vector3& n, float ni_over_nt, Vector3& refracted)
	{
		//折射公式的推导:https://blog.csdn.net/puppet_master/article/details/81144266
		Vector3 uv = Vector3::unit_vector(v);
		float dt = Vector3::dot(uv, n);
		float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);		//这个值是折射光线与法线夹角的cos值
		if(discriminant > 0)	//如果折射光线与法线夹角在0~90之间，代表可以发生折射
		{
			refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
			return true;
		}
		return false;
	}

	//schlick菲涅尔反射 cosine:光线方向与法线的夹角的补角的cos值 ref_idx:折射率
	float schlick(float cosine, float ref_idx)
	{
		float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
		r0 = r0 * r0;			//反射强度
		return (r0 + (1.0f - r0) * pow((1 - cosine), 5));
	}

	//随机生成一个长度大于1并且每一项都在0~1之间的矢量
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
