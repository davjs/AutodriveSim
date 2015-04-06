/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"

#include "generated/msv/UserButtonData.h"

namespace msv {
	using namespace std;
	using namespace core::base;
	
	UserButtonData::UserButtonData() :
	    SerializableData()
		, m_buttonStatus()
		, m_duration(0.0)
	{}
	
	UserButtonData::UserButtonData(const UserButtonData &obj) :
	    SerializableData()
		, m_buttonStatus(obj.m_buttonStatus)
		, m_duration(obj.m_duration)
	{}
	
	UserButtonData::~UserButtonData() {}
	
	UserButtonData& UserButtonData::operator=(const UserButtonData &obj) {
		m_buttonStatus = obj.m_buttonStatus;
		m_duration = obj.m_duration;
		return (*this);
	}
	
	UserButtonData::ButtonStatus UserButtonData::getButtonStatus() const {
		return m_buttonStatus;
	}
	
	void UserButtonData::setButtonStatus(const UserButtonData::ButtonStatus &val) {
		m_buttonStatus = val;
	}
	double UserButtonData::getDuration() const {
		return m_duration;
	}
	
	void UserButtonData::setDuration(const double &val) {
		m_duration = val;
	}
	
	const string UserButtonData::toString() const {
		stringstream s;
	
		switch(getButtonStatus()) {
			case PRESSED :
			s << "ButtonStatus: UserButtonData::PRESSED (1) ";
			break;
			case RELEASED :
			s << "ButtonStatus: UserButtonData::RELEASED (0) ";
			break;
			case UNDEFINED :
			s << "ButtonStatus: UserButtonData::UNDEFINED (-1) ";
			break;
		}
		s << "Duration: " << getDuration() << " ";
	
		return s.str();
	}
	
	ostream& UserButtonData::operator<<(ostream &out) const {
		SerializationFactory sf;
	
		Serializer &s = sf.getSerializer(out);
	
		int32_t int32t_buttonStatus = m_buttonStatus;
		s.write(CRC32 < CharList<'b', CharList<'u', CharList<'t', CharList<'t', CharList<'o', CharList<'n', CharList<'S', CharList<'t', CharList<'a', CharList<'t', CharList<'u', CharList<'s', NullType> > > > > > > > > > > >  >::RESULT,
				int32t_buttonStatus);
		s.write(CRC32 < CharList<'d', CharList<'u', CharList<'r', CharList<'a', CharList<'t', CharList<'i', CharList<'o', CharList<'n', NullType> > > > > > > >  >::RESULT,
				m_duration);
		return out;
	}
	
	istream& UserButtonData::operator>>(istream &in) {
		SerializationFactory sf;
	
		Deserializer &d = sf.getDeserializer(in);
	
		int32_t int32t_buttonStatus = 0;
		d.read(CRC32 < CharList<'b', CharList<'u', CharList<'t', CharList<'t', CharList<'o', CharList<'n', CharList<'S', CharList<'t', CharList<'a', CharList<'t', CharList<'u', CharList<'s', NullType> > > > > > > > > > > >  >::RESULT,
				int32t_buttonStatus);
		m_buttonStatus = static_cast<UserButtonData::ButtonStatus>(int32t_buttonStatus);
		d.read(CRC32 < CharList<'d', CharList<'u', CharList<'r', CharList<'a', CharList<'t', CharList<'i', CharList<'o', CharList<'n', NullType> > > > > > > >  >::RESULT,
				m_duration);
		return in;
	}
} // msv
