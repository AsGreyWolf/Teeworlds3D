#include "Map.h"
#include <stdio.h>
#include <cstring>
#include "../../shared/System.h"
#include "../../shared/World.h"
#include "../../shared/world/Tile.h"
#include "../Client.h"
#include "Graphics.h"
#include "graphics/Resources.h"
#include "graphics/Model.h"
//TODO: move physical object to shared

class Map* pMap;
Map* g_Map(){ return pMap; }

Map::Map() : Component(){
	pMap = this;
}
Map::~Map(){
	UnLoad();
	pMap = NULL;
}
void Map::Input(unsigned char* keys,int xrel,int yrel,int wheel){}
void Map::StateChange(STATE lastState){
	if(!lastState.ingame && g_Client()->state.ingame)
	{
		m_Model=new Model(g_Graphics());
		Load("1234");
		return;
	}
	if(lastState.ingame && !g_Client()->state.ingame){
		UnLoad();
	}
}
void Map::Render(){
	if(g_Client()->state.ingame)
		m_Model->Render();
}
void Map::RenderBillboard(){}
void Map::Render2d(){}
void Map::Tick(){}
void Map::Message(int type,char* value){}

bool Map::Load(string name){
	g_World()->Load(name);
	string p = "mapres/" + string(g_World()->tileset) + ".png";
	texture=-1;
	g_Graphics()->m_Resources->LoadTexture(texture,false,false,p);

	for (Tile& buffer : g_World()->tilesById){
		if(!buffer.hasx){
			m_Model->AddQuad(quad3(
				vec3(buffer.x*32-16,buffer.y*32-16,buffer.z*32+16),
				vec3(buffer.x*32-16,buffer.y*32+16,buffer.z*32+16),
				vec3(buffer.x*32-16,buffer.y*32+16,buffer.z*32-16),
				vec3(buffer.x*32-16,buffer.y*32-16,buffer.z*32-16)
				),vec3(-1,0,0),g_Graphics()->m_Resources->texturePos16[buffer.texOther]);

		}
		if(!buffer.hasX){
			m_Model->AddQuad(quad3(
				vec3(buffer.x*32+16,buffer.y*32+16,buffer.z*32+16),
				vec3(buffer.x*32+16,buffer.y*32-16,buffer.z*32+16),
				vec3(buffer.x*32+16,buffer.y*32-16,buffer.z*32-16),
				vec3(buffer.x*32+16,buffer.y*32+16,buffer.z*32-16)
				),vec3(1,0,0),g_Graphics()->m_Resources->texturePos16[buffer.texOther]);
		}

		if(!buffer.hasy){
			m_Model->AddQuad(quad3(
				vec3(buffer.x*32+16,buffer.y*32-16,buffer.z*32+16),
				vec3(buffer.x*32-16,buffer.y*32-16,buffer.z*32+16),
				vec3(buffer.x*32-16,buffer.y*32-16,buffer.z*32-16),
				vec3(buffer.x*32+16,buffer.y*32-16,buffer.z*32-16)
				),vec3(0,-1,0),g_Graphics()->m_Resources->texturePos16[buffer.texOther]);
		}
		if(!buffer.hasY){
			m_Model->AddQuad(quad3(
				vec3(buffer.x*32-16,buffer.y*32+16,buffer.z*32+16),
				vec3(buffer.x*32+16,buffer.y*32+16,buffer.z*32+16),
				vec3(buffer.x*32+16,buffer.y*32+16,buffer.z*32-16),
				vec3(buffer.x*32-16,buffer.y*32+16,buffer.z*32-16)
				),vec3(0,1,0),g_Graphics()->m_Resources->texturePos16[buffer.texOther]);
		}
		if(!buffer.hasZ){
			m_Model->AddQuad(quad3(
				vec3(buffer.x*32+16,buffer.y*32+16,buffer.z*32+16),
				vec3(buffer.x*32-16,buffer.y*32+16,buffer.z*32+16),
				vec3(buffer.x*32-16,buffer.y*32-16,buffer.z*32+16),
				vec3(buffer.x*32+16,buffer.y*32-16,buffer.z*32+16)
				),vec3(0,0,1),g_Graphics()->m_Resources->texturePos16[buffer.texTop]);
		}
		if(!buffer.hasz){
			m_Model->AddQuad(quad3(
				vec3(buffer.x*32+16,buffer.y*32-16,buffer.z*32-16),
				vec3(buffer.x*32-16,buffer.y*32-16,buffer.z*32-16),
				vec3(buffer.x*32-16,buffer.y*32+16,buffer.z*32-16),
				vec3(buffer.x*32+16,buffer.y*32+16,buffer.z*32-16)
				),vec3(0,0,-1),g_Graphics()->m_Resources->texturePos16[buffer.texBottom]);
		}
	}
	m_Model->texture=texture;
	m_Model->Create();
	return true;
}
void Map::UnLoad(){
	if(m_Model!=nullptr){
		delete m_Model;
		g_Graphics()->m_Resources->UnLoadTexture(texture);
	}
	g_World()->UnLoad();
}
