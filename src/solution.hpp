
#pragma once

#include <string>

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
		Simple( double a, double b, double c, double t0, double y0, double yp0 ) ;
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
		Single( double a, double b, double c, double t0, double y0, double yp0 ) ;
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
		Complex( double a, double b, double c, double t0, double y0, double yp0 ) ;
} ;
