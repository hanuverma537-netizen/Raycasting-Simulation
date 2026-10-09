#include "Player.h"
#include<cmath>
#include<algorithm>

//PLAYER CLASS HELPER FUNCTIONS


Vector2 rotatePoint(Vector2 vertex, Vector2 playerCenter, int turnAngle) {
    float radians = turnAngle * DEG2RAD;

    float x = vertex.x - playerCenter.x;
    float y = vertex.y - playerCenter.y;

    float rotatedX = x * cos(radians) - y * sin(radians);
    float rotatedY = x * sin(radians) + y * cos(radians);

    return {rotatedX + playerCenter.x,
            rotatedY + playerCenter.y};
}

Vector2 getDirection(int turnAngle) {
    return {(float) sin(turnAngle * DEG2RAD), 
            (float) -cos(turnAngle * DEG2RAD)};
}

//ALL PLAYER CLASS FUNCTIONS


//PLAYER DRAW
void Player::draw() {
    DrawTriangle(playerShape.v1, playerShape.v2, playerShape.v3, YELLOW);
}

//PLAYER SHAPE UPDATE
void Player::updateShape(Vector2 screenDim) {
    Vector2 center = {screenDim.x / 2, screenDim.y / 2};

    //PLAYER POSITION
    playerShape.v1 = {center.x + velocity.x, center.y + velocity.y};
    playerShape.v2 = {playerShape.v1.x - playerShape.offset, playerShape.v1.y + playerShape.offset + playerShape.height};
    playerShape.v3 = {playerShape.v1.x + playerShape.offset, playerShape.v1.y + playerShape.offset + playerShape.height};
    playerShape.center = {(playerShape.v1.x + playerShape.v2.x + playerShape.v3.x) / 3, (playerShape.v1.y + playerShape.v2.y + playerShape.v3.y) / 3};

    playerShape.v1 = rotatePoint(playerShape.v1, playerShape.center, turnAngle);
    playerShape.v2 = rotatePoint(playerShape.v2, playerShape.center, turnAngle);
    playerShape.v3 = rotatePoint(playerShape.v3, playerShape.center, turnAngle);
}

//PLAYER MOVEMENT
void Player::playerMovement() {
    Vector2 playerDirection = getDirection(turnAngle);

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        velocity.y += playerDirection.y * speed;
        velocity.x += playerDirection.x * speed;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        velocity.y -= playerDirection.y * speed;
        velocity.x -= playerDirection.x * speed;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        turnAngle -= angleSpeed;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        turnAngle += angleSpeed;
    }
}

//PLAYER HITBOX
void Player::updateHitbox() {
    float left = std::min(std::min(playerShape.v1.x, playerShape.v2.x), playerShape.v3.x);
    float right = std::max(std::max(playerShape.v1.x, playerShape.v2.x), playerShape.v3.x);

    float top = std::min(std::min(playerShape.v1.y, playerShape.v2.y), playerShape.v3.y);
    float bottom = std::max(std::max(playerShape.v1.y, playerShape.v2.y), playerShape.v3.y);

    hitbox = {left, top, right - left, bottom - top};
}

//PLAYER HITBOX DRAW
void Player::drawHitbox() {
    DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, RAYWHITE);
}