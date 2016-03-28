#pragma once

class Input
{
	bool isInit;
	float keyRelease[400];
	float keyPress[400];
	bool keyState[400];

	float mouseRelease[10];
	float mousePress[10];
	bool mouseState[10];

	Input() : isInit(false) { }

	float mouseX, mouseY;
public:
	static Input &instance() 
	{ static Input instance; return instance; }

	bool init();
	bool step();
	void term() {}

	// based on the beginning of the frame
	bool getKey(unsigned);			//true if key is down
	bool getKeyPress(unsigned);		//true the frame the key was pressed
	bool getKeyRelease(unsigned);	//true on the frame key was released

	bool getMouseButton(unsigned);
	bool getMouseButtonPress(unsigned);
	bool getMouseButtonRelease(unsigned);

	float keyDelta(unsigned); //difference between last press & release

	float getMouseX();
	float getMouseY();

	bool isInitialized()
	{ return isInit; }
};