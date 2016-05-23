#include "Model2d.h"

#include <client/components/Graphics.h>
#include <client/components/graphics/shaders/Shader2d.h>

Model2d::Model2d(int t) {
	type = t;
	data = Model2dDataPtr();
	position = glm::vec2(0, 0);
	color = glm::vec4(1, 1, 1, 0);
	depth = 0.0f;
	g_Shader2d()->RegisterModel(this);
}
Model2d::Model2d(const Model2d &second) : Model(second) {
	type = second.type;
	data = second.data;
	position = second.position;
	color = second.color;
	depth = second.depth;
	texture = second.texture;
	g_Shader2d()->RegisterModel(this);
}
Model2d &Model2d::operator=(const Model2d &second) {
	data.reset();
	type = second.type;
	data = second.data;
	position = second.position;
	color = second.color;
	depth = second.depth;
	texture = second.texture;
	return *this;
}
Model2d::~Model2d() {
	g_Shader2d()->UnregisterModel(this);
	data.reset();
}
void Model2d::Render() {
	texture.Bind();
	g_Shader2d()->SetColor(color);
	g_Shader2d()->SetPosition(position, depth);
	data->Render(type);
}
void Model2d::Add(const Geometry2d &geom) { data->Add(geom); }

Model2d::Data::Data() {
	g_Graphics(); // TODO: fix
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbuffer);
	glGenBuffers(1, &tbuffer);
}
Model2d::Data::~Data() {
	g_Graphics(); // TODO: fix
	glDeleteBuffers(1, &vbuffer);
	glDeleteBuffers(1, &tbuffer);
	glDeleteVertexArrays(1, &vao);
}
void Model2d::Data::Render(int type) {
	Validate();
	g_Graphics(); // TODO: fix
	glBindVertexArray(vao);
	glDrawArrays(type, 0, geometry.v.size());
}
void Model2d::Data::Validate() {
	if (!valid) {
		g_Graphics(); // TODO: fix
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * geometry.v.size() * 2,
		             geometry.v.size() > 0 ? &geometry.v[0] : NULL, GL_STATIC_DRAW);
		glVertexAttribPointer(SHADER_POS, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SHADER_POS);

		glBindBuffer(GL_ARRAY_BUFFER, tbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * geometry.t.size() * 2,
		             geometry.t.size() > 0 ? &geometry.t[0] : NULL, GL_STATIC_DRAW);
		glVertexAttribPointer(SHADER_TEXMAP, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SHADER_TEXMAP);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	valid = true;
}
void Model2d::Data::Add(const Geometry2d &geom) {
	geometry += geom;
	valid = false;
}