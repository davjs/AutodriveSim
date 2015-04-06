/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"

#include "generated/msv/SteeringData.h"

namespace msv {
	using namespace std;
	using namespace core::base;
	
	SteeringData::SteeringData() :
	    SerializableData()
		, m_exampleData(0.0)
	{}
	
	SteeringData::SteeringData(const SteeringData &obj) :
	    SerializableData()
		, m_exampleData(obj.m_exampleData)
	{}
	
	SteeringData::~SteeringData() {}
	
	SteeringData& SteeringData::operator=(const SteeringData &obj) {
		m_exampleData = obj.m_exampleData;
		return (*this);
	}
	
	double SteeringData::getExampleData() const {
		return m_exampleData;
	}
	
	void SteeringData::setExampleData(const double &val) {
		m_exampleData = val;
	}
	
	const string SteeringData::toString() const {
		stringstream s;
	
		s << "ExampleData: " << getExampleData() << " ";
	
		return s.str();
	}
	
	ostream& SteeringData::operator<<(ostream &out) const {
		SerializationFactory sf;
	
		Serializer &s = sf.getSerializer(out);
	
		s.write(CRC32 < CharList<'e', CharList<'x', CharList<'a', CharList<'m', CharList<'p', CharList<'l', CharList<'e', CharList<'D', CharList<'a', CharList<'t', CharList<'a', NullType> > > > > > > > > > >  >::RESULT,
				m_exampleData);
		return out;
	}
	
	istream& SteeringData::operator>>(istream &in) {
		SerializationFactory sf;
	
		Deserializer &d = sf.getDeserializer(in);
	
		d.read(CRC32 < CharList<'e', CharList<'x', CharList<'a', CharList<'m', CharList<'p', CharList<'l', CharList<'e', CharList<'D', CharList<'a', CharList<'t', CharList<'a', NullType> > > > > > > > > > >  >::RESULT,
				m_exampleData);
		return in;
	}
} // msv
