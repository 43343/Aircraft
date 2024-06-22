#include "EnterIPState.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include "InputField.h"
#include "Label.h"


#include <SFML/Graphics/RenderWindow.hpp>


EnterIPState::EnterIPState(StateStack& stack, Context context)
	: State(stack, context)
	, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
	float x = getContext().window->getView().getSize().x;
	float y = getContext().window->getView().getSize().y;

	mBackgroundSprite.setScale(x / mBackgroundSprite.getLocalBounds().width, y / mBackgroundSprite.getLocalBounds().height);
	auto labelIP = std::make_shared<GUI::Label>("Enter the IP address", *context.fonts);
	labelIP->setPosition(80.f, 300.f);
	labelIP->setCharacterSize(24.f);
	auto errorIP = std::make_shared<GUI::Label>("The IP Address is entered incorrectly", *context.fonts);
	errorIP->setPosition(80.f, 700.f);
	errorIP->setColor(sf::Color::Transparent);
	auto inputIP = std::make_shared<GUI::InputField>(context);
	inputIP->setPosition(80.f, 400.f);
	auto connectButton = std::make_shared<GUI::Button>(context);
	connectButton->setPosition(80.f, 500.f);
	connectButton->setText("Connect");
	connectButton->setCallback([&, inputIP, errorIP, context,  this]()
		{
			if (isValidIpAddress(inputIP->getValue())) {
				requestStateClear();
				context.ipAddress->set(inputIP->getValue());
				std::cout << "Assigned IP: " << inputIP->getValue() << std::endl;
				requestStackPush(States::JoinGame);
			}
			else errorIP->setColor(sf::Color::Red);
		});

	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(80.f, 620.f);
	backButton->setText("Back");
	backButton->setCallback([this]()
		{
			requestStackPop();
		});

	mGUIContainer.pack(labelIP);
	mGUIContainer.pack(errorIP);
	mGUIContainer.pack(inputIP);
	mGUIContainer.pack(connectButton);
	mGUIContainer.pack(backButton);
}
bool EnterIPState::isValidIpAddress(const std::string& ip) {
	int parts[4];
	char dot;
	std::istringstream iss(ip);
	if (!(iss >> parts[0] >> dot >> parts[1] >> dot >> parts[2] >> dot >> parts[3])) {
		return false;
	}
	if (dot != '.') {
		return false;
	}
	for (int i = 0; i < 4; ++i) {
		if (parts[i] < 0 || parts[i] > 255) {
			return false;
		}
	}
	if (iss.rdbuf()->in_avail() != 0) {
		return false;
	}

	return true;
}

void EnterIPState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool EnterIPState::update(sf::Time)
{
	mGUIContainer.update();
	return true;
}

bool EnterIPState::handleEvent(const sf::Event& event)
{
	
	mGUIContainer.handleEvent(event, *getContext().window);

	return false;
}
