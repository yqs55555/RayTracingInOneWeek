#include "Vector3.h"

namespace YQS
{
	Vector3::Vector3() : e{ 0.0f,0.0f,0.0f }
	{
	}

	Vector3::Vector3(float x, float y, float z)
	{
		e[0] = x;
		e[1] = y;
		e[2] = z;
	}

	Vector3::Vector3(const Vector3& v)
	{
		e[0] = v.e[0];
		e[1] = v.e[1];
		e[2] = v.e[2];
	}

	Vector3::~Vector3()
	{
	}

	float Vector3::x() const
	{
		return e[0];
	}

	float Vector3::y() const
	{
		return e[1];
	}

	float Vector3::z() const
	{
		return e[2];
	}

	float Vector3::r() const
	{
		return e[0];
	}

	float Vector3::g() const
	{
		return e[1];
	}

	float Vector3::b() const
	{
		return e[2];
	}

	const Vector3& Vector3::operator+() const
	{
		return *this;
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-e[0], -e[1], -e[2]);
	}

	float Vector3::operator[](const int i) const
	{
		return e[i];
	}

	Vector3 Vector3::operator+=(const Vector3& v2)
	{
		*this = *this + v2;
		return *this;
	}

	Vector3 Vector3::operator-=(const Vector3& v2)
	{
		*this = *this - v2;
		return *this;
	}

	Vector3 Vector3::operator*=(const Vector3& v2)
	{
		*this = *this * v2;
		return *this;
	}


	Vector3 Vector3::operator*=(const float scale)
	{
		*this = *this * scale;
		return *this;
	}

	Vector3 Vector3::operator/=(const float scale)
	{
		*this = *this / scale;
		return *this;
	}

	float Vector3::length() const
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	float Vector3::squared_length() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	Vector3 Vector3::unit_vector(const Vector3& v)
	{
		return v / v.length();
	}

	float Vector3::dot(const Vector3& v1, const Vector3& v2)
	{
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}

	Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
			v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
			v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
	}

	std::ostream& operator<<(std::ostream& ouput, const Vector3& v)
	{
		ouput << "(" << v.e[0] << "," << v.e[1] << "," << v.e[2] << ")" << std::endl;
		return ouput;
	}
}
