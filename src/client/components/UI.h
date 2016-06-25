#ifndef UI_H
#define UI_H

#include "../ClientComponent.h"
#include <tools/vmath.h>
#include <set>

class Layout;
class View;

class UI : public ClientComponent {
private:
	UI();
	friend UI *g_UI();

public:
	~UI() override;
	void Tick() override;

	void RegisterView(View *view);
	void UnregisterView(View *view);

	void EnableCursor();
	void DisableCursor();
	inline bool CursorEnabled() const { return cursorEnabled; };

	Layout *screenLayout;
	glm::vec2 cursorPosition;

private:
	std::set<View *> registredViews;
	View *cursor;
	bool cursorEnabled;
};
UI *g_UI();

#endif
