#pragma once
#include "Helpers.h"

namespace MathClasses
{
	class Vector3
	{
	public:

		Vector3() : Vector3{ 0 }
		{
		}
		Vector3(const float x, const float y, const float z) : x{ x }, y{ y }, z{ z }
		{
		}
		Vector3(const float value) : x{ value }, y{ value }, z(value)
		{
		}

	public:

		operator float*() const
		{
			return const_cast<float*>(data);
		}

		float& operator[](int index)
		{
			return data[index];
		}
		const float& operator[](int index) const
		{
			return data[index];
		}

		Vector3 operator+(Vector3 rhs) const
		{
			Vector3 sum;
			
			sum.x = (x + rhs.x);
			sum.y = (y + rhs.y);
			sum.z = (z + rhs.z);

			return sum;
		}

		Vector3 operator+=(const Vector3 rhs)
		{

			for (int i = 0; i < 3; ++i) {
				data[i] = data[i] + rhs[i];
			}

			return *this;
		}

		Vector3 operator-(const Vector3 rhs) const
		{
			Vector3 sum;

			sum.x = (x - rhs.x);
			sum.y = (y - rhs.y);
			sum.z = (z - rhs.z);

			return sum;
		}

		Vector3 operator-=(const Vector3 rhs)
		{
			for (int i = 0; i < 3; ++i) {
				data[i] = data[i] - rhs[i];
			}

			return *this;
		}

		Vector3 operator*(float scale) const
		{
			return Vector3(x * scale, y * scale, z * scale);
		}

		Vector3 operator/(float scale) const
		{
			if (scale == 0) {
				throw std::runtime_error("Cannot divide by 0");
			}

			return Vector3(x / scale, y / scale, z / scale);
		}

		bool operator==(const Vector3 rhs) const
		{
			return IsEqual(rhs);
		}
		bool operator!=(const Vector3 rhs) const
		{
			return !(*this == rhs);
		}
		bool IsEqual(const Vector3& rhs, float precision = constants::FLOAT_PRECISION) const
		{
			float xDist = fabsf(x - rhs.x);
			float yDist = fabsf(y - rhs.y);
			float zDist = fabsf(z - rhs.z);

			return  xDist < precision &&
				yDist < precision &&
				zDist < precision;
		}

		float Dot(const Vector3& rhs) const
		{
			return ((x * rhs.x) + (y * rhs.y) + (z * rhs.z));
		}
		float Dot(float rhsX, float rhsY, float rhsZ) const
		{
			return ((x * rhsX) + (y * rhsY) + (z * rhsZ));
		}

		Vector3 Cross(const Vector3& rhs) const
		{
			float a, b, c;
			a = (y * rhs.z) - (z * rhs.y);
			b = (z * rhs.x) - (x * rhs.z);
			c = (x * rhs.y) - (y * rhs.x);

			return Vector3(a, b, c);
		}

		float Magnitude() const
		{
			return SqrtF(MagnitudeSqr());
		}

		float MagnitudeSqr() const
		{
			return x * x + y * y + z * z;
		}

		void Normalise()
		{

			float m = Magnitude();

			if (m == 0) {
				return;
			}

			x /= m;
			y /= m;
			z /= m;

		}

		Vector3 Normalised() const
		{
			Vector3 copy = *this;
			copy.Normalise();
			return copy;
		}

		float Distance(const Vector3& other) const
		{
			return (*this - other).Magnitude();
		}

		std::string ToString() const
		{
			return (std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z));
		}

	public:

		union {
			struct { float x, y, z; };
			struct { float r, g, b; };
			float data[3];
		};

		friend Vector3 operator*(float lhs, const Vector3& rhs)
		{
			return rhs*lhs;
		}
		friend float DotProduct(const Vector3& vec1, const Vector3& vec2)
		{
			float a, b, c;
			a = vec1[0] * vec2[0];
			b = vec1[1] * vec2[1];
			c = vec1[2] * vec2[2];
		
			float total = a + b;
			total = total + c;
		
			return a + b + c;
		}
	};


	
}