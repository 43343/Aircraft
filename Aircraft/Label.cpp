#include "Label.h"
#include "Utility.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

	Label::Label(const std::string& text, const FontHolder& fonts)
		: mText(text, fonts.get(Fonts::Main), 16)
	{
	}

	bool Label::isSelectable() const
	{
		return false;
	}

	void Label::handleEvent(const sf::Event&, const sf::RenderWindow& mWindow)
	{
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mText, states);
	}

	void Label::setText(const std::string& text)
	{
		mText.setString(text);
	}
	void Label::setFont(const sf::Font& font)
	{
		mText.setFont(font);
	}
	void Label::setColor(const sf::Color& color)
	{
		mText.setColor(color);
	}
	void Label::setCharacterSize(const unsigned int size)
	{
		mText.setCharacterSize(size);
	}

}