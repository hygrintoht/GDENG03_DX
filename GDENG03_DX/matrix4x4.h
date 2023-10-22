#pragma once

#include <memory>
#include "vector3.h"
#include "vector4.h"

class matrix4x4
{
public:
	matrix4x4()
	{
	}

	~matrix4x4()
	{
	}

	void setIdentity()
	{
		::memset(m_mat, 0, sizeof(float) * 16);
		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}
	// must update code for cube
	void setTranslation(const vector3& translation)
	{
		//setIdentity();
		m_mat[3][0] = translation.m_x;
		m_mat[3][1] = translation.m_y;
		m_mat[3][2] = translation.m_z;
	}
	// must update code for cube
	void setScale(const vector3& scale)
	{
		//setIdentity();
		m_mat[0][0] = scale.m_x;
		m_mat[1][1] = scale.m_y;
		m_mat[2][2] = scale.m_z;
	}

	void setRotationX(float x)
	{
		m_mat[1][1] = cos(x);
		m_mat[1][2] = sin(x);
		m_mat[2][1] = -sin(x);
		m_mat[2][2] = cos(x);
	}

	void setRotationY(float y)
	{
		m_mat[0][0] = cos(y);
		m_mat[0][2] = -sin(y);
		m_mat[2][0] = sin(y);
		m_mat[2][2] = cos(y);
	}

	void setRotationZ(float z)
	{
		m_mat[0][0] = cos(z);
		m_mat[0][1] = sin(z);
		m_mat[1][0] = -sin(z);
		m_mat[1][1] = cos(z);
	}

	void setRotation(const vector3& rotation) //note: xyz rotation
	{
		int x = rotation.m_x;
		int y = rotation.m_y;
		int z = rotation.m_z;

		m_mat[0][0] = cos(y) * cos(z);
		m_mat[0][1] = cos(y) * sin(z);
		m_mat[0][2] = sin(y) * -1;
		m_mat[1][0] = sin(x) * sin(y) * cos(z) - cos(x) * sin(z);
		m_mat[1][1] = sin(x) * sin(y) * sin(z) + cos(x) * cos(z);
		m_mat[1][2] = sin(x) * cos(y);
		m_mat[2][0] = cos(x) * sin(y) * cos(z) + sin(x) * sin(z);
		m_mat[2][1] = cos(x) * sin(y) * sin(z) - sin(x) * cos(z);
		m_mat[2][2] = cos(x) * cos(y);
	}

	float getDeterminant()
	{
		vector4 v1 = vector4(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
		vector4 v2 = vector4(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
		vector4 v3 = vector4(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);

		vector4 minor;
		minor.cross(v1, v2, v3);
		float determinant = 
				  this->m_mat[0][3] * minor.m_x 
				+ this->m_mat[1][3] * minor.m_y 
				+ this->m_mat[2][3] * minor.m_z 
				+ this->m_mat[3][3] * minor.m_w;
		determinant *= -1;
		return determinant;
	}

	void inverse()
	{
		int a, i, j;
		matrix4x4 out;
		vector4 v, vec[3];
		float determinant = 0.0f;

		determinant = this->getDeterminant();
		if (!determinant) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].m_x = (this->m_mat[j][0]);
					vec[a].m_y = (this->m_mat[j][1]);
					vec[a].m_z = (this->m_mat[j][2]);
					vec[a].m_w = (this->m_mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_mat[0][i] = pow(-1.0f, i) * v.m_x / determinant;
			out.m_mat[1][i] = pow(-1.0f, i) * v.m_y / determinant;
			out.m_mat[2][i] = pow(-1.0f, i) * v.m_z / determinant;
			out.m_mat[3][i] = pow(-1.0f, i) * v.m_w / determinant;
		}

		this->setMatrix(out);
	}

	void operator *=(const matrix4x4& matrix)
	{
		matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.m_mat[i][j] =
					  m_mat[i][0] * matrix.m_mat[0][j]
					+ m_mat[i][1] * matrix.m_mat[1][j]
					+ m_mat[i][2] * matrix.m_mat[2][j]
					+ m_mat[i][3] * matrix.m_mat[3][j];
			}
		}
		setMatrix(out);
	}

	void setMatrix(const matrix4x4& matrix)
	{
		::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
	}

	vector3 getZDirection()
	{
		return vector3(m_mat[2][0], m_mat[2][1], m_mat[2][2]);
	}
	vector3 getXDirection()
	{
		return vector3(m_mat[0][0], m_mat[0][1], m_mat[0][2]);
	}
	vector3 getTranslation()
	{
		return vector3(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
	}

	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
		float yscale = 1.0f / tan(fov / 2.0f);
		float xscale = yscale / aspect;
		m_mat[0][0] = xscale;
		m_mat[1][1] = yscale;
		m_mat[2][2] = zfar / (zfar - znear);
		m_mat[2][3] = 1.0f;
		m_mat[3][2] = (-znear * zfar) / (zfar - znear);
	}

	void setOrthoLH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();
		m_mat[0][0] = 2.0f / width;
		m_mat[1][1] = 2.0f / height;
		m_mat[2][2] = 1.0f / (far_plane - near_plane);
		m_mat[3][2] = -(near_plane / (far_plane - near_plane));
	}

	static matrix4x4 identityMatrix()
	{
		matrix4x4 temp;
		temp.setIdentity();
		return temp;
	}

	float m_mat[4][4] = {};
};