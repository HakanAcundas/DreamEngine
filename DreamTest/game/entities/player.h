#pragma once

#include <scene_object.h>

using namespace dream;
using namespace graphics;

class Player : public SceneObject
{
public:
    glm::vec2 velocity;
    glm::vec2 acceleration;

    float max_speed = 5.0f;
    float acceleration_rate = 20.0f;
    float friction = 0.9f;
    float gravity = -9.8f;
    float jump_velocity = 15.0f;
    bool is_jumping = false;
    bool is_on_ground = true;

    Player(glm::vec3 position, glm::vec2 size, Texture2D *texture)
        : SceneObject(position, size, texture) { }

    Player(glm::vec3 position, glm::vec2 size, Texture2D::SubTexture2D *sub_texture)
        : SceneObject(position, size, sub_texture) { }

    void apply_input(float dt, bool move_left, bool move_right, bool jump)
    {
        // Horizontal Movement (left and right)
        if (move_left) {
            acceleration.x = -acceleration_rate;
        }
        else if (move_right) {
            acceleration.x = acceleration_rate;
        }
        else {
            // Apply friction when no input is pressed
            acceleration.x = 0.0f;
            velocity.x *= friction;
        }

        // Apply jumping logic
        if (jump && is_on_ground) {
            velocity.y = jump_velocity;
            is_jumping = true;
            is_on_ground = false;
        }

        // Apply gravity only if in the air
        if (!is_on_ground) {
            velocity.y += gravity * dt;
        }
    }

    void update(float dt)
    {
        // Update velocity with acceleration
        velocity.x += acceleration.x * dt;

        // Clamp velocity to max speed
        if (velocity.x > max_speed) velocity.x = max_speed;
        if (velocity.x < -max_speed) velocity.x = -max_speed;

        // Update position using velocity
        glm::vec3 new_position = get_position();
        new_position.x += velocity.x * dt;
        new_position.y += velocity.y * dt;

        // Set the new position
        set_position(new_position);

        // Ground collision detection (assuming y = 0 is the ground)
        if (new_position.y <= 0.0f) {
            new_position.y = 0.0f;
            velocity.y = 0.0f;
            is_on_ground = true;
            is_jumping = false;
        }

        set_position(new_position);
    }

    void draw()
    {
        Renderer2D::get_instance()->draw_quad(get_position(), get_size(), get_sub_texture_2d());
    }
};

