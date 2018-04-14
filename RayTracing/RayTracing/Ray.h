#pragma once
#include "Vector3.h"

namespace YQS
{
	class Ray
	{
	public:
		Ray();
		Ray(const Vector3& a, const Vector3& b);
		~Ray();
		Vector3 origin() const;
		Vector3 direction() const;
		Vector3 point_at_parameter(float t) const;
		Ray operator=(const Ray& ray)
		{
			this->a = ray.a;
			this->b = ray.b;
			return *this;
		}

	private:
		Vector3 a;
		Vector3 b;
	};
}
