#pragma once
#include "../Essentials/Sound.h"

namespace zSounds
{
	class SoundSource
	{
	private:
		uint32_t ID;
		uint32_t soundID = 0;

	public:
		SoundSource();
		~SoundSource();

		void Play(const Sound& sound);
		void Resume();
		void Pause();
		void Stop();

		void SetPitch(float pitch);
		void SetVolume(float volume);
		void SetLoop(bool loop);

		float GetPitch();
		float GetVolume();
		bool IsLooping();

		bool IsPlaying();
		bool IsPaused();

		void SetPosition(float x, float y, float z);
	};
}