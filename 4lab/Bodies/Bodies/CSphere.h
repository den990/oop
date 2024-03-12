#pragma once
#include "CSolidBody.h"

class CSphere final : public CSolidBody
{
public:
	CSphere(double density, double radius);

	double GetRadius() const;
	double GetVolume() const override;
	std::string GetType() const override;
	~CSphere();

private:
	void AppendProperties(std::ostringstream& strm) const override;
	double m_radius;
};