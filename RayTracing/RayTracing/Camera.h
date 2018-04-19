#pragma once
#include "Ray.h"
#include "Material.h"

namespace YQS
{
	#define PI 3.1415926
	Vector3 random_in_unit_disk() 
	{
		Vector3 p;
		do 
		{
			p = 2.0*Vector3(drand48(), drand48(), 0) - Vector3(1, 1, 0);
		} while (Vector3::dot(p, p) >= 1.0);
		return p;
	}
	class Camera
	{
	public:
		Camera(Vector3 lookfrom, Vector3 lookat, Vector3 vup, float vfov, float aspect, float aperture, float focus_dist)
		{
			lens_radius = aperture / 2;
			float theta = vfov * PI / 180;
			float half_height = tan(theta / 2);
			float half_width = aspect * half_height;
			origin = lookfrom;
			w = Vector3::unit_vector(lookfrom - lookat);
			u = Vector3::unit_vector(Vector3::cross(vup, w));
			v = Vector3::cross(w, u);
			lower_left_corner = origin - half_width * u * focus_dist - half_height * v * focus_dist - w * focus_dist;
			horizontal = 2 * half_width * focus_dist * u;
			vertical = 2 * half_height * focus_dist * v;
		}
		Ray get_ray(float s, float t) const
		{
			Vector3 rd = lens_radius * random_in_unit_disk();
			Vector3 offset = rd.x() * u + v * rd.y();
			return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
		}
		Vector3 origin;
		Vector3 lower_left_corner;
		Vector3 horizontal;
		Vector3 vertical;
		Vector3 u, v, w;
		float lens_radius;
	};
}
