#pragma once
#include "Material.h"
#include "Vector3.h"

namespace YQS
{
	//�����أ����������
	class Lambertian : public Material
	{
	public:
		Lambertian(const Vector3& a)
			:albedo(a)
		{

		}

		virtual bool scatter(const Ray& ray_in, const Hit_record& rec, Vector3& attenuation, Ray& scatter) const
		{
			Vector3 target = rec.normal + random_in_unit_sphere();		//����ײ���ΪԲ�Ĺ���һ������������߷���Ϊ������������һ������
			scatter = Ray(rec.p, target);		//����ɢ�����¹���
			attenuation = albedo;				//����ϵ����Ϊ�˲��ʵ�albedo
			return true;
		}
		Vector3 albedo;
	};
}