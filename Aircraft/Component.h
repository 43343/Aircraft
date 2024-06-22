#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>


namespace sf
{
    class Event;
}

namespace GUI
{

    class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
    {
    public:
        typedef std::shared_ptr<Component> Ptr;


    public:
        Component();
        virtual				~Component();

        virtual bool		isSelectable() const = 0;
        bool				isSelected() const;
        virtual void		select();
        virtual void		deselect();
        sf::FloatRect       getLocalBounds() const;
        sf::FloatRect       getGlobalBounds() const;
        sf::IntRect         componentRect;
        virtual bool		isActive() const;
        virtual void		activate();
        virtual void		deactivate();

        virtual void		handleEvent(const sf::Event& event, const sf::RenderWindow& mWindow) = 0;
        virtual void        update();

    private:
        bool				mIsSelected;
        bool				mIsActive;
    };

}