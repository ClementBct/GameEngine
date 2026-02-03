#include "Engine/System/Render/RenderSystem.h"
#include "Engine/Core/Renderer/Renderer.h"
#include "Engine/Core/Renderer/Texture.h"
#include "Engine/Core/Camera.h"
#include "Engine/Core/Scene.h"
//UI
#include "Engine/UI/UserInterface.h"
#include "Engine/UI/Widget/UIWidget.h"
//UI Componenent
#include "Engine/UI/Component/UITransform.h"

#include "Engine/System/Physics/PhysicsSystem.h"
#include "SDL3/SDL.h"

/*GameObject*/
#include "Engine/ECS/GameObject.h"
/*Component*/
#include "Engine/ECS/Component/SpriteComponent.h"
#include "Engine/ECS/Component/Collider2DComponent.h"


//tempo
#include <print>


RenderSystem::RenderSystem(Renderer& i_renderer, Camera& i_camera) : m_renderer(i_renderer), m_camera(i_camera)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::renderUserInterface(UserInterface* i_ui) {
    if (!i_ui) {
        return;
    }
    for (auto widget : i_ui->getWidgetList()) {
        Texture* texture = widget->getTexture();
        if (texture) {
            m_renderer.drawTexture(texture, 0 , 0, 500, 500, 0);
        }
    }
}

void RenderSystem::renderFrame(Scene* scene, std::vector<UserInterface*>& i_ui_list)
{
    m_renderer.beginFrame();

    renderScene(scene);        // monde
    for (auto ui : i_ui_list) {
        renderUserInterface(ui);   // UI par-dessus
    }
    m_renderer.endFrame();
}

void RenderSystem::renderScene(Scene* i_scene)
{
    if (!i_scene) {
        return;
    }
    //remplacer par une ref
	for (auto game_object : i_scene->getGameObjectList()) {
        for (auto sprite : game_object->getComponents<SpriteComponent>()) {
            drawSprite(sprite, m_camera.getCameraZoom());
        }
		for (auto collider : game_object->getComponents<Collider2DComponent>()) {
			if (collider->m_is_collider_visible) {
				drawCollider(collider);
			}
		}
	}
}

void RenderSystem::drawSprite(SpriteComponent* i_sprite, float i_camera_zoom)
{
    if (!i_sprite) {
        return;
    }
    float w = i_sprite->getWorldSize().x * i_camera_zoom;
    float h = i_sprite->getWorldSize().y * i_camera_zoom;
	Vector2D screen_center = m_camera.convertWorldPositionToScreenPosition(i_sprite->getWorldPosition());

	float x = screen_center.x - (w * 0.5f);
	float y = screen_center.y - (h * 0.5f);

	m_renderer.drawTexture(i_sprite->getTexture(),x,y, w, h, i_sprite->getWorldRotation());
}

void RenderSystem::drawCollider(Collider2DComponent* i_collider)
{
    b2ShapeId shapeId = *i_collider->getShapeId();
    b2ShapeType type = b2Shape_GetType(shapeId);
    b2BodyId bodyId = b2Shape_GetBody(shapeId);
    b2Transform transform = b2Body_GetTransform(bodyId);
    if (type == b2_polygonShape) {
        b2Polygon polygon = b2Shape_GetPolygon(shapeId);

        std::vector<SDL_FPoint> points(polygon.count + 1);

        for (int j = 0; j < polygon.count; j++) {
            // Transformer le vertex avec la transform du body
            b2Vec2 worldVertex = b2TransformPoint(transform, polygon.vertices[j]);

            Vector2D physics_position = { worldVertex.x ,worldVertex.y };
            Vector2D world_position = convertPhysicsPositionToWorldPosition(physics_position);
            Vector2D screen_position = m_camera.convertWorldPositionToScreenPosition(world_position);
            points[j].x = screen_position.x;
            points[j].y = screen_position.y;
        }

        points[polygon.count] = points[0];
        m_renderer.drawLine(points.data(), polygon.count + 1);
    }
    else if (type == b2_circleShape) {
        b2Circle circle = b2Shape_GetCircle(shapeId);

        b2Vec2 worldCenter = b2TransformPoint(transform, circle.center);

        const float SCALE = 30.0f;
        int cx = static_cast<int>(worldCenter.x * SCALE);
        int cy = static_cast<int>(worldCenter.y * SCALE);
        int radius = static_cast<int>(circle.radius * SCALE);

        //DrawCircle(renderer, cx, cy, radius);
    }
}
