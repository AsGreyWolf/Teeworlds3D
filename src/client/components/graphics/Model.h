#ifndef MODEL_H
#define MODEL_H

#include <vector>

class Graphics;
#include "../../../tools/quad2.h"
#include "../../../tools/quad3.h"
#include "../../../../other/glew/include/glew.h"
#include "../../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../../other/glm/gtc/type_ptr.hpp"

///<summary>3d Model object</summary>
class Model{
public:
	///<summary>Texture used in shaders</summary>
	GLuint texture;
	///<summary>Position of the model</summary>
	glm::vec3 position;
	///<summary>Ratation of the model</summary>
	glm::vec3 rot;
	///<summary>Link to the Graphics component</summary>
	class Graphics* m_Graphics;
	glm::vec4 coloring;

	///<summary>Creates the model and buffers in the GPU</summary>
	///<param name="type">Type of the verts (GL_TRIANGLES)</param>
	///<param name="g">Link to the Graphics component</param>
	///<param name="lighting">Use lighting?</param>
	Model(int type,Graphics* g,bool lighting=true);
	///<summary>Creates the model and buffers in the GPU</summary>
	///<param name="g">Link to the Graphics component</param>
	Model(Graphics* g,bool lighting=true);
	~Model();
	///<summary>Fills the buffers in the GPU with values in the RAM</summary>
	void create();
	///<summary>Pushes the model into the shader</summary>
	void render();
	///<summary>Deletes the buffers in the GPU and RAM</summary>
	void remove();
	///<summary>Deletes the buffers in the RAM</summary>
	void clear();
	///<summary>Appends vector of vertex to the buffers in the RAM</summary>
	///<param name="v">Vertex positions</param>
	///<param name="n">Vertex normals</param>
	///<param name="t">Vertex UV coordinates</param>
	void addVertex(std::vector<glm::vec3> v,std::vector<glm::vec3> n,std::vector<glm::vec2> t);
	///<summary>Appends 1 vertex to the buffers in the RAM</summary>
	///<param name="v">Vertex position</param>
	///<param name="n">Vertex normal</param>
	///<param name="t">Vertex UV coordinates</param>
	void addVertex(glm::vec3 v,glm::vec3 n,glm::vec2 t);
	///<summary>Appends 1 quad to the buffers in the RAM</summary>
	///<param name="v">Vertex positions</param>
	///<param name="n">Vertex normal</param>
	///<param name="t">Vertex UV coordinates</param>
	void addQuad(quad3 v,glm::vec3 n,quad2 t);

	///<summary>Add generated sphere data in the buffers</summary>
	///<param name="rings">Number of rings</param>
	///<param name="sectors">Number of sectors</param>
	///<param name="lengthiness">3-axis deformation</param>
	///<param name="radius">Radius</param>
	///<param name="texcoord">UV coordinates</param>
	///<param name="backstart">Reverse generation</param>
	void addSphere(int rings, int sectors,vec3 lengthiness,float radius,quad2 texcoord,bool backstart);

	///<summary>Add generated data in the buffers from the OBJ file</summary>
	///<param name="filename">Path to the file from data folder</param>
	void addObjModel(std::string filename);

private:
	///<summary>Vertex positions buffer in the RAM</summary>
	std::vector <glm::vec3> vertex;
	///<summary>Vertex normals buffer in the RAM</summary>
	std::vector <glm::vec3> normal;
	///<summary>Vertex UV coordinates buffer in the RAM</summary>
	std::vector <glm::vec2> texcoord;
	///<summary>Vertex array object</summary>
	GLuint VAO;
	///<summary>Vertex positions buffer in the GPU</summary>
	GLuint vbuffer;
	///<summary>Vertex normals buffer in the GPU</summary>
	GLuint nbuffer;
	///<summary>Vertex UV coordinates buffer in the GPU</summary>
	GLuint tbuffer;
	///<summary>Type of the model (GL_TRIANGLES)</summary>
	int type;
	///<summary>Use lighting?</summary>
	bool lighting;
};

#endif