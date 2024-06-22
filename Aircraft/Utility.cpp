#include "Utility.h"
#include "Animation.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <random>
#include <cmath>
#include <ctime>
#include <cassert>


namespace
{
	std::default_random_engine createRandomEngine()
	{
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto RandomEngine = createRandomEngine();
}

std::string keyToString(sf::Keyboard::Key key)
{
	static const std::unordered_map<sf::Keyboard::Key, std::string> keyMap = {
		{sf::Keyboard::Unknown, "Unknown"},
		{sf::Keyboard::A, "A"},
		{sf::Keyboard::B, "B"},
		{sf::Keyboard::C, "C"},
		{sf::Keyboard::D, "D"},
		{sf::Keyboard::E, "E"},
		{sf::Keyboard::F, "F"},
		{sf::Keyboard::G, "G"},
		{sf::Keyboard::H, "H"},
		{sf::Keyboard::I, "I"},
		{sf::Keyboard::J, "J"},
		{sf::Keyboard::K, "K"},
		{sf::Keyboard::L, "L"},
		{sf::Keyboard::M, "M"},
		{sf::Keyboard::N, "N"},
		{sf::Keyboard::O, "O"},
		{sf::Keyboard::P, "P"},
		{sf::Keyboard::Q, "Q"},
		{sf::Keyboard::R, "R"},
		{sf::Keyboard::S, "S"},
		{sf::Keyboard::T, "T"},
		{sf::Keyboard::U, "U"},
		{sf::Keyboard::V, "V"},
		{sf::Keyboard::W, "W"},
		{sf::Keyboard::X, "X"},
		{sf::Keyboard::Y, "Y"},
		{sf::Keyboard::Z, "Z"},
		{sf::Keyboard::Num0, "Num0"},
		{sf::Keyboard::Num1, "Num1"},
		{sf::Keyboard::Num2, "Num2"},
		{sf::Keyboard::Num3, "Num3"},
		{sf::Keyboard::Num4, "Num4"},
		{sf::Keyboard::Num5, "Num5"},
		{sf::Keyboard::Num6, "Num6"},
		{sf::Keyboard::Num7, "Num7"},
		{sf::Keyboard::Num8, "Num8"},
		{sf::Keyboard::Num9, "Num9"},
		{sf::Keyboard::Escape, "Escape"},
		{sf::Keyboard::LControl, "LControl"},
		{sf::Keyboard::LShift, "LShift"},
		{sf::Keyboard::LAlt, "LAlt"},
		{sf::Keyboard::LSystem, "LSystem"},
		{sf::Keyboard::RControl, "RControl"},
		{sf::Keyboard::RShift, "RShift"},
		{sf::Keyboard::RAlt, "RAlt"},
		{sf::Keyboard::Space, "Space"},
		{sf::Keyboard::Left, "Left"},
		{sf::Keyboard::Right, "Right"},
		{sf::Keyboard::Up, "Up"},
		{sf::Keyboard::Down, "Down"}
	};
	auto it = keyMap.find(key);
	if (it != keyMap.end())
	{
		return it->second;
	}
	else
	{
		return "Unknown";
	}
}

sf::Keyboard::Key stringToKey(std::string key)
{
	static const std::unordered_map<std::string, sf::Keyboard::Key> keyMap = {
		{"Unknown", sf::Keyboard::Unknown},
		{"A", sf::Keyboard::A},
		{"B", sf::Keyboard::B},
		{"C", sf::Keyboard::C},
		{"D", sf::Keyboard::D},
		{"E", sf::Keyboard::E},
		{"F", sf::Keyboard::F},
		{"G", sf::Keyboard::G},
		{"H", sf::Keyboard::H},
		{"I", sf::Keyboard::I},
		{"J", sf::Keyboard::J},
		{"K", sf::Keyboard::K},
		{"L", sf::Keyboard::L},
		{"M", sf::Keyboard::M},
		{"N", sf::Keyboard::N},
		{"O", sf::Keyboard::O},
		{"P", sf::Keyboard::P},
		{"Q", sf::Keyboard::Q},
		{"R", sf::Keyboard::R},
		{"S", sf::Keyboard::S},
		{"T", sf::Keyboard::T},
		{"U", sf::Keyboard::U},
		{"V", sf::Keyboard::V},
		{"W", sf::Keyboard::W},
		{"X", sf::Keyboard::X},
		{"Y", sf::Keyboard::Y},
		{"Z", sf::Keyboard::Z},
		{"Num0", sf::Keyboard::Num0},
		{"Num1", sf::Keyboard::Num1},
		{"Num2", sf::Keyboard::Num2},
		{"Num3", sf::Keyboard::Num3},
		{"Num4", sf::Keyboard::Num4},
		{"Num5", sf::Keyboard::Num5},
		{"Num6", sf::Keyboard::Num6},
		{"Num7", sf::Keyboard::Num7},
		{"Num8", sf::Keyboard::Num8},
		{"Num9", sf::Keyboard::Num9},
		{"Escape", sf::Keyboard::Escape},
		{"LControl", sf::Keyboard::LControl},
		{"LShift", sf::Keyboard::LShift},
		{"LAlt", sf::Keyboard::LAlt},
		{"LSystem", sf::Keyboard::LSystem},
		{"RControl", sf::Keyboard::RControl},
		{"RShift", sf::Keyboard::RShift},
		{"RAlt", sf::Keyboard::RAlt} ,
		{"Space", sf::Keyboard::Space},
		{"Left", sf::Keyboard::Left},
		{"Right", sf::Keyboard::Right},
		{"Up", sf::Keyboard::Up},
		{"Down", sf::Keyboard::Down}
	};
	auto it = keyMap.find(key);
	if (it != keyMap.end())
	{
		return it->second;
	}
	else
	{
		return sf::Keyboard::Unknown;
	}
}

void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(Animation& animation)
{
	sf::FloatRect bounds = animation.getLocalBounds();
	animation.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

float toDegree(float radian)
{
	return 180.f / 3.141592653589793238462643383f * radian;
}

float toRadian(float degree)
{
	return 3.141592653589793238462643383f / 180.f * degree;
}

int randomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector)
{
	assert(vector != sf::Vector2f(0.f, 0.f));
	return vector / length(vector);
}