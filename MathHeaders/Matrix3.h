#pragma once
#include "Helpers.h"

namespace MathClasses
{
	class Matrix3 {
	public:

		Matrix3::Matrix3()
		{
			m00 = m01 = m02 = m10 = m11 = m12 = m20 = m21 = m22 = 0.0f;
		}

		Matrix3::Matrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
		{
			//X axis
			this->m00 = m00;
			this->m10 = m01;
			this->m20 = m02;

			//Y axis
			this->m01 = m10;
			this->m11 = m11;
			this->m21 = m12;

			//Z axis
			this->m02 = m20;
			this->m12 = m21;
			this->m22 = m22;

		}

		Matrix3::Matrix3(float numbers[])
		{
			for (int i = 0; i < 9; ++i) {
				m[i] = numbers[i];
			}

		}

		Matrix3 Matrix3::Transposed() const
		{
			return Matrix3(m00, m01, m02,
				m10, m11, m12,
				m20, m21, m22);
		}

		Vector3 Matrix3::GetRow(int index) const
		{
			Vector3 vec;
			switch (index)
			{
			case 0:
				vec = Vector3(m00, m01, m02);
				break;
			case 1:
				vec = Vector3(m10, m11, m21);
				break;
			case 2:
				vec = Vector3(m20, m21, m22);
				break;
			}
			return vec;
		}

		Matrix3::operator float* () const
		{
			return const_cast<float*>(m);
		}

		friend bool Matrix3::operator==(Matrix3 rhs, Matrix3 lhs)
		{
			return lhs.IsEqual(rhs);
		}

		bool Matrix3::operator!=(const Matrix3& rhs)
		{
			return !(*this == rhs);
		}

		bool Matrix3::IsEqual(Matrix3 rhs, float precision = constants::FLOAT_PRECISION)
		{
			for (int i = 0; i < 9; ++i) {
				if (m[i] - rhs[i] < precision) {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
		}

		Matrix3 Matrix3::operator*(Matrix3 rhs) const
		{
			// stores the return value
			Matrix3 result;
			// iterate through first matrix
			for (int i = 0; i < 3; ++i)
			{
				// current row from first matrix
				Vector3 row(mm[0][i], mm[1][i], mm[2][i]);

				// iterate through second matrix
				for (int j = 0; j < 3; ++j)
				{
					// dot each row with each column and assign to result matrix
					// result is calculated row-by-row
					result.mm[j][i] = row.Dot(rhs.axis[j]);
				}
			}

			return result;
		}

		Vector3 Matrix3::operator*(Vector3 rhs) const
		{
			return Vector3(
				Vector3(m00, m01, m02).Dot(rhs),
				Vector3(m10, m11, m12).Dot(rhs),
				Vector3(m20, m21, m22).Dot(rhs)
			);
		}

		float& Matrix3::operator[](int dim)
		{
			return m[dim];
		}

		const float& Matrix3::operator[](int dim) const
		{
			return m[dim];
		}

		std::string Matrix3::ToString() const
		{
			//make header
			std::string str = ("|   x    |    y   |    z   |\n|--------|--------|--------| \n");


			for (int i = 0; i < 3; i++)
			{
				Vector3 row = GetRow(i);
				for (int j = 0; j < 3; j++)
				{
					str += "|" + std::to_string(row[j]);
				}
				str += "|\n";
			}
			return str;
		}
	public:

		union {
			struct { // float mROW_COLUMN
				float m00, m10, m20, //X axis
					m01, m11, m21, //Y axis
					m02, m12, m22; //Z axis
			};
			struct {

				Vector3 xAxis;
				Vector3 yAxis;
				Vector3 zAxis;

			};
			float m[9];
			float mm[3][3];
			Vector3 axis[3];
		};


		static const Matrix3 MakeIdentity()
		{
			Matrix3 identity;
			//xAxis
			identity.m00 = 1;
			identity.m10 = 0;
			identity.m20 = 0;

			//yAxis
			identity.m01 = 0;
			identity.m11 = 1;
			identity.m21 = 0;

			//zAxis
			identity.m02 = 0;
			identity.m12 = 0;
			identity.m22 = 1;

			return identity;
		}

		static Matrix3 MakeRotateX(float r)
		{
			return Matrix3(1, 0, 0,     //xAxis
				0, cosf(r), -sinf(r), //yAxis
				0, sinf(r), cosf(r)); //zAxis
		}
		//Param: r is radians
		static Matrix3 MakeRotateY(float r)
		{
			return Matrix3(cosf(r), 0, sinf(r),  //xAxis
				0, 1, 0,     //yAxis
				-sinf(r), 0, cosf(r)); //zAxis
		}
		//Param: r is radians
		static Matrix3 MakeRotateZ(float r)
		{
			return Matrix3(cosf(r), sinf(r), 0, //xAxis
				-sinf(r), cosf(r), 0, //yAxis
				0, 0, 1);//zAxis
		}

		static Matrix3 MakeEuler(float pitch, float yaw, float roll)
		{
			Matrix3 x = MakeRotateX(pitch);
			Matrix3 y = MakeRotateY(yaw);
			Matrix3 z = MakeRotateZ(roll);

			return (z * y * x);
		}

		static Matrix3 MakeEuler(Vector3 euler) {

			return MakeEuler(euler.x, euler.y, euler.z);
		}

		static Matrix3 MakeScale(float xScale, float yScale, float zScale)
		{
			return Matrix3(xScale, 0, 0,
				0, yScale, 0,
				0, 0, zScale);
		}

		static Matrix3 MakeScale(float xScale, float yScale)
		{
			return MakeScale(xScale, yScale, 1);
		}


		static Matrix3 MakeScale(Vector3 scale)
		{
			return MakeScale(scale.x, scale.y, scale.z);
		}

		static Matrix3 MakeTranslation(float dirX, float dirY, float dirZ) {

			return Matrix3(1, 0, 0,
				0, 1, 0,
				dirX, dirY, dirZ);
		}

		static Matrix3 MakeTranslation(Vector3 dir) {
			return MakeTranslation(dir.x, dir.y, dir.z);
		}
	};
}