#include "Engine/ECS/Component/Sound2DComponent.h"
#include "Engine/System/AudioSystem.h"
#include "Engine/ECS/GameObject.h"
#include "Engine/Core/GameManager.h"

Sound2DComponent::Sound2DComponent(GameObject& i_owner, const std::string& i_path) : SoundComponent(i_owner, i_path)
{
}

void Sound2DComponent::play()
{
	m_owner.getGameMgr()->m_audio_system->play2DSound(*this);
}
