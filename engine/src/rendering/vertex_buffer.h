#include <gl/glew.h>

#include <cstdint>

#include "utils/vertex.h"
// Wrapper around a vertex Buffer

class VertexBuffer
{
public:

	VertexBuffer(int numVerts, int numTris) : m_numVerts(numVerts), m_numElts(numTris)
	{
		// Vertex Arrray Object
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vbo);
		
		// Vertex Buffer

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vao);

		glBufferData(GL_ARRAY_BUFFER, m_numVerts*sizeof(Vertex), nullptr, GL_STATIC_DRAW);

		// Vertex Buffer Attributes:
		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		// Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normals)));
		// Texture Coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoords)));

		// Element Buffer		
		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numTris * 3 * sizeof(unsigned int), nullptr, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

	}

	void PushVertices(const std::vector<Vertex>& verts, const std::vector<unsigned int> &indices)
	{
		// Add Vertices at the End, resizing as neccessary
		
		GLsizei numVerts_cached = m_numVerts;
		GLsizei numTris_cached = m_numElts;

		m_numVerts + verts.size();

		assert(indices.size() % 3 == 0 && "Number of indcies must be divisible by 3, because triangle elements are used");

		resizeVBO(m_numVerts + verts.size());
		resizeEBO(m_numElts + indices.size() / 3);
	
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, numVerts_cached, m_numVerts, verts.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, numTris_cached * 3, m_numElts * 3, indices.data());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void resizeVBO(int numVerts)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(Vertex), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_numVerts = numVerts;
	}

	void resizeEBO(int numElts)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElts * 3 * sizeof(unsigned int), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		m_numElts = numElts;
	}
	
	void removeVerts(int vertOffset, int size)
	{
		// Apparently there is no proper way of doing this...

		// 1.) (remove the region in the Buffer)

		// 2.) map the buffer into CPU memory

		// 3.) write the trailing memory back into the GPU buffer, so no holes are left

		
		glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
		Vertex* v = static_cast<Vertex*>(glMapBufferRange(GL_ARRAY_BUFFER, vertOffset, size, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));

		// overwrite the deleted region

	}

	void removeElements(int elementOffset, int size)
	{

	}

private:
	GLsizei m_numVerts;
	GLsizei m_numElts;
	
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	
};
