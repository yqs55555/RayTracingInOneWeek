#pragma once
#include "Ray.h"
#include "Material.h"

namespace YQS
{
	#define PI 3.1415926
	//随机获得一条长度小于1的矢量
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
	* \param lookfrom 摄像机坐标
	* \param lookat 摄像机指向
	* \param vup 摄像机y轴
	* \param vfov 摄像机视椎体张开角度(垂直方向上
	* \param aspect 摄像机横纵比
	* \param aperture 摄像机孔径
	* \param focus_dist 焦距
	*/
	class Camera
	{
	public:
		/**
		* \brief
		* \param lookfrom 摄像机坐标
		* \param lookat 摄像机指向
		* \param vup 摄像机y轴
		* \param vfov 摄像机视椎体张开角度(垂直方向上
		* \param aspect 摄像机横纵比
		* \param aperture 摄像机孔径（镜头的半径）
		* \param focus_dist 焦距
		*/
		Camera(Vector3 lookfrom, Vector3 lookat, Vector3 vup, float vfov, float aspect, float aperture, float focus_dist)
		{
			lens_radius = aperture / 2.0f;
			float theta = vfov * PI / 180;			//角度转为弧度
			float half_height = tan(theta / 2);		//摄像机显示的高度的一半
			float half_width = aspect * half_height;//宽度的一半
			origin = lookfrom;
			w = Vector3::unit_vector(lookfrom - lookat);
			u = Vector3::unit_vector(Vector3::cross(vup, w));
			v = Vector3::cross(w, u);
			lower_left_corner = origin - half_width * u * focus_dist - half_height * v * focus_dist - w * focus_dist;
			horizontal = 2 * half_width * focus_dist * u;
			vertical = 2 * half_height * focus_dist * v;
		}
		//从坐标（s,t）发射一条射线
		Ray get_ray(float s, float t) const
		{
			Vector3 rd = lens_radius * random_in_unit_disk();
			Vector3 offset = rd.x() * u + rd.y() * v;
			return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
		}
		Vector3 origin;				//摄像机坐标
		Vector3 lower_left_corner;	//摄像机左下角
		Vector3 horizontal;
		Vector3 vertical;
		Vector3 u;		//摄像机u轴，横轴，由v和w轴确定，相互垂直
		Vector3 v;		//摄像机v轴，指向上方
		Vector3 w;		//摄像机w轴，深度信息轴
		float lens_radius;	//半径
	};
}
