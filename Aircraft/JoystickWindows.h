#pragma once
#include <SFML/Window/Joystick.hpp>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <XInput.h>
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <vector>


#pragma comment(lib, "Xinput.lib")
#endif

class JoystickWindows : public sf::Joystick
{
public:
    JoystickWindows();
    static bool Vibrate(int leftVal, int rightVal, int durationMs, int controllerId);
private:
    static void ThreadVibrate(int leftVal, int rightVal, int durationMs, int controllerId);

};
