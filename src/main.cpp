
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <cmath>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;


class Solution ;
Solution * ode( double a, double b, double c, double t0, double y0, double yp0 ) ;

class Solution {
	public :
		virtual const std::string toString() = 0 ;
		virtual double y( double t ) = 0 ;
} ;

class Simple : public Solution {
	private:
		double r1 ;
		double r2 ;
		double c2  ;
		double c1 ;
		double toff ;

	public :
		const std::string toString() {
			char buf[200] ;
			sprintf( buf, "y = %.2f e^%.2ft  %+.2f e^%.2ft" , c1, r1, c2, r2 ) ; 
			std::string rc = buf ;
			return rc ;
		} 
		double y( double t ) {
			double y = c1 * exp( r1 * (t+toff) ) + c2 * exp( r2 * (t+toff) ) ;
		}
		Simple( double a, double b, double c, double t0, double y0, double yp0 ) {
			r1 = ( -b + sqrt( b*b - 4*a*c ) ) / ( 2 * a ) ;
			r2 = ( -b - sqrt( b*b - 4*a*c ) ) / ( 2 * a ) ;

			// y0 = c1 + c2
			// y' = r1*c1 + r2*c2
			// 
			// so...
			// 	c1 = y0 - c2
			// 	yp0 = ( r1 * ( y0-c2 ) ) + r2*c2
			//      = r1*y0 - r1*c2 + r2*c2
			//      = r1*y0 + c2( r2 - r1 )
			//  c2 = ( yp0 - r1*y0 ) / ( r2 - r1 )

			c2 = ( yp0 - r1*y0 ) / ( r2 - r1 ) ;
			c1 = y0 - c2 ;
			toff = -t0 ;
		}
} ;


class Single : public Solution {
	private:
		double r ;
		double c2  ;
		double c1 ;
		double toff ;

	public :
		const std::string toString() {
			char buf[200] ;
			sprintf( buf, "y = %.2f e^%.2ft  %+.2f t e^%.2ft" , c1, r, c2, r ) ;
			std::string rc = buf ;
			return rc ;
		} 
		double y( double t ) {
			double y = c1 * exp( r * (t-toff) ) + c2 * (t-toff) * exp( r * (t-toff) ) ;
		}
		Single( double a, double b, double c, double t0, double y0, double yp0 ) {
			r =  -b / ( 2 * a ) ;

			// y0 = c1
			// y' = r*c1 + c2
			// 
			// so...
			// c1 = y0
			// c2 = yp0 - r*y0

			c1 = y0 ;
			c2 = yp0 - r * y0 ;
			toff = -t0 ;
		}
} ;



class Complex : public Solution {
	private:
		double re ;
		double im ;
		double c2  ;
		double c1 ;
		double toff ;

	public :
		const std::string toString() {
			char buf[200] ;
			sprintf( buf,"y = %.2f e^%.2ft cos(%.2f t ) %+.2f e^%.2ft sin(%.2f t )" , 
				c1, re, im, c2, re, im ) ;
			std::string rc = buf ;
			return rc ;
		} 
		double y( double t ) {
			double y = c1 * exp( re * (t-toff) ) + cos( im * (t-toff) ) +
					   c2 * exp( re * (t-toff) ) + sin( im * (t-toff) ) ;
		}
		Complex( double a, double b, double c, double t0, double y0, double yp0 ) {
			re = ( -b / (2*a) ) ;
			im = sqrt( 4*a*c - b*b ) / ( 2 * a ) ;

			//
			// y = c1 * e^re*t cos( im*t) + c2 * e^re*t sin( im*t)
			// y' = e ^re t ( sin( im * t) * ( c2*re - c1*im ) +  cos( im * t) * ( c1*re + c2*im ) )  
			// 
			// @t=0
			// y0 = c1
			// yp0 = y0 * re + c2 * im
			// 
			// c1 = y0
			// c2 = ( yp0 - ( y0 * re ) ) / im
			//
			c1 = y0 ;
			c2 = ( yp0 - ( y0 * re ) ) / im ;
			toff = -t0 ;
		}
} ;



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

