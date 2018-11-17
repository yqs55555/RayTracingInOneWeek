#pragma once
#include "Ray.h"
#include "Material.h"

namespace YQS
{
	#define PI 3.1415926
	//������һ������С��1��ʸ��
	Vector3 random_in_unit_disk()
	{
		Vector3 p;
		do
		{
			p = 2.0 * Vector3(drand48(), drand48(), 0) - Vector3(1, 1, 0);
		} while (Vector3::dot(p, p) >= 1.0);
		return p;
	}
	/**
	* \brief
	* \param lookfrom ���������
	* \param lookat �����ָ��
	* \param vup �����y��
	* \param vfov �������׵���ſ��Ƕ�(��ֱ������
	* \param aspect ��������ݱ�
	* \param aperture ������׾�
	* \param focus_dist ����
	*/
	class Camera
	{
	public:
		/**
		* \brief
		* \param lookfrom ���������
		* \param lookat �����ָ��
		* \param vup �����y��
		* \param vfov �������׵���ſ��Ƕ�(��ֱ������
		* \param aspect ��������ݱ�
		* \param aperture ������׾�����ͷ�İ뾶��
		* \param focus_dist ����
		*/
		Camera(Vector3 lookfrom, Vector3 lookat, Vector3 vup, float vfov, float aspect, float aperture, float focus_dist)
		{
			lens_radius = aperture / 2.0f;
			float theta = vfov * PI / 180;			//�Ƕ�תΪ����
			float half_height = tan(theta / 2);		//�������ʾ�ĸ߶ȵ�һ��
			float half_width = aspect * half_height;//��ȵ�һ��
			origin = lookfrom;
			w = Vector3::unit_vector(lookfrom - lookat);
			u = Vector3::unit_vector(Vector3::cross(vup, w));
			v = Vector3::cross(w, u);
			lower_left_corner = origin - half_width * u * focus_dist - half_height * v * focus_dist - w * focus_dist;
			horizontal = 2 * half_width * focus_dist * u;
			vertical = 2 * half_height * focus_dist * v;
		}
		//�����꣨s,t������һ������
		Ray get_ray(float s, float t) const
		{
			Vector3 rd = lens_radius * random_in_unit_disk();
			Vector3 offset = rd.x() * u + rd.y() * v;
			return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
		}
		Vector3 origin;				//���������
		Vector3 lower_left_corner;	//��������½�
		Vector3 horizontal;
		Vector3 vertical;
		Vector3 u;		//�����u�ᣬ���ᣬ��v��w��ȷ�����໥��ֱ
		Vector3 v;		//�����v�ᣬָ���Ϸ�
		Vector3 w;		//�����w�ᣬ�����Ϣ��
		float lens_radius;	//�뾶
	};
}
