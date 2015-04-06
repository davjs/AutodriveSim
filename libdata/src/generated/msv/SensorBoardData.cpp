/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"

#include "generated/msv/SensorBoardData.h"

namespace msv {
	using namespace std;
	using namespace core::base;
	
	SensorBoardData::SensorBoardData() :
	    SerializableData()
		, m_numberOfSensors(0)
		, m_mapOfDistances()
	{}
	
	SensorBoardData::SensorBoardData(const SensorBoardData &obj) :
	    SerializableData()
		, m_numberOfSensors(obj.m_numberOfSensors)
		, m_mapOfDistances(obj.m_mapOfDistances)
	{}
	
	SensorBoardData::~SensorBoardData() {}
	
	SensorBoardData& SensorBoardData::operator=(const SensorBoardData &obj) {
		m_numberOfSensors = obj.m_numberOfSensors;
		m_mapOfDistances = obj.m_mapOfDistances;
		return (*this);
	}
	
	uint32_t SensorBoardData::getNumberOfSensors() const {
		return m_numberOfSensors;
	}
	
	void SensorBoardData::setNumberOfSensors(const uint32_t &val) {
		m_numberOfSensors = val;
	}
	std::map<uint32_t, double> SensorBoardData::getMapOfDistances() const {
		return m_mapOfDistances;
	}
	
	void SensorBoardData::setMapOfDistances(const std::map<uint32_t, double> &val) {
		m_mapOfDistances = val;
	}
	
	void SensorBoardData::clear_MapOfDistances() {
		m_mapOfDistances.clear();
	}
	
	uint32_t SensorBoardData::getSize_MapOfDistances() const {
		return m_mapOfDistances.size();
	}
	
	bool SensorBoardData::isEmpty_MapOfDistances() const {
		return m_mapOfDistances.empty();
	}
	
	void SensorBoardData::putTo_MapOfDistances(const uint32_t &key, const double &val) {
		m_mapOfDistances[key] = val;
	}
	
	bool SensorBoardData::containsKey_MapOfDistances(const uint32_t &key) const {
		return (m_mapOfDistances.count(key) > 0);
	}
	
	double SensorBoardData::getValueForKey_MapOfDistances(const uint32_t &key) {
		return m_mapOfDistances[key];
	}
	
	std::pair<std::map<uint32_t, double>::iterator, std::map<uint32_t, double>::iterator> SensorBoardData::iteratorPair_MapOfDistances() {
		return std::make_pair(m_mapOfDistances.begin(), m_mapOfDistances.end());
	}
	
	const string SensorBoardData::toString() const {
		stringstream s;
	
		s << "NumberOfSensors: " << getNumberOfSensors() << " ";
		s << "Number of elements in map of Distances: " << getSize_MapOfDistances() << " ";
	
		return s.str();
	}
	
	ostream& SensorBoardData::operator<<(ostream &out) const {
		SerializationFactory sf;
	
		Serializer &s = sf.getSerializer(out);
	
		s.write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'S', CharList<'e', CharList<'n', CharList<'s', CharList<'o', CharList<'r', CharList<'s', NullType> > > > > > > > > > > > > > >  >::RESULT,
				m_numberOfSensors);
		{
			// Write number of elements in m_mapOfDistances.
			const uint32_t numberOfDistances = static_cast<uint32_t>(m_mapOfDistances.size());
			s.write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'D', CharList<'i', CharList<'s', CharList<'t', CharList<'a', CharList<'n', CharList<'c', CharList<'e', CharList<'s', NullType> > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfDistances);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfDistances;
			std::map<uint32_t, double>::const_iterator it = m_mapOfDistances.begin();
			while (it != m_mapOfDistances.end()) {
			    sstrOfDistances << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfDistances > 0) {
				s.write(CRC32 < CharList<'D', CharList<'i', CharList<'s', CharList<'t', CharList<'a', CharList<'n', CharList<'c', CharList<'e', CharList<'s', NullType> > > > > > > > >  >::RESULT,
						sstrOfDistances.str());
			}
		}
		return out;
	}
	
	istream& SensorBoardData::operator>>(istream &in) {
		SerializationFactory sf;
	
		Deserializer &d = sf.getDeserializer(in);
	
		d.read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'S', CharList<'e', CharList<'n', CharList<'s', CharList<'o', CharList<'r', CharList<'s', NullType> > > > > > > > > > > > > > >  >::RESULT,
				m_numberOfSensors);
		// Clean up the existing map of Distances.
		m_mapOfDistances.clear();
		
		// Read number of elements in m_mapOfDistances.
		uint32_t numberOfDistances = 0;
		d.read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'D', CharList<'i', CharList<'s', CharList<'t', CharList<'a', CharList<'n', CharList<'c', CharList<'e', CharList<'s', NullType> > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfDistances);
		
		if (numberOfDistances > 0) {
		    // Read string of elements.
		    string elements;
			d.read(CRC32 < CharList<'D', CharList<'i', CharList<'s', CharList<'t', CharList<'a', CharList<'n', CharList<'c', CharList<'e', CharList<'s', NullType> > > > > > > > >  >::RESULT,
			       elements);
		
			stringstream sstr(elements);
		
			while (!sstr.eof()) {
			    string line;
			    getline(sstr, line);
		
			    // Trying to find key-value-pair.
			    size_t delimiter = line.find_first_of("=");
		
			    // Compute length of value-entry by allowing comments right after values.
			    size_t valueLength = line.length();
		
			    // Skip lines with invalid position pointers.
			    if (! ( (delimiter > 0) && (valueLength > 0) ) ) {
			        continue;
			    }
		
			    string key = line.substr(0, delimiter);
			    string value = line.substr(delimiter + 1, valueLength);
		
			    // Skip lines with invalid keys or values.
			    if ( (key.length() == 0) || (value.length() == 0) ) {
			        continue;
			    }
		
			    stringstream sstrKey(key);
			    uint32_t _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    double _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfDistances(_key, _value);
			}
		}
		return in;
	}
} // msv
