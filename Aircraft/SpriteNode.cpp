#include "SpriteNode.h"

#include <SFML/Graphics/RenderTarget.hpp>


SpriteNode::SpriteNode(const sf::Texture& texture)
	: mSprite(texture)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
	: mSprite(texture, textureRect),
	  spriteRect(textureRect)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
sf::FloatRect SpriteNode::getLocalBounds() const
    {
		
        const auto width  = static_cast<float>(std::abs(spriteRect.width));
        const auto height = static_cast<float>(std::abs(spriteRect.height));

        return {{0.f, 0.f}, {width, height}};
    }