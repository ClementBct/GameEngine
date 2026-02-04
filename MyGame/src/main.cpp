#include "Engine/Core/GameManager.h"

#include "Engine/Core/PlayerController.h"
#include "Scene/MainScene.h"
#include "Scene/MenuScene.h"
#include "Blueprint/mainGameMode.h"

int main(int argc, char** argv) {
    GameManager game_mgr;
    mainGameMode main_gm;
    game_mgr.createPlayerController("main_pc");
    //ajouter un gameMode, dans le gameMode, on a le default pawn, la scene, le playerController
    MainScene main_scene(game_mgr);
    MenuScene menu_scene(game_mgr);
    game_mgr.setCurrentScene(main_scene);
    game_mgr.run();
    return 0;
}