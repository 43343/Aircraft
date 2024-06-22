#include "Joystick.h"
#include <functional>

Joystick::Joystick()
{
}

bool Joystick::Vibrate(int leftVal, int rightVal, int durationMs, int controllerId)
{
#if defined(_WIN32) || defined(_WIN64)
    auto boundFunction = std::bind(&Joystick::ThreadVibrate, leftVal, rightVal, durationMs, controllerId);
    std::thread vibrationThread(boundFunction);
    vibrationThread.detach(); 
#endif
    return true;
}
void Joystick::ThreadVibrate(int leftVal, int rightVal, int durationMs, int controllerId)
{
#if defined(_WIN32) || defined(_WIN64)
    XINPUT_VIBRATION vibration;
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed = leftVal;
    vibration.wRightMotorSpeed = rightVal;
    XInputSetState(controllerId, &vibration);
    std::this_thread::sleep_for(std::chrono::milliseconds(durationMs));
    vibration.wLeftMotorSpeed = 0;
    vibration.wRightMotorSpeed = 0;
    XInputSetState(controllerId, &vibration);
#endif
}
