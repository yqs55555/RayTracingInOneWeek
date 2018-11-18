#pragma once
#include "Material.h"

namespace YQS
{
	//���ʲ��ϣ�����������������ʿ��ܻ�ͬʱ��������ͷ���
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
			Vector3 reflected = reflect(ray_in.direction(), rec.normal);	//��������ʱ�ķ������
			float ni_over_nt;
			attenuation = Vector3(1.0, 1.0, 1.0);
			Vector3 refracted;
			float reflect_prob;
			float cosine;
			if (Vector3::dot(ray_in.direction(), rec.normal) > 0) {		//������ߵķ�������ײ��ķ��߽Ƕ�С��90�ȣ�Ҳ����˵����ʱ�ǹ����������ڲ��������
				outward_normal = -rec.normal;							//���߱�Ϊָ������
				ni_over_nt = ref_idx;
				//         cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
				cosine = Vector3::dot(ray_in.direction(), rec.normal) / ray_in.direction().length();	//������������뷨�ߵļнǵ�cosֵ
				cosine = sqrt(1 - ref_idx * ref_idx*(1 - cosine * cosine));
			}
			else {										//���ߵķ����뷨�߽Ƕȴ���90�ȣ������ߴ�ʱ�ɿ�����������
				outward_normal = rec.normal;
				ni_over_nt = 1.0f / ref_idx;
				cosine = -Vector3::dot(ray_in.direction(), rec.normal) / ray_in.direction().length();	//������������뷨�ߵļнǵĲ��ǵ�cosֵ
			}
			if (refract(ray_in.direction(), outward_normal, ni_over_nt, refracted))	//�������������
				reflect_prob = schlick(cosine, ref_idx);
			else
				reflect_prob = 1.0;
			if (drand48() < reflect_prob)			//���ڽ���n�μ��㣬����ʵ���Ϸ���/����Ĵ�����reflect_prob���
				scattered = Ray(rec.p, reflected);	//����
			else
				scattered = Ray(rec.p, refracted);	//����
			return true;
		}

		float ref_idx;	//������
	};
}