#include "Engine/UI/Widget/UIImage.h"
#include "Engine/Core/Renderer/Texture.h"

UIImage::UIImage(const std::string& i_name, UIWidget* i_parent) : UIWidget(i_name, i_parent) {

}

UIImage::~UIImage() {

}

void UIImage::setTexture(Texture* i_texture) {
	m_img_texture = i_texture;
}

Texture* UIImage::getTexture() {
	return m_img_texture;
}