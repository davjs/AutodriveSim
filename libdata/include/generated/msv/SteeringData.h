/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef MSV_STEERINGDATA_H
#define MSV_STEERINGDATA_H

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"


#include "core/data/SerializableData.h"


namespace msv {
	using namespace std;
	
	class SteeringData : public core::data::SerializableData {
		public:
			SteeringData();
	
			virtual ~SteeringData();
	
			/**
			 * Copy constructor.
			 *
			 * @param obj Reference to an object of this class.
			 */
			SteeringData(const SteeringData &obj);
	
			/**
			 * Assignment operator.
			 *
			 * @param obj Reference to an object of this class.
			 * @return Reference to this instance.
			 */
			SteeringData& operator=(const SteeringData &obj);
	
		public:
			/**
			 * @return exampleData.
			 */
			double getExampleData() const;
			
			/**
			 * This method sets exampleData.
			 *
			 * @param val Value for exampleData.
			 */
			void setExampleData(const double &val);
	
		public:
			virtual ostream& operator<<(ostream &out) const;
			virtual istream& operator>>(istream &in);
	
			virtual const string toString() const;
	
		private:
			double m_exampleData;
	};
} // msv

#endif /*MSV_STEERINGDATA_H*/
