#include "SoundDevice.h"
#include <iostream>
#include <AL/al.h>
#include <stdio.h>
#include <vector>

namespace zSounds
{
	SoundDevice* SoundDevice::Get()
	{
		static SoundDevice* device = new SoundDevice();
		return device;
	}
	void SoundDevice::SetLocation(float x, float y, float z)
	{
		alListener3f(AL_POSITION, x, y, z);
	}
	void SoundDevice::SetOrientation(float atx, float aty, float atz, float upx, float upy, float upz)
	{
		std::vector<float> ori;
		ori.push_back(atx);
		ori.push_back(aty);
		ori.push_back(atz);
		ori.push_back(upx);
		ori.push_back(upy);
		ori.push_back(upz);
		alListenerfv(AL_ORIENTATION, ori.data());
	}
	SoundDevice::SoundDevice() : deviceName{""}
	{
		alcDevice = alcOpenDevice(nullptr);
		if (!alcDevice)
			std::cout << "Failed to open sound Device!" << std::endl;

		alcContext = alcCreateContext(alcDevice, nullptr);
		if (!alcContext)
			std::cout << "Failed to create sound Context!" << std::endl;

		if (!alcMakeContextCurrent(alcContext))
			std::cout << "Failed to make sound Context current!" << std::endl;

		//get name
		if (alcIsExtensionPresent(alcDevice, "ALC_ENUMERATE_ALL_EXT"))
			deviceName = alcGetString(alcDevice, ALC_ALL_DEVICES_SPECIFIER);
		if (!deviceName.c_str() || alcGetError(alcDevice) != AL_NO_ERROR)
			deviceName = alcGetString(alcDevice, ALC_DEVICE_SPECIFIER);

		std::cout << "success opened sound Device: " << deviceName << std::endl;
	}
	SoundDevice::~SoundDevice()
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(alcContext);
		alcCloseDevice(alcDevice);

		delete this;
	}
	void SoundDevice::SetMasterVolume(float volume)
	{
		float newVol = volume;
		if (newVol < 0.0f)
			newVol = 0.0f;
		else if (newVol > 1.0f)
			newVol = 1.0f;

		alListenerf(AL_GAIN, newVol);
	}
}
