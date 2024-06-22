#pragma once
#include "Component.h"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/Text.hpp>


namespace GUI
{

    class Label : public Component
    {
    public:
        typedef std::shared_ptr<Label> Ptr;


    public:
        Label(const std::string& text, const FontHolder& fonts);

        virtual bool		isSelectable() const;
        void				setText(const std::string& text);
        void				setFont(const sf::Font& font);
        void				setColor(const sf::Color& color);
        void				setCharacterSize(const unsigned int size);

        virtual void		handleEvent(const sf::Event& event, const sf::RenderWindow& mWindow);


    private:
        void				draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Text			mText;
    };

}