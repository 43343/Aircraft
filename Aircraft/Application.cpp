#include "Application.h"
#include "Utility.h"
#include "State.h"
#include "StateIdentifiers.h"
#include "TitleState.h"
#include "GameState.h"
#include "MultiplayerGameState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "SettingsState.h"
#include "GameOverState.h"
#include "EnterIPState.h"
#include <SFML/Network/IpAddress.hpp>


const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: mWindow(sf::VideoMode(1920, 1080), "Aircraft", sf::Style::Default)
	, mTextures()
	, mFonts()
	, mMusic()
	, mSounds()
	, mBinaryDataHandler(mKeyBinding1, mKeyBinding2)
	, mKeyBinding1(0)
	, mKeyBinding2(1)
	, mIpAddress()
	, mStateStack(State::Context(mWindow,mWindow, mTextures, mFonts, mMusic, mSounds, mKeyBinding1, mKeyBinding2, mIpAddress))
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);
	mBinaryDataHandler.read();
	auto image = sf::Image{};
	if (!image.loadFromFile("Textures/Entities.png"))
	{
		// Error handling...
	}
	mWindow.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

	mFonts.load(Fonts::Main, "Fonts/Sansation.ttf");

	mTextures.load(Textures::TitleScreen, "Textures/TitleScreen.png");
	mTextures.load(Textures::Buttons, "Textures/Buttons.png");

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	mStateStack.pushState(States::Title);

	mMusic.setVolume(25.f);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<MultiplayerGameState>(States::HostGame, true);
	mStateStack.registerState<EnterIPState>(States::EnterIPState);
	mStateStack.registerState<MultiplayerGameState>(States::JoinGame, false);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<PauseState>(States::NetworkPause, true);
	mStateStack.registerState<SettingsState>(States::Settings);
	mStateStack.registerState<GameOverState>(States::GameOver, "Mission Failed!");
	mStateStack.registerState<GameOverState>(States::MissionSuccess, "Mission Successful!");
}