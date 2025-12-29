#pragma once
#include "Component.h"
class SoundComponent : public Component
{
public:
	SoundComponent(class GameObject& i_owner, const std::string& i_path);
	void setVolume(float i_volume);
	float getVolume();
	virtual void play() = 0;
	void pause();
	void setLooping(bool i_looping);
	bool getIsLooping();
	float getPitch();
	std::string getPath();
private :
	int m_sound_id = -1;
	float m_volume = 1.0f;
	float m_pitch = 1.0f;
	bool m_is_looping = false;
	std::string m_path;
};

