#pragma once
#include "Material.h"

namespace YQS
{
	//µç½âÖÊ
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
			Vector3 reflected = reflect(ray_in.direction(), rec.normal);
			float ni_over_nt;
			attenuation = Vector3(1.0, 1.0, 1.0);
			Vector3 refracted;
			float reflect_prob;
			float cosine;
			if (Vector3::dot(ray_in.direction(), rec.normal) > 0) {
				outward_normal = -rec.normal;
				ni_over_nt = ref_idx;
				//         cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
				cosine = Vector3::dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
				cosine = sqrt(1 - ref_idx * ref_idx*(1 - cosine * cosine));
			}
			else {
				outward_normal = rec.normal;
				ni_over_nt = 1.0 / ref_idx;
				cosine = -Vector3::dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
			}
			if (refract(ray_in.direction(), outward_normal, ni_over_nt, refracted))
				reflect_prob = schlick(cosine, ref_idx);
			else
				reflect_prob = 1.0;
			if (drand48() < reflect_prob)
				scattered = Ray(rec.p, reflected);
			else
				scattered = Ray(rec.p, refracted);
			return true;
		}
		float ref_idx;
	};
}