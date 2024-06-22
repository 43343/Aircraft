#include "InputField.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "ResourceHolder.h"
#include "Joystick.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>


namespace GUI
{

	InputField::InputField(State::Context context) : windowBase(context.windowBase)
	{
		// Настройка прямоугольника
		mRect.setSize(sf::Vector2f(240.f, 40.f));
		mRect.setFillColor(sf::Color::White);
		mRect.setOutlineColor(sf::Color::Black);
		mRect.setOutlineThickness(1);
		sf::IntRect textureRect(0, 50, 240, 40);
		componentRect = textureRect;
		mRect.setTextureRect(textureRect);
		mText.setFont(context.fonts->get(Fonts::Main));
		mText.setPosition(5, 5);
		mText.setCharacterSize(24);
		mText.setFillColor(sf::Color::Black);

		mPlaceholderText.setFont(context.fonts->get(Fonts::Main));
		mPlaceholderText.setPosition(5, 5);
		mPlaceholderText.setCharacterSize(24);
		mPlaceholderText.setFillColor(sf::Color(150, 150, 150)); 
		mPlaceholderText.setString("Enter a text");

		mCursor.setSize(sf::Vector2f(2, mText.getCharacterSize()));
		mCursor.setFillColor(sf::Color::Black);
		updateTextAndCursor();
		textCursor.loadFromSystem(sf::Cursor::Text);
		arrowCursor.loadFromSystem(sf::Cursor::Arrow);
	}

	std::string InputField::getValue()
	{
		return mText.getString();
	}

	void InputField::setToggle(bool flag)
	{
		
	}

	bool InputField::isSelectable() const
	{
		return false;
	}

	void InputField::activate()
	{
		Component::activate();
	}

	void InputField::deactivate()
	{
		Component::deactivate();
	}

	bool InputField::isValidCharacter(char c) {
		return std::isdigit(c) || c == '.';
	}

	void InputField::handleEvent(const sf::Event& event, const sf::RenderWindow& mWindow)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
		if (getGlobalBounds().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)))) windowBase->setMouseCursor(textCursor);
		else windowBase->setMouseCursor(arrowCursor);
		if(event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) || Joystick::isButtonPressed(0, 0))  windowBase->setMouseCursor(arrowCursor);
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				
				std::cout << getGlobalBounds().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))) << std::endl;
				if (getGlobalBounds().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)))) {
					isActive = true;
					mRect.setOutlineThickness(3);
				}
				else {
					mRect.setOutlineThickness(1);
					isActive = false;
					cursorVisible = false;
				}
			}
		}
		if (isActive) {
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) { 
					char enteredChar = static_cast<char>(event.text.unicode);
					if (isValidCharacter(enteredChar) && input.size() < 15) {
						input.insert(cursorPosition, 1, enteredChar);
						cursorPosition++;
					}
				}
				updateTextAndCursor();
			}
			else if (event.type == sf::Event::KeyPressed ) { 

				if (event.key.code == sf::Keyboard::Left) {
					arrowLeftHeld = true;
				}
				else if (event.key.code == sf::Keyboard::Right) {
					arrowRightHeld = true;
				}
				else if (event.key.code == sf::Keyboard::Backspace) {
					backspaceHeld = true;
				}
			}
			else if (event.type == sf::Event::KeyReleased ) {
				if (event.key.code == sf::Keyboard::Left) {
					arrowLeftHeld = false;
				}
				else if (event.key.code == sf::Keyboard::Right) {
					arrowRightHeld = false;
				}
				else if (event.key.code == sf::Keyboard::Backspace) {
					backspaceHeld = false;
				}
			}
		}
	}
	void InputField::update()
	{
		std::cout << cursorPosition;
		if (backspaceClock.getElapsedTime().asMilliseconds() >= backspaceInterval && backspaceHeld) {
			if (!input.empty() && cursorPosition > 0) {
				input.erase(cursorPosition - 1, 1);
				cursorPosition--;
				updateTextAndCursor();
			}
			backspaceClock.restart(); 
		}
		if (cursorClock.getElapsedTime().asMilliseconds() >= cursorBlinkInterval && isActive && !((arrowRightHeld || arrowLeftHeld))) {
			cursorVisible = !cursorVisible;
			cursorClock.restart();
		}
		if (arrowHeldClock.getElapsedTime().asMilliseconds() >= cursorMoveInterval && isActive && (arrowRightHeld || arrowLeftHeld)) {
			if (arrowLeftHeld && cursorPosition >  0) {
				cursorPosition--;
			}
			if (arrowRightHeld && cursorPosition < input.size()) {
				cursorPosition++;
			}
			cursorClock.restart();
			cursorVisible = true;
			updateTextAndCursor();
			arrowHeldClock.restart();
		}
	}

	void InputField::updateTextAndCursor()
	{
		mText.setString(input);
		float cursorX = mText.getPosition().x + mText.findCharacterPos(cursorPosition).x - 6;
		mCursor.setPosition(cursorX, mText.getPosition().y + 3);
	}

	void InputField::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mRect, states);
		if(input.empty() && !isActive) target.draw(mPlaceholderText, states);
		else target.draw(mText, states);
		if (cursorVisible) {
			target.draw(mCursor, states); 
		}
	}

};