#include "UserInterface/mainUserInterface.h"
#include "Engine/UI/Widget/UIImage.h"
#include "Engine/ECS/GameObject.h"
#include "Engine/Core/Renderer/Texture.h"
#include "Engine/Core/Scene.h"
#include "Engine/Core/GameManager.h"
#include "Engine/Core/RessourceLoader.h"

MainUserInterface::MainUserInterface(PlayerController& i_pc, RessourceLoader& i_ressource_loader) : UserInterface(i_pc, i_ressource_loader){
    UIImage* img = createWidget<UIImage>("main_img");
    Texture* ui_img_texture = m_ressource_loader.createTexture("carrot.png");
    img->setTexture(ui_img_texture);
}