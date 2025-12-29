#include "Engine/ECS/Component/SoundComponent.h"

SoundComponent::SoundComponent(GameObject& i_owner, const std::string& i_path) : Component(i_owner), m_path(i_path)
{
}

void SoundComponent::setVolume(float i_volume)
{
	m_volume = i_volume;
}

float SoundComponent::getVolume()
{
	return m_volume;
}

void SoundComponent::pause()
{
}

void SoundComponent::setLooping(bool i_looping)
{
	m_is_looping = i_looping;
}

bool SoundComponent::getIsLooping()
{
	return m_is_looping;
}

float SoundComponent::getPitch()
{
	return m_pitch;
}

std::string SoundComponent::getPath()
{
	return m_path;
}
