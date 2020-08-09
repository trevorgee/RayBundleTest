//--------------------------------------------------
// Implementation code for RaySetPointUtil
//
// @author: Wild Boar
//--------------------------------------------------

#include "RaySetPointUtil.h"
using namespace Amantis;

//--------------------------------------------------
// Convergence Calculation
//--------------------------------------------------

/**
 * Find the convergence point for a set of rays
 * @param rays The set of rays that we are calculating
 * @return Return a Point3D
 */
Point3d RaySetPointUtil::FindCPoint(vector<Ray> & rays)
{
	Mat A = Mat::zeros(3, 3, CV_64FC1); Vec3d b; auto Adata = (double*)A.data;

	for (auto ray : rays) 
	{
		for (auto row = 0; row < 3; row++) 
		{
			for (auto column = 0; column < 3; column++) 
			{
				auto index = column + row * 3;
				if (row == column) Adata[index]++;
				Adata[index] -= ray.GetDirection()[column] * ray.GetDirection()[row];
			}			
		}

		auto dotProduct = ray.GetStart().dot(ray.GetDirection());

		b[0] += ray.GetStart().x - ray.GetDirection()[0] * dotProduct;
		b[1] += ray.GetStart().y - ray.GetDirection()[1] * dotProduct;
		b[2] += ray.GetStart().z - ray.GetDirection()[2] * dotProduct;
	}

	Mat result; solve(A, b, result, DECOMP_LU); 

	return Point3d(((double *)result.data)[0], ((double*)result.data)[1], ((double*)result.data)[2]);
}

