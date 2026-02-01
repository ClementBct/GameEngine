#include "Engine/System/Audio/AudioSystem.h"

#include <algorithm>
#include <print>
#include <iostream>

#include "Engine/ECS/GameObject.h"
#include "Engine/ECS/Component/SoundComponent.h"
#include "Engine/ECS/Component/Sound2DComponent.h"
#include "Engine/ECS/Component/Sound3DComponent.h"

AudioSystem::AudioSystem()
{
    m_device = alcOpenDevice(nullptr);
    if (!m_device) { 
        std::println("Enable to open OpenAL device");
        return;
    }
    m_context = alcCreateContext(m_device, nullptr);
    alcMakeContextCurrent(m_context);
    //On alloue un nombre de source définis en amont
    m_sources_list.resize(m_max_sources);
    alGenSources(m_max_sources, m_sources_list.data());
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        std::println("Enable to generate sources: {0}", err);
    }
}

AudioSystem::~AudioSystem()
{
    // Libérer les sources
    alDeleteSources(m_sources_list.size(), m_sources_list.data());
    // Libérer buffers
    for (auto& buffer : m_buffers_list) {
        alDeleteBuffers(1, &buffer.second);
    }

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}

void AudioSystem::setListenerPosition(Vector3D& i_listener_position)
{
    m_listener_position = i_listener_position;
}

SoundHandler_t AudioSystem::play2DSound(Sound2DComponent& i_sound_2d)
{
    SoundHandler_t audio_handler;
    //Récupérer une source disponible
    ALuint source = getFreeSource();

    //On récupère le buffer data lier au fichier
    auto it = m_buffers_list.find(i_sound_2d.getPath());
    if (it != m_buffers_list.end()) {
        //Link buffer data to source
        ALuint buffer = it->second;
        alSourcei(source, AL_BUFFER, it->second);
    }else {
        std::println("Can't play sound: buffer data not found in map");
        return audio_handler;
    }
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        std::cerr << "OpenAL error: " << err << std::endl;
    }
    alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
    //Define source position in world space
    alSource3f(source, AL_POSITION, 0, 0, 0);
    //Define source attenuation over disrtance
    alSourcef(source, AL_ROLLOFF_FACTOR, 0.0f);
    if (i_sound_2d.getIsLooping()) {
        alSourcei(source, AL_LOOPING, AL_TRUE);
    }
    else {
        alSourcei(source, AL_LOOPING, AL_FALSE);
    }
    alSourcef(source, AL_GAIN, i_sound_2d.getVolume());   // volume
    alSourcef(source, AL_PITCH, i_sound_2d.getPitch());  // vitesse

    alSourcePlay(source);
    err = alGetError();
    if (err != AL_NO_ERROR) {
        std::cerr << "OpenAL error: " << err << std::endl;
    }
    return audio_handler;
}

SoundHandler_t AudioSystem::play3DSound(Sound3DComponent& i_sound_3d)
{
    SoundHandler_t tempo;
    return tempo;
    /*
    ALuint source;
    alGenSources(1, &source);
    //Link buffer data to source
    alSourcei(source, AL_BUFFER, m_buffers_list[i_sound_id]);
    alSourcei(source, AL_SOURCE_RELATIVE, AL_FALSE);
    //Define source position in world space
    alSource3f(source, AL_POSITION, 0, 0, 0);
    //Define source attenuation over disrtance
    alSourcef(source, AL_ROLLOFF_FACTOR, 0.0f); //attenuation factor
    if (looping) {
        alSourcei(source, AL_LOOPING, AL_TRUE);
    }
    alSourcef(source, AL_GAIN, 0.7f);   // volume
    alSourcef(source, AL_PITCH, 1.0f);  // vitesse
    alSourcePlay(source);
    // Stocker la source pour pouvoir la contrôler plus tard
    if (i_sound_id >= m_sources_list.size()) {
        m_sources_list.resize(i_sound_id + 1, 0);
    }
    m_sources_list[i_sound_id] = source;
    */
}

void AudioSystem::pauseSound(SoundHandler_t& i_sound_handler)
{
    /*
    auto source = std::find(m_sources_list.begin(), m_sources_list.end(), i_sound_id);
    if (source != m_sources_list.end()) {
        alSourcePause(source);
    }
    */
}

void AudioSystem::stopSound(SoundHandler_t& i_sound_handler)
{
    /*
    alSourceStop();
    */
}

void AudioSystem::loadSound(GameObject* i_game_object)
{
    for (auto audio_component : i_game_object->getComponents<SoundComponent>() ){
        auto iter = m_buffers_list.find(audio_component->getPath());
        if (iter != m_buffers_list.end()) {
            //Buffer trouvé dans la map donc pas besoin de la charger
            continue;
        }
        ALuint buffer = -1;
        if (loadWav(audio_component->getPath().c_str(), buffer)) {
            m_buffers_list.emplace(audio_component->getPath(), buffer);
        }
    }
}

ALuint AudioSystem::getFreeSource()
{
    for (ALuint& source : m_sources_list)
    {
        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);

        if (state != AL_PLAYING) {
            return source;
        }
    }

    // Toutes occupées les sources sont occuper on vole la plus ancienne
    alSourceStop(m_sources_list[0]);
    return m_sources_list[0];
}
bool AudioSystem::loadWav(const std::string& i_path, ALuint& o_buffer)
{
    FILE* filePtr = nullptr;
    if (fopen_s(&filePtr, i_path.c_str(), "rb") != 0 || !filePtr) {
        std::println("Failed to open WAV: {0}", i_path);
        return false;
    }

    RiffWaveHeaderType riffWaveFileHeader;
    SubChunkHeaderType subChunkHeader;
    FmtType fmtData;
    unsigned int count, seekSize;
    bool foundFormat, foundData;
    
    // Read in the riff wave file header.
    count = fread(&riffWaveFileHeader, sizeof(riffWaveFileHeader), 1, filePtr);
    if (count != 1)
    {
        return false;
    }

    // Check that the chunk ID is the RIFF format.
    if ((riffWaveFileHeader.chunkId[0] != 'R') || (riffWaveFileHeader.chunkId[1] != 'I') || (riffWaveFileHeader.chunkId[2] != 'F') || (riffWaveFileHeader.chunkId[3] != 'F'))
    {
        return false;
    }

    // Check that the file format is the WAVE format.
    if ((riffWaveFileHeader.format[0] != 'W') || (riffWaveFileHeader.format[1] != 'A') || (riffWaveFileHeader.format[2] != 'V') || (riffWaveFileHeader.format[3] != 'E'))
    {
        return false;
    }

    foundFormat = false;
    while (foundFormat == false)
    {
        // Read in the sub chunk header.
        count = fread(&subChunkHeader, sizeof(subChunkHeader), 1, filePtr);
        if (count != 1)
        {
            return false;
        }

        // Determine if it is the fmt header.  If not then move to the end of the chunk and read in the next one.
        if ((subChunkHeader.subChunkId[0] == 'f') && (subChunkHeader.subChunkId[1] == 'm') && (subChunkHeader.subChunkId[2] == 't') && (subChunkHeader.subChunkId[3] == ' '))
        {
            foundFormat = true;
        }
        else
        {
            fseek(filePtr, subChunkHeader.subChunkSize, SEEK_CUR);
        }
    }
    count = fread(&fmtData, sizeof(fmtData), 1, filePtr);
    if (count != 1)
    {
        return false;
    }

    // Check that the audio format is WAVE_FORMAT_PCM (1).
    if (fmtData.audio_format != 1)
    {
        return false;
    }

    // Check that the wave file was recorded in stereo format.
    if (fmtData.num_channels != 2)
    {
        return false;
    }
    // Ensure that the wave file was recorded in 16 bit format.
    if (fmtData.bits_per_sample != 16)
    {
        return false;
    }
    seekSize = subChunkHeader.subChunkSize - 16;
    fseek(filePtr, seekSize, SEEK_CUR);

    // Read in the sub chunk headers until you find the data chunk.
    foundData = false;
    while (foundData == false)
    {
        // Read in the sub chunk header.
        count = fread(&subChunkHeader, sizeof(subChunkHeader), 1, filePtr);
        if (count != 1)
        {
            return false;
        }

        // Determine if it is the data header.  If not then move to the end of the chunk and read in the next one.
        if ((subChunkHeader.subChunkId[0] == 'd') && (subChunkHeader.subChunkId[1] == 'a') && (subChunkHeader.subChunkId[2] == 't') && (subChunkHeader.subChunkId[3] == 'a'))
        {
            foundData = true;
        }
        else
        {
            fseek(filePtr, subChunkHeader.subChunkSize, SEEK_CUR);
        }
    }

    // Store the size of the data chunk.
    m_waveSize = subChunkHeader.subChunkSize;

    // Create a temporary buffer to hold the wave file data.
    m_waveData = new unsigned char[m_waveSize];

    // Read in the wave file data into the newly created buffer.
    count = fread(m_waveData, 1, m_waveSize, filePtr);
    if (count != m_waveSize)
    {
        return false;
    }

    // Close the file once done reading.
    fclose(filePtr);
    alGenBuffers(1, &o_buffer);
    alBufferData(o_buffer, AL_FORMAT_STEREO16, m_waveData, m_waveSize, 48000);
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        std::cerr << "Failed to fill OpenAL buffer: " << err << std::endl;
        return false;
    }
    return true;
}

