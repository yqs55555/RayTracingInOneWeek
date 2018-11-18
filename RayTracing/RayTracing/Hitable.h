#pragma once
#include "Ray.h"

namespace YQS
{
	class Material;
	struct Hit_record
	{
		float t;
		Vector3 p;
		Vector3 normal;	//���ߣ�����ʼ��Ϊ��λ����
		Material* mat_ptr;
	};

	class Hitable
	{
	public:
		virtual bool hit(const Ray& ray, float t_min, float t_max, Hit_record& rec) const = 0;
	};
}