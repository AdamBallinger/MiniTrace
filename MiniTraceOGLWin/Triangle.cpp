/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
* 
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#include "Triangle.h"

Triangle::Triangle()
{
	m_vertices[0] = Vector3(-1.0, 0.0, -5.0);
	m_vertices[1] = Vector3(0.0, 1.0, -5.0);
	m_vertices[2] = Vector3(1.0, 0.0, -5.0);
	m_normal = Vector3(0.0, 0.0, 1.0);
	m_primtype = PRIMTYPE_Triangle;
}

Triangle::Triangle(Vector3 pos1, Vector3 pos2, Vector3 pos3)
{
	SetTriangle(pos1, pos2, pos3);

	m_primtype = PRIMTYPE_Triangle;
}


Triangle::~Triangle()
{
}

void Triangle::SetTriangle(Vector3 v0, Vector3 v1, Vector3 v2)
{
	m_vertices[0] = v0;
	m_vertices[1] = v1;
	m_vertices[2] = v2;

	//Calculate Normal
	Vector3 NormalA = m_vertices[1] - m_vertices[0];
	Vector3 NormalB = m_vertices[2] - m_vertices[0];
	Vector3 Norm = NormalA.CrossProduct(NormalB);
	Norm.Normalise();
	m_normal = Norm;
}


RayHitResult Triangle::IntersectByRay(Ray& ray)
{
	RayHitResult result = Ray::s_defaultHitResult;
	double t = FARFAR_AWAY;
	Vector3 intersection_point;
	
	// TODO: Calculate the intersection between in the input ray and this triangle
	// If you have implemented ray-plane intersection, you have done half the work for ray-triangle intersection.
	// The remaining test is to check if the intersection point is inside the triangle
	//
	// Similar to the plane case, you should check if the ray is parallel to the triangle
	// and check if the ray intersects the triangle from the front or the back
	if (ray.GetRay().DotProduct(m_normal) < 0)
	{
		double d = -(m_vertices[0].DotProduct(m_normal));

		t = -(ray.GetRayStart().DotProduct(m_normal) + d) / ray.GetRay().DotProduct(m_normal);

		if (t <= 0.0f)
			return result;

		//Calculate the exact location of the intersection using the result of t
		intersection_point = ray.GetRayStart() + ray.GetRay() * t;

		// Calculate the barycentric coordinates of the intersection point
		Vector3 a = m_vertices[1] - m_vertices[0];
		Vector3 b = m_vertices[2] - m_vertices[0];
		Vector3 c = intersection_point - m_vertices[0];

		float aa = a.DotProduct(a);
		float ab = a.DotProduct(b);
		float bb = b.DotProduct(b);
		float ca = c.DotProduct(a);
		float cb = c.DotProduct(b);

		float denom = aa * bb - ab * ab;

		float v = (bb * ca - ab * cb) / denom;
		float w = (aa * cb - ab * ca) / denom;
		float u = 1.0f - v - w;

		if (v >= 0 && w >= 0 && u >= 0)
		{
			if (t > 0 && t < FARFAR_AWAY) { //ray intersection
				result.t = t;
				result.normal = this->m_normal;
				result.point = intersection_point;
				result.data = this;
				return result;
			}
		}
	}
		

	return result;
}
