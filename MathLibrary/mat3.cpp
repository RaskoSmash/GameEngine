#include "mat3.h"
#include "mat2.h"

mat3 &operator+(const mat3 &a, const mat3 &b)
{
	mat3 c = mat3{ a.m[0][0] + b.m[0][0], a.m[0][1] + b.m[0][1], a.m[0][2] + b.m[0][2],
					a.m[1][0] + b.m[1][0], a.m[1][1] + b.m[1][1], a.m[1][2] + b.m[1][2],
					a.m[2][0] + b.m[2][0], a.m[2][1] + b.m[2][1], a.m[2][2] + b.m[2][2] };
	return c;
}

mat3 &operator-(const mat3 &a, const mat3 &b)
{
	mat3 c = mat3{ a.m[0][0] - b.m[0][0], a.m[0][1] - b.m[0][1], a.m[0][2] - b.m[0][2],
					a.m[1][0] - b.m[1][0], a.m[1][1] - b.m[1][1], a.m[1][2] - b.m[1][2],
					 a.m[2][0] - b.m[2][0], a.m[2][1] - b.m[2][1], a.m[2][2] - b.m[2][2] };
	return c;
}

mat3 operator*(const mat3 &a, const mat3 &b)
{
	mat3 c; /* = mat3(a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0], a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1], a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2],
				  a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0], a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1], a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2],
				  a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0], a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1],	a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2]);*/

	c.c[0] = vec3(a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0], 
				  a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1], 
				  a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2]);

	c.c[1] = vec3(a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0], 
				  a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1],
				  a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2]);

	c.c[2] = vec3(a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0],
				  a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1],
				  a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2]);
		return c;
}

mat3 & mat3::operator+=(const mat3 & b)
{
	return *this = mat3{ m[0][0] += b.m[0][0], m[0][1] += b.m[0][1], m[0][2] += b.m[0][2],
						 m[1][0] += b.m[1][0], m[1][1] += b.m[1][1], m[1][2] += b.m[1][2],
						 m[2][0] += b.m[2][0], m[2][1] += b.m[2][1], m[2][2] += b.m[2][2] };
}

mat3 & mat3::operator-=(const mat3 & b)
{
	return *this = mat3{ m[0][0] += b.m[0][0], m[0][1] += b.m[0][1], m[0][2] += b.m[0][2],
						 m[1][0] += b.m[1][0], m[1][1] += b.m[1][1], m[1][2] += b.m[1][2],
						 m[2][0] += b.m[2][0], m[2][1] += b.m[2][1], m[2][2] += b.m[2][2] };
}

mat3 & mat3::operator*=(const mat3 & b)
{
	return *this = mat3{ m[0][0] * b.m[0][0] + m[0][1] * b.m[1][0] + m[0][2] * b.m[2][0],
						 m[0][0] * b.m[0][1] + m[0][1] * b.m[1][1] + m[0][2] * b.m[2][1],
						 m[0][0] * b.m[0][2] + m[0][1] * b.m[1][2] + m[0][2] * b.m[2][2],

						 m[1][0] * b.m[0][0] + m[1][1] * b.m[1][0] + m[1][2] * b.m[2][0],
						 m[1][0] * b.m[0][1] + m[1][1] * b.m[1][1] + m[1][2] * b.m[2][1],
						 m[1][0] * b.m[0][2] + m[1][1] * b.m[1][2] + m[1][2] * b.m[2][2],

						 m[2][0] * b.m[0][0] + m[2][1] * b.m[1][0] + m[2][2] * b.m[2][0],
						 m[2][0] * b.m[0][1] + m[2][1] * b.m[1][1] + m[2][2] * b.m[2][1],
						 m[2][0] * b.m[0][2] + m[2][1] * b.m[1][2] + m[2][2] * b.m[2][2] };
}

mat3 mat3::rotate(float b)
{
	mat3 c;
	c = c.identity();
	c.c[0] = vec3(cos(b), sin(b), 0);
	c.c[1] = vec3(-sin(b), cos(b), 0);
	return c;
}

mat3 mat3::translate(const vec2 &xy)
{
	mat3 c;
	c = c.identity();
	c.m[0][2] = xy.x;
	c.m[1][2] = xy.y;
	return c;
}

mat3 mat3::scale(const vec2 &xy)
{
	mat3 c;
	c = c.identity();
	c.m[0][0] = xy.x;
	c.m[1][1] = xy.y;
	return c;
}

mat3 mat3::transpose()
{
	/*mat3 c;
	c.c[0] = vec3(m[0][0], m[1][0], m[2][0]);
	c.c[1] = vec3(m[0][1], m[1][1], m[2][1]);
	c.c[2] = vec3(m[0][2], m[1][2], m[2][2]);
	return c;*/
	return mat3(m[0][0], m[1][0], m[2][0],
		m[0][1], m[1][1], m[2][1],
		m[0][2], m[1][2], m[2][2]);
}

mat3 mat3::inverse()
{
	mat3 c;
	float d = determinate();
	c = cofactor();
	c = c.transpose();

	return mat3(c.m[0][0] / d, c.m[0][1] / d, c.m[0][2] / d, 
				c.m[1][0] / d, c.m[1][1] / d, c.m[1][2] / d, 
				c.m[2][0] / d, c.m[2][1] / d, c.m[2][2] / d);
}

float mat3::determinate()
{
	mat2 a = mat2(m[1][1], m[1][2], m[2][1], m[2][2]);
	mat2 b = mat2(m[1][0], m[1][2], m[2][0], m[2][2]);
	mat2 c = mat2(m[1][0], m[1][1], m[2][0], m[2][1]);
	return (m[0][0] * a.determinate()) - (m[0][1] * b.determinate()) + (m[0][2] * c.determinate());
}

mat3 mat3::cofactor()
{
	mat2 a_11 = mat2(m[1][1], m[1][2], m[2][1], m[2][2]);
	mat2 a_12 = mat2(m[1][0], m[1][2], m[2][0], m[2][2]);
	mat2 a_13 = mat2(m[1][0], m[1][1], m[2][0], m[2][1]);

	mat2 a_21 = mat2(m[0][1], m[0][2], m[2][1], m[2][2]);
	mat2 a_22 = mat2(m[0][0], m[0][2], m[2][0], m[2][2]);
	mat2 a_23 = mat2(m[0][0], m[0][1], m[2][0], m[2][1]);

	mat2 a_31 = mat2(m[0][1], m[0][2], m[1][1], m[1][2]);
	mat2 a_32 = mat2(m[0][0], m[0][2], m[1][0], m[1][2]);
	mat2 a_33 = mat2(m[0][0], m[0][1], m[1][0], m[1][1]);

	return  mat3(	a_11.determinate(),	  (-a_12.determinate()),	a_13.determinate(),
				  (-a_21.determinate()),	a_22.determinate(),	  (-a_23.determinate()),
					a_31.determinate(),	  (-a_32.determinate()),	a_33.determinate());
}

mat3 mat3::identity()
{
	mat3 c;
	c.c[0] = vec3{ 1,0,0 };
	c.c[1] = vec3{ 0,1,0 };
	c.c[2] = vec3{ 0,0,1 };
	return c;
}

vec3 operator*(const mat3 &a, const vec3 &b)
{
	vec3 c;
	c.x = a.m[0][0] * b.x + a.m[0][1] * b.y + a.m[0][2] * b.z;
	c.y = a.m[1][0] * b.x + a.m[1][1] * b.y + a.m[1][2] * b.z;
	c.z = a.m[2][0] * b.x + a.m[2][1] * b.y + a.m[2][2] * b.z;
	return c;
}

vec3 operator*(const vec3 &a, const mat3 &b)
{
	vec3 c;
	c.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.z;
	c.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.z;
	c.z = b.m[2][0] * a.x + b.m[2][1] * a.y + b.m[2][2] * a.z;
	return c;
}

/*bool operator==(const mat3 &l, const mat3 &r)
{ 
	if (l.m[0][0] == r.m[0][0], l.m[0][1] == r.m[0][1], l.m[0][2] == r.m[0][2],
		l.m[1][0] == r.m[1][0], l.m[1][1] == r.m[1][1], l.m[1][2] == r.m[1][2],
		l.m[2][0] == r.m[2][0], l.m[0][0] == r.m[2][1], l.m[2][2] == r.m[2][2])
	{
		return true;
	}
	else return false;
}*/