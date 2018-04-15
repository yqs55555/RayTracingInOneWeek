#pragma once
#include "Ray.h"
#include "Random.h"
namespace YQS
{
	class Camera
	{
	public:
		Camera()
		{
			lower_left_corner = Vector3(-2.0f, -1.0f, -1.0f);
			horizontal = Vector3(4.0f, 0.0f, 0.0f);
			vertical = Vector3(0.0f, 2.0f, 0.0f);
			origin = Vector3(0.0f, 0.0f, 0.0f);
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

	inline Vector3 random_in_unit_sphere()
	{
		Vector3 p;
		do
		{
			p = 2.0f * Vector3(drand48(), drand48(), drand48()) - Vector3(1, 1, 1);
		} while (p.squared_length() >= 1.0f);
		return p;
	}
}