#pragma once
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <SFML/Network/IpAddress.hpp>



namespace sf
{
	class RenderWindow;
}

class StateStack;
class MusicPlayer;
class SoundPlayer;
class KeyBinding;
class IpAddress;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, sf::WindowBase& windowBase, TextureHolder& textures, FontHolder& fonts,
			MusicPlayer& music, SoundPlayer& sounds, KeyBinding& keys1, KeyBinding& keys2, IpAddress& ipAddress);

		sf::RenderWindow* window;
		sf::WindowBase* windowBase;
		TextureHolder* textures;
		FontHolder* fonts;
		MusicPlayer* music;
		SoundPlayer* sounds;
		KeyBinding* keys1;
		KeyBinding* keys2;
		IpAddress* ipAddress;
	};


public:
	State(StateStack& stack, Context context);
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(sf::Time dt) = 0;
	virtual bool		handleEvent(const sf::Event& event) = 0;

	virtual void		onActivate();
	virtual void		onDestroy();


protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;


private:
	StateStack* mStack;
	Context				mContext;
};
