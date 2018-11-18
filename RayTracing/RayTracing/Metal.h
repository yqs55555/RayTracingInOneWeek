#pragma once
#include "Material.h"

namespace YQS
{
	//�������ʣ�
	class Metal : public Material
	{
	public:
		Metal(const Vector3& a,float f)
			:albedo(a),fuzz(f < 1 ? f : 1)
		{
		}

		virtual bool scatter(const Ray& ray_in, const Hit_record& rec, Vector3& attenuation, Ray& scattered) const
		{
			Vector3 reflected = reflect(Vector3::unit_vector(ray_in.direction()), rec.normal);
			scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
			attenuation = albedo;
			return (Vector3::dot(scattered.direction(), rec.normal) > 0);
		}
		Vector3 albedo;
		float fuzz;		//���������ĥ��̶�
	};
}

