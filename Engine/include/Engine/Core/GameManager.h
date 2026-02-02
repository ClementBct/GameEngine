#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

#include "Engine/Utils/Math.h"

class Scene;
class PlayerController;
class Camera;
class RessourceLoader;
//System
class UISystem;
class PhysicsSystem;
class RenderSystem;
class InputSystem;
class AudioSystem;

class Renderer;
class Window;

class GameManager
{
public:
    GameManager();
    ~GameManager();
    void run();
    void shutdown();
    void setCurrentScene(Scene& i_scene);
    void setCurrentPlayerController(PlayerController& i_pc);
    PlayerController* createPlayerController(const std::string& i_pc_name);
    PlayerController* getPlayerController()const;
    const Camera& getCamera()const;
    RessourceLoader& getRessourceLoader()const;
private:
    void updateGame(float i_dt_s);
    void fixedUpdateGame(float i_fixed_dt_s);
    void generateOutput();
    void loadScene(Scene& i_scene);
    void unloadScene(Scene& i_scene);

    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<RessourceLoader> m_ressource_loader;
    //System
    std::unique_ptr<InputSystem> m_input_system;
    std::unique_ptr<AudioSystem> m_audio_system;
    std::unique_ptr<UISystem> m_ui_system;
    std::unique_ptr<PhysicsSystem> m_physics_system;
    std::unique_ptr<RenderSystem> m_render_system;

    uint32_t m_ticks_count = 0;
    double m_accumulator = 0.0;
    bool m_is_running = true;
    Scene* m_current_scene = nullptr;
    PlayerController* m_pc = nullptr;
};
