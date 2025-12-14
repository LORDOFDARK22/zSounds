#pragma once
#include <AL/alc.h>
#include <string>

namespace zSounds
{
	class SoundDevice
	{
	private:
		ALCdevice* alcDevice;
		ALCcontext* alcContext;
		std::string deviceName;

		SoundDevice();
		~SoundDevice();

	public:
		static SoundDevice* Get();

		void SetMasterVolume(float volume);

		inline const std::string GetCurrentDeviceName() const { return deviceName; }

		void SetLocation(float x, float y, float z);
		void SetOrientation(float atx, float aty, float atz, float upx, float upy, float upz);
	};
}