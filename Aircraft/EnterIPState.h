#pragma once
#include "State.h"
#include "KeyBinding.h"
#include "IpAddress.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class EnterIPState : public State
{
public:
	EnterIPState(StateStack& stack, Context context);

	virtual void					draw();
	virtual bool					update(sf::Time dt);
	virtual bool					handleEvent(const sf::Event& event);


private:
	sf::Sprite											mBackgroundSprite;
	GUI::Container										mGUIContainer;
	bool isValidIpAddress(const std::string& ip);
};
