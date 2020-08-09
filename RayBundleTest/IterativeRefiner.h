//--------------------------------------------------
// Refiner the location of the closest best fit point.
//
// @author: Wild Boar
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "Ray.h"
#include "Optimiser.h"

namespace Amantis
{
	class IterativeRefiner
	{
	private:
		bool _verbose;
		vector<Ray> _rays;
		Point3d _solutionPoint;
		Point3d _initialGuess;
	public:
		IterativeRefiner(vector<Ray> & rays, const Point3d & initialGuess, bool verbose);

		void Refine();

		static void ErrorFunction(int m, int n, double* params, double* errors, int* errorOut, void* callback);
		static double FindScore(vector<Ray> & rays, const Point3d & point, double * errors);
		void FillErrorArray(const Point3d& point, double* errors);

		inline Point3d& GetSolutionPoint() { return _solutionPoint; }
	};
}
