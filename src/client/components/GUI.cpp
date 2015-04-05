#include "GUI.h"
#include "../Client.h"
#include "Graphics.h"
#include "graphics/Resources.h"
#include "graphics/Text.h"
#include "graphics/Model2d.h"
#include "graphics/TextGenerator.h"

class GUI* mp_GUI;
GUI* m_GUI(){ return mp_GUI; }

Model2d* test;
GUI::GUI() : Component(){
	mp_GUI = this;
	fpsObject=new Text();
	fpsObject->depth = 1;
	fpsObject->addText(std::to_string(m_Client()->fps), Resources::FONT_BIG, TextGenerator::ALIGN_RIGHT_TOP, true);
	fpsObject->create();
	fpsObject->position = m_Graphics()->screen.p11;
	fpsTitle=new Text();
	fpsTitle->depth = 1;
	fpsTitle->addText("FPS=",Resources::FONT_BIG,TextGenerator::ALIGN_RIGHT_TOP,false);
	fpsTitle->create();
	fpsTitle->position=fpsObject->data->geometry.p01+fpsObject->position;
	float round=0.05f;
	fill(quad2(fpsTitle->data->geometry.p00+fpsTitle->position,fpsObject->data->geometry.p10+fpsObject->position,fpsTitle->data->geometry.p01+fpsTitle->position,fpsObject->data->geometry.p11+fpsObject->position),quad2(fpsTitle->data->geometry.p00+fpsTitle->position-vec2(round/2,round/2),fpsObject->data->geometry.p10+fpsObject->position-vec2(0,round/2),fpsTitle->data->geometry.p01+fpsTitle->position-vec2(round/2,0),fpsObject->data->geometry.p11+fpsObject->position));
}
GUI::~GUI(){
	delete fpsObject;
	delete fpsTitle;
	mp_GUI = NULL;
}
void GUI::Input(unsigned char* keys,int xrel,int yrel,int wheel){}
void GUI::StateChange(STATE lastState){}
void GUI::Render(){}
void GUI::RenderBillboard(){}
void GUI::Render2d(){
	test->render();
	fpsObject->setText(std::to_string(m_Client()->fps));
	fpsObject->render();
	fpsTitle->render();
}
void GUI::Tick(){}
void GUI::Message(int type,char* value){}
void GUI::fill(quad2 in,quad2 out){
	test=new Model2d();
	test->addRectangle(in,out);
	test->coloring=vec4(0,0,0,0.5f);
	test->create();
}