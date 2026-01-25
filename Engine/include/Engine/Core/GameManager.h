#pragma once
#include <vector>
#include <unordered_map>
#include <string>

#include "Engine/Utils/Math.h"

class GameManager
{
public:
    GameManager();
    void run();
    void shutdown();

    template<typename T>
    T* spawnGameObject(Vector2D i_position = {0.0f,0.0f}, Vector2D i_scale = {1.0f,1.0f}, float i_rotation = 0.0f);


    void addScene(class Scene* i_scene);
    class RessourceLoader* m_ressource_loader = nullptr;
    class InputSystem* m_input_system = nullptr;
    class AudioSystem* m_audio_system = nullptr;
    void setCurrentScene(class Scene& i_scene);
private:
    void processInput();
    void updateGame(float i_dt_s);
    void generateOutput();
    void loadScene(class Scene& i_scene);
    void unloadScene(class Scene& i_scene);

    class PhysicsSystem* m_physics_system = nullptr;
    class RenderSystem* m_render_system = nullptr;
    class Renderer* m_renderer = nullptr;
    class Camera* m_camera = nullptr;
    class Window* m_window = nullptr;

    std::vector<class Scene*> m_scene_list;

    uint32_t m_ticks_count = 0;
    double m_accumulator = 0.0;
    bool m_is_running = true;
    class Scene* m_current_scene = nullptr;
};

// Inclusion du .inl � la fin du header
#include "GameManager.inl"
