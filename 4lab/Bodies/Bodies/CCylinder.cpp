#include "CCylinder.h"

CCylinder::CCylinder(double baseRadius, double height, double density)
	: CSolidBody(density)
	, m_baseRadius(baseRadius)
	, m_height(height)
{
}

CCylinder::~CCylinder()
{
}

double CCylinder::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return M_PI * pow(m_baseRadius, 2) * m_height;
}

std::string CCylinder::GetType() const
{
	return "�������";
}


void CCylinder::AppendProperties(std::ostringstream& strm) const
{
	strm << "\t������� ������ ��������: " << GetBaseRadius() << std::endl
		 << "\t������ ��������: " << GetHeight() << std::endl;
}