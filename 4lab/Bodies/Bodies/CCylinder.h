#pragma once
#include "CSolidBody.h"

class CCylinder final : public CSolidBody
{
public:
	CCylinder(double baseRadius, double height, double density);
	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;
	std::string GetType() const override;
	~CCylinder();

private:
	void AppendProperties(std::ostringstream& strm) const;
	double m_baseRadius;
	double m_height;
};