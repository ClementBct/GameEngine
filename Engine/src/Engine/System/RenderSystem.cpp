#include "Engine/System/RenderSystem.h"
#include "Engine/Core/Renderer/Renderer.h"
#include "Engine/Core/Renderer/Texture.h"
#include "Engine/Core/Camera.h"
#include "Engine/Core/Scene.h"

#include "Engine/System/PhysicsSystem.h"
#include "SDL3/SDL.h"

/*GameObject*/
#include "Engine/ECS/GameObject.h"
/*Component*/
#include "Engine/ECS/Component/SpriteComponent.h"
#include "Engine/ECS/Component/Collider2DComponent.h"

#include <iostream>

RenderSystem::RenderSystem(Renderer& i_renderer, Camera& i_camera) : m_renderer(i_renderer), m_camera(i_camera)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::renderScene(Scene* i_scene)
{
	m_renderer.beginFrame();
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
	m_renderer.endFrame();
}

void RenderSystem::drawSprite(SpriteComponent* i_sprite, float i_camera_zoom)
{
    if (!i_sprite) {
        std::cout << "Sprite is not valid" << std::endl;
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
