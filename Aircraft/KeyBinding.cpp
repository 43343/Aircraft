#include "KeyBinding.h"

#include <string>
#include <algorithm>
#include <iostream>


KeyBinding::KeyBinding(int controlPreconfiguration)
	: mKeyMap()
{

		if (controlPreconfiguration == 0)
		{
			mKeyMap[sf::Keyboard::Left] = PlayerAction::MoveLeft;
			mKeyMap[sf::Keyboard::Right] = PlayerAction::MoveRight;
			mKeyMap[sf::Keyboard::Up] = PlayerAction::MoveUp;
			mKeyMap[sf::Keyboard::Down] = PlayerAction::MoveDown;
			mKeyMap[sf::Keyboard::Space] = PlayerAction::Fire;
			mKeyMap[sf::Keyboard::M] = PlayerAction::LaunchMissile;
		}
		else if (controlPreconfiguration == 1)
		{
			// Player 2
			mKeyMap[sf::Keyboard::A] = PlayerAction::MoveLeft;
			mKeyMap[sf::Keyboard::D] = PlayerAction::MoveRight;
			mKeyMap[sf::Keyboard::W] = PlayerAction::MoveUp;
			mKeyMap[sf::Keyboard::S] = PlayerAction::MoveDown;
			mKeyMap[sf::Keyboard::F] = PlayerAction::Fire;
			mKeyMap[sf::Keyboard::R] = PlayerAction::LaunchMissile;
		}
		joystickIdentificator = controlPreconfiguration;
		mJoyButtonMap[0] = PlayerAction::LaunchMissile;
		mJoyButtonMap[1] = PlayerAction::Fire;
	
}

void KeyBinding::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyMap.begin(); itr != mKeyMap.end(); )
	{
		if (itr->second == action)
			mKeyMap.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyMap[key] = action;
}

sf::Keyboard::Key KeyBinding::getAssignedKey(Action action) const
{
	for(auto pair : mKeyMap)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

bool KeyBinding::checkAction(sf::Keyboard::Key key, Action& out) const
{
		auto found = mKeyMap.find(key);
		if (found == mKeyMap.end())
		{
			return false;
		}
		else
		{
			out = found->second;
			return true;
		}

}
bool KeyBinding::checkAction(unsigned int key, Action& out) const
{
		auto found = mJoyButtonMap.find(key);
		if (found == mJoyButtonMap.end())
		{
			return false;
		}
		else
		{
			out = found->second;
			return true;
		}
	return true;
	
}

std::vector<KeyBinding::Action> KeyBinding::getRealtimeActions() const
{
	// Return all realtime actions that are currently active.
	std::vector<Action> actions;
	if (Joystick::isConnected(joystickIdentificator)) {
		for(auto pair : mJoyButtonMap)
		{
			// If key is pressed and an action is a realtime action, store it
			if (Joystick::isButtonPressed(joystickIdentificator, pair.first) && isRealtimeAction(pair.second))
				actions.push_back(pair.second);
		}
		float x = Joystick::getAxisPosition(joystickIdentificator, Joystick::X);
		float y = Joystick::getAxisPosition(joystickIdentificator, Joystick::Y);
		std::cout << x << std::endl;
		if (x > 50) actions.push_back(PlayerAction::MoveRight);
		if (x < -50) actions.push_back(PlayerAction::MoveLeft);
		if (y > 50) actions.push_back(PlayerAction::MoveDown);
		if (y < -50) actions.push_back(PlayerAction::MoveUp);
	}
		for(auto pair : mKeyMap)
		{
			// If key is pressed and an action is a realtime action, store it
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
				actions.push_back(pair.second);
		}
	

	return actions;
}

bool isRealtimeAction(PlayerAction::Type action)
{
	switch (action)
	{
	case PlayerAction::MoveLeft:
	case PlayerAction::MoveRight:
	case PlayerAction::MoveDown:
	case PlayerAction::MoveUp:
	case PlayerAction::Fire:
		return true;

	default:
		return false;
	}
}