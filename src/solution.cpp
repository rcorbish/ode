
#include "solution.hpp"

#include <math.h>

const std::string Simple::toString() {
	char buf[200] ;
	sprintf( buf, "y = %.2f e^%.2ft  %+.2f e^%.2ft" , c1, r1, c2, r2 ) ; 
	std::string rc = buf ;
	return rc ;
} 

double Simple::y( double t ) {
	double y = c1 * exp( r1 * (t+toff) ) + c2 * exp( r2 * (t+toff) ) ;
}

Simple::Simple( double a, double b, double c, double t0, double y0, double yp0 ) {
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


const std::string Single::toString() {
	char buf[200] ;
	sprintf( buf, "y = %.2f e^%.2ft  %+.2f t e^%.2ft" , c1, r, c2, r ) ;
	std::string rc = buf ;
	return rc ;
} 

double Single::y( double t ) {
	double y = c1 * exp( r * (t-toff) ) + c2 * (t-toff) * exp( r * (t-toff) ) ;
}

Single::Single( double a, double b, double c, double t0, double y0, double yp0 ) {
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



const std::string Complex::toString() {
	char buf[200] ;
	sprintf( buf,"y = %.2f e^%.2ft cos(%.2f t ) %+.2f e^%.2ft sin(%.2f t )" , 
		c1, re, im, c2, re, im ) ;
	std::string rc = buf ;
	return rc ;
} 

double Complex::y( double t ) {
	double y = c1 * exp( re * (t-toff) ) + cos( im * (t-toff) ) +
				c2 * exp( re * (t-toff) ) + sin( im * (t-toff) ) ;
}

Complex::Complex( double a, double b, double c, double t0, double y0, double yp0 ) {
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
