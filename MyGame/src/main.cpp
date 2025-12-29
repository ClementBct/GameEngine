#include "Engine/Core/GameManager.h"

#include "Scene/MainScene.h"
#include "Scene/MenuScene.h"

int main(int argc, char** argv) {
    GameManager engine;
    MainScene main_scene(engine);
    MenuScene menu_scene(engine);
    engine.setCurrentScene(main_scene);
    engine.run();

    return 0;
}