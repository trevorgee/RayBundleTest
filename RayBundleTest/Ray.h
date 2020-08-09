//--------------------------------------------------
// Defines a ray entity in 3D space.
//
// @author: Wild Boar
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

namespace Amantis
{
	class Ray
	{
	private:
		Point3d _start;
		Vec3d _direction;
	public:
		Ray(const Point3d & start, const Vec3d & direction);
		Ray(const Point3d& start, const Point3d& point);

		Point3d ProjectPoint(double magnitude);

		inline const Point3d & GetStart() { return _start; }
		inline const Vec3d & GetDirection() { return _direction; }
	};
}
