#pragma once
#include "Helpers.h"

namespace MathClasses
{

	class Matrix4 {
	public:

		Matrix4::Matrix4()
		{
			for (int i = 0; i < 16; ++i) {
				m[i] = 0.0f;
			}
		}

		Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
		{
			//X axis
			this->m00 = m00;
			this->m10 = m01;
			this->m20 = m02;
			this->m30 = m03;

			//Y axis
			this->m01 = m10;
			this->m11 = m11;
			this->m21 = m12;
			this->m31 = m13;

			//Z axis
			this->m02 = m20;
			this->m12 = m21;
			this->m22 = m22;
			this->m32 = m23;

			//local pos
			this->m03 = m30;
			this->m13 = m31;
			this->m23 = m32;
			this->m33 = m33;
		}

		Matrix4::Matrix4(float numbers[])
		{
			for (int i = 0; i < 16; ++i) {
				m[i] = numbers[i];
			}

		}

		Matrix4::operator float* () const
		{
			return const_cast<float*>(m);
		}

		Vector4 Matrix4::GetRow(int index) const
		{
			Vector4 vec;
			switch (index)
			{
			case 0:
				vec = Vector4(m00, m01, m02, m03);
				break;
			case 1:
				vec = Vector4(m10, m11, m12, m13);
				break;
			case 2:
				vec = Vector4(m20, m21, m22, m23);
				break;
			case 3:
				vec = Vector4(m30, m31, m32, m33);
				break;
			}
			return vec;
		}

		void Matrix4::SetScaled(float x, float y, float z) {
			// set scale of each axis
			xAxis = { x, 0, 0, 0 };
			yAxis = { 0, y, 0, 0 };
			zAxis = { 0, 0, z, 0 };
			translation = { 0, 0, 0, 1 };
		}

		void Matrix4::SetRotateX(float radians) {
			// leave X axis and elements unchanged
			xAxis = { 1, 0, 0, 0 };
			yAxis = { 0, cosf(radians), sinf(radians), 0 };
			zAxis = { 0, -sinf(radians), cosf(radians), 0 };
			translation = { 0, 0, 0, 1 };
		}

		void Matrix4::Translate(float x, float y, float z) {
			// apply vector offset
			translation += Vector4(x, y, z, 0);
		}

		friend bool operator==(Matrix4 rhs, Matrix4 lhs) {
			return lhs.IsEqual(rhs);
		}

		bool Matrix4::operator!=(const Matrix4& rhs)
		{
			return !(*this == rhs);
		}

		bool Matrix4::IsEqual(Matrix4 rhs, float precision = constants::FLOAT_PRECISION)
		{
			return (xAxis.IsEqual(rhs.xAxis, precision) &&
				yAxis.IsEqual(rhs.yAxis, precision) &&
				zAxis.IsEqual(rhs.zAxis, precision) &&
				translation.IsEqual(rhs.translation, precision));
		}

		// binary * operator
		Vector4 Matrix4::operator * (const Vector4& v) const {
			Vector4 result;

			result[0] = mm[0][0] * v[0] + mm[1][0] * v[1] +
				mm[2][0] * v[2] + mm[3][0] * v[3];

			result[1] = mm[0][1] * v[0] + mm[1][1] * v[1] +
				mm[2][1] * v[2] + mm[3][1] * v[3];

			result[2] = mm[0][2] * v[0] + mm[1][2] * v[1] +
				mm[2][2] * v[2] + mm[3][2] * v[3];

			result[3] = mm[0][3] * v[0] + mm[1][3] * v[1] +
				mm[2][3] * v[2] + mm[3][3] * v[3];
			return result;
		}

		// binary * operator
		Matrix4 Matrix4::operator*(const Matrix4& other) const {
			Matrix4 result;

			for (int r = 0; r < 4; ++r) {
				for (int c = 0; c < 4; ++c) {
					float v = 0.0f;
					for (int i = 0; i < 4; ++i) {
						v += mm[i][r] * other.mm[c][i];
					}
					result.mm[c][r] = v;
				}
			}
			return result;
		}

		float& Matrix4::operator[](int dim)
		{
			return m[dim];
		}

		const float& Matrix4::operator[](int dim) const
		{
			return m[dim];
		}

		std::string Matrix4::ToString() const
		{
			//make header
			std::string str = ("|   x    |    y   |    z   |    T   |\n|--------|--------|--------|--------| \n");


			for (int i = 0; i < 4; i++)
			{
				Vector4 row = GetRow(i);
				for (int j = 0; j < 4; j++)
				{
					str += "|" + std::to_string(row[j]);
				}
				str += "|\n";
			}
			return str;
		}


	public:

		union {
			struct { //ROW,COLUMN
				float m00, m10, m20, m30,//X axis
					m01, m11, m21, m31,//Y axis
					m02, m12, m22, m32,//Z axis
					m03, m13, m23, m33;//Translation
			};

			struct {
				Vector4 xAxis;
				Vector4 yAxis;
				Vector4 zAxis;
				Vector4 translation;
			};

			float m[16];
			float mm[4][4];
			Vector4 axis[4];
		};
	

		static const Matrix4 MakeIdentity()
		{
			Matrix4 identity;
			//xAxis
			identity.m00 = 1;
			identity.m10 = 0;
			identity.m20 = 0;
			identity.m30 = 0;

			//yAxis
			identity.m01 = 0;
			identity.m11 = 1;
			identity.m21 = 0;
			identity.m31 = 0;

			//zAxis
			identity.m02 = 0;
			identity.m12 = 0;
			identity.m22 = 1;
			identity.m32 = 0;

			//Local Position
			identity.m03 = 0;
			identity.m13 = 0;
			identity.m23 = 0;
			identity.m33 = 1;

			return identity;
		}

		static Matrix4 MakeRotateX(float r)
		{
			return Matrix4(1, 0, 0, 0,     //xAxis
				0, cosf(r), -sinf(r), 0, //yAxis
				0, sinf(r), cosf(r), 0, // zAxis
				0, 0, 0, 1);
		}
		//Param: r is radians
		static Matrix4 MakeRotateY(float r)
		{
			return Matrix4(cosf(r), 0, sinf(r), 0,  //xAxis
				0, 1, 0, 0,  //yAxis
				-sinf(r), 0, cosf(r), 0,	//zAxis
				0, 0, 0, 1);
		}
		//Param: r is radians
		static Matrix4 MakeRotateZ(float r)
		{
			return Matrix4(cosf(r), sinf(r), 0, 0, //xAxis
				-sinf(r), cosf(r), 0, 0, //yAxis
				0, 0, 1, 0, //zAxis
				0, 0, 0, 1);
		}

		static Matrix4 MakeEuler(float pitch, float yaw, float roll)
		{
			Matrix4 x = MakeRotateX(pitch);
			Matrix4 y = MakeRotateY(yaw);
			Matrix4 z = MakeRotateZ(roll);

			return (z * y * x);
		}
		static Matrix4 MakeEuler(Vector3 euler)
		{
			Matrix4 x = MakeRotateX(euler.x);
			Matrix4 y = MakeRotateY(euler.y);
			Matrix4 z = MakeRotateZ(euler.z);

			return (z * y * x);
		}

		static Matrix4 MakeScale(float xScale, float yScale, float zScale)
		{
			return Matrix4(xScale, 0, 0, 0,
							0, yScale, 0, 0,
							0, 0, zScale, 0,
							0, 0, 0, 1);
		}
		static Matrix4 MakeScale(Vector3 scale)
		{
			return MakeScale(scale.x, scale.y, scale.z);
		}

		static Matrix4 MakeTranslation(float dirX, float dirY, float dirZ) {

			return Matrix4(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				dirX, dirY, dirZ, 1);
		}

		static Matrix4 MakeTranslation(Vector3 dir) {
			return MakeTranslation(dir.x, dir.y, dir.z);
		}
	};
}