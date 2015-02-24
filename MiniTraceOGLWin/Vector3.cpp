/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
*
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#include <math.h>
#include "Vector3.h"

double Vector3::operator [] (const int i) const
{
	return m_element[i];
}

double& Vector3::operator [] (const int i)
{
	return m_element[i];
}

Vector3 Vector3::operator + (const Vector3& rhs) const
{
	return Vector3(
		(*this)[0] + rhs[0],
		(*this)[1] + rhs[1],
		(*this)[2] + rhs[2]);
}

Vector3 Vector3::operator - (const Vector3& rhs) const
{
	return Vector3(
		(*this)[0] - rhs[0],
		(*this)[1] - rhs[1],
		(*this)[2] - rhs[2]);
}

Vector3& Vector3::operator = (const Vector3& rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
	m_element[2] = rhs[2];
	return *this;
}

Vector3 Vector3::operator * (const Vector3& rhs) const
{
	return Vector3(
		m_element[0] * rhs[0],
		m_element[1] * rhs[1],
		m_element[2] * rhs[2]);
}

Vector3 Vector3::operator * (double scale) const
{
	return Vector3(
		m_element[0] * scale,
		m_element[1] * scale,
		m_element[2] * scale
		);
}

double Vector3::Norm() const
{
	return sqrtf(m_element[0] * m_element[0] + m_element[1] * m_element[1] + m_element[2] * m_element[2]);
}

double Vector3::Norm_Sqr() const
{
	return m_element[0] * m_element[0] + m_element[1] * m_element[1] + m_element[2] * m_element[2];
}

double Vector3::DotProduct(const Vector3& rhs) const
{
	return m_element[0] * rhs[0] + m_element[1] * rhs[1] + m_element[2] * rhs[2];
}

Vector3 Vector3::Normalise()
{
	double length = this->Norm();

	if (length > 1.0e-8f)
	{
		double invLen = 1.0f / length;

		m_element[0] *= invLen;
		m_element[1] *= invLen;
		m_element[2] *= invLen;
	}

	return *this;
}

Vector3 Vector3::CrossProduct(const Vector3& rhs) const
{
	return Vector3(
		(m_element[1] * rhs[2] - m_element[2] * rhs[1]),
		(m_element[2] * rhs[0] - m_element[0] * rhs[2]),
		(m_element[0] * rhs[1] - m_element[1] * rhs[0])
		);
}

Vector3 Vector3::Reflect(const Vector3& n) const
{
	Vector3 result;
	Vector3 self = *(this);
	
	//TODO: Calculate the reflection of this vector given the input normal n
	//Store the result in result

	result = n * 2 * self.DotProduct(n) - self;
	
	return result;
}

Vector3 Vector3::Refract(const Vector3& n, double r_coeff) const
{
	Vector3 result;
	Vector3 self = *(this);
	
	//TODO: Calculate the refraction of this vector given the input normal n and the refractive coefficient r_index
	//Store the result in result
	//Refraction is governed by the Snell's law

	float r = 1.0f / r_coeff;

	float cosI = -1.0f * n.DotProduct(self);
	float cosT2 = 1.0f - r * r * (1.0f - cosI - cosI);

	if (cosT2 < 0)
	{
		result.SetZero();
		return result;
	}

	result = (self * r) = (n * (r * cosI - sqrtf(cosT2)));
	result.Normalise();

	return result;
}

void Vector3::SetZero()
{
	m_element[0] = m_element[1] = m_element[2] = 0.0f;
}
