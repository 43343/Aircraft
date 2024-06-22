#pragma once
#include "Component.h"
#include "ResourceIdentifiers.h"
#include "State.h"
#include "ResourceHolder.h"
#include <SFML/Window/Cursor.hpp>

#include <SFML/Graphics.hpp>
#include <string>



class SoundPlayer;

namespace GUI
{

    class InputField : public Component
    {
    public:
        typedef std::shared_ptr<InputField>		Ptr;

        enum Type
        {
            Normal,
            Selected,
            Pressed,
            ButtonCount
        };


    public:
        InputField(State::Context context);

        std::string					getValue();
        void					setToggle(bool flag);

        virtual bool			isSelectable() const;

        virtual void			activate();
        virtual void			deactivate();

        virtual void			handleEvent(const sf::Event& event, const sf::RenderWindow& mWindow);
        virtual void            update();


    private:
        virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::RectangleShape mRect;
        sf::Text mText;
        sf::Text mPlaceholderText;
        std::string input;
        sf::RectangleShape mCursor;
        bool isValidCharacter(char c);
        bool isActive = false;
        sf::Clock backspaceClock;
        const int backspaceInterval = 100;
        bool backspaceHeld = false;
        bool cursorVisible = false; // Флаг для отслеживания видимости курсора
        sf::Clock cursorClock; // Часы для мигания курсора
        const int cursorBlinkInterval = 500; // Интервал мигания курсора в миллисекундах
        sf::Cursor textCursor;
        sf::Cursor arrowCursor;
        sf::WindowBase* windowBase;
        void updateTextAndCursor();
        int cursorPosition = 0;
        sf::Clock arrowHeldClock;
        const int cursorMoveInterval = 100;
        bool arrowLeftHeld = false;
        bool arrowRightHeld = false;
    };

}
