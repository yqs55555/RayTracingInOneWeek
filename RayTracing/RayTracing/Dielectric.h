#pragma once
#include "Material.h"

namespace YQS
{
	//介质材料，即光线射入此类物质可能会同时出现折射和反射
	class Dielectric : public Material
	{
	public:
		Dielectric(float ri)
			:ref_idx(ri)
		{

		}
		bool scatter(const Ray& ray_in, const Hit_record& rec, Vector3& attenuation, Ray& scattered) const override
		{
			Vector3 outward_normal;
			Vector3 reflected = reflect(ray_in.direction(), rec.normal);	//发生反射时的反射光线
			float ni_over_nt;
			attenuation = Vector3(1.0, 1.0, 1.0);
			Vector3 refracted;
			float reflect_prob;
			float cosine;
			if (Vector3::dot(ray_in.direction(), rec.normal) > 0) {		//如果光线的方向与碰撞点的法线角度小于90度，也就是说，此时是光线由球体内部射向空气
				outward_normal = -rec.normal;							//法线变为指向球心
				ni_over_nt = ref_idx;
				//         cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
				cosine = Vector3::dot(ray_in.direction(), rec.normal) / ray_in.direction().length();	//计算入射光线与法线的夹角的cos值
				cosine = sqrt(1 - ref_idx * ref_idx*(1 - cosine * cosine));
			}
			else {										//光线的方向与法线角度大于90度，即光线此时由空气射向球体
				outward_normal = rec.normal;
				ni_over_nt = 1.0f / ref_idx;
				cosine = -Vector3::dot(ray_in.direction(), rec.normal) / ray_in.direction().length();	//计算入射光线与法线的夹角的补角的cos值
			}
			if (refract(ray_in.direction(), outward_normal, ni_over_nt, refracted))	//如果发生了折射
				reflect_prob = schlick(cosine, ref_idx);
			else
				reflect_prob = 1.0;
			if (drand48() < reflect_prob)			//由于进行n次计算，所以实际上反射/折射的次数与reflect_prob相关
				scattered = Ray(rec.p, reflected);	//反射
			else
				scattered = Ray(rec.p, refracted);	//折射
			return true;
		}

		float ref_idx;	//折射率
	};
}