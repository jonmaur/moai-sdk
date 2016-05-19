#ifndef	SDLJOYSTICK_H
#define	SDLJOYSTICK_H

#include <SDL.h>

class Joystick
{
public:
	Joystick(int index, int akuid);
	virtual ~Joystick();

	void Open();
	void Close();
	const char* getName();
	int UpdateAxis(int axis, float* x, float* y);
	bool UpdateButton(int button, bool* buttonstate);
	int m_index;
	int m_akuid;

private:
	
	SDL_GameController *m_gamepad;
	SDL_Haptic *m_haptic;
	SDL_JoystickID m_instance_id;

	bool m_connected;
	bool m_buttonstates[SDL_CONTROLLER_BUTTON_MAX];
};

#endif
