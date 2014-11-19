#include "Model.h"
#include <string>
#include <cstdio>
#include <map>
#include <cstring>
#include <fstream>
#include <sstream>
#include "../Graphics.h"
#include "../../Client.h"
#include "Resources.h"
#include "../../../../other/glm/gtc/matrix_transform.hpp"

void Model::render(){
	m_Graphics->PushMatrix();

	m_Graphics->SetModelMatrix(position,rot,vec3(1,1,1));
	m_Graphics->SetColor(coloring);

	//if(this!=m_Graphics->m_Resources->coordsModel)
	//m_Graphics->m_Resources->coordsModel->render();

	glBindTexture(GL_TEXTURE_2D,texture);
	glBindVertexArray(VAO);
	m_Graphics->SetLight(lighting);
	glDrawArrays(type , 0, vertex.size());
	m_Graphics->PopMatrix();
}

Model::Model(int type,Graphics* g,bool lighting){
	this->lighting=lighting;
	m_Graphics=g;
	this->type=type;
	position=vec3(0,0,0);
	rot=vec3(0,0,0);
	coloring=vec4(0,0,0,0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1,&vbuffer);
	glGenBuffers(1,&nbuffer);
	glGenBuffers(1,&tbuffer);
	texture=g->m_Resources->textureBlank;
}
Model::Model(Graphics* g,bool lighting){
	this->lighting=lighting;
	m_Graphics=g;
	type=GL_TRIANGLES;
	position=vec3(0,0,0);
	rot=vec3(0,0,0);
	coloring=vec4(0,0,0,0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1,&vbuffer);
	glGenBuffers(1,&nbuffer);
	glGenBuffers(1,&tbuffer);
	texture=g->m_Resources->textureBlank;
}
void Model::create(){
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex.size()*3, &vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_POS, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_POS);

	glBindBuffer(GL_ARRAY_BUFFER,tbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texcoord.size()*2, &texcoord[0], GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_TEXMAP, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_TEXMAP);

	glBindBuffer(GL_ARRAY_BUFFER,nbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normal.size()*3, &normal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER,0);
}

Model::~Model(){
	remove();
}

void Model::remove(){
	glDeleteBuffers(1,&vbuffer);
	glDeleteBuffers(1,&nbuffer);
	glDeleteBuffers(1,&tbuffer);
	glDeleteVertexArrays(1,&VAO);
	clear();
}

void Model::clear(){
	vertex.clear();
	normal.clear();
	texcoord.clear();
}

void Model::addVertex(vec3 v,vec3 n,vec2 t){
	vertex.push_back(v);
	normal.push_back(n);
	texcoord.push_back(t);
}

void Model::addVertex(std::vector<vec3> v,std::vector<vec3> n,std::vector<vec2> t){
	vertex.insert(vertex.end(),v.begin(),v.end());
	normal.insert(normal.end(),n.begin(),n.end());
	texcoord.insert(texcoord.end(),t.begin(),t.end());
}

void Model::addQuad(quad3 v,vec3 n,quad2 t){
	addVertex(v.p1,n,t.p10);
	addVertex(v.p2,n,t.p00);
	addVertex(v.p3,n,t.p01);

	addVertex(v.p1,n,t.p10);
	addVertex(v.p3,n,t.p01);
	addVertex(v.p4,n,t.p11);
}

void Model::addSphere(int rings, int sectors,vec3 lengthiness,float radius,quad2 texc,bool backstart){

	float const R = 1./(float)(rings-1);
	float const S = 1./(float)(sectors-1);
	int r, s;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec2> texcoords;

	vertices.resize(rings * sectors);
	normals.resize(rings * sectors);
	texcoords.resize(rings * sectors);
	std::vector<vec3>::iterator v = vertices.begin();
	std::vector<vec3>::iterator n = normals.begin();
	std::vector<vec2>::iterator t = texcoords.begin();
	float tcsizex=texc.p10.x-texc.p00.x;
	float tcsizey=texc.p01.y-texc.p00.y;
	if(backstart)
		for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
			float const z = -sin( -M_PI_2 + M_PI * r * R );
			float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
			float const y = sin(2*M_PI * s * S) * sin( M_PI * r * R );
			*t++ = vec2(texc.p00.x+s*S*tcsizex,texc.p00.y+r*R*tcsizey);
			*v++ = vec3(-x * radius*lengthiness.x,y * radius*lengthiness.y,z*radius*lengthiness.z);
			*n++ = vec3(-x,y,z);
		}
	else
		for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
			float const z = -sin( -M_PI_2 + M_PI * r * R );
			float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
			float const y = sin(2*M_PI * s * S) * sin( M_PI * r * R );
			*t++ = vec2(texc.p00.x+s*S*tcsizex,texc.p00.y+r*R*tcsizey);
			*v++ = vec3(x * radius*lengthiness.x,y * radius*lengthiness.y,z*radius*lengthiness.z);
			*n++ = vec3(x,y,z);
		}
		if(backstart)
			for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
				addVertex(vertices[ r * sectors + s+1],normals[ r * sectors + s+1],texcoords[ r * sectors + s+1]);

				addVertex(vertices[(r+1) * sectors + s+1],normals[(r+1) * sectors + s+1],texcoords[(r+1) * sectors + s+1]);

				addVertex(vertices[ (r+1) * sectors + (s)],normals[ (r+1) * sectors + (s)],texcoords[ (r+1) * sectors + (s)]);

				addVertex(vertices[ r * sectors + s+1],normals[ r * sectors + s+1],texcoords[ r * sectors + s+1]);

				addVertex(vertices[ (r+1) * sectors + (s)],normals[ (r+1) * sectors + (s)],texcoords[ (r+1) * sectors + (s)]);

				addVertex(vertices[ r * sectors + (s)],normals[ r * sectors + (s)],texcoords[ r * sectors + (s)]);
			}
		else
			for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
				addVertex(vertices[ r * sectors + s],normals[ r * sectors + s],texcoords[ r * sectors + s]);

				addVertex(vertices[(r+1) * sectors + s],normals[(r+1) * sectors + s],texcoords[(r+1) * sectors + s]);

				addVertex(vertices[ (r+1) * sectors + (s+1)],normals[ (r+1) * sectors + (s+1)],texcoords[ (r+1) * sectors + (s+1)]);

				addVertex(vertices[ r * sectors + s],normals[ r * sectors + s],texcoords[ r * sectors + s]);

				addVertex(vertices[ (r+1) * sectors + (s+1)],normals[ (r+1) * sectors + (s+1)],texcoords[ (r+1) * sectors + (s+1)]);

				addVertex(vertices[ r * sectors + (s+1)],normals[ r * sectors + (s+1)],texcoords[ r * sectors + (s+1)]);
			}
}

void Model::addObjModel(string filename){
	std::ifstream file(m_Graphics->m_Client->GetDataFile(filename));
	if(!file.good()) {
		file.close();
		return;
	}
	std::string line;
	std::vector <vec3> verts;
	std::vector <vec3> norms;
	std::vector <vec2> texs;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string com;
		if (!(iss >> com)) { continue; }
		if(com.compare("v")==0){
			vec3 v;
			if (!(iss >> v.x>>v.y>>v.z)) { continue; }
			vec3 buf=v;
			buf*=32;
			verts.push_back(buf);
		}
		else if(com.compare("vn")==0){
			vec3 vn;
			if (!(iss >> vn.x>>vn.y>>vn.z)) { continue; }
			norms.push_back(vn);
		}
		else if(com.compare("vt")==0){
			vec2 vt;
			if (!(iss >> vt.x>>vt.y)) { continue; }
			vt.y=1-vt.y;
			texs.push_back(vt);
		}
		else if(com.compare("f")==0){
			if(norms.size()>0 && texs.size()>0){
				int v1,v2,v3,t1,t2,t3,n1,n2,n3;
				char c;
				if (!(iss >>v1>>c>>t1>>c>>n1>>v2>>c>>t2>>c>>n2>>v3>>c>>t3>>c>>n3)) { continue; }
				addVertex(verts[v1-1],norms[n1-1],texs[t1-1]);
				addVertex(verts[v2-1],norms[n2-1],texs[t2-1]);
				addVertex(verts[v3-1],norms[n3-1],texs[t3-1]);
			}
			else if(norms.size()>0){
				int v1,v2,v3,n1,n2,n3;
				char c;
				if (!(iss >>v1>>c>>c>>n1>>v2>>c>>c>>n2>>v3>>c>>c>>n3)) { continue; }
				addVertex(verts[v1-1],norms[n1-1],vec2(0,0));
				addVertex(verts[v2-1],norms[n2-1],vec2(0,0));
				addVertex(verts[v3-1],norms[n3-1],vec2(0,0));
			}
			else if(texs.size()>0){
				int v1,v2,v3,t1,t2,t3;
				char c;
				if (!(iss >>v1>>c>>t1>>c>>v2>>c>>t2>>c>>v3>>c>>t3)) { continue; }
				addVertex(verts[v1-1],vec3(0,0,1),texs[t1-1]);
				addVertex(verts[v2-1],vec3(0,0,1),texs[t2-1]);
				addVertex(verts[v3-1],vec3(0,0,1),texs[t3-1]);
			}
			else{
				int v1,v2,v3;
				if (!(iss >>v1>>v2>>v3)) { continue; }
				addVertex(verts[v1-1],vec3(0,0,1),vec2(0,0));
				addVertex(verts[v2-1],vec3(0,0,1),vec2(0,0));
				addVertex(verts[v3-1],vec3(0,0,1),vec2(0,0));
			}
		}
	}
	file.close();
}