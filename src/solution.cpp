
#include "solution.hpp"

#include <math.h>


std::string * floatPrinter( double x ) {
	std::string *rc = NULL ;

	if( x == -1.0 ) {
		rc = new std::string( "-" ) ; 
	} else if( x != 0.0 ) {
		char buf[10] ;
		std::sprintf( buf, "%4.2g", x  ) ; 
		rc = new std::string( buf ) ;
	}
	return rc ;
}

const std::string Simple::toString() {
	char buf[200] ;

	int n = sprintf( buf, "y = " ) ;

	std::string *s = floatPrinter( c1 ) ;
	std::string *r = floatPrinter( r1 ) ;
	if( s ) {
		if( r ) {
			n += sprintf( buf+n, "%s e^{%st}", s->c_str(), r->c_str() ) ; 
		} else {
			n += sprintf( buf+n, "%s ", s->c_str() ) ; 
		}
	}
	delete r ;
	delete s ;

	s = floatPrinter( c2 ) ;
	r = floatPrinter( r2 ) ;
	if( s ) {
		if( c2 > 0 ) {
			n += sprintf( buf+n, "+" ) ; 
		}
		if( r ) {
			n += sprintf( buf+n, "%s e^{%st}", s->c_str(), r->c_str() ) ; 
		} else {
			n += sprintf( buf+n, "%s", s->c_str() ) ; 
		}
	}
	delete r ;
	delete s ;

	std::string rc = buf ;
	return rc ;
} 

double Simple::y( double t ) {
	double y = c1 * exp( r1 * (t+toff) ) + c2 * exp( r2 * (t+toff) ) ;
}

Simple::Simple( OdeParams &p ) {
	r1 = ( -p.b + sqrt( p.b*p.b - 4*p.a*p.c ) ) / ( 2 * p.a ) ;
	r2 = ( -p.b - sqrt( p.b*p.b - 4*p.a*p.c ) ) / ( 2 * p.a ) ;

	// y0 = c1 + c2
	// y' = r1*c1 + r2*c2
	// 
	// so...
	// 	c1 = y0 - c2
	// 	yp0 = ( r1 * ( y0-c2 ) ) + r2*c2
	//      = r1*y0 - r1*c2 + r2*c2
	//      = r1*y0 + c2( r2 - r1 )
	//  c2 = ( yp0 - r1*y0 ) / ( r2 - r1 )

	c2 = ( p.yp0 - r1*p.y0 ) / ( r2 - r1 ) ;
	c1 = p.y0 - c2 ;
	toff = -p.t0 ;
}


const std::string Single::toString() {
	char buf[200] ;
	// sprintf( buf, "y = %.2f e^%.2ft  %+.2f t e^%.2ft" , c1, r, c2, r ) ;
	// char buf[200] ;

	int n = sprintf( buf, "y = " ) ;

	std::string *s = floatPrinter( c1 ) ;
	std::string *rs = floatPrinter( r ) ;
	if( s ) {
		if( rs ) {
			n += sprintf( buf+n, "%s e^{%st} +", s->c_str(), rs->c_str() ) ; 
		} else {
			n += sprintf( buf+n, "%s +", s->c_str() ) ; 
		}
	}
	delete s ;

	s = floatPrinter( c2 ) ;
	if( s ) {
		if( rs ) {
			n += sprintf( buf+n, "%st e^{%st}", s->c_str(), rs->c_str() ) ; 
		} else {
			n += sprintf( buf+n, "%st", s->c_str() ) ; 
		}
	}
	delete rs ;
	delete s ;

	
	std::string rc = buf ;
	return rc ;
} 

double Single::y( double t ) {
	double y = c1 * exp( r * (t-toff) ) + c2 * (t-toff) * exp( r * (t-toff) ) ;
}

Single::Single( OdeParams &p ) {
	r =  -p.b / ( 2 * p.a ) ;

	// y0 = c1
	// y' = r*c1 + c2
	// 
	// so...
	// c1 = y0
	// c2 = yp0 - r*y0

	c1 = p.y0 ;
	c2 = p.yp0 - r * p.y0 ;
	toff = -p.t0 ;
}



const std::string Complex::toString() {
	char buf[200] ;
	// sprintf( buf,"y = %.2f e^%.2ft cos(%.2f t ) %+.2f e^%.2ft sin(%.2f t )" , 
	// 	c1, re, im, c2, re, im ) ;

	int n = sprintf( buf, "y = " ) ;

	std::string *s = floatPrinter( c1 ) ;
	std::string *res = floatPrinter( re ) ;
	std::string *ims = floatPrinter( im ) ;

	if( s ) {
		n += sprintf( buf+n, "%s e^{%st} \\cos(%st) +", s->c_str(), res->c_str() , ims->c_str() ) ; 
	}
	delete s ;

	s = floatPrinter( c2 ) ;
	if( s ) {
		n += sprintf( buf+n, "%s e^{%st} \\sin(%st)", s->c_str(), res->c_str() , ims->c_str() ) ; 
	}
	delete res ;
	delete ims ;
	delete s ;

	std::string rc = buf ;
	return rc ;
} 

double Complex::y( double t ) {
	double y = c1 * exp( re * (t-toff) ) + cos( im * (t-toff) ) +
				c2 * exp( re * (t-toff) ) + sin( im * (t-toff) ) ;
}

Complex::Complex( OdeParams &p ) {
	re = ( -p.b / (2*p.a) ) ;
	im = sqrt( 4*p.a*p.c - p.b*p.b ) / ( 2 * p.a ) ;

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
	c1 = p.y0 ;
	c2 = ( p.yp0 - ( p.y0 * re ) ) / im ;
	toff = -p.t0 ;
}
