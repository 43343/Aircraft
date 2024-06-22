#pragma once
#include "SceneNode.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>



class SpriteNode : public SceneNode
{
public:
	explicit			SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
	sf::FloatRect       getLocalBounds() const;


private:
    sf::Sprite			mSprite;
	sf::IntRect         spriteRect;
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


};