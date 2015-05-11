#pragma once
#include <string.h>
#include <math.h>
#include "imageprocessor/command.hpp"
#include "sensordata.hpp"
#include "maneuver.hpp"

namespace Autodrive {

	namespace Parking {
		
		// the different parking procedures
		enum Procedure { NO_PROCEDURE, PARALLEL_STANDARD, PARALLEL_WIDE, PERPENDICULAR_STANDARD };
        Procedure parkingProcedure;
		
		int gapLength = 0;
		int gapStart = 0;
		
		// measure the length of a gap
	    int GetGapLength(){
	        if(SensorData::irFrontRight < 0){
				gapLength = SensorData::encoderDistance() - gapStart;
			}else{
				gapStart = SensorData::encoderDistance();
			}
	        return gapLength;
	    }
	
	    // defines the procedure to engage depending on the size of a  gap
		void SetParkingProcedure(int length) {
	
	        // return the appropriate parking procedure
			if (SensorData::usFrontRight < 0) {		
				parkingProcedure = PARALLEL_WIDE;
			} else {
				if (length > 6 && SensorData::irRearRight > 0) {		
					parkingProcedure = PARALLEL_STANDARD;
				} else if (length > 3 && length < 6 && SensorData::irRearRight > 0) {
					parkingProcedure = PERPENDICULAR_STANDARD;
				} else {
					parkingProcedure = NO_PROCEDURE;
				}
			}
		}
		
		command Park(){
            std::cout << "PARKING" << std::endl;
			command cmd; // so ugly!
            
            switch (parkingProcedure) {			                        // switch to the appropriate parking procedure
	            
                case PARALLEL_STANDARD:						
    				return Maneuver::ParallelStandard();
                    
    			case PARALLEL_WIDE:
    				return cmd; //Maneuver::ParallelWide();
    				
    			case PERPENDICULAR_STANDARD:
    				return Maneuver::PerpendicularStandard();
                    
    			default:
    				return cmd;
            }
	    }													
	} // Parking
}

