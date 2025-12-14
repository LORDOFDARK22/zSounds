#include "Sound.h"

#define DR_WAV_IMPLEMENTATION
#include "../../dr_wav.h"
#define DR_MP3_IMPLEMENTATION
#include "../../dr_mp3.h"

#include <algorithm>

namespace zSounds
{
	bool Sound::LoadAudioFile(const char* filename, std::vector<char>& buffer, ALenum& format, ALsizei& freq)
	{
		std::string file = filename;

		std::transform(file.begin(), file.end(), file.begin(), ::tolower);

		if (file.find(".wav") != std::string::npos)
		{
			drwav wav;
			if (!drwav_init_file(&wav, filename, nullptr))
			{
				std::cout << "Failed to load WAV file: " << filename << std::endl;
				return false;
			}

			freq = wav.sampleRate;

			switch (wav.channels)
			{
			case 1:
				format = AL_FORMAT_MONO16;
				break;
			case 2:
				format = AL_FORMAT_STEREO16;
				break;
			default:
				std::cout << "Unsupported channel count: " << wav.channels << std::endl;
				drwav_uninit(&wav);
				return false;
				break;
			}

			size_t totalSamples = wav.totalPCMFrameCount * wav.channels;
			buffer.resize(totalSamples * sizeof(int16_t));
			drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, reinterpret_cast<int16_t*>(buffer.data()));

			drwav_uninit(&wav);
			return true;
		}
		else if (file.find(".mp3") != std::string::npos)
		{
			drmp3 mp3;
			if (!drmp3_init_file(&mp3, filename, NULL))
			{
				std::cout << "Failed to load MP3 File: " << filename << "\n";
				return false;
			}

			drmp3_uint64 frameCount;
			drmp3_config config;
			int16_t* sampleData = drmp3__full_read_and_close_s16(&mp3, &config, &frameCount);
			if (!sampleData)
			{
				std::cout << "Failed to read file MP3\n";
				return false;
			}

			freq = (ALsizei)mp3.sampleRate;

			switch (mp3.channels)
			{
			case 1:
				format = AL_FORMAT_MONO16;
				break;
			case 2:
				format = AL_FORMAT_STEREO16;
				break;
			default:
				std::cout << "Unsupported channel count: " << mp3.channels << std::endl;
				drmp3_free(sampleData, NULL);
				return false;
				break;
			}

			size_t sampleCount = (size_t)frameCount * config.channels;
			buffer.resize(sampleCount * sizeof(int16_t));
			memcpy(buffer.data(), sampleData, buffer.size());

			drmp3_free(sampleData, NULL);
			return true;
		}

		std::cout << "Unsupported audio format: " << file << std::endl;
		return false;
	}
	Sound::Sound(const std::string& soundPath)
	{
		std::vector<char> buffer;
		ALenum format;
		ALsizei freq;

		if (!LoadAudioFile(soundPath.c_str(), buffer, format, freq))
		{
			return;
		}

		alGenBuffers(1, &ID);

		alBufferData(ID, format, buffer.data(), static_cast<ALsizei>(buffer.size()), freq);
	}
	Sound::~Sound()
	{
		alDeleteBuffers(1, &ID);
	}
}