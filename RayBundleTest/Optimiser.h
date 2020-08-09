//----------------------------------------------------
// An implementation of Levenberg-Marquardt
//
// @author: Wild Boar
//----------------------------------------------------

#pragma once

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

class Optimiser
{
private:
	double dpmpar[3];
	void * _callback;
public:
	Optimiser(void * callback) { dpmpar[0] = 2.220446049250313e-16; dpmpar[1] = 2.225073858507201e-308; dpmpar[2] = 1.797693134862315e308; _callback = callback; }
	int Refine(void f(int, int, double*, double*, int*, void* callback), int m, int n, double x[], int msk[], double fvec[], double tol, int *info, int *nfev);
private:
	double enorm(int n, double x[]);
	double rownorm(int m, int r, int c, double **x);
	double colnorm(int m, int r, int c, double **x);
	void fdjac2(void f(int, int, double*, double*, int*, void* callback), int m, int n, double x[], double fvec[], double **fjac, int *iflag, double epsfcn, double wa[]);
	void lmpar(int n, double **fjac, int ipvt[], double diag[], double qtf[], double delta, double *par, double wa1[], double wa2[], double wa3[], double wa4[]);
	void qrfac(int m, int n, double **a, int pivot, int ipvt[], double rdiag[], double acnorm[], double wa[]);
	void lmdif(void f(int, int, double*, double*, int*, void* callback), int m, int n, double x[], int msk[], double fvec[], double ftol, double xtol, double gtol, int maxfev, double epsfcn, double diag[], int mode, double factor, int *info, int *nfev, double **fjac, int ipvt[], double qtf[], double wa1[], double wa2[], double wa3[], double wa4[]);
	void qrsolv(int n, double **r, int ipvt[], double diag[], double qtb[], double x[], double sdiag[], double wa[]);
};