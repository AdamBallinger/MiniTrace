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
#include "Sphere.h"

#include <stdio.h>

Sphere::Sphere()
{
	//the default sphere is centred around the origin of the world coordinate
	//default radius is 2.0

	m_centre.SetZero();
	m_radius = 2.0;
	m_primtype = PRIMTYPE_Sphere;
}

Sphere::Sphere(double x, double y, double z, double r)
{
	m_centre.SetVector(x, y, z);
	m_radius = r;
	m_primtype = PRIMTYPE_Sphere;
}

Sphere::~Sphere()
{
}

RayHitResult Sphere::IntersectByRay(Ray& ray)
{
	RayHitResult result = Ray::s_defaultHitResult;

	double t = FARFAR_AWAY;
	Vector3 normal;
	Vector3 intersection_point;

	//TODO: Calculate the intersection between the input ray and this sphere
	// Store the parametric result in t
	// The algebraic form of a sphere is  (x - cx)^2 + (y - cy)^2 + (z - cz)^2 = r^2 where
	// (x,y,z) is a point on the sphere
	// (cx, cy, cz) is the centre of the sphere.,i.e. m_centre
	// r is the radius of the sphere
	//
	// Note, the solution to ray-sphere intersection is the root(s) of a quadratic equation
	// therefore, there will be three scenarios
	// 1. Two real roots, the ray intersects the sphere twice. In this case, we are only interested in the closest intersection
	// 2. One real root, the ray tangentially intersects the sphere
	// 3. No real root, no intersection

	//float a = -ray.GetRay().DotProduct(ray.GetRayStart() - m_centre);
	//float b = ray.GetRay().DotProduct(ray.GetRayStart() - m_centre);
	//float c = ray.GetRay().DotProduct(ray.GetRay()) * ((ray.GetRayStart() - m_centre).DotProduct(ray.GetRayStart() - m_centre) - (m_radius * m_radius));

	//t = (a * sqrt((b * b) - c) / ray.GetRay().DotProduct(ray.GetRay()));

	Vector3 ray_distance = ray.GetRayStart() - m_centre;

	float b = -ray_distance.DotProduct(ray.GetRay());

	t = (b * b) - ray_distance.DotProduct(ray_distance) + (m_radius * m_radius);

	if (t > 0)
	{
		// Find smallest root (First intersection).
		float t_sqrt = sqrtf(t);
		float t0 = (b + t_sqrt);
		float t1 = (b - t_sqrt);

		// Sets t equal to the first intersection of the sphere (smallest root)
		t = t0 <= t1 ? t0 : t1;		
	}

	//Calculate the exact location of the intersection using the result of t
	intersection_point = ray.GetRayStart() + ray.GetRay() * t;

	//TODO: Calculate normal
	//Normals vary across the surface of a sphere
	//You need to calculate the normal based on the location of the intersection

	normal = (intersection_point - m_centre);


	if (t>0.0 && t < FARFAR_AWAY)
	{
		result.t = t;
		result.data = this;
		result.point = intersection_point;
		result.normal = normal.Normalise();
	}

	return result;
}
