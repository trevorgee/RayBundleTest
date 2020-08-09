//--------------------------------------------------
// Startup code module
//
// @author: Wild Boar
//--------------------------------------------------

#include "Engine.h"
using namespace Amantis;

//--------------------------------------------------
// Main Methods
//--------------------------------------------------

/**
 * Main Method
 */
int main() 
{
    try 
    {
        Engine().Run();
    }
    catch (string exception) 
    {
        cerr << "ERROR: " << exception << endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

