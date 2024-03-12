#pragma once
#include "CSolidBody.h"
#include <vector>
//выяснить для чего нужен override
// Override в языке программирования C 
//является специальным типом идентификатора, который указывает на переопределение методов. 
//Переопределение методов — это очень удобный и нужный механизм. Его смысл заключается в том, что вы создаете 
//собственный дочерний метод в производственном классе, который повторяет какой-нибудь родительский метод, но со своей спецификацией. 

class CCompound final : public CBody//читать внимтельнее задание
{
public:
	CCompound();
	double GetVolume() const;
	double GetMass() const;
	double GetDensity() const ;
	size_t GetSize() const;
	std::string GetType() const override;
	bool AddChild(std::shared_ptr<CBody> child);
	~CCompound();

private:
	void AddParent(CCompound* parent);
	void AppendProperties(std::ostringstream& output) const override;
	CCompound* m_parent;
	std::vector<std::shared_ptr<CBody>> m_children;
};