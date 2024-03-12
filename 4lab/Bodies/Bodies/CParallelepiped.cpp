#include "CParallelepiped.h"

CParallelepiped::CParallelepiped(double density, double height, double width, double depth)
	: CSolidBody(density)
	, m_height(height)
	, m_width(width)
	, m_depth(depth)
{
}

CParallelepiped::~CParallelepiped()
{
}


double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetVolume() const
{
	return m_width * m_height * m_depth;
}

std::string CParallelepiped::GetType() const
{
	return "Параллелепипед";
}


void CParallelepiped::AppendProperties(std::ostringstream& strm) const
{
	strm << "\tДлина параллелепипеда: " << GetHeight() << std::endl
		 << "\tШирина парллелепипеда: " << GetWidth() << std::endl
		 << "\tГлубина параллелепипеда: " << GetDepth() << std::endl;
}
