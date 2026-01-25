#pragma once

#include "Engine/System/System.h"
#include "Engine/Utils/Math.h"
#include <string>
#include <unordered_map>
#include <vector>

#include <AL/alc.h>
#include <AL/al.h>

/**
 * @brief Sound handler
 */
typedef struct SoundHandler_t {
	unsigned int id;
};

struct RiffWaveHeaderType
{
    char chunkId[4];
    unsigned int chunkSize;
    char format[4];
};

struct SubChunkHeaderType
{
    char subChunkId[4];
    unsigned int subChunkSize;
};

struct FmtType
{
    unsigned short audio_format;
    unsigned short num_channels;
    unsigned int sample_rate;
    unsigned int bytes_per_second;
    unsigned short block_align;
    unsigned short bits_per_sample;
};

class AudioSystem : public System
{
public :
	AudioSystem();
	~AudioSystem();
	void setListenerPosition(Vector3D& i_listener_position);
	SoundHandler_t play2DSound(class Sound2DComponent& i_sound_2d);
	SoundHandler_t play3DSound(class Sound3DComponent& i_sound_3d);
	void pauseSound(SoundHandler_t& i_sound_handler);
	void stopSound(SoundHandler_t& i_sound_handler);
	void loadSound(class GameObject* i_game_object);
private :
	/**
	 * @brief The maximum number of sources that can be played at the same time
	 */
	const int m_max_sources = 32;
	ALCdevice* m_device = nullptr;
	ALCcontext* m_context = nullptr;
	Vector3D m_listener_position = { 0.0f, 0.0f, 0.0f };
	/*Correspond au données du son*/
	std::unordered_map<std::string, ALuint> m_buffers_list;
	/*Correspond au générateur de son*/
	std::vector<ALuint> m_sources_list;
	ALuint getFreeSource();
	bool loadWav(const char* i_path, ALuint& o_buffer);
	//tempo
	unsigned char* m_waveData;
	unsigned int m_waveSize;
};

