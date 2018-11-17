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

	private:
		Vector3 a;	//起始点
		Vector3 b;	//ray的方向
	};
}
