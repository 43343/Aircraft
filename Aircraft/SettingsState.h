#pragma once
#include "State.h"
#include "KeyBinding.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"
#include "BinaryDataHandler.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>
#include <map>


class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);

	virtual void					draw();
	virtual bool					update(sf::Time dt);
	virtual bool					handleEvent(const sf::Event& event);


private:
	void							updateLabels();
	void							addButtonLabel(std::size_t index, std::size_t x, std::size_t y, const std::string& text, Context context);


private:
	sf::Sprite											mBackgroundSprite;
	GUI::Container										mGUIContainer;
	std::array<GUI::Button::Ptr, 2 * PlayerAction::Count>	mBindingButtons;
	std::array<GUI::Label::Ptr, 2 * PlayerAction::Count> 	mBindingLabels;
	std::map<unsigned int, std::string>						mSaveKeyMap;
	BinaryDataHandler                                       mBinaryDataHandler;
};