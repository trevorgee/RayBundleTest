//--------------------------------------------------
// Defines a basic engine for a vanilla C++ project.
//
// @author: Wild Boar
//--------------------------------------------------

#pragma once

#include <random>
#include <iostream>
using namespace std;

#include "Ray.h"
#include "RaySetPointUtil.h"
#include "IterativeRefiner.h"

namespace Amantis
{
	class Engine
	{
	public:
		Engine() { srand(time(NULL)); }
		void Run();
	private:
		void FillLines(vector<Ray>& rays);
		Point3d GetPoint(default_random_engine & generator, normal_distribution<double> & distribution);
	};
}