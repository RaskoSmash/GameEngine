#include "mat4.h"
#include "vector4.h"
#include "mat3.h"
#include <math.h>

mat4 mat4::identity()
{
	mat4 c;
	c.c[0] = vec4{ 1,0,0,0 };
	c.c[1] = vec4{ 0,1,0,0 };
	c.c[2] = vec4{ 0,0,1,0 };
	c.c[3] = vec4{ 0,0,0,1 };
	return c;
}

mat4 mat4::rotate(const vec3 &a, float angle)
{
	mat4 c;
	vec3 _angle = a;
	_angle.normalise();
	float _cos = cosf(angle);
	float _sin = sinf(angle);
	float sinMinus1 = 1 - _sin;
	float cosMinus1 = 1 - _cos;

	c = c.identity();
	c.c[0] = vec4(_cos + ((_angle.x * _angle.x) * (cosMinus1))         , (_angle.x * _angle.y * cosMinus1) - (_angle.z * _sin),
				 (_angle.x * _angle.z * cosMinus1) + (_angle.y * _sin) , 0													 );

	c.c[1] = vec4((_angle.y * _angle.x * cosMinus1) + (_angle.z * _sin), (_cos + (_angle.y * _angle.y * cosMinus1))			  ,
				 ((_angle.y * _angle.z * cosMinus1)-(_angle.x * _sin)) , 0);

	c.c[2] = vec4((_angle.z * _angle.x * cosMinus1) - (_angle.y * _sin), (_angle.z * _angle.y * cosMinus1) + (_angle.x * _sin), 
				   _cos + (_angle.z * _angle.z * cosMinus1)			   , 0);

	c.c[3] = vec4(0,0,0,1);
	return c;
}

mat4 mat4::scale(const vec3 &xyz)
{
	mat4 c;
	c = c.identity();
	c.m[0][0] = xyz.x;
	c.m[1][1] = xyz.y;
	c.m[2][2] = xyz.z;
	return c;
}

mat4 mat4::translate(const vec3 & xyz)
{
	mat4 c;
	c = c.identity();
	c.m[0][3] = xyz.x;
	c.m[1][3] = xyz.y;
	c.m[2][3] = xyz.z;
	return c;
}

mat4 mat4::transpose()
{
	return mat4(m[0][0], m[1][0], m[2][0], m[3][0],
				m[0][1], m[1][1], m[2][1], m[3][1],
				m[0][2], m[1][2], m[2][2], m[3][2],
				m[0][3], m[1][3], m[2][3], m[3][3]);
}

mat4 mat4::inverse()
{
	mat4 c;
	float d = determinate();
	c = cofactor();
	c = c.transpose();

	return mat4(c.m[0][0] / d, c.m[0][1] / d, c.m[0][2] / d, c.m[0][3] / d, 
				c.m[1][0] / d, c.m[1][1] / d, c.m[1][2] / d, c.m[1][3] / d,
				c.m[2][0] / d, c.m[2][1] / d, c.m[2][2] / d, c.m[2][3] / d,
				c.m[3][0] / d, c.m[3][1] / d, c.m[3][2] / d, c.m[3][3] / d);
}

float mat4::determinate()
{
	mat3 a = mat3(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
	mat3 b = mat3(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
	mat3 c = mat3(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
	mat3 d = mat3(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

	return (m[0][0] * a.determinate()) - (m[0][1] * b.determinate()) + (m[0][2] * c.determinate()) - (m[0][3] * d.determinate());
}

mat4 mat4::cofactor()
{
	mat3 a_11 = mat3(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
	mat3 a_12 = mat3(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
	mat3 a_13 = mat3(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
	mat3 a_14 = mat3(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

	mat3 a_21 = mat3(m[0][1], m[0][2], m[0][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
	mat3 a_22 = mat3(m[0][0], m[0][2], m[0][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
	mat3 a_23 = mat3(m[0][0], m[0][1], m[0][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
	mat3 a_24 = mat3(m[0][0], m[0][1], m[0][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

	mat3 a_31 = mat3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[3][1], m[3][2], m[3][3]);
	mat3 a_32 = mat3(m[0][0], m[0][2], m[0][3], m[1][0], m[1][2], m[1][3], m[3][0], m[3][2], m[3][3]);
	mat3 a_33 = mat3(m[0][0], m[0][1], m[0][3], m[1][0], m[1][1], m[1][3], m[3][0], m[3][1], m[3][3]);
	mat3 a_34 = mat3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[3][0], m[3][1], m[3][2]);

	mat3 a_41 = mat3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3]);
	mat3 a_42 = mat3(m[0][0], m[0][2], m[0][3], m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3]);
	mat3 a_43 = mat3(m[0][0], m[0][1], m[0][3], m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3]);
	mat3 a_44 = mat3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);

	return mat4( a_11.determinate(), -a_12.determinate(), a_13.determinate(), -a_14.determinate(),
				 -a_21.determinate(), a_22.determinate(), -a_23.determinate(), a_24.determinate(),
				 a_31.determinate(), -a_32.determinate(), a_33.determinate(), -a_34.determinate(),
				 -a_41.determinate(), a_42.determinate(), -a_43.determinate(), a_44.determinate());
}

mat4 & mat4::operator+=(const mat4 & b)
{
	return *this = mat4{ m[0][0] += b.m[0][0], m[0][1] += b.m[0][1], m[0][2] += b.m[0][2], m[0][3] += b.m[0][3],
						 m[1][0] += b.m[1][0], m[1][1] += b.m[1][1], m[1][2] += b.m[1][2], m[1][3] += b.m[1][3],
						 m[2][0] += b.m[2][0], m[2][1] += b.m[2][1], m[2][2] += b.m[2][2], m[2][3] += b.m[2][3], 
						 m[3][0] += b.m[3][0], m[3][1] += b.m[3][1], m[3][2] += b.m[3][2], m[3][3] += b.m[3][3]};
}

mat4 & mat4::operator-=(const mat4 & b)
{
	return *this = mat4{ m[0][0] -= b.m[0][0], m[0][1] -= b.m[0][1], m[0][2] -= b.m[0][2], m[0][3] -= b.m[0][3],
						 m[1][0] -= b.m[1][0], m[1][1] -= b.m[1][1], m[1][2] -= b.m[1][2], m[1][3] -= b.m[1][3],
						 m[2][0] -= b.m[2][0], m[2][1] -= b.m[2][1], m[2][2] -= b.m[2][2], m[2][3] -= b.m[2][3],
						 m[3][0] -= b.m[3][0], m[3][1] -= b.m[3][1], m[3][2] -= b.m[3][2], m[3][3] -= b.m[3][3] };
}

mat4 & mat4::operator*=(const mat4 & b)
{
	return *this = mat4{  m[0][0] * b.m[0][0] +  m[0][1] * b.m[1][0] +  m[0][2] * b.m[2][0] +  m[0][3] * b.m[3][0],
						  m[0][0] * b.m[0][1] +  m[0][1] * b.m[1][1] +  m[0][2] * b.m[2][1] +  m[0][3] * b.m[3][1],
						  m[0][0] * b.m[0][2] +  m[0][1] * b.m[1][2] +  m[0][2] * b.m[2][2] +  m[0][3] * b.m[3][2],
						  m[0][0] * b.m[0][3] +  m[0][1] * b.m[1][3] +  m[0][2] * b.m[2][3] +  m[0][3] * b.m[3][3],

						  m[1][0] * b.m[0][0] +  m[1][1] * b.m[1][0] +  m[1][2] * b.m[2][0] +  m[1][3] * b.m[3][0],
						  m[1][0] * b.m[0][1] +  m[1][1] * b.m[1][1] +  m[1][2] * b.m[2][1] +  m[1][3] * b.m[3][1],
						  m[1][0] * b.m[0][2] +  m[1][1] * b.m[1][2] +  m[1][2] * b.m[2][2] +  m[1][3] * b.m[3][2],
						  m[1][0] * b.m[0][3] +  m[1][1] * b.m[1][3] +  m[1][2] * b.m[2][3] +  m[1][3] * b.m[3][3],

						  m[2][0] * b.m[0][0] +  m[2][1] * b.m[1][0] +  m[2][2] * b.m[2][0] +  m[2][3] * b.m[3][0],
						  m[2][0] * b.m[0][1] +  m[2][1] * b.m[1][1] +  m[2][2] * b.m[2][1] +  m[2][3] * b.m[3][1],
						  m[2][0] * b.m[0][2] +  m[2][1] * b.m[1][2] +  m[2][2] * b.m[2][2] +  m[2][3] * b.m[3][2],
						  m[2][0] * b.m[0][3] +  m[2][1] * b.m[1][3] +  m[2][2] * b.m[2][3] +  m[2][3] * b.m[3][3],

						  m[3][0] * b.m[0][0] +  m[3][1] * b.m[1][0] +  m[3][2] * b.m[2][0] +  m[3][3] * b.m[3][0],
						  m[3][0] * b.m[0][1] +  m[3][1] * b.m[1][1] +  m[3][2] * b.m[2][1] +  m[3][3] * b.m[3][1],
						  m[3][0] * b.m[0][2] +  m[3][1] * b.m[1][2] +  m[3][2] * b.m[2][2] +  m[3][3] * b.m[3][2],
						  m[3][0] * b.m[0][3] +  m[3][1] * b.m[1][3] +  m[3][2] * b.m[2][3] +  m[3][3] * b.m[3][3]};
}

mat4 & operator+(const mat4 &a, const mat4 &b)
{
	mat4 c = mat4{ a.m[0][0] + b.m[0][0], a.m[0][1] + b.m[0][1], a.m[0][2] + b.m[0][2], a.m[0][3] + b.m[0][3],
				   a.m[1][0] + b.m[1][0], a.m[1][1] + b.m[1][1], a.m[1][2] + b.m[1][2], a.m[1][3] + b.m[1][3],
				   a.m[2][0] + b.m[2][0], a.m[2][1] + b.m[2][1], a.m[2][2] + b.m[2][2], a.m[2][3] + b.m[2][3],
				   a.m[3][0] + b.m[3][0], a.m[3][1] + b.m[3][1], a.m[3][2] + b.m[3][2], a.m[3][3] + b.m[3][3] };
	return c;
}

mat4 & operator-(const mat4 &a, const mat4 &b)
{
	mat4 c = mat4{ a.m[0][0] - b.m[0][0], a.m[0][1] - b.m[0][1], a.m[0][2] - b.m[0][2], a.m[0][3] - b.m[0][3],
				   a.m[1][0] - b.m[1][0], a.m[1][1] - b.m[1][1], a.m[1][2] - b.m[1][2], a.m[1][3] - b.m[1][3],
				   a.m[2][0] - b.m[2][0], a.m[2][1] - b.m[2][1], a.m[2][2] - b.m[2][2], a.m[2][3] - b.m[2][3],
				   a.m[3][0] - b.m[3][0], a.m[3][1] - b.m[3][1], a.m[3][2] - b.m[3][2], a.m[3][3] - b.m[3][3] };
	return c;
}

mat4 & operator*(const mat4 &a, const mat4 &b)
{
	mat4 c;
	c.c[0] = vec4(a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0] + a.m[0][3] * b.m[3][0],
				  a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1] + a.m[0][3] * b.m[3][1], 
				  a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2] + a.m[0][3] * b.m[3][2], 
				  a.m[0][0] * b.m[0][3] + a.m[0][1] * b.m[1][3] + a.m[0][2] * b.m[2][3] + a.m[0][3] * b.m[3][3]);

	c.c[1] = vec4(a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0] + a.m[1][3] * b.m[3][0],
				  a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1] + a.m[1][3] * b.m[3][1],
			   	  a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2] + a.m[1][3] * b.m[3][2],
				  a.m[1][0] * b.m[0][3] + a.m[1][1] * b.m[1][3] + a.m[1][2] * b.m[2][3] + a.m[1][3] * b.m[3][3]);

	c.c[2] = vec4(a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0] + a.m[2][3] * b.m[3][0],
				  a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1] + a.m[2][3] * b.m[3][1],
				  a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2] + a.m[2][3] * b.m[3][2],
				  a.m[2][0] * b.m[0][3] + a.m[2][1] * b.m[1][3] + a.m[2][2] * b.m[2][3] + a.m[2][3] * b.m[3][3]);

	c.c[3] = vec4(a.m[3][0] * b.m[0][0] + a.m[3][1] * b.m[1][0] + a.m[3][2] * b.m[2][0] + a.m[3][3] * b.m[3][0],
				  a.m[3][0] * b.m[0][1] + a.m[3][1] * b.m[1][1] + a.m[3][2] * b.m[2][1] + a.m[3][3] * b.m[3][1],
				  a.m[3][0] * b.m[0][2] + a.m[3][1] * b.m[1][2] + a.m[3][2] * b.m[2][2] + a.m[3][3] * b.m[3][2],
				  a.m[3][0] * b.m[0][3] + a.m[3][1] * b.m[1][3] + a.m[3][2] * b.m[2][3] + a.m[3][3] * b.m[3][3]);
	return c;
}

vec4 operator*(const mat4 &a, const vec4 &b)
{
	
	return vec4(a.m[0][0] * b.x + a.m[0][1] * b.y + a.m[0][2] * b.z + a.m[0][3] * b.w, 
				a.m[1][0] * b.x + a.m[1][1] * b.y + a.m[1][2] * b.z + a.m[1][3] * b.w, 
				a.m[2][0] * b.x + a.m[2][1] * b.y + a.m[2][2] * b.z + a.m[2][3] * b.w,
				a.m[3][0] * b.x + a.m[3][1] * b.y + a.m[3][2] * b.z + a.m[3][3] * b.w);
}

vec4 operator*(const vec4 &a, const mat4 &b)
{
	return vec4(b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.z + b.m[0][3] * a.w,
				b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.z + b.m[1][3] * a.w,
				b.m[2][0] * a.x + b.m[2][1] * a.y + b.m[2][2] * a.z + b.m[2][3] * a.w,
				b.m[3][0] * a.x + b.m[3][1] * a.y + b.m[3][2] * a.z + b.m[3][3] * a.w);
}

mat4 OthroProjection(float right, float left, float top, float bottom, float far, float near)
{
	return mat4(2 / (right - left), 0, 0, 0,
		0, 2 / (top - bottom), 0, 0,
		0, 0, -2 / (far - near), 0,
		-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1);
}

