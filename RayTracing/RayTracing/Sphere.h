#pragma once

#include "Hitable.h"
namespace YQS
{
	//������ײ��
	class Sphere : public Hitable
	{
	public:

		Vector3 center;
		float radius;
		Material* mat_ptr;

		//center �������꣬r ����뾶��mat �������
		Sphere(Vector3 center, float r, Material* mat)
			:center(center),radius(r), mat_ptr(mat)
		{
			
		}

		bool hit(const Ray& ray, float t_min, float t_max, Hit_record& rec) const override
		{
			/*
			 * ����������ײ�㣬ʹ�ù�ʽ�����ߵĳ�����O����֪�����ӵ���ײ��P��P=O + t * d����������OP��P-C��������ģ��õ���������ģ��������İ뾶R����dot��P-C��P-C��=R * R
			 * �õ�ʽ��dot(d,d)*t*t + 2*dot(d,OC)*t + dot(OC,OC) - R*R = 0
			 */
			Vector3 oc = ray.origin() - center;			
			float a = Vector3::dot(ray.direction(), ray.direction());
			float b = Vector3::dot(oc, ray.direction());
			float c = Vector3::dot(oc, oc) - radius * radius;
			float discriminant = b * b - a * c;		//������һԪ���η��̵�delta�����ڳ���ʽ��b*b-4*a*c��1/4)
			if (discriminant > 0)		//�������������������ߴ���������򣬲�������������
			{
				float temp = (-b - sqrt(discriminant)) / a;	//����1����С���Ǹ���
				if (temp < t_max && temp > t_min)
				{
					rec.t = temp;
					rec.p = ray.point_at_parameter(rec.t);
					rec.normal = (rec.p - center) / radius;
					rec.mat_ptr = mat_ptr;
					return true;
				}
				return false;
				temp = (-b + sqrt(discriminant)) / a;		//����2���ϴ���Ǹ��⣬�̳��д��ڣ����Ǹо�û�д��ڵ����壬������ע�͵�
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