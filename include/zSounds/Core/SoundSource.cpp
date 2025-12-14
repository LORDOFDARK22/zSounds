#include "SoundSource.h"

namespace zSounds
{
	SoundSource::SoundSource()
	{
		alGenSources(1, &ID);

		alSource3f(ID, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSource3f(ID, AL_VELOCITY, 0.0f, 0.0f, 0.0f);

		SetPitch(1.0f);
		SetVolume(1.0f);
		SetLoop(false);
	}
	SoundSource::~SoundSource()
	{
		alDeleteSources(1, &ID);
	}
	void SoundSource::Play(const Sound& sound)
	{
		if (IsPlaying() && IsPaused())
			return;

		ALuint newSoundID = sound.GetID();
		if (newSoundID != soundID)
		{
			soundID = newSoundID;
			alSourcei(ID, AL_BUFFER, static_cast<ALint>(soundID));
		}

		alSourceRewind(ID);
		alSourcePlay(ID);
	}
	void SoundSource::Resume()
	{
		if (IsPaused())
			alSourcePlay(ID);
	}
	void SoundSource::Pause()
	{
		alSourcePause(ID);
	}
	void SoundSource::Stop()
	{
		alSourceStop(ID);
		alSourceRewind(ID);
	}
	void SoundSource::SetPitch(float pitch)
	{
		float newPitch = pitch;
		if (newPitch < 0.0f)
			newPitch = 0.0f;
		else if (newPitch > 2.0f)
			newPitch = 2.0f;

		alSourcef(ID, AL_PITCH, newPitch);
	}
	void SoundSource::SetVolume(float volume)
	{
		float newVol = volume;
		if (newVol < 0.0f)
			newVol = 0.0f;
		else if (newVol > 1.0f)
			newVol = 1.0f;

		alSourcef(ID, AL_GAIN, newVol);
	}
	void SoundSource::SetLoop(bool loop)
	{
		alSourcei(ID, AL_LOOPING, (int)loop);
	}
	float SoundSource::GetPitch()
	{
		float pitch;
		alGetSourcef(ID, AL_PITCH, &pitch);
		return pitch;
	}
	float SoundSource::GetVolume()
	{
		float volume;
		alGetSourcef(ID, AL_GAIN, &volume);
		return volume;
	}
	bool SoundSource::IsLooping()
	{
		int loop;
		alGetSourcei(ID, AL_LOOPING, &loop);
		return loop == 1 ? true : false;
	}
	bool SoundSource::IsPlaying()
	{
		int state;
		alGetSourcei(ID, AL_SOURCE_STATE, &state);
		return (state == AL_PLAYING);
	}
	bool SoundSource::IsPaused()
	{
		int state;
		alGetSourcei(ID, AL_SOURCE_STATE, &state);
		return (state == AL_PAUSED);
	}
	void SoundSource::SetPosition(float x, float y, float z)
	{
		alSource3f(ID, AL_POSITION, x, y, z);
	}
}