//--------------------------------------------------
// Implementation code for IterativeRefiner
//
// @author: Wild Boar
//--------------------------------------------------

#include "IterativeRefiner.h"
using namespace Amantis;

//--------------------------------------------------
// Constructors
//--------------------------------------------------

/**
 * Main Constructor
 * @param rays The input set of rays
 */
IterativeRefiner::IterativeRefiner(vector<Ray> & rays, const Point3d& initialGuess, bool verbose = false)
{
	for (auto ray : rays) _rays.push_back(ray); _solutionPoint = _initialGuess = initialGuess; 
	_verbose = verbose;
}

//--------------------------------------------------
// Optimization
//--------------------------------------------------

/**
 * Trigger the refinement
 */
void IterativeRefiner::Refine()
{
	// Reset the solution Point
	_solutionPoint = _initialGuess;

	// Setup the optimizer
	auto m = (int)_rays.size(); double x[3] = { 0, 0, 0 }; int mask[3] = { 1, 1, 1 }; double* fvec = new double[m]; int info, nfev;

	// Perform Optimization
	auto optimizer = Optimiser(this); optimizer.Refine(ErrorFunction, m, 3, x, mask, fvec, 1.0e-10, &info, &nfev);

	// Retrieve the result
	_solutionPoint = Point3d{ x[0], x[1], x[2] };

	// Free working variables
	delete[] fvec;
}

//--------------------------------------------------
// Score
//--------------------------------------------------

/**
 * Find the "spread" that a given set of rays have wrt a given point
 * @param rays The rays that we are passing into the system
 * @param point The point that we are testing against
 * @param errors An array of individual errors for each ray
 * @return Return a double
 */
double IterativeRefiner::FindScore(vector<Ray> & rays, const Point3d & point, double * errors)
{
	auto counter = 0; auto total = 0.0;

	for (auto ray : rays) 
	{
		// Find the magnitude of the component that the point is on the line
		auto pointComponentDistance = (point - ray.GetStart()).dot(ray.GetDirection());

		// Find the magnitude of the full distance to the point
		auto xDiff = (point.x - ray.GetStart().x);
		auto YDiff = (point.y - ray.GetStart().y);
		auto ZDiff = (point.z - ray.GetStart().z);
		auto pointDistance = xDiff * xDiff + YDiff * YDiff + ZDiff * ZDiff;

		// Calculate the error
		auto error = pointDistance - (pointComponentDistance * pointComponentDistance);

		// Assign the errors
		if (errors != nullptr) total += errors[counter] = error;
		else total += error;

		// Update the counter
		counter++;
	}

	return total / counter;
}

/**
 * Static callback function for the optimisation method
 * @param m The amount of data elements that we are using
 * @param n The number of parameters that we are working with
 * @param params The actual values of the parameters
 * @param errors The vector of errors
 * @param errorOUt The out vector
 * @param callback method
 */
void IterativeRefiner::ErrorFunction(int m, int n, double* params, double* errors, int* errorOut, void* callback)
{
	IterativeRefiner* refiner = (IterativeRefiner*)callback;
	refiner->FillErrorArray(Point3d(params[0], params[1], params[2]), errors);
}

/**
 * Fill a given array of errors
 * @param point The point that we are currently have
 * @param errors The list of errors that we are processing
 */
void IterativeRefiner::FillErrorArray(const Point3d& point, double* errors) 
{
	auto error = FindScore(_rays, point, errors);
	if (_verbose) cout << "ERROR: " << error << endl;
}
