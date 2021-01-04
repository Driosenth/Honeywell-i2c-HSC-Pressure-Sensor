#ifndef _HSC_h
#define _HSC_h

#include "Wire.h"




class HSC
	{
	public:
	
	// Contructor
		HSC(uint8_t);

	// Set functions
		bool setPmin(double, String);
		bool setPmax(double, String);
		
	// Get Functions
		// 
		
		double 	getPmin(String);
		double 	getPmax(String);
		
		int 	getT_bit();
		double 	getT(char);
		
		int 	getP_bit();
		double 	getP(String);
		
		int getstatus();
		bool measurePressure();
		
	private:
	//variables
		int i2c_add = 0x28;
		byte buffer[4];
		int status = 0;
		double Pmin_Pa = -1000;
		double Pmax_Pa =  1000;
		int P_bit = 8191;
		int T_bit = 767;
	};
#endif
