#include "CBody.h"

CBody::CBody()
{
}

CBody::~CBody()
{
}


std::string CBody::ToString(std::ostringstream& strm) const
{
	strm << GetType() << ":" << std::endl
		 << std::setprecision(10) // обрезание 10 сиволов
		 << "\tПлонтность = " << GetDensity() << std::endl
		 << "\tОбъём = " << GetVolume() << std::endl
		 << "\tМасса = " << GetMass() << std::endl;
	AppendProperties(strm);
	return strm.str();
}