
#pragma once

#include <string>


struct OdeParams {
	double a ;
	double b ;
	double c ;

	double y0 ;
	double yp0 ;
	double t0 ;

	OdeParams( double _a, double _b, double _c, double _y0, double _yp0, double _t0 ) :
	a(_a), b(_b), c(_c), t0(_t0), y0(_y0), yp0(_yp0) {}
} ;


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
		const std::string toString() ;
		double y( double t ) ;
		Simple( OdeParams &p ) ;
} ;


class Single : public Solution {
	private:
		double r ;
		double c2  ;
		double c1 ;
		double toff ;

	public :
		const std::string toString() ;
		double y( double t ) ;
		Single( OdeParams &p ) ;
} ;



class Complex : public Solution {
	private:
		double re ;
		double im ;
		double c2  ;
		double c1 ;
		double toff ;

	public :
		const std::string toString() ;
		double y( double t ) ;
		Complex( OdeParams &p ) ;
} ;
