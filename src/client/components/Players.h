#ifndef PLAYERS_H
#define PLAYERS_H

#include <vector>
#include "../Component.h"
#include "../../tools/Protocol.h"

class PlayerModel;

class Players : Component{
public:
	Players();
	~Players();
	///<summary>Input callback</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	void Input(unsigned char* keys,int xrel,int yrel,int wheel);
	///<summary>State change callback</summary>
	///<param name="lastState">Last state</param>
	void StateChange(STATE lastState);
	///<summary>3d render callback</summary>
	void Render();
	///<summary>Render 3d Billboard</summary>
	void RenderBillboard();
	///<summary>2d render callback</summary>
	void Render2d();
	///<summary>Tick callback</summary>
	void Tick();
	///<summary>System message callback</summary>
	void Message(int type,char* value);
private:
	///<summary>Players array</summary>
	PlayerModel* playerModels[MAX_PLAYERS];
};
Players* g_Players();

#endif