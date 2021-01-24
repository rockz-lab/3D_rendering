#pragma once

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "utils/vertex.h"

// wavefront basic elements:

// v:	vertices
// vt:	texture coordinates
// vn:	vertex normals
// f:	face (indices)


void loadOBJ(std::string fileName, std::vector<Vertex>& verts, std::vector<unsigned int>& indices)
{
	struct vec3
	{
		float x, y, z;
	};

	using namespace std;

	ifstream file;
	vector<vec3> vertices;
	vector<vec3> normals;
	//vector<unsigned int> indices;

	// open file

	int n = 0;

	file.open(fileName);
	if (file.is_open())
	{
		string line;

		while (getline(file, line))
		{
			// get first word
			string first;

			stringstream ss(line);
			ss >> first;

			float x, y, z;

			if (first.c_str()[0] == '#')
			{
				// ignore line
			}
			else if (first == "v")
			{
				ss.ignore();	// ignore command
				//Vertex vert;
				ss >> x >> y >> z;

				Vertex v;
				v.pos = { x, y, z };
				verts.push_back(v);


				//cout << x << endl;
				//cout << z << endl;
				//cout << y << endl;
			}
			else if (first == "vn")
			{
				ss.ignore();
				//Vertex vert;
				ss >> x >> y >> z;

				normals.push_back({ x, y, z });
			}


			if (first == "f")
			{
				ss.ignore();	// ignore command

				// read all 
				string index;

				vector<unsigned int> faceIndices; // = vector<unsigned int>(istream_iterator<unsigned int>(ss), std::istream_iterator<unsigned int>());
				vector<unsigned int> normalIndices;
				while (getline(ss, index, '/'))
				{
					faceIndices.push_back(stoi(index));

					getline(ss, index, '/');
					getline(ss, index, ' ');

					normalIndices.push_back(stoi(index));
				}

				if (faceIndices.size() == 4)
				{
					// we're dealing with quads --> Triangulate them!
					// 0---1
					// | \ |
					// 3---2

					indices.push_back(faceIndices[0] - 1);
					indices.push_back(faceIndices[2] - 1);
					indices.push_back(faceIndices[3] - 1);

					indices.push_back(faceIndices[0] - 1);
					indices.push_back(faceIndices[1] - 1);
					indices.push_back(faceIndices[2] - 1);

					// normal indices corresponding to vertex indices


					verts[faceIndices[0] - 1].normals = { normals[normalIndices[0] - 1].x, normals[normalIndices[0] - 1].y, normals[normalIndices[0] - 1].z };
					verts[faceIndices[1] - 1].normals = { normals[normalIndices[1] - 1].x, normals[normalIndices[1] - 1].y, normals[normalIndices[1] - 1].z };
					verts[faceIndices[2] - 1].normals = { normals[normalIndices[2] - 1].x, normals[normalIndices[2] - 1].y, normals[normalIndices[2] - 1].z };
					verts[faceIndices[3] - 1].normals = { normals[normalIndices[3] - 1].x, normals[normalIndices[3] - 1].y, normals[normalIndices[3] - 1].z };
				}
				else if (faceIndices.size() == 3)
				{
					cout << "Triangle" << endl;
				}



			}
		}
		file.close();
	}
	else
	{
		cout << "Model load failed! .obj file could not be opened." << endl;
	}

	// read verts and indices


}
