#pragma once
#include <vector>
#include <Windows.h>

class Mouse
{
	friend class Window;

private:
	enum class ButtonState
	{
		bsFREE,
		bsDOWN,
		bsHOLD,
		bsUP
	};

	enum class WheelState
	{
		wsIDLE,
		wsFORWARD,
		wsBACKWARD
	};

private:
	static Mouse instance;

	static constexpr int numButtons = 7;

	ButtonState previousButtonStates[numButtons] = {};
	ButtonState currentButtonStates[numButtons] = {};

	WheelState wheelState = WheelState::wsIDLE;

	std::vector<POINT> rawDeltas[2];
	size_t activeRawDeltaIndex = 0;

	POINT position = {};

	bool wheelMoved = false;
	bool confined = false;
	bool frozen = false;

private:
	Mouse() = default;

public:
	static void SetCursorVisibility(bool visible);
	static void SetConfinement(bool confine);
	static void SetCursorMovement(bool freeze);

	static bool IsCursorConfined();

	static bool IsButtonFree(int button);
	static bool IsButtonDown(int button);
	static bool IsButtonHold(int button);
	static bool IsButtonUp(int button);

	static bool IsWheelForward();
	static bool IsWheelBackward();

	// client space position
	static POINT GetPosition() { return instance.position; }

	static std::vector<POINT>& GetRawDeltas();

private:
	static void RegisterRawInputDevice(HWND hwnd);
	static bool HandleWM(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static void Update();
};