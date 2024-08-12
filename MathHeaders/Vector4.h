#pragma once
#include "Helpers.h"
#include <cmath>

namespace MathClasses
{

	class Vector4
	{
	public:

		Vector4() : Vector4{ 0 }
		{
		
		}

		Vector4(const float x, const float y, const float z, const float w) : x{ x }, y{ y }, z{ z }, w{ w }
		{
		}

		Vector4(const float value) : x{ value }, y{ value }, z{ value }, w{ value }
		{
		}

	public:

		operator float* () const
		{
			return const_cast<float*>(data);
		}

		Vector4 operator+(Vector4 rhs) const
		{
			Vector4 sum;

			sum.x = (x + rhs.x);
			sum.y = (y + rhs.y);
			sum.z = (z + rhs.z);
			sum.w = (w + rhs.w);

			return sum;
		}

		Vector4 operator-(const Vector4 rhs) const
		{
			Vector4 sum;

			sum.x = (x - rhs.x);
			sum.y = (y - rhs.y);
			sum.z = (z - rhs.z);
			sum.w = (w - rhs.w);

			return sum;
		}

		Vector4 operator*(float scale) const
		{
			return Vector4(x * scale, y * scale, z * scale, w * scale);
		}

		Vector4 operator/(float scale) const
		{
			if (scale == 0) {
				throw std::runtime_error("Cannot divide by 0");
			}

			return Vector4(x / scale, y / scale, z / scale, w / scale);
		}

		bool operator==(const Vector4& rhs) const
		{
			return IsEqual(rhs);
		}

		bool operator!=(const Vector4& rhs) const
		{
			return !(*this == rhs);
		}

		bool IsEqual(Vector4 rhs, float precision = constants::FLOAT_PRECISION) const
		{
			float xDist = fabsf(x - rhs.x);
			float yDist = fabsf(y - rhs.y);
			float zDist = fabsf(z - rhs.z);
			float wDist = fabsf(w - rhs.w);

			return  xDist < precision &&
				yDist < precision &&
				zDist < precision &&
				wDist < precision;
		}

		Vector4& operator+=(const Vector4& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		Vector4& operator-=(const Vector4& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		Vector4& operator*=(float& scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		float& operator[](int index)
		{
			return data[index];
		}

		float operator[](const int index) const
		{
			return data[index];
		}

		float Magnitude() const {
			return SqrtF(x * x + y * y + z * z + w * w);
		}

		void Normalise() {
			const float mag = Magnitude();

			if (mag == 0) {
				return;
			}

			x /= mag;
			y /= mag;
			z /= mag;
			w /= mag;
		}

		Vector4 Normalised() {
			Vector4 copy = *this;
			copy.Normalise();
			return copy;
		}

		float Dot(const Vector4& other) const {
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		Vector4 Cross(const Vector4& rhs) const
		{
			float a, b, c;
			a = (y * rhs.z) - (z * rhs.y);
			b = (z * rhs.x) - (x * rhs.z);
			c = (x * rhs.y) - (y * rhs.x);

			return Vector4(a, b, c, w);
		}


		std::string ToString() const
		{
			return std::string(std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w));
		}

	public:

		union {
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			float data[4];
		};

		friend Vector4 operator*(float lhs, Vector4 rhs)
		{
			return rhs * lhs;
		}

		friend float DotProduct(const Vector4& vec1, const Vector4& vec2)
		{
			float a, b, c, d;
			a = vec1[0] * vec2[0];
			b = vec1[1] * vec2[1];
			c = vec1[2] * vec2[2];
			d = vec1[3] * vec2[3];

			float total = a + b + c;
			total = total + d;

			return a + b + c + d;
		}
		
	};

	
}