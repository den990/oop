#include "CSphere.h"

CSphere::CSphere(double density, double radius)
	: CSolidBody(density)
	, m_radius(radius)
{
}

double CSphere::GetRadius() const
{
	return m_radius;
}

std::string CSphere::GetType() const
{
	return "Сфера";
}

CSphere::~CSphere()
{
}

double CSphere::GetVolume() const
{
	return ((pow(m_radius, 3) * M_PI) * 4 / 3);
}

void CSphere::AppendProperties(std::ostringstream& strm) const
{
	strm << "\tradius = " << GetRadius() << std::endl;
}
