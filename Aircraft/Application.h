#pragma once

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "KeyBinding.h"
#include "StateStack.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
#include "IpAddress.h"
#include "BinaryDataHandler.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Application
{
public:
	Application();
	void					run();


private:
	void					processInput();
	void					update(sf::Time dt);
	void					render();

	void					updateStatistics(sf::Time dt);
	void					registerStates();


private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	TextureHolder			mTextures;
	FontHolder				mFonts;
	MusicPlayer				mMusic;
	SoundPlayer				mSounds;
	BinaryDataHandler	    mBinaryDataHandler;

	KeyBinding				mKeyBinding1;
	KeyBinding				mKeyBinding2;
	IpAddress				mIpAddress;
	StateStack				mStateStack;

	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames;
};