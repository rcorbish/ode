
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

#include "solution.hpp"

#ifndef NO_MATPLOT
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
#endif


Solution * ode( OdeParams &p ) ;


//#define DEBUG 

int main( int argc, char **argv ) {

	// 
	// Defines an array of 2nd order ODE of the form 
	// 	ay" + by' + cy = 0
	//
	// with initial params
	// 	y   = initial y
	// 	yp0 = initial y'
	// 	t   = starting time
	//
	//    a,     b,   c,  y0,  yp0,  t0
	OdeParams p[] = {
		{ 1,     2,   3,   4,    6,   0 },
		{ 2,   -16,  32,   2,   -1,   0 },
		{ 4,     8,   1,   3,   -2,   0 },
		{ -12, -12,  12,   3,    1,   0 },
		{ 9.8,  -2,   0,   100,  0,   0 }
	} ;
	const int M = sizeof(p) / sizeof( p[0] ) ;

	std::cout << "Plug this into: https://katex.org/" << std::endl ;
	std::cout << "\\begin{aligned}" << std::endl ;
	for( int i=0 ; i<M ; i++ ) {
		Solution *soln = ode( p[i] ) ;
		if( soln ) {
			std::cout << soln->toString() << "\\\\" << std::endl ;
			delete soln ;
		}
	}
	std::cout << "\\end{aligned}" << std::endl ;

	int N = M-1 ;
	Solution *soln = ode( p[N] ) ;

	std::vector<double> y(100) ;

	double t = 0 ;
	for( int i=0 ; i<100 ; i++, t+=0.01 ) {
		y[i] = soln->y( t ) ;
	}	
	delete soln ;

#ifndef NO_MATPLOT
	plt::plot( y ) ;
	plt::show() ;
#endif

	return 0 ;
}



Solution * ode( OdeParams &p ) {

	if( p.a == 1.0 ) {
		std::printf( "y'' "  ) ; 
	} else if( p.a == -1.0 ) {
		std::printf( "-y'' "  ) ; 
	} else if( p.a != 0.0 ) {
		std::printf( "%4.0fy'' ", p.a  ) ; 
	}

	if( p.b == 1.0 ) {
		if( p.a == 0 ) {
			std::printf( "y' "  ) ; 
		} else {
			std::printf( "+ y' "  ) ; 
		}
	} else if( p.b == -1.0 ) {
		std::printf( "-y'' "  ) ; 
	} else if( p.b != 0.0 ) {
		std::printf( "%+4.0fy' ", p.b  ) ;
	}

	if( p.c == 0.0 ) {
		std::printf( "= 0" ) ; 
	} else if( p.c == 1.0 ) {
		if( p.b == 0 && p.a==0 ) {
			std::printf( "y = 0 "  ) ; 
		} else {
			std::printf( "+y = 0 "  ) ; 
		}
	} else if( p.c == -1.0 ) {
		std::printf( "-y = 0" ) ; 
	} else {
		std::printf( "%+4.0fy = 0", p.c ) ;
	}
 	std::cout << "&\\xrightarrow{y_" << p.t0 << "=" << p.y0 <<  "\\space y'_" << p.t0 << "=" << p.yp0 <<"}" << std::endl ;

	Solution *soln = NULL ;

	if( p.b*p.b > (4*p.a*p.c) ) {
		soln = new Simple( p ) ;
	} else if( p.b*p.b == (4*p.a*p.c) ) {
		soln = new Single( p ) ;
	} else {
		soln = new Complex( p ) ;
	}

	return soln ;
}


