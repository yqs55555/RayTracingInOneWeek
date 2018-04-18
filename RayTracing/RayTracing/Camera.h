#pragma once
#include "Ray.h"
namespace YQS
{
#define PI 3.1415926
	class Camera
	{
	public:
		Camera(Vector3 lookfrom, Vector3 lookat, Vector3 vup, float vfov, float aspect)
		{
			Vector3 u, v, w;
			float theta = vfov * PI / 180;
			float half_height = tan(theta / 2);
			float half_width = aspect * half_height;
			origin = lookfrom;
			w = Vector3::unit_vector(lookfrom - lookat);
			u = Vector3::unit_vector(Vector3::cross(vup, w));
			v = Vector3::cross(w, u);
			lower_left_corner = origin - half_width * u - half_height * v - w;
			horizontal = 2 * half_width * u;
			vertical = 2 * half_height * v;
		}
		Ray get_ray(float u, float v) const
		{
			return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
		}
		Vector3 origin;
		Vector3 lower_left_corner;
		Vector3 horizontal;
		Vector3 vertical;
	};
}