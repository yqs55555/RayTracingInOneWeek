#pragma once
#include <ostream>

namespace YQS
{
	class Vector3
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector3& v);
		~Vector3();
		float x() const;
		float y() const;
		float z() const;
		float r() const;
		float g() const;
		float b() const;

		const Vector3& operator+() const;
		Vector3 operator-() const;
		float operator[](int i) const;

		Vector3 operator+=(const Vector3 &v2);
		Vector3 operator-=(const Vector3 &v2);
		Vector3 operator*=(const Vector3 &v2);

		Vector3 operator*=(const float scale);
		Vector3 operator/=(const float scale);
		inline Vector3 operator/=(const Vector3& v)
		{
			e[0] /= v.e[0];
			e[1] /= v.e[1];
			e[2] /= v.e[2];
			return *this;
		}

		float length() const;
		float squared_length() const;
		void to_unit_vector() { *this /= this->length(); }
		static Vector3 unit_vector(const Vector3& v);
		static float dot(const Vector3& v1, const Vector3& v2);
		static Vector3 cross(const Vector3& v1, const Vector3& v2);

		friend std::ostream& operator<<(std::ostream& ouput, const Vector3& v);

	private:
		float e[3];
	};

	inline Vector3 operator*(const float scale, const Vector3& v)
	{
		return Vector3(v[0] * scale, v[1] * scale, v[2] * scale);
	}

	inline Vector3 operator/(const Vector3& v, const float scale)
	{
		return Vector3(v[0] / scale, v[1] / scale, v[2] / scale);
	}

	inline Vector3 operator*(const Vector3& v, const float scale)
	{
		return Vector3(v[0] * scale, v[1] * scale, v[2] * scale);
	}

	inline Vector3 operator+(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
	}

	inline Vector3 operator-(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
	}

	inline Vector3 operator*(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
	}
}
