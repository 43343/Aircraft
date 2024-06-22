#include "Component.h"

namespace GUI
{

	Component::Component()
		: mIsSelected(false)
		, mIsActive(false)
	{
	}

	Component::~Component()
	{
	}

	bool Component::isSelected() const
	{
		return mIsSelected;
	}

	void Component::select()
	{
		mIsSelected = true;
	}

	void Component::deselect()
	{
		mIsSelected = false;
	}

	bool Component::isActive() const
	{
		return mIsActive;
	}

	void Component::activate()
	{
		mIsActive = true;
	}

	void Component::deactivate()
	{
		mIsActive = false;
	}
	void Component::update()
	{

	}
	sf::FloatRect Component::getLocalBounds() const
    {
		
        const auto width  = static_cast<float>(std::abs(componentRect.width));
        const auto height = static_cast<float>(std::abs(componentRect.height));

        return {{0.f, 0.f}, {width, height}};
    }
    sf::FloatRect Component::getGlobalBounds() const
    {  
        return getTransform().transformRect(getLocalBounds());
    }
}