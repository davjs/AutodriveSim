/**
 * 
 *
 *  - - - - -- - -  AutodriveSim , Autodrive wrapper for opendavinci
 *
 *
 */
#include <stdio.h>

#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "core/macros.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/data/Constants.h"
#include "core/data/Container.h"
#include "core/data/image/SharedImage.h"
#include "core/io/ContainerConference.h"
#include "core/data/control/VehicleControl.h"
#include "core/data/environment/VehicleData.h"
#include "core/wrapper/SharedMemoryFactory.h"

#include "tools/player/Player.h"

#include "GeneratedHeaders_Data.h"

#define _DEBUG
#include "../Autodrive/Include/autodrive.hpp"
#include "AutodriveSim.hpp"

const int maxSpeed = 2;

namespace msv {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace core::data::image;
    using namespace core::data::control;
    using namespace core::data::environment;
    using namespace tools::player;
    using namespace cv;

    AutodriveSim::AutodriveSim(const int32_t &argc, char **argv) : ConferenceClientModule(argc, argv, "AutodriveSim"),
        m_hasAttachedToSharedImageMemory(false),
        m_sharedImageMemory(),
        m_image(NULL),
        m_debug(false) {}

    AutodriveSim::~AutodriveSim() {}

    void AutodriveSim::setUp() {
	    // This method will be call automatically _before_ running body().
        Autodrive::SensorData::setCarLength(7);
        Autodrive::setInitialStatus(Autodrive::DETECTING_GAP);
    }

    void AutodriveSim::tearDown() {
	    // This method will be call automatically _after_ return from body().
	    if (m_image != NULL) {
		    cvReleaseImage(&m_image);
	    }
    }

    bool AutodriveSim::readSharedImage(Container &c) {
	    bool retVal = false;

	    if (c.getDataType() == Container::SHARED_IMAGE) {
		    SharedImage si = c.getData<SharedImage> ();

		    // Check if we have already attached to the shared memory.
		    if (!m_hasAttachedToSharedImageMemory) {
			    m_sharedImageMemory
					    = core::wrapper::SharedMemoryFactory::attachToSharedMemory(
							    si.getName());
		    }

		    // Check if we could successfully attach to the shared memory.
		    if (m_sharedImageMemory->isValid()) {
			    // Lock the memory region to gain exclusive access. REMEMBER!!! DO NOT FAIL WITHIN lock() / unlock(), otherwise, the image producing process would fail.
			    m_sharedImageMemory->lock();
			    {
				    const uint32_t numberOfChannels = 3;
				    // For example, simply show the image.
				    if (m_image == NULL) {
					    m_image = cvCreateImage(cvSize(si.getWidth(), si.getHeight()), IPL_DEPTH_8U, numberOfChannels);
				    }

				    // Copying the image data is very expensive...
				    if (m_image != NULL) {
					    memcpy(m_image->imageData,
							   m_sharedImageMemory->getSharedMemory(),
							   si.getWidth() * si.getHeight() * numberOfChannels);
				    }
			    }

			    // Release the memory region so that the image produce (i.e. the camera for example) can provide the next raw image data.
			    m_sharedImageMemory->unlock();

			    // Mirror the image.
			    cvFlip(m_image, 0, -1);

			    retVal = true;
		    }
	    }
	    return retVal;
    }
    
    void AutodriveSim::updateAutodriveData(){
        
        /* ----------------------------------- Data ---------------------------- */
        // Vehicle data
        Container containerVehicleData = getKeyValueDataStore().get(Container::VEHICLEDATA);
        VehicleData vd = containerVehicleData.getData<VehicleData> ();

        // Sensor board data
        Container containerSensorBoardData = getKeyValueDataStore().get(Container::USER_DATA_0);
        SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();

        // Assigning the values of the sensors
        Autodrive::SensorData::infrared.frontright = sbd.getMapOfDistances()[0];
        Autodrive::SensorData::infrared.rear = sbd.getMapOfDistances()[1];
        Autodrive::SensorData::infrared.rearright = sbd.getMapOfDistances()[2];
        Autodrive::SensorData::ultrasound.front = sbd.getMapOfDistances()[3];
        Autodrive::SensorData::ultrasound.frontright = sbd.getMapOfDistances()[4];
        Autodrive::SensorData::ultrasound.rear = sbd.getMapOfDistances()[5];

        // Assigning the values of the vehicle
        Autodrive::SensorData::encoderPulses = vd.getAbsTraveledPath();
        Autodrive::SensorData::gyroHeading = vd.getHeading() * Constants::RAD2DEG;
    /* ---------------------------------------------------------------------- */      
    }

    // You should start your work in this method.
    void AutodriveSim::drive() {
    
        updateAutodriveData();

        /*  ----- RESIZE AND DISPLAY IMAGE ----- */
        Mat frame = cv::cvarrToMat(m_image);
        cv::Mat copy;
        cv::resize(frame,copy,cv::Size(240,135));
        Autodrive::SensorData::image = &copy;
        cv::resize(copy,frame,cv::Size(640,480));
        if (m_debug) {
            if (m_image != NULL) {
                imshow("opencv_eye", frame);
            }
        }

    /* ----------------------------------- Debug ---------------------------- */
        // sensor data
        std::cerr << "Distance front right infrared '" << Autodrive::SensorData::infrared.frontright << "'" << std::endl;
        std::cerr << "Distance rear rigth infrared '" << Autodrive::SensorData::infrared.rearright << "'" << std::endl;
        
        std::cerr << "GapLength '" << Autodrive::Parking::gapLength << "'" << std::endl;
        //std::cerr << "Distance front ultrasonic '" << Autodrive::SensorData::usFront << "'" << std::endl;
        //std::cerr << "Distance front right ultrasonic '" << Autodrive::SensorData::usFrontRight << "'" << std::endl;
        //std::cerr << "Gap length '" << Autodrive::Parking::gapLength << "'" << std::endl;

        // vehicle data
        //std::cerr << "speed: "<< Autodrive::getSpeed() << std::endl;
        //std::cerr << "Heading '" << Autodrive::SensorData::currentAngle << "'" << std::endl;
        //std::cerr << "Heading Start '" << Autodrive::Parking::headingStart << "'" << std::endl;
        //std::cout << "speed: "<< Autodrive::getSpeed() << std::endl;
    /* ---------------------------------------------------------------------- */
    
        // Run autodrive
        Autodrive::drive();
    
    /* ------------------------- Vehicle Control ---------------------------- */
         
        if(Autodrive::speedChanged()|| Autodrive::angleChanged()){//Only send packets when nescecary
            
            // With setSpeed you can set a desired speed for the vehicle in the range of -2.0 (backwards) .. 0 (stop) .. +2.0 (forwards)
            if(Autodrive::speedChanged())
                vc.setSpeed(Autodrive::getSpeed() * maxSpeed);
            // With setSteeringWheelAngle, you can steer in the range of -26 (left) .. 0 (straight) .. +25 (right)
            if(Autodrive::angleChanged())
                vc.setSteeringWheelAngle(Autodrive::getAngle());
            // Create container for finally sending the data.
            Container c(Container::VEHICLECONTROL, vc);
            // Send container.
            getConference().send(c);
        }
    }

    // This method will do the main data processing job.
    // Therefore, it tries to open the real camera first. If that fails, the virtual camera images from camgen are used.
    ModuleState::MODULE_EXITCODE AutodriveSim::body() {
	    // Get configuration data.
	    KeyValueConfiguration kv = getKeyValueConfiguration();
	    m_debug = kv.getValue<int32_t> ("AutodriveSim.debug") == 1;

        Player *player = NULL;
/*
        // Lane-detector can also directly read the data from file. This might be interesting to inspect the algorithm step-wisely.
        core::io::URL url("file://recorder.rec");

        // Size of the memory buffer.
        const uint32_t MEMORY_SEGMENT_SIZE = kv.getValue<uint32_t>("global.buffer.memorySegmentSize");

        // Number of memory segments.
        const uint32_t NUMBER_OF_SEGMENTS = kv.getValue<uint32_t>("global.buffer.numberOfMemorySegments");

        // If AUTO_REWIND is true, the file will be played endlessly.
        const bool AUTO_REWIND = true;

        player = new Player(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS);
*/

        // "Working horse."
	    while (getModuleState() == ModuleState::RUNNING) {
		    bool has_next_frame = false;

		    // Use the shared memory image.
            Container c;
            if (player != NULL) {
		        // Read the next container from file.
                c = player->getNextContainerToBeSent();
            }
            else {
		        // Get the most recent available container for a SHARED_IMAGE.
		        c = getKeyValueDataStore().get(Container::SHARED_IMAGE);
            }                

		    if (c.getDataType() == Container::SHARED_IMAGE) {
			    // Example for processing the received container.
			    has_next_frame = readSharedImage(c);
		    }

		    // Process the read image.
		    if (true == has_next_frame) {
			    drive();
		    }
	    }

        OPENDAVINCI_CORE_DELETE_POINTER(player);

	    return ModuleState::OKAY;
    }

} // msv

