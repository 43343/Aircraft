#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "Joystick.h"

#include <map>
#include <vector>


namespace PlayerAction
{
	enum Type
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		LaunchMissile,
		Count
	};
}

class KeyBinding
{
public:
	typedef PlayerAction::Type Action;


public:
	explicit				KeyBinding(int controlPreconfiguration);

	void					assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key		getAssignedKey(Action action) const;

	bool					checkAction(sf::Keyboard::Key key, Action& out) const;
	bool					checkAction(unsigned int key, Action& out) const;
	std::vector<Action>		getRealtimeActions() const;


private:
	void					initializeActions();


private:
	std::map<sf::Keyboard::Key, Action>		mKeyMap;
	std::map<unsigned int, Action>		mJoyButtonMap;
	int joystickIdentificator;
};

bool					isRealtimeAction(PlayerAction::Type action);