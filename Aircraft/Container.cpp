#include "Container.h"
#include "JoystickWindows.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

	Container::Container()
		: mChildren()
		, mSelectedChild(-1)
	{
	}

	void Container::pack(Component::Ptr component)
	{
		mChildren.push_back(component);

		if (!hasSelection() && component->isSelectable())
			select(mChildren.size() - 1);
	}

	bool Container::isSelectable() const
	{
		return false;
	}

	void Container::handleEvent(const sf::Event& event, const sf::RenderWindow& mWindow)
	{
		
		// If we have selected a child then give it events
		int povY = JoystickWindows::getAxisPosition(0, JoystickWindows::PovY);
		std::cout << povY;
		for (auto child : mChildren) {
			if (!child->isSelectable()) child->handleEvent(event,mWindow);
		}
	    if (event.type == sf::Event::KeyPressed || (event.type == sf::Event::JoystickMoved && povY != 0))
		{
			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up || povY > 50)
			{
				pressedPreviousHeld = true;
			}
			if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down || povY < -50)
			{
				pressedNextHeld = true;
			}
		}
		else if (event.type == sf::Event::KeyReleased || event.type == sf::Event::JoystickButtonReleased ||  (event.type == sf::Event::JoystickMoved && povY == 0))
		{
			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up || povY == 0)
			{
				pressedPreviousHeld = false;
			}
			if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down || povY == 0)
			{
				pressedNextHeld = false;
			}
			if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space || event.joystickButton.button == 0)
			{
				if (hasSelection())
					mChildren[mSelectedChild]->activate();
			}
		}
		for(int i = 0; i < mChildren.size(); i++) {
			if(mChildren[i]->getGlobalBounds().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))) && mChildren[i]->isSelectable()) {
				select(i);
				if (event.type == sf::Event::MouseButtonPressed && hasSelection()) {
					mChildren[mSelectedChild]->activate();
					pressedNextHeld = false;
					pressedPreviousHeld = false;
				}
			}
		}

	}
	void Container::update() {
		for (auto child : mChildren) {
			if (!child->isSelectable()) child->update();
		}
		if (pressedClock.getElapsedTime().asMilliseconds() >= pressedInterval && (pressedNextHeld || pressedPreviousHeld))
		{
			if (pressedNextHeld) selectNext();
			else if (pressedPreviousHeld) selectPrevious();
			pressedClock.restart();

		}
	}

	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for(const Component::Ptr & child : mChildren)
			target.draw(*child, states);
	}

	bool Container::hasSelection() const
	{
		return mSelectedChild >= 0;
	}

	void Container::select(std::size_t index)
	{
			if (hasSelection())
				mChildren[mSelectedChild]->deselect();

			mChildren[index]->select();
			mSelectedChild = index;
	}

	void Container::selectNext()
	{
		if (!hasSelection())
			return;

		// Search next component that is selectable, wrap around if necessary
		int next = mSelectedChild;
		do
			next = (next + 1) % mChildren.size();
		while (!mChildren[next]->isSelectable());

		// Select that component
		select(next);
	}

	void Container::selectPrevious()
	{
		if (!hasSelection())
			return;

		// Search previous component that is selectable, wrap around if necessary
		int prev = mSelectedChild;
		do
			prev = (prev + mChildren.size() - 1) % mChildren.size();
		while (!mChildren[prev]->isSelectable());

		// Select that component
		select(prev);
	}

}