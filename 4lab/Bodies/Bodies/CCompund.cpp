#include "CCompound.h"
const std::string TYPE_COMPOUND = "Составное тело";
	//density-плотность volume-объем 
CCompound::CCompound()
	: m_parent(nullptr)
{
}

double CCompound::GetDensity() const
{
	double mass = 0;
	double volume = 0;
	for (const std::shared_ptr<CBody>& body : m_children)
	{
		mass += body->GetMass();
		volume += body->GetVolume();
	}

	return mass / volume;
}

std::string CCompound::GetType() const
{
	return "Составное тело";
}

size_t CCompound::GetSize() const
{
	return m_children.size();
}

double CCompound::GetVolume() const
{
	double volume = 0;
	for (const std::shared_ptr<CBody>& body : m_children)
	{
		volume += body->GetVolume();
	}

	return volume;
}

double CCompound::GetMass() const
{
	double mass = 0;
	for (const std::shared_ptr<CBody>& body : m_children)
	{
		mass += body->GetMass();
	}

	return mass;
}

void CCompound::AddParent(CCompound* parent)
{
	m_parent = parent;
}

bool CCompound::AddChild(std::shared_ptr<CBody> child)
{
	bool add = true;
	if (child->GetType() == TYPE_COMPOUND)
	{
		auto c = dynamic_cast<CCompound*>(child.get());
		c->AddParent(this);
		CCompound* parent = c->m_parent;
		while (parent != nullptr)
		{
			if (parent == c)
			{
				add = false;
				break;
			}
			auto b = parent;
			parent = b->m_parent;
		}
	}
	if (add)
	{
		m_children.push_back(child);
		return true;
	}
	return false;
}

CCompound::~CCompound()
{
}

void CCompound::AppendProperties(std::ostringstream& output) const
{
	output << "\tСостоит из: ";
	for (auto& ptr : m_children)
	{
		std::string type = ptr->GetType();
		output << type << " ";
		if (type == TYPE_COMPOUND)
		{
			output << "\n";
			ptr->ToString(output);
		}
	}
	output << std::endl;
}