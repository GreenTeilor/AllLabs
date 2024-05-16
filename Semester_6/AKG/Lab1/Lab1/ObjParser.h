#pragma once
#include <fstream>
#include "ObjComponent.h"
#include "Face.h"

class ObjParser
{
private:
	std::ifstream m_file;
	std::vector <std::vector<float>> m_vertices;
	std::vector <std::vector<float>> m_tVertices;
	std::vector <std::vector<float>> m_nVertices;
	std::vector<Face> m_faces;
	std::map<std::string, std::vector <std::vector<float>>&> m_typeMap;

public:
	ObjParser(std::string filePath);
	void next();
	std::vector<Face> parse();
	~ObjParser();
};

