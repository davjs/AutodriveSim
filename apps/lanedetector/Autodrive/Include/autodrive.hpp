#pragma once
#include "sensordata.hpp"
#include "imageprocessor/imageprocessor.hpp"

namespace Autodrive
{
    command lastCommand;

    bool speedChanged() 
    {
        return lastCommand.changedSpeed;
    }

    bool angleChanged()
    {
        return lastCommand.changedAngle;
    }

    int getSpeed()
    {
        return lastCommand.speed;
    }

    float getAngle()
    {
        return lastCommand.angle;
    }

    enum carstatus
    {
        DETECTING_GAP,PARKING,SEARCHING_FOR_LANES,FOLLOWING_LANES,UNKNOWN
    };  
    
    carstatus status;

    void reset()
    {
        // status = SEARCHING_FOR_LANES;
        status = DETECTING_GAP;
    }

    void drive()
    {
        /* Reset command */
        lastCommand = command();

        switch (status)
        {
            case Autodrive::SEARCHING_FOR_LANES:
                if (Autodrive::imageProcessor::init_processing(Autodrive::SensorData::image))
                {
                    lastCommand.setSpeed(62);
                    status = FOLLOWING_LANES;
                }
                break;
            case Autodrive::FOLLOWING_LANES:
                lastCommand = Autodrive::imageProcessor::continue_processing(*Autodrive::SensorData::image);
                break;
            // debug only!    
            case Autodrive::DETECTING_GAP:
                Autodrive::Parking::SetParkingProcedure(GetGapLength());
                if(Autodrive:Parking::parkingProcedure != Autodrive::Parking::NO_PROCEDURE){
                    status = PARKING;
                }
                break;
            // -----------
            case Autodrive::PARKING:
                Autodrive::Park();
                break;
                
            case Autodrive::UNKNOWN:
                /*
                
                EXAMPLE:

                if(Autodrive::SensorData::infrared[1] < 10)
                    lastCommand.setSpeed(0);

                */
                break;
            default:
                break;
        }
    }






}
