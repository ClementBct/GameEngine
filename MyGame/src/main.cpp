#include "Engine/Core/GameManager.h"

#include "Engine/ECS/PlayerController.h"
#include "Scene/MainScene.h"
#include "Scene/MenuScene.h"
#include "Engine/Core/GameMode.h"

int main(int argc, char** argv) {
    GameManager game_mgr;
    GameMode main_gm;
    game_mgr.createPlayerController("main_pc");
    //ajouter un gameMode, dans le gameMode, on a le default pawn, la scene, le playerController
    MainScene main_scene(game_mgr);
    MenuScene menu_scene(game_mgr);
    game_mgr.setCurrentScene(main_scene);
    game_mgr.run();
    return 0;
}