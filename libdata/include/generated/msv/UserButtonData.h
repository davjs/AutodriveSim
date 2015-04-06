/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef MSV_USERBUTTONDATA_H
#define MSV_USERBUTTONDATA_H

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"


#include "core/data/SerializableData.h"


namespace msv {
	using namespace std;
	
	class UserButtonData : public core::data::SerializableData {
		public:
			enum ButtonStatus {
				PRESSED = 1,
				RELEASED = 0,
				UNDEFINED = -1,
			};
		public:
			UserButtonData();
	
			virtual ~UserButtonData();
	
			/**
			 * Copy constructor.
			 *
			 * @param obj Reference to an object of this class.
			 */
			UserButtonData(const UserButtonData &obj);
	
			/**
			 * Assignment operator.
			 *
			 * @param obj Reference to an object of this class.
			 * @return Reference to this instance.
			 */
			UserButtonData& operator=(const UserButtonData &obj);
	
		public:
		public:
			/**
			 * @return buttonStatus.
			 */
			ButtonStatus getButtonStatus() const;
			
			/**
			 * This method sets buttonStatus.
			 *
			 * @param val Value for buttonStatus.
			 */
			void setButtonStatus(const ButtonStatus &val);
		public:
			/**
			 * @return duration.
			 */
			double getDuration() const;
			
			/**
			 * This method sets duration.
			 *
			 * @param val Value for duration.
			 */
			void setDuration(const double &val);
	
		public:
			virtual ostream& operator<<(ostream &out) const;
			virtual istream& operator>>(istream &in);
	
			virtual const string toString() const;
	
		private:
		private:
			ButtonStatus m_buttonStatus;
		private:
			double m_duration;
	};
} // msv

#endif /*MSV_USERBUTTONDATA_H*/
