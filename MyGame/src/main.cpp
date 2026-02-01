#include "Engine/Core/GameManager.h"

#include "Engine/ECS/PlayerController.h"
#include "Scene/MainScene.h"
#include "Scene/MenuScene.h"


int main(int argc, char** argv) {
    GameManager engine;
    MainScene main_scene(engine);
    MenuScene menu_scene(engine);
    engine.createPlayerController("main_pc");
    engine.setCurrentScene(main_scene);
    engine.run();
    return 0;
}