#include "Ray.h"

namespace YQS
{
	Ray::Ray()
	{
	}

	Ray::Ray(const Vector3& a, const Vector3& b)
		:a(a), b(b)
	{
	}

	Ray::~Ray()
	{
	}

	Vector3 Ray::origin() const
	{
		return a;
	}

	Vector3 Ray::direction() const
	{
		return b;
	}

	Vector3 Ray::point_at_parameter(float t) const
	{
		return a + t * b;
	}
}