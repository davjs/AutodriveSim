#pragma once
#include <string.h>
#include <math.h>
#include "imageprocessor/command.hpp"
#include "sensordata.hpp"

namespace Autodrive {

	namespace Parking {
		
		// the different parking procedures
		enum Procedure { NO_PROCEDURE, PARALLEL_STANDARD, PARALLEL_WIDE, PERPENDICULAR_STANDARD };
        Procedure parkingProcedure;
		
		// measure the length of a gap
	    // TODO: make it work no matter if it starts next to an obstacle or not
	    int GetGapLength(){
	        if(SensorData::irFrontRight < 0){
				gapLength = traveledPath - gapStart;
			}else{
				gapStart = traveledPath;
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
		
		void Park(){
            cout << "PARKING" << endl;
            
            switch (parkingProcedure) {			                        // switch to the appropriate parking procedure
	            
                case PARALLEL_STANDARD:
                	currentState = DETECT_GAP;							// toggle comment to test this parking procedure
    				// currentState = ParallelStandard();
    				break;
                    
    			case PARALLEL_WIDE:
    				currentState = DETECT_GAP;
    				//currentState = ParallelWide();
    				cout << "parallel wide" << endl;
    				break;
                    
    			case PERPENDICULAR_STANDARD:
    				currentState = PerpendicularStandard();
    				cout << "perpendicular" << endl;
    				break;
                    
    			default:
    				break;
            }
	    }													
	} // Parking
}

