#pragma once
#include <vector>
#include <string>

class Termin;

class Termin
{
	Termin* m_parentTermin;
	std::vector<int> m_pagesNums;
	std::vector<Termin> m_subTermins;
	std::string m_name;

	void printPages();
	//-1 not present, otherwise return position
	int subTerminNamePos(const std::string& name);
	void printPointer(Termin termin, int level);
	void findParentsWithSubTerminName_private(Termin* termin, const std::string name, std::vector<Termin*>& result);
	void findTermins_private(Termin* termin, const std::string name, std::vector<Termin*>& result);
	void sortByAlphabet_private(Termin& termin);
	void sortByPages_private(Termin& termin);
	void sortInts(std::vector<int>& pagesNums);

public:
	Termin(const std::string& name = "", std::vector<int> pagesNums = {});
	bool addSubTermin(Termin subTermin);
	bool addPage(const int pageNum);
	bool deletePage(const int pageNum);
	bool deleteSubTermin(const std::string& name);
	void printTermin();
	void printSubjectPointer();
	void printTerminAndSubTermins(Termin* termin);
	void findParentsWithSubTerminName(const std::string name, std::vector<Termin*>& result);
	void findTermins(const std::string name, std::vector<Termin*>& result);
	void setName(const std::string& newName);
	bool replacePageNum(const int oldPageNum, const int newPageNum);
	void sortByAlphabet();
	void sortByPages();
};
