
#pragma once

#include <string>

/*!\mainpage
 * Solves equations of the form <br><br>
 * \f$ a \frac{d^2y}{dt^2} + b \frac{dy}{dt} + c y = 0\>\left\{ a \neq 0 \right. \f$ 
 * <br><br>given initial settings <br><br>
 * \f$
 * \begin{aligned}
 * t &= t_0\\
 * y &= y_0\\
 * \frac{dy}{dt} &= yp_0\\
 * \end{aligned}
 * \f$
 */


struct OdeParams {
	double a ;		//!< coefficient of the second derivative
	double b ;		//!< coefficient of the first derivative
	double c ;		//!< coefficient of value

	double y0 ;		//!< initial y value
	double yp0 ;	//!< initial slope of y
	double t0 ;		//!< starting at time

	OdeParams( double _a, double _b, double _c, double _y0, double _yp0, double _t0 ) :
	a(_a), b(_b), c(_c), t0(_t0), y0(_y0), yp0(_yp0) {}
} ;

/*!
 * 
 */
class Solution {
	public :
		/*!
		 * Print the solution as a latex string 
 		*/
		virtual const std::string toString() = 0 ;
		/*!
		 * Return the value at time t
 		*/
		virtual double y( double t ) = 0 ;
} ;

/*!
 *  The basic solution where there are two real
 *  roots to the equation
 * 
 *  \f$ y = C_1 e^{r_1t} + C_2 e^{r_2t} \f$ <br>
 */
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


/*!
 *  The basic solution where there is a single
 *  root to the equation
 * 
 *  \f$ y = C_1 e^{rt} + C_2 te^{rt} \f$ <br>
 */
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



/*!
 *  The solution where there is a complex
 *  root to the equation
 * 
 *  \f$ y = C_1 e^{\lambda t} \cos(\mu t) + C_2 e^{\lambda t} \sin(\mu t) \f$ <br>
 *  The conjugate root of the equation is \f$ y = \lambda \pm \mu i  \f$ <br> 
 */
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
