
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "solution.hpp"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;


Solution * ode( double a, double b, double c, double t0, double y0, double yp0 ) ;


//#define DEBUG 

int main( int argc, char **argv ) {

	const int M = 3 ;

	double a[] = { 1, 2, 4 } ;
	double b[] = { 2, -16, 8 } ;
	double c[] = { 5, 32, 1 } ;

	double y0[] = { 4, 2, 3 } ;
	double yp0[] = { 6, -1, -2 } ;
	double t0[] = { 0, 0, 0 } ;

	for( int i=0 ; i<M ; i++ ) {
		Solution *soln = ode( a[i],b[i],c[i], t0[i], y0[i], yp0[i] ) ;
		if( soln ) {
			std::cout << soln->toString() ;
			std::cout << std::endl ;
		}
		delete soln ;
	}

	int N = 0 ;
	Solution *soln = ode( a[N],b[N],c[N], t0[N], y0[N], yp0[N] ) ;

	std::vector<double> y(100) ;

	double t = 0 ;
	for( int i=0 ; i<100 ; i++, t+=0.3 ) {
		y[i] = soln->y( t ) ;
	}	
	delete soln ;

	plt::plot( y );
	plt::show();

	return 0 ;
}

Solution * ode( double a, double b, double c, double t0, double y0, double yp0 ) {

	std::printf( "%.2fy\" %+.2fy' %+.2f = 0\n", a,b,c ) ; 

	Solution *soln = NULL ;

	if( b*b > (4*a*c) ) {
		soln = new Simple( a,b,c, t0, y0, yp0 ) ;
	} else if( b*b == (4*a*c) ) {
		soln = new Single( a,b,c, t0, y0, yp0 ) ;
	} else {
		soln = new Complex( a,b,c, t0, y0, yp0 ) ;
	}


	return soln ;
}

