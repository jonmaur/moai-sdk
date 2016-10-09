#include "SDLJoystick.h"


const float DEADZONE = 0.0f;

Joystick::Joystick(int index, int akuid)
	: m_index(index)
	, m_akuid(akuid)
	, m_connected(false)
	, m_gamepad(0)
	, m_instance_id(-1)
	, m_haptic(0)
{
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
	{
		m_buttonstates[i] = false;
	}
}

Joystick::~Joystick()
{
	Close();
}

// Opens the joystick controller
void Joystick::Open()
{
	printf("Is %d Gamecontroller %d\n", m_index, SDL_IsGameController(m_index));
	m_gamepad = SDL_GameControllerOpen(m_index);
	if (!m_gamepad)
	{
		printf("Failed to open GameController %d\n", m_index);
		m_connected = false;
		return;
	}

	m_connected = true;

	SDL_Joystick *j = SDL_GameControllerGetJoystick(m_gamepad);
	if (!j)
	{
		printf("Failed to open GameController Joystick %d\n", m_index);
		Close();
		return;
	}

	m_instance_id = SDL_JoystickInstanceID(j);
	
	/*if (SDL_JoystickIsHaptic(j))
	{
		m_haptic = SDL_HapticOpenFromJoystick(j);
		printf("Haptic Effects: %d\n", SDL_HapticNumEffects(m_haptic));
		printf("Haptic Query: %x\n", SDL_HapticQuery(m_haptic));
		if (SDL_HapticRumbleSupported(m_haptic))
		{
			if (SDL_HapticRumbleInit(m_haptic) != 0)
			{
				printf("Haptic Rumble Init: %s\n", SDL_GetError());
				SDL_HapticClose(m_haptic);
				m_haptic = 0;
			}
		}
		else
		{
			SDL_HapticClose(m_haptic);
			m_haptic = 0;
		}
	}*/
}

void Joystick::Close()
{
	if (m_connected)
	{
		m_connected = false;
		if (m_haptic)
		{
			SDL_HapticClose(m_haptic);
			m_haptic = 0;
		}
		SDL_GameControllerClose(m_gamepad);
		m_gamepad = 0;
	}
}

const char* Joystick::getName() 
{
    return SDL_JoystickNameForIndex(m_index);
}

int Joystick::UpdateAxis(int axis, float* x, float* y)
{
	int sensor = 0;
	float p_x = 0.0f;
	float p_y = 0.0f;

	if (axis == SDL_CONTROLLER_AXIS_LEFTX || axis == SDL_CONTROLLER_AXIS_LEFTY)
	{
		p_x = (float)SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_LEFTX);
		p_y = (float)SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_LEFTY);
	}
	else if (axis == SDL_CONTROLLER_AXIS_RIGHTX || axis == SDL_CONTROLLER_AXIS_RIGHTY)
	{
		p_x = (float)SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_RIGHTX);
		p_y = (float)SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_RIGHTY);
		sensor = 1;
	}
	else if (axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT || axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
	{
		p_x = (float)SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
		p_y = (float)SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		sensor = 2;

		if (p_x > DEADZONE)
		{
			if (p_x > 32767.0f)
				p_x = 32767.0f;
			p_x -= DEADZONE;
		} else {
			p_x = 0.0f;
		}

		if (p_y > DEADZONE)
		{
			if (p_y > 32767.0f)
				p_y = 32767.0f;
			p_y -= DEADZONE;
		} else {
			p_y = 0.0f;
		}

		*x = p_x / (32767.0f - DEADZONE);
		*y = p_y / (32767.0f - DEADZONE);

		return sensor;
	}


	// use raw values to calculate normalized direction vector
	float Magnitude_raw =
		sqrt(p_x * p_x + p_y * p_y);
	float X_dir = p_x / Magnitude_raw;
	float Y_dir = p_y / Magnitude_raw;

	// enforce deadzone to get normalized magnitude
	float Magnitude_norm = 0.0f;
	if (Magnitude_raw > DEADZONE)
	{
		if (Magnitude_raw > 32767.0f)
			Magnitude_raw = 32767.0f;
		Magnitude_raw -= DEADZONE;
		Magnitude_norm = Magnitude_raw / (32767.0f - DEADZONE);
	} else {
		Magnitude_raw = 0.0f;
		Magnitude_norm = 0.0f;
	}

	// multiply normalized magnitude by direction vector to get 
	// final result
	*x = Magnitude_norm * X_dir;
	*y = Magnitude_norm * Y_dir;

	return sensor;
}

bool Joystick::UpdateButton(int button, bool* buttonstate)
{
	*buttonstate = SDL_GameControllerGetButton(m_gamepad, (SDL_GameControllerButton)button) == 1;

	if (*buttonstate != m_buttonstates[button])
	{
		m_buttonstates[button] = *buttonstate;
		return true;
	}

	return false;
}
