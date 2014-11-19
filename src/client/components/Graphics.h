#define GLM_FORCE_RADIANS
#ifndef GRAPHICS_H
#define GRAPHICS_H

#define M_PI 3.14159265359
#define M_PI_2 1.57079632679489661923

#include <string>
#include <stack>
#include "../Component.h"
#include "../../tools/quad2.h"
#include "../../tools/quad3.h"
#include "../../../other/sdl/include/SDL.h"
#include "../../../other/glew/include/glew.h"
#include "../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../other/glm/gtc/type_ptr.hpp"

using namespace std;
class Resources;

///<summary>Graphics component</summary>
class Graphics : public Component{
public:
	///<summary>Shader data IDs</summary>
	enum {
		SHADER_POS=0,
		SHADER_TEXMAP,
		SHADER_NORMAL
		//SHADER_COLOR
	};

	///<summary>Stores 'c' to 'm_Client'</summary>
	Graphics(Client* c) : Component(c){};
	///<summary>Initialization callback</summary>
	///<returns>true if all right, false if error found</returns>
	bool OnInit();
	///<summary>Input callback</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	void OnInput(unsigned char* keys,int xrel,int yrel,int wheel);
	///<summary>State change callback</summary>
	///<param name="lastState">Last state</param>
	void OnStateChange(STATE lastState);
	///<summary>Quit callback</summary>
	void OnQuit();
	///<summary>3d render callback</summary>
	void OnRender();
	///<summary>2d render callback</summary>
	void OnRender2d();
	///<summary>Tick callback</summary>
	void OnTick();
	///<summary>System message callback</summary>
	void OnMessage(int type,char* value);

	///<summary>Convertes SDL_Surface in RGBA mode</summary>
	///<param name="src">Source</param>
	void to_RGBA(SDL_Surface* &src);
	///<summary>Convertes screen coords to pixels</summary>
	///<param name="coord">Coord</param>
	int to_pixels(float coord);
	///<summary>Convertes pixels to screen coords</summary>
	///<param name="pix">Pixels</param>
	float to_screen(int pix);
	///<summary>Updates color uniform in 3d shader</summary>
	///<param name="color">Color</param>
	void SetColor(vec4 color);
	///<summary>Updates light uniform in 3d shader</summary>
	///<param name="light">Use light?</param>
	void SetLight(bool light);
	///<summary>Updates color uniform in 2d shader</summary>
	///<param name="color">Color</param>
	void SetColor2d(vec4 color);
	///<summary>Updates position uniform in 2d shader</summary>
	///<param name="pos">Position</param>
	void SetPos2d(glm::vec2 pos);
	///<summary>Updates viewProjectionMatrix uniform in 3d shader</summary>
	///<param name="position">Position of the camera</param>
	///<param name="center">Vector directed forward the camera</param>
	///<param name="up">Vector directed upforwards the camera</param>
	void SetViewMatrix(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up);
	///<summary>Updates modelMatrix uniform in 3d shader</summary>
	///<param name="position">Position of the model</param>
	///<param name="rotation">Rotation of the model</param>
	///<param name="size">Size of the model</param>
	void SetModelMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &size);
	///<summary>Translates current model matrix</summary>
	///<param name="position">Position of the model</param>
	void Translate(const glm::vec3 &position);
	///<summary>Rotates current model matrix</summary>
	///<param name="rotation">Rotation of the model</param>
	void RotateX(const glm::vec3 &rotation);
	///<summary>Rotates current model matrix</summary>
	///<param name="rotation">Rotation of the model</param>
	void RotateY(const glm::vec3 &rotation);
	///<summary>Rotates current model matrix</summary>
	///<param name="rotation">Rotation of the model</param>
	void RotateZ(const glm::vec3 &rotation);
	///<summary>Pushes current model matrix to the stack</summary>
	void PushMatrix();
	///<summary>Restores current model matrix from the stack</summary>
	void PopMatrix();
	///<summary>Stack of the model matrix</summary>
	stack<glm::mat4> ModelMatrixStack;

	///<summary>Light uniform in 3d shader</summary>
	unsigned int lightUniform;
	///<summary>Color uniform in 3d shader</summary>
	unsigned int colorUniform3d;
	///<summary>viewProjectionMatrix uniform in 3d shader</summary>
	unsigned int viewProjectionMatrixUniform;
	///<summary>modelMatrix uniform in 3d shader</summary>
	unsigned int modelMatrixUniform;
	///<summary>normalMatrix uniform in 3d shader</summary>
	unsigned int normalMatrixUniform;

	///<summary>Color uniform in 2d shader</summary>
	unsigned int colorUniform2d;
	///<summary>Aspect uniform in 2d shader</summary>
	unsigned int aspectUniform2d;
	///<summary>Position uniform in 2d shader</summary>
	unsigned int posUniform2d;

	///<summary>Aspect (screen width/screen height)</summary>
	float aspect;
	///<summary>Screen quad</summary>
	quad2 screen;
	///<summary>Height in pixels</summary>
	float screenSize;

	///<summary>Data loader</summary>
	class Resources* m_Resources;

	///<summary>3d projection matrix</summary>
	glm::mat4 perspectiveMatrix;
	///<summary>3d view matrix</summary>
	glm::mat4 viewMatrix;
	///<summary>3d model matrix</summary>
	glm::mat4 modelMatrix;
	///<summary>3d normal matrix</summary>
	glm::mat4 normalMatrix;
	///<summary>3d viewProjection matrix</summary>
	glm::mat4 viewProjectionMatrix;
};

#endif GRAPHICS_H