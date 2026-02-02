#include "Engine/ECS/Component/Sound3DComponent.h"
#include "Engine/ECS/GameObject.h"
#include "Engine/System/Audio/AudioSystem.h"
#include "Engine/Core/GameManager.h"
#include "Engine/Core/Scene.h"

Sound3DComponent::Sound3DComponent(GameObject& i_owner, const std::string& i_path) : SoundComponent(i_owner, i_path)
{
}

void Sound3DComponent::play()
{
	//m_owner.getScene().getGameManager().m_audio_system->play3DSound(*this);
}
