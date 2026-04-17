#pragma once
#include <AL/al.h>
#include <iostream>
#include <vector>

namespace zSounds
{
	class Sound
	{
	private:
		uint32_t ID;

		bool LoadAudioFile(const wchar_t* filename, std::vector<char>& buffer, ALenum& format, ALsizei& freq);

	public:
		Sound(const wchar_t* filename);
		~Sound();

		inline uint32_t GetID() const { return ID ? ID : 0; }

	};
}