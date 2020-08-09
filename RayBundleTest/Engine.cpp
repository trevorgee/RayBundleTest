//--------------------------------------------------
// Implementation code for Engine
//
// @author: Wild Boar
//--------------------------------------------------

#include "Engine.h"
using namespace Amantis;

//--------------------------------------------------
// Execution Entry Point
//--------------------------------------------------

/**
 * Entry point function
 */
void Engine::Run()
{
    // Construct the rays
    cout << "Setting up Test Rays...";
    auto rays = vector<Ray>(); FillLines(rays);
    cout << "Done!" << endl << endl;

    // Attempt to use the Levenberg-Marquardt approach to find the best point
    cout << "Using LM to refine best point..." << endl;
    auto start = getTickCount();
    auto refiner = IterativeRefiner(rays, Point3d(10, 10, 10), false); refiner.Refine();
    auto end = getTickCount();    
    auto score1 = refiner.FindScore(rays, refiner.GetSolutionPoint(), nullptr);
    cout << "Done! Best point is at: [" << refiner.GetSolutionPoint().x << ", " << refiner.GetSolutionPoint().y << ", " << refiner.GetSolutionPoint().z << "] with a error of " << score1  << endl;
    cout << "Time Taken: " << (end - start) / getTickFrequency() << " seconds" << endl << endl;

    // Attempt to use the closed form solution
    cout << "Using close-form approach for the best point..." << endl;
    start = getTickCount();
    auto point = RaySetPointUtil::FindCPoint(rays);
    end = getTickCount();
    auto score2 = refiner.FindScore(rays, point, nullptr);
    cout << "Done! Best point is at: [" << point.x << ", " << point.y << ", " << point.z << "] with a error of " << score2 << endl;
    cout << "Time Taken: " << (end - start) / getTickFrequency() << " seconds" << endl;
}

//--------------------------------------------------
// Generate a set of working points
//--------------------------------------------------

/**
 * Define a set of rays that converge roughly at a spot
 * @param rays The set of rays that are attempting to converge
 */
void Engine::FillLines(vector<Ray>& rays) 
{
    auto generator = default_random_engine(); auto distribution = normal_distribution<double>(rand() % 100, 0.5);

    for (auto i = 0; i < 50; i++) 
    {
        auto start = Point3d((200.0 * i / 9.0) - 100, 0, -500);
        auto end = GetPoint(generator, distribution);
        rays.push_back(Ray(start, end));
    }
}

/**
 * The point at the convergence of the rays
 * 2param generator A random number generator
 * @param distribution The distribution that we are using to generate the point
 * @return The point that we are measuring
 */
Point3d Engine::GetPoint(default_random_engine& generator, normal_distribution<double>& distribution)
{
    auto X = distribution(generator);
    auto Y = distribution(generator);
    auto Z = 2;//  distribution(generator);
    return Point3d(X, Y, Z);
}
