#include "Termin.h"
#include <iostream>
#include <algorithm>
#include "SHA256.h"

std::string Termin::makeHash(const Termin& termin)
{
	std::string pagesNumsStr{ "" };
	for (int i = 0; i < termin.m_pagesNums.size(); ++i)
		pagesNumsStr += termin.m_pagesNums[i];
	if (termin.m_parentTermin != nullptr)
		return sha256(termin.m_name + termin.m_parentTermin->m_name + pagesNumsStr);
	return sha256(termin.m_name + pagesNumsStr);
}

void Termin::printPages()
{
	for (int i = 0; i < m_pagesNums.size(); ++i)
		std::cout << m_pagesNums[i] << " ";
}

int Termin::subTerminNamePos(const std::string& name)
{
	int isFound{ -1 };
	for (int i = 0; i < m_subTermins.size(); ++i)
		if (m_subTermins[i].m_name == name)
		{
			isFound = i;
			//m_subTermins.erase(m_subTermins.begin() + i);
		}
	return isFound;
}

void Termin::printPointer(Termin termin, int level)
{
	for (int i = 1; i < level; ++i)
		std::cout << '\t';
	if (level != 0)
		termin.printTermin();
	if (termin.m_subTermins.size() == 0)
		return;
	int i = 0;
	while (i < termin.m_subTermins.size())
	{
		printPointer(termin.m_subTermins[i], level + 1);
		++i;
	}
	/*
	for (int i = 0; i < termin.m_subTermins.size(); ++i)
	{
		termin.printTermin();


	}
	*/
}

void Termin::findParentsWithSubTerminName_private(Termin* termin, const std::string name, std::vector<Termin*>& result)
{
	if (name == "/")
	{
		result.push_back(nullptr);
		return;
	}
	if (termin->m_name == name)
		result.push_back(termin->m_parentTermin);
	if (termin->m_subTermins.size() == 0)
		return;
	for (int i = 0; i < termin->m_subTermins.size(); ++i)
		findParentsWithSubTerminName_private(&(termin->m_subTermins[i]), name, result);
}

void Termin::findTermins_private(Termin* termin, const std::string name, std::vector<Termin*>& result)
{
	if (name == "/")
	{
		result.push_back(termin);
		return;
	}
	if (termin->m_name == name)
		result.push_back(termin);
	if (termin->m_subTermins.size() == 0)
		return;
	int i{ 0 };
	while (i < termin->m_subTermins.size())
	{
		findTermins_private(&(termin->m_subTermins[i]), name, result);
		++i;
	}
}

Termin::Termin(const std::string& name, std::vector<int> pagesNums) : m_parentTermin{ nullptr }, m_name{ name }, m_pagesNums{ pagesNums }, m_id{ sha256(name) }
{
	m_subTermins.resize(0);
}

bool Termin::addSubTermin(Termin subTermin)
{
	if (subTermin.m_name != this->m_name && subTerminNamePos(subTermin.m_name) == -1)
	{
		subTermin.m_parentTermin = this;
		subTermin.m_id = makeHash(subTermin);
		m_subTermins.push_back(subTermin);
		return true;
	}
	return false;
}

bool Termin::addPage(const int pageNum)
{
	if (std::find(m_pagesNums.begin(), m_pagesNums.end(), pageNum) == m_pagesNums.end())
	{
		m_pagesNums.push_back(pageNum);
		m_id = makeHash(*this);
		return true;
	}
	return false;
}

bool Termin::deletePage(const int pageNum)
{
	if (!(std::find(m_pagesNums.begin(), m_pagesNums.end(), pageNum) == m_pagesNums.end()) && m_pagesNums.size() > 1)
	{
		m_pagesNums.erase(std::find(m_pagesNums.begin(), m_pagesNums.end(), pageNum));
		m_id = makeHash(*this);
		return true;
	}
	return false;
}

bool Termin::deleteSubTermin(const std::string& name)
{
	int position{ this->subTerminNamePos(name) };
	if (position != -1)
		m_subTermins.erase(m_subTermins.begin() + position);
	return (position == -1) ? false : true;
}

void Termin::printTermin()
{
	std::cout << "Имя термина: " << m_name << ". Хеш термина: ";
	for (int i = 0; i < 5; ++i)
		std::cout << m_id[i];
	std::cout << "..";
	for (int i = 5; i < 10; ++i)
		std::cout << m_id[i];
	std::cout << ". Термин расположен на страницах: ";
	this->printPages();
	std::cout << std::endl;
}

void Termin::printSubjectPointer()
{
	printPointer(*this, 0);
}

void Termin::printTerminAndSubTermins(Termin* termin)
{
	if (termin->m_name != "")
		termin->printTermin();
	for (int i = 0; i < termin->m_subTermins.size(); ++i)
	{
		std::cout << '\t';
		termin->m_subTermins[i].printTermin();
	}
}

void Termin::findParentsWithSubTerminName(const std::string name, std::vector<Termin*>& result)
{
	findParentsWithSubTerminName_private(this, name, result);
}

void Termin::findTermins(const std::string name, std::vector<Termin*>& result)
{
	findTermins_private(this, name, result);
}

void Termin::sortInts(std::vector<int>& pagesNums)
{
	for (int i = 1; i < pagesNums.size(); ++i)
		for (int j = 0; j < pagesNums.size() - i; ++j)
			if (pagesNums[j] > pagesNums[j + 1])
			{
				int temp = pagesNums[j];
				pagesNums[j] = pagesNums[j + 1];
				pagesNums[j + 1] = temp;
			}
}

void Termin::sortByAlphabet_private(Termin& termin)
{
	for (int i = 1; i < termin.m_subTermins.size(); ++i)
		for (int j = 0; j < termin.m_subTermins.size() - i; ++j)
			if (termin.m_subTermins[j].m_name > termin.m_subTermins[j + 1].m_name)
			{
				Termin temp{ termin.m_subTermins[j] };
				termin.m_subTermins[j] = termin.m_subTermins[j + 1];
				termin.m_subTermins[j + 1] = temp;
			}
	for (int i = 0; i < termin.m_subTermins.size(); ++i)
		sortByAlphabet_private(termin.m_subTermins[i]);
}

void Termin::sortByPages_private(Termin& termin)
{
	//if (termin.m_subTermins.size() == 0)
		//return;
	for (int i = 0; i < termin.m_subTermins.size(); ++i)
		this->sortInts(termin.m_subTermins[i].m_pagesNums);
	for (int i = 1; i < termin.m_subTermins.size(); ++i)
		for (int j = 0; j < termin.m_subTermins.size() - i; ++j)
			if (termin.m_subTermins[j].m_pagesNums[0] > termin.m_subTermins[j + 1].m_pagesNums[0])
			{
				Termin temp{termin.m_subTermins[j]};
				termin.m_subTermins[j] = termin.m_subTermins[j + 1];
				termin.m_subTermins[j + 1] = temp;
			}
	for (int i = 0; i < termin.m_subTermins.size(); ++i)
		sortByPages_private(termin.m_subTermins[i]);
}

void Termin::setName(const std::string& newName)
{
	m_name = newName;
	m_id = makeHash(*this);
}

bool Termin::replacePageNum(const int oldPageNum, const int newPageNum)
{
	auto position{ std::find(m_pagesNums.begin(), m_pagesNums.end(), oldPageNum) };
	if (!(position == m_pagesNums.end()) && std::find(m_pagesNums.begin(), m_pagesNums.end(), newPageNum) == m_pagesNums.end())
	{
		std::replace(m_pagesNums.begin(), m_pagesNums.end(), oldPageNum, newPageNum);
		m_id = makeHash(*this);
		return true;
	}
	return false;
}

void Termin::sortByAlphabet()
{
	sortByAlphabet_private(*this);
}

void Termin::sortByPages()
{
	sortByPages_private(*this);
}