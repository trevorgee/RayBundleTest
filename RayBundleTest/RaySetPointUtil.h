//--------------------------------------------------
// A utility that calculates the "convergence" point for a set of rays.
//
// @author: Wild Boar
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "Ray.h"

namespace Amantis
{
	class RaySetPointUtil
	{
	public:
		static Point3d FindCPoint(vector<Ray> & rays);
	};
}
