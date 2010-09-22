/**************************************
*Diz-listener.cpp by Chris Lewis
*Defines the DIZ_LISTENER class from diz-sound.h
**************************************/

//Declare our include file
#include "../Include/diz-sound.h"

//Define our Constructor, initialise everything and start up our alut session
DIZ_LISTENER::DIZ_LISTENER() {
	//Set our default Position values
	pos[0] = 0.0f; pos[1] = 0.0f; pos[2] = 0.0f;
	//Set our default Velocity values
	vel[0] = 0.0f; vel[1] = 0.0f; vel[2] = 0.0f;
	//Set our default Orientation values
	ori[0] = 0.0f; ori[1] = 0.0f; ori[2] = -1.0f; ori[3] = 0.0f; ori[4] = 1.0f; ori[5] = 0.0f;

	//Finally, initialise alut so all our sound will work
	//alutInit(NULL, NULL);

	//Now set up our audio context- start by opening an Audio Device
	hDevice = alcOpenDevice("DirectSound3D");
	if (hDevice == NULL) {
		MessageBox(NULL, "Couldn't open an Audio Device.", "DiZ Sound Error", MB_OK | MB_ICONINFORMATION);
	}
	//Now create an Audio Context from our Device
	hContext = alcCreateContext(hDevice, NULL);
	if (alcGetError(hDevice) != ALC_NO_ERROR) {
		MessageBox(NULL, "Couldn't create an Audio Context.", "DiZ Sound Error", MB_OK | MB_ICONINFORMATION);
	}

	//Then set our context as current, and start it processing just in case
	alcMakeContextCurrent(hContext);
	alcProcessContext(hContext);
}

//Define our Deconstructor
DIZ_LISTENER::~DIZ_LISTENER() {

}

//This function sets the OpenAL Listener values to our values
bool DIZ_LISTENER::update() {
	//Set our main values- Position
	alListenerfv(AL_POSITION, pos);
	//Velocity
	alListenerfv(AL_VELOCITY, vel);
	//Orientation
	alListenerfv(AL_ORIENTATION, ori);

	//Then check for errors and return accordingly
	if (alGetError() != AL_NO_ERROR) {
		MessageBox(NULL, "Error setting Listener values.", "Diz Sound Error", MB_OK | MB_ICONINFORMATION);
		return false;
	}else {
		return true;
	}
}

//This function exits our alut session and so on
void DIZ_LISTENER::kill() {
	//Exit alut
	//alutExit();

	//Start off by releasing our Audio Context
	alcMakeContextCurrent(NULL);
	//Then delete it
	alcDestroyContext(hContext);
	//And finally close our Audio Device
	alcCloseDevice(hDevice);
}