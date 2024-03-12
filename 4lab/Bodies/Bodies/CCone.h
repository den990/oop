#pragma once
#include "CSolidBody.h"

class CCone final : public CSolidBody
{
public:
	CCone(double baseRadius, double height, double destiny);
	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;
	std::string GetType() const override;
	~CCone();

private:
	void AppendProperties(std::ostringstream& strm) const override;
	double m_baseRadius;
	double m_height;
};