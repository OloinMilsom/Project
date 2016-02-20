#include "XBoxController.h"

std::vector<bool> XBoxController::buttonWasPressed(10, false);
std::vector<bool> XBoxController::stickWasPressed(2, false);
std::vector<bool> XBoxController::dPadWasPressed(4, false);

bool XBoxController::isStickMoving(unsigned int joystick, XBoxStick stick){
	float x;
	float y;		
	switch (stick) {
	case XBoxStick::Left:
		x = getAxisPosition(joystick, Axis::X);
		y = getAxisPosition(joystick, Axis::Y);
		if (sqrt((x * x) + (y * y)) > DEAD_ZONE){
			if (!stickWasPressed[0]){
				stickWasPressed[0] = true;
				return true;
			}
		}
		else {
			stickWasPressed[0] = false;
		}
		break;
	case XBoxStick::Right:
		x = getAxisPosition(joystick, Axis::U);
		y = getAxisPosition(joystick, Axis::R);
		if (sqrt((x * x) + (y * y)) > DEAD_ZONE) {
			if (!stickWasPressed[1]){
				stickWasPressed[1] = true;
				return true;
			}
		}
		else {
			stickWasPressed[1] = false;
		}
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
	if (Joystick::isButtonPressed(joystick, static_cast<int>(button))) {
		if (!buttonWasPressed[static_cast<int>(button)]) {
			buttonWasPressed[static_cast<int>(button)] = true;
			return true;
		}
	}
	else {
		buttonWasPressed[static_cast<int>(button)] = false;
	}
	return false;
}

bool XBoxController::isDPadPressed(unsigned int joystick, Direction direction){
	switch (direction){
	case Direction::UP:
		if (getAxisPosition(joystick, Axis::PovY) == 100) {
			if (!dPadWasPressed[0]){
				dPadWasPressed[0] = true;
				return true;
			}
		}
		else {
			dPadWasPressed[0] = false;
		}
		break;
	case Direction::LEFT:
		if (getAxisPosition(joystick, Axis::PovX) == -100){
			if (!dPadWasPressed[1]){
				dPadWasPressed[1] = true;
				return true;
			}
		}
		else {
			dPadWasPressed[1] = false;
		}
		break;
	case Direction::DOWN:
		if (getAxisPosition(joystick, Axis::PovY) == -100) {
			if (!dPadWasPressed[2]){
				dPadWasPressed[2] = true;
				return true;
			}
		}
		else {
			dPadWasPressed[2] = false;
		}
		break;
	case Direction::RIGHT:
		if (getAxisPosition(joystick, Axis::PovX) == 100) {
			if (!dPadWasPressed[3]){
				dPadWasPressed[3] = true;
				return true;
			}
		}
		else {
			dPadWasPressed[3] = false;
		}
		break;
	default:
		return false;
	}
	return false;
}