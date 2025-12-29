#include "Engine/Core/GameManager.h"

#include "Engine/ECS/GameObject.h"

#include "Engine/System/AudioSystem.h"
#include "Engine/System/PhysicsSystem.h"
#include "Engine/System/RenderSystem.h"
#include "Engine/System/InputSystem.h"

#include "Engine/Core/RessourceLoader.h"
#include "Engine/Core/Camera.h"
#include "Engine/Core/Window.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/Scene.h"

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
    ressource_loader = new RessourceLoader(*m_renderer);

    initialize();
}

// --- Public Methods ---
bool GameManager::initialize() {
    m_ticks_count = 0;
    return true;
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
        processInput();
        // Mise à jour physique avec steps fixes
        while (accumulator >= FIXED_TIMESTEP) {
            updateGame(FIXED_TIMESTEP);
            accumulator -= FIXED_TIMESTEP;
        }
        generateOutput();
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
    delete ressource_loader;
}

void GameManager::processInput() {
    if (m_current_scene) {
        m_input_system->processInput(m_current_scene);
    }
}
void GameManager::updateGame(float i_dt_s) {
    //Update du moteur physique
    m_physics_system->updatePhysicsSystem(i_dt_s);
    //Update des gameObject et des component
    if (m_current_scene) {
        for (auto game_object : m_current_scene->getGameObjectList()) {
            game_object->onUpdate(i_dt_s);
        }
    }
}

void GameManager::generateOutput() {
    if (m_current_scene) {
        m_render_system->renderScene(m_current_scene);
    }
}

void GameManager::addScene(class Scene* i_scene) {
    m_scene_list.push_back(i_scene);
}

void GameManager::setCurrentScene(class Scene& i_scene) {
    m_current_scene = &i_scene;
    loadScene(i_scene);
}

void GameManager::loadScene(Scene& i_scene) {
    //On viens crée les physics body pour chaque objet s'il possède un Rb ainsi que l'audio
    for (auto game_object : i_scene.getGameObjectList()) {
        m_physics_system->createPhysicsBody(game_object);
        m_audio_system->loadSound(game_object);
        m_render_system->loadTexture(game_object);
    }
    for (auto game_object : i_scene.getGameObjectList()) {
        game_object->onStart();
    }
}


void GameManager::unloadScene(Scene& i_scene) {

    // Because ~GameObject calls RemoveGameObject, have to use a different style loop
    /*
    while (!m_game_object_list.empty())
    {
        delete m_game_object_list.back();
    }
    */
}

