#include "XBoxController.h"

bool XBoxController::isStickMoving(unsigned int joystick, XBoxStick stick){
	float x;
	float y;
	switch (stick) {
	case XBoxStick::Left:
		x = getAxisPosition(joystick, Axis::X);
		y = getAxisPosition(joystick, Axis::Y);
		if (sqrt(x * x + y * y) > DEAD_ZONE)
			return true;
		break;
	case XBoxStick::Right:
		x = getAxisPosition(joystick, Axis::U);
		y = getAxisPosition(joystick, Axis::R);
		if (sqrt(x * x + y * y) > DEAD_ZONE)
			return true;
		break;
	default:
		return false;
	}
	return false;
}

sf::Vector2f XBoxController::getStickDirection(unsigned int joystick, XBoxStick stick){
	float x;
	float y;
	switch (stick) {
	case XBoxStick::Left:
		x = getAxisPosition(joystick, Axis::X);
		y = getAxisPosition(joystick, Axis::Y);
		break;
	case XBoxStick::Right:
		x = getAxisPosition(joystick, Axis::U);
		y = getAxisPosition(joystick, Axis::R);
		break;
	default:
		return sf::Vector2f(0,0);
	}
	return sf::Vector2f(x, y);
}

bool XBoxController::isButtonPressed(unsigned int joystick, XboxButton button){
	return Joystick::isButtonPressed(joystick, static_cast<int>(button));
}

bool XBoxController::isDPadPressed(unsigned int joystick, Direction direction){
	switch (direction){
	case Direction::UP:
		if (getAxisPosition(joystick, Axis::PovY) == 100)
			return true;
		break;
	case Direction::LEFT:
		if (getAxisPosition(joystick, Axis::PovX) == -100)
			return true;
		break;
	case Direction::DOWN:
		if (getAxisPosition(joystick, Axis::PovY) == -100)
			return true;
		break;
	case Direction::RIGHT:
		if (getAxisPosition(joystick, Axis::PovX) == 100)
			return true;
		break;
	default:
		return false;
	}
	return false;
}