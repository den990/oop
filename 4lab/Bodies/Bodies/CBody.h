#pragma once
#include "iostream"
#include <sstream>
#include <iomanip>
class CBody
{
public:
	CBody();

	virtual double GetDensity() const = 0;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const = 0;
	std::string ToString(std::ostringstream& output) const;
	virtual std::string GetType() const = 0;
	virtual ~CBody();//выяснить для чего нужен вирт деструктор

private:
	virtual void AppendProperties(std::ostringstream& strm) const = 0;
};