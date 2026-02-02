#include "UserInterface/mainUserInterface.h"
#include "Engine/UI/Widget/UIImage.h"
#include "Engine/ECS/GameObject.h"
#include "Engine/Core/Renderer/Texture.h"
#include "Engine/Core/Scene.h"
#include "Engine/Core/GameManager.h"
#include "Engine/Core/RessourceLoader.h"

MainUserInterface::MainUserInterface(GameObject& i_owner) : UserInterface(i_owner, "") {
    UIImage* img = createWidget<UIImage>("main_img");
    Texture* ui_img_texture = m_owner.getScene().getGameManager().getRessourceLoader().createTexture("carrot.png");
    img->setTexture(ui_img_texture);
}