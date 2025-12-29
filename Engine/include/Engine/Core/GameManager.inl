#pragma once

#include "Engine/System/PhysicsSystem.h"
#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/GameObject.h"

template<typename T>
T* GameManager::spawnGameObject(Vector2D i_position, Vector2D i_scale, float i_rotation)
{
    static_assert(std::is_base_of<GameObject, T>::value,
        "T doit hériter de GameObject");

    auto object = new T(*this);

    object->transform->position = i_position;
    object->transform->scale = i_scale;
    object->transform->rotation = i_rotation;

    m_physics_system->createPhysicsBody(object);
    object->onStart();
    return object;
}
