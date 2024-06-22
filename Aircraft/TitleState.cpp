#include "TitleState.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include "Joystick.h"
#include <SFML/Graphics/RenderWindow.hpp>


TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, mShowText(true)
	, mTextEffectTime(sf::Time::Zero)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
    float x = getContext().window->getView().getSize().x;
    float y = getContext().window->getView().getSize().y;

    mBackgroundSprite.setScale( x / mBackgroundSprite.getLocalBounds().width, y / mBackgroundSprite.getLocalBounds().height);
	mText.setFont(context.fonts->get(Fonts::Main));
	mText.setString("Press any key to start");
	centerOrigin(mText);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);
	mText.setPosition(sf::Vector2f(window.getSize() / 2u));

	if (mShowText)
		window.draw(mText);
}

bool TitleState::update(sf::Time dt)
{
	mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}
	if (Joystick::isConnected(0)) mText.setString("Press START");
	else mText.setString("Press any key to start");

	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonPressed ||  Joystick::isButtonPressed(0,7))
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}