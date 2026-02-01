#include "Engine/Core/GameManager.h"

#include "Engine/ECS/GameObject.h"

//System
#include "Engine/System/Audio/AudioSystem.h"
#include "Engine/System/Physics/PhysicsSystem.h"
#include "Engine/System/RenderSystem.h"
#include "Engine/System/Input/InputSystem.h"
#include "Engine/System/UI/UISystem.h"


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
    m_window = new Window();
    m_renderer = new Renderer();
    m_renderer->createRenderer(m_window->getWindow());
    m_camera = new Camera(*m_window);

    m_input_system = new InputSystem();
    m_input_system->registerQuitCallback([this]() { m_is_running = false; });

    m_audio_system = new AudioSystem();

    m_physics_system = new PhysicsSystem();
    m_render_system = new RenderSystem(*m_renderer, *m_camera);
    m_ressource_loader = new RessourceLoader(*m_renderer);

    m_ui_system = new UISystem();
}

void GameManager::run() {
    const float FIXED_TIMESTEP = 1.0f / 240.0f; // 240 FPS
    float accumulator = 0.0f;

    Uint32 lastTime = SDL_GetTicks();
    while (m_is_running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        if (deltaTime > 0.25f) {
            deltaTime = 0.25f;
        }
        accumulator += deltaTime;
        //update clavier/souris
        m_input_system->onUpdate(deltaTime);
        // Mise à jour physique avec steps fixes
        while (accumulator >= FIXED_TIMESTEP) {
            updateGame(FIXED_TIMESTEP);
            accumulator -= FIXED_TIMESTEP;
        }
        generateOutput();
        m_ui_system->onUpdate(deltaTime);
    }
}

void GameManager::shutdown() {
    //unloadScene();
    delete m_physics_system;
    delete m_render_system;
    delete m_audio_system;
    delete m_window;
    delete m_renderer;
    delete m_camera;
    delete m_ressource_loader;
}
void GameManager::updateGame(float i_dt_s) {
    //Update du moteur physique
       m_physics_system->onUpdate(i_dt_s);
    //Update des gameObject et des component
    if (m_current_scene) {
        m_current_scene->onUpdate(i_dt_s);
    }
}

void GameManager::generateOutput() {
    if (m_current_scene) {
        m_render_system->renderScene(m_current_scene);
    }
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
    auto pc = std::make_shared<PlayerController>(*m_input_system, i_pc_name);
    m_pc = pc.get();
    return m_pc;
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

