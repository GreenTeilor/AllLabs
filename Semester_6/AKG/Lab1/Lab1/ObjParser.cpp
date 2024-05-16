#include "ObjParser.h"
#include <regex>
#include <sstream>
#include <iostream>

#define TIMER

#ifdef TIMER
#include <chrono>
#endif

extern double parseTime;
double ifsTime = 0.0;

ObjParser::ObjParser(std::string filePath) : m_file{ filePath }
{
	m_vertices.reserve(1000000);
	m_tVertices.reserve(1000000);
	m_nVertices.reserve(1000000);
	m_faces.reserve(1000000);
}

std::vector<std::string> splitString(std::string& str) {
	std::istringstream iss(str);
	std::vector<std::string> tokens;
	std::string token;
	while (iss >> token) {
		if (!token.empty()) {
			tokens.push_back(token);
		}
	}
	return tokens;
}

std::vector<std::string> splitByChar(const std::string& str, char c) {
	std::string segment;
	std::vector<std::string> seglist;
	std::stringstream stream{ str };

	while (getline(stream, segment, c))
	{
		seglist.push_back(segment);
	}
	return seglist;
}

void ObjParser::next()
{
	/*
	std::string line{};
	const std::regex pattern{ R"(^s*$)" };
	while (getline(m_file, line))
	{
		if (!std::regex_match(line, pattern) && line[0] != '#')
		{
			std::regex words_regex("\\S+");
			std::vector<std::string> tokens{
				std::sregex_token_iterator(line.begin(), line.end(), words_regex),
				std::sregex_token_iterator()
			};

			if (ObjType::typeMap.find(tokens.at(0)) != ObjType::typeMap.end())
				return ObjComponent{ ObjType::typeMap.at(tokens.at(0)), std::vector<std::string>{tokens.begin() + 1, tokens.end()} };
		}
	}
	return ObjComponent{ ObjType::FILE_END, std::vector<std::string>{} };
	*/

	std::string line{};
	//std::vector<Face::Part> partsOrder{ Face::Part::V, Face::Part::VT, Face::Part::VN };
	//const std::vector< std::vector <std::vector<float>>* > vectorsOrder{ &m_vertices, &m_tVertices, &m_nVertices };
	while (getline(m_file, line))
	{

		if (!line.empty() && (line.front() == 'v' || line.front() == 'vt' || line.front() == 'vn' || line.front() == 'f'))
		{
#ifdef TIMER
			auto ifsBeg = std::chrono::high_resolution_clock::now();
#endif
			//std::vector<std::string> tokens{};
			//tokens = splitString(line);


			std::vector<float> coordinates{};
			if (line.find("v", 0) != std::string::npos)
			{
				//for (int i = 1; i < tokens.size(); ++i)
				//	coordinates.push_back(atof(tokens[i].c_str()));
				//m_vertices.push_back(coordinates);
				std::istringstream ss(line);
				ss >> line;
				float x, y, z, w = 1.0f;
				ss >> x >> y >> z;
				m_vertices.push_back(std::vector<float>{x, y, z, w});
			}
			else if (line.find("vt", 0) != std::string::npos)
			{
				//for (int i = 1; i < tokens.size(); ++i)
				//	coordinates.push_back(atof(tokens[i].c_str()));
				//m_tVertices.push_back(coordinates);
				std::istringstream ss(line);
				ss >> line;
				float x, y, z, w = 1.0f;
				ss >> x >> y >> z;
				m_tVertices.push_back(std::vector<float>{x, y, z, w});
			}
			else if (line.find("vn", 0) != std::string::npos)
			{
				//for (int i = 1; i < tokens.size(); ++i)
				//	coordinates.push_back(atof(tokens[i].c_str()));
				//m_nVertices.push_back(coordinates);
				std::istringstream ss(line);
				ss >> line;
				float x, y, z, w = 1.0f;
				ss >> x >> y >> z;
				m_nVertices.push_back(std::vector<float>{x, y, z, w});
			}
			else if (line.find("f", 0) != std::string::npos)
			{
				/*
				std::vector<Face::Component> components;
				std::replace(token.begin(), token.end(), '/', ' ');
				for (int i = 1; i < tokens.size(); ++i)
				{
					std::vector<std::string> componentsStr = splitByChar(tokens[i], '/');
					Face::Component component{};
					for (int i = 0; i < componentsStr.size(); ++i)
						component.insert({ partsOrder[i], (*vectorsOrder[i])[atoi(componentsStr[i].c_str()) - 1] });
					components.push_back(component);
				}
				m_faces.push_back(components);
				*/
				std::vector<Face::Component> components{};
				std::istringstream ss(line);
				ss >> line;
				std::vector<std::string> tokens(
					std::istream_iterator<std::string>{ss},
					std::istream_iterator<std::string>{}
				);
				if (tokens.size() == 3)
				{
					for (auto& token : tokens)
					{
						size_t vertexInd, textureInd, normalInd;
						replace(token.begin(), token.end(), '/', ' ');
						std::istringstream ss(token);
						ss >> vertexInd >> textureInd >> normalInd;
						Face::Component component{};
						component.insert({ Face::Part::V, m_vertices[vertexInd - 1] });
						if (textureInd - 1 < m_tVertices.size())
							component.insert({ Face::Part::VT, m_tVertices[textureInd - 1] });
						if (normalInd - 1 < m_nVertices.size())
							component.insert({ Face::Part::VN, m_nVertices[normalInd - 1] });
						components.push_back(component);
					}
					m_faces.push_back(components);
				}
				else if (tokens.size() == 4)
				{
					for (auto& token : tokens)
					{
						size_t vertexInd, textureInd, normalInd;
						replace(token.begin(), token.end(), '/', ' ');
						std::istringstream ss(token);
						ss >> vertexInd >> textureInd >> normalInd;
						Face::Component component{};
						component.insert({ Face::Part::V, m_vertices[vertexInd - 1] });
						if (textureInd - 1 < m_tVertices.size())
							component.insert({ Face::Part::VT, m_tVertices[textureInd - 1] });
						if (normalInd - 1 < m_nVertices.size())
							component.insert({ Face::Part::VN, m_nVertices[normalInd - 1] });
						components.push_back(component);
					}
					m_faces.push_back(std::vector<Face::Component>{components[0], components[1], components[2]});
					m_faces.push_back(std::vector<Face::Component>{components[0], components[2], components[3]});
				}
			}

#ifdef TIMER
			std::chrono::duration<double> ftime = std::chrono::high_resolution_clock::now() - ifsBeg;
			ifsTime += ftime.count();
#endif
		}
	}
}

ObjParser::~ObjParser()
{
	for (auto& face : m_faces)
	{
		//delete &face;
	}
}

std::vector<Face> ObjParser::parse()
{
	ObjComponent component{};
#ifdef TIMER
	auto beg = std::chrono::high_resolution_clock::now();
#endif
	next();
#ifdef TIMER
	std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - beg;
	parseTime += time.count();
#endif
	std::cout << "Ifs time:" << ifsTime << std::endl;
	std::cout << "Parse time" << parseTime << std::endl;
	return m_faces;
}
