/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef EXAMPLE3DATA_H_
#define EXAMPLE3DATA_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/SerializableData.h"

namespace examples {

	using namespace std;

	class Example3Data : public core::data::SerializableData {
		public:
			Example3Data();

			virtual ~Example3Data();

			/**
			 * Copy constructor.
			 *
			 * @param obj Reference to an object of this class.
			 */
			Example3Data(const Example3Data &obj);

			/**
			 * Assignment operator.
			 *
			 * @param obj Reference to an object of this class.
			 * @return Reference to this instance.
			 */
			Example3Data& operator=(const Example3Data &obj);

			/**
			 * This method returns the numerical value.
			 *
			 * @return Numerical value.
			 */
			uint32_t getNumericalValue() const;

			/**
			 * This method sets the numerical value.
			 *
			 * @param nv Numerical value.
			 */
			void setNumericalValue(const uint32_t &nv);

			/**
			 * This method returns the string value.
			 *
			 * @return String value.
			 */
			const string getStringValue() const;

			/**
			 * This method sets the string value.
			 *
			 * @param sv String value.
			 */
			void setStringValue(const string &sv);

			virtual ostream& operator<<(ostream &out) const;
			virtual istream& operator>>(istream &in);

			virtual const string toString() const;

		private:
			uint32_t m_numericalValue;
			string m_stringValue;
	};

} // examples

#endif /*EXAMPLE3DATA_H_*/
