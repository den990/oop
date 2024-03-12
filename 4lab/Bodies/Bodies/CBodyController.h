#pragma once
#include "Result.h"
#include "CBody.h"
#include "CSolidBody.h"
#include "CSphere.h"
#include "CParallelepiped.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CCompound.h"
#include <iostream>
#include <string>
#include <regex>

class CBodyController
{
public:
	CBodyController(std::istream& input, std::ostream& output, std::vector<std::shared_ptr<CBody>>& bodies);
	Result Interpret();

private:
	struct ResultValidation
	{
		Status status;
		int value;
	};
	Result ExecuteCommand(int command);
	double ReadValue() const;
	std::shared_ptr<CSphere> CreateSphere();
	std::shared_ptr<CParallelepiped> CreateParallelepiped();
	std::shared_ptr<CCone> CreateCone();
	std::shared_ptr<CCylinder> CreateCylinder();
	Result AddBody();
	Result FindBodyWithMaxMass() const;
	Result FindBodyWithMinWeightInWater() const;
	Result PrintAllBodies() const;
	Result AddCompound(std::shared_ptr<CCompound>& compound);
	Result AddBodyCompound(std::shared_ptr<CCompound>& compound);
	bool IsNumber(const std::string& str) const;
	ResultValidation ValidationValue() const;

	std::vector<std::shared_ptr<CBody>>& m_bodies;
	std::istream& m_input;
	std::ostream& m_output;
	
};