//--------------------------------------------------
// Implementation code for Ray
//
// @author: Wild Boar
//--------------------------------------------------

#include "Ray.h"
using namespace Amantis;

//--------------------------------------------------
// Constructors
//--------------------------------------------------

/**
 * Main Constructor
 * @param start The starting point of the ray
 * @param direction The direction of the ray
 */
Ray::Ray(const Point3d & start, const Vec3d & direction)
{
	auto magnitude = sqrt(direction[0] * direction[0] + direction[1] * direction[1] + direction[2] * direction[2]);
	_direction = Vec3d(direction[0] / magnitude, direction[1] / magnitude, direction[2] / magnitude);
	_start = start;
}

/**
 * Point Constructor
 * @param start The start point of the ray
 * @param end Some other point on the ray
 */
Ray::Ray(const Point3d& start, const Point3d& point)
{
	auto direction = Vec3d(point.x - start.x, point.y - start.y, point.z - start.z);
	auto magnitude = sqrt(direction[0] * direction[0] + direction[1] * direction[1] + direction[2] * direction[2]);
	_direction = Vec3d(direction[0] / magnitude, direction[1] / magnitude, direction[2] / magnitude);
	_start = start;
}

//--------------------------------------------------
// Project Point
//--------------------------------------------------

/**
 * Project Points down the ray
 * @param magnitude The magnitude to project by
 * @return Return a Point3d
 */
Point3d Ray::ProjectPoint(double magnitude)
{
	auto X = _start.x + magnitude * _direction[0];
	auto Y = _start.y + magnitude * _direction[1];
	auto Z = _start.z + magnitude * _direction[2];

	return Point3d(X, Y, Z);
}
