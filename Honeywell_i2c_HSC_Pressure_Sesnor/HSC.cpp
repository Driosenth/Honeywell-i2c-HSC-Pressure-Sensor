/*************************************************
 *	
 *	Honeywell i²c Pressure Sensors
 *	Designed specifically for the HSC Series of Pressure Sensors
 *
 *	By Driosenth 2021-01-02
		Driosenth@gmail.com
 *	
 *	Changelog
 *		v0.0.1 	- initial Release
 *
 *************************************************/
 
#include "HSC.h"
#include "Wire.h"

	// Contructor
		HSC::HSC(uint8_t _add){
			if(	!(	_add == 0x28 ||		// check to see if address matches what the data sheet allows
					_add == 0x38 ||
					_add == 0x48 ||
					_add == 0x58 ||
					_add == 0x68 ||
					_add == 0x78)){
				i2c_add = 0x28;
			}
			else {
				i2c_add = _add;
			}
		}
	
	// Set Function	
		bool HSC::setPmin(double P_, String unit_){
			if(	!(	unit_ == "Pa" 	||		// if input unit_ is not recognized
					unit_ == "kPa"	||
					unit_ == "MPa" 	||
					unit_ == "bar" 	||
					unit_ == "mbar" ||
					unit_ == "psi" 	||
					unit_ == "inH2O")){
				return(false);
			}
			else if (unit_ == "Pa"	){	Pmin_Pa = P_; 			}
			else if (unit_ == "kPa"	){	Pmin_Pa = P_*1000; 		}
			else if (unit_ == "MPa"	){	Pmin_Pa = P_*1000000;	}
			else if (unit_ == "bar"	){	Pmin_Pa = P_*100000;	}
			else if (unit_ == "mbar"	){	Pmin_Pa = P_*100;		}
			else if (unit_ == "psi"	){	Pmin_Pa = P_*6894.76;	}
			else if (unit_ == "inH2O"){	Pmin_Pa = P_*248.84;	}
			return (true);
		}
		
		bool HSC::setPmax(double P_, String unit_){
			if(	!(	unit_ == "Pa" 	||		// if input unit_ is not recognized
					unit_ == "kPa"	||
					unit_ == "MPa" 	||
					unit_ == "bar" 	||
					unit_ == "mbar" ||
					unit_ == "psi" 	||
					unit_ == "inH2O")){
				return(false);
			}
			else if (unit_ == "Pa"	){	Pmax_Pa = P_; 			}
			else if (unit_ == "kPa"	){	Pmax_Pa = P_*1000; 		}
			else if (unit_ == "MPa"	){	Pmax_Pa = P_*1000000;	}
			else if (unit_ == "bar"	){	Pmax_Pa = P_*100000;	}
			else if (unit_ == "mbar"	){	Pmax_Pa = P_*100;		}
			else if (unit_ == "psi"	){	Pmax_Pa = P_*6894.76;	}
			else if (unit_ == "inH2O"){	Pmax_Pa = P_*248.84;	}
			return (true);
		}
		
	// Read Data Function
		bool HSC::measurePressure(){
			Wire.beginTransmission(i2c_add);
			Wire.write(1);
			Wire.endTransmission();
		 
			delay (20);

			Wire.requestFrom(i2c_add, 4);
			while(Wire.available() == 0);
			buffer[0]	= Wire.read();
			buffer[1]	= Wire.read();
			buffer[2]	= Wire.read();
			buffer[3]	= Wire.read();
			status = (buffer[0] & 0xc0) >> 6;
			if(status == 0){
				P_bit = ((buffer[0] & 0x3f) << 8) + buffer[1];
				T_bit = ((buffer[2] << 8) + (buffer[3] & 0xe0)) >> 5;
				return(true);
			}
			else{	return(false);	}
		}
	
	// Get Function	
		double HSC::getPmin(String unit_){
			if(	!(	unit_ == "Pa" 	||		// if input unit_ is not recognized
					unit_ == "kPa"	||
					unit_ == "MPa" 	||
					unit_ == "bar" 	||
					unit_ == "mbar" ||
					unit_ == "psi" 	||
					unit_ == "inH2O")){
				return(0);
			}
			else if (unit_ == "Pa"	){	return(Pmin_Pa			);	}
			else if (unit_ == "kPa"	){	return(Pmin_Pa/1000		);	}
			else if (unit_ == "MPa"	){	return(Pmin_Pa/1000000	);	}
			else if (unit_ == "bar"	){	return(Pmin_Pa/100000	);	}
			else if (unit_ == "mbar"	){	return(Pmin_Pa/100		);	}
			else if (unit_ == "psi"	){	return(Pmin_Pa/6894.76	);	}
			else if (unit_ == "inH2O"){	return(Pmin_Pa/248.84	);	}
      else {return(0);}
		}
		
		double HSC::getPmax(String unit_){
			if(	!(	unit_ == "Pa" 	||		// if input unit_ is not recognized
					unit_ == "kPa"	||
					unit_ == "MPa" 	||
					unit_ == "bar" 	||
					unit_ == "mbar" ||
					unit_ == "psi" 	||
					unit_ == "inH2O")){
				return(0);
			}
			else if (unit_ == "Pa"	){	return(Pmax_Pa			);	}
			else if (unit_ == "kPa"	){	return(Pmax_Pa/1000		);	}
			else if (unit_ == "MPa"	){	return(Pmax_Pa/1000000	);	}
			else if (unit_ == "bar"	){	return(Pmax_Pa/100000	);	}
			else if (unit_ == "mbar"	){	return(Pmax_Pa/100		);	}
			else if (unit_ == "psi"	){	return(Pmax_Pa/6894.76	);	}
			else if (unit_ == "inH2O"){	return(Pmax_Pa/248.84	);	}
      else {return(0);}
		}
		
		int HSC::getstatus()	{	return status;	}
		int HSC::getT_bit() 	{	return T_bit;	}
		int HSC::getP_bit() 	{	return P_bit;	}
		
		
		double 	HSC::getT(char unit_){
			if(	!(	unit_ == 'K' 	||		// if input unit_ is not recognized
					unit_ == 'C'	||
					unit_ == 'R' 	||
					unit_ == 'F' 	)){
				return(0);
			}
			else if (unit_ == 'K'	){	return( double(T_bit)*200/2047+223.15			); 	}
			else if (unit_ == 'C'	){	return( double(T_bit)*200/2047-50				); 	}
			else if (unit_ == 'R'	){	return((double(T_bit)*200/2047-50)*9/5+32		);	}
			else if (unit_ == 'F'	){	return((double(T_bit)*200/2047-50)*9/5+491.67	);	}
      else {return(0);}
		}
		
		double HSC::getP(String unit_){
			if(	!(	unit_ == "Pa" 	||		// if input unit_ is not recognized
					unit_ == "kPa"	||
					unit_ == "MPa" 	||
					unit_ == "bar" 	||
					unit_ == "mbar" ||
					unit_ == "psi" 	||
					unit_ == "inH2O")){
				return(0);
			}
			else if (unit_ == "Pa"	){	return(map(double(P_bit),0,16383,Pmin_Pa,Pmax_Pa)			);	}
			else if (unit_ == "kPa"	){	return(map(double(P_bit),0,16383,Pmin_Pa,Pmax_Pa)/1000		); 	}
			else if (unit_ == "MPa"	){	return(map(double(P_bit),0,16383,Pmin_Pa,Pmax_Pa)/1000000	);	}
			else if (unit_ == "bar"	){	return(map(double(P_bit),0,16383,Pmin_Pa,Pmax_Pa)/100000	);	}
			else if (unit_ == "mbar"){	return(map(double(P_bit),0,16383,Pmin_Pa,Pmax_Pa)/100		);	}
			else if (unit_ == "psi"	){	return(map(double(P_bit),0,16383,Pmin_Pa,Pmax_Pa)/6894.76	);	}
			else if (unit_ == "inH2O"){	return(map(double(P_bit),0,16383,Pmin_Pa,Pmax_Pa)/248.84	);	}
      else {return(0);}
		}
		
		
		
	
