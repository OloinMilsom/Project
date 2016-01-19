#ifndef XBOXCONTROLLER_H
#define XBOXCONTROLLER_H

#include "stdafx.h"
#include "Direction.h"

class XBoxController : public sf::Joystick {
private:
	static const int DEAD_ZONE = 20;

public:
	enum XboxButton
	{
		A,
		B,
		X,
		Y,
		LB,
		RB,
		Back,
		Start,
		LS,
		RS
	};

	enum XBoxStick
	{
		Left,
		Right
	};

	// checks if a stick is out of the dead zone
	static bool isStickMoving(unsigned int joystick, XBoxStick stick);

	// returns a vector direction of a stick
	static sf::Vector2f getStickDirection(unsigned int joystick, XBoxStick stick);

	// checks if an xbox button is pressed
	static bool isButtonPressed(unsigned int joystick, XboxButton button);

	// checks if the dpad is pressed
	static bool isDPadPressed(unsigned int joystick, Direction direction);	
};

#endif