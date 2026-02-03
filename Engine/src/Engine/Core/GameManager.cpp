#include "Engine/Core/GameManager.h"

#include "Engine/ECS/GameObject.h"

//System
#include "Engine/System/Audio/AudioSystem.h"
#include "Engine/System/Physics/PhysicsSystem.h"
#include "Engine/System/Render/RenderSystem.h"
#include "Engine/System/Input/InputSystem.h"
#include "Engine/System/UI/UISystem.h"
#include "Engine/System/Scene/SceneSystem.h"

#include "Engine/UI/UserInterface.h"


#include "Engine/Core/RessourceLoader.h"
#include "Engine/Core/Camera.h"
#include "Engine/Core/Window.h"
#include "Engine/Core/Renderer/Renderer.h"
#include "Engine/Core/Scene.h"
#include "Engine/ECS/PlayerController.h"

#include <SDL3/SDL_timer.h> //Get_Ticks()

#include <print>
#include <algorithm>

GameManager::GameManager(): m_is_running(true) {
    m_window = std::make_unique<Window>("no name");
    m_renderer = std::make_unique<Renderer>();
    m_renderer->createRenderer(m_window->getWindow());
    m_camera = std::make_unique<Camera>(*m_window);

    m_input_system = std::make_unique<InputSystem>();
    m_input_system->registerQuitCallback([this]() { m_is_running = false; });

    m_audio_system = std::make_unique<AudioSystem>();

    m_physics_system = std::make_unique<PhysicsSystem>();
    m_render_system = std::make_unique<RenderSystem>(*m_renderer, *m_camera);
    m_ui_system = std::make_unique<UISystem>();

    m_ressource_loader = std::make_unique<RessourceLoader>(*m_renderer);
    m_scene_system = std::make_unique<SceneSystem>();
}

GameManager::~GameManager() {
    shutdown();
}
void GameManager::run()
{
    constexpr float FIXED_TIMESTEP = 1.0f / 240.0f; // 240 Hz physique
    float accumulator = 0.0f;

    Uint32 lastTime = SDL_GetTicks();

    while (m_is_running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // Évite le spiral of death
        if (deltaTime > 0.25f)
            deltaTime = 0.25f;

        accumulator += deltaTime;

        //UPDATE VARIABLE (chaque frame)

        updateGame(deltaTime);          // caméra, animations, logique non physique

        //FIXED UPDATE (physique / gameplay)
        while (accumulator >= FIXED_TIMESTEP)
        {
            fixedUpdateGame(FIXED_TIMESTEP);
            accumulator -= FIXED_TIMESTEP;
        }

        //RENDER (après updates)
        generateOutput();
    }
}

void GameManager::shutdown() {
    if (m_current_scene) {
        unloadScene(*m_current_scene);
    }
}
void GameManager::updateGame(float i_dt_s) {
    //Update des inputs
    m_input_system->onUpdate(i_dt_s);
    //Update des gameObject et des component
    if (m_current_scene) {
        m_current_scene->onUpdate(i_dt_s);
    }
    //Update des animation UI
    m_ui_system->onUpdate(i_dt_s);
}

void GameManager::fixedUpdateGame(float i_fixed_dt_s) {
  //Update du moteur physique
  m_physics_system->onUpdate(i_fixed_dt_s);
}

void GameManager::generateOutput() {
    m_render_system->renderFrame(m_current_scene, m_ui_system->getActiveUserInterface());
}

void GameManager::setCurrentScene(Scene& i_scene) {
    if (m_current_scene) {
        unloadScene(*m_current_scene);
    }
    m_current_scene = &i_scene;
    loadScene(i_scene);
}

void GameManager::setCurrentPlayerController(PlayerController& i_pc) {
    m_pc = &i_pc;
}

PlayerController* GameManager::createPlayerController(const std::string& i_pc_name) {
    //auto pc = std::make_shared<PlayerController>(*m_input_system, i_pc_name);
    //m_pc = pc.get();
    //fuite mémmoire ici car par supprimer !!!!!!
    m_pc = new PlayerController(*m_input_system,*m_ui_system);
    return m_pc;
}

PlayerController& GameManager::getPlayerController() const{
    return *m_pc;
}

const Camera& GameManager::getCamera()const {
    return *m_camera;
}

RessourceLoader& GameManager::getRessourceLoader()const {
    return *m_ressource_loader;
}

UISystem& GameManager::getUISystem()const {
    return *m_ui_system;
}

void GameManager::loadScene(Scene& i_scene) {
    //On viens crée les physics body pour chaque objet s'il possède un Rb ainsi que l'audio
    for (auto game_object : i_scene.getGameObjectList()) {
        m_physics_system->createPhysicsBody(game_object);
        m_audio_system->loadSound(game_object);

    }
    for (auto game_object : i_scene.getGameObjectList()) {
        game_object->onStart();
    }
}


void GameManager::unloadScene(Scene& i_scene) {
    i_scene.onUnLoad();
}

