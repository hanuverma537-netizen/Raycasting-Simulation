#include<iostream>
#include<raylib.h>
#include<vector>
#include<cmath>

const int screenWidth = 1600;
const int screenHeight = 900;

typedef struct Border {
    int x = 40;
    int y = 40;
}Border;

typedef struct Wall{
    Rectangle rect;
    Color color;

    void draw() {
        DrawRectangleRec(rect, color);
    }

}Wall;

class Arena {
    public:
        Border border;
        std::vector<Wall> walls;
        
        Arena() {
            walls.resize(5);
        }

        Vector2 getBorderDimensions(Vector2 screenDim) {
            return {
                (float)screenDim.x - (border.x * 2), 
                (float)screenDim.y - (border.y * 2)
            };
        }
        
        void update(Vector2 screenDim) {
            Vector2 borderDim = getBorderDimensions(screenDim);
            

            Vector2 wallDimH = {(borderDim.x / 4), border.x};
            Vector2 wallDimV = {border.y, (borderDim.y / 4)};

            //BOTTOM LEFT QUADRANT HORIZONTAL
            walls[0].rect.x = (borderDim.x / 4) + border.x;
            walls[0].rect.y = border.y + borderDim.y - wallDimH.y;
            walls[0].rect.width = wallDimH.x;
            walls[0].rect.height = wallDimH.y;
            walls[0].color = RAYWHITE;
            
            //TOP LEFT QUADRANT HORIZONTAL
            walls[1].rect.x = (borderDim.x / 4) + border.x;
            walls[1].rect.y = (borderDim.y / 4) + border.y - wallDimH.y;
            walls[1].rect.width = wallDimH.x;
            walls[1].rect.height = wallDimH.y;
            walls[1].color = RAYWHITE;

            //TOP RIGHT QUADRANT HORIZONTAL
            walls[2].rect.x = (borderDim.x / 2) + border.x + (borderDim.x / 8);
            walls[2].rect.y = borderDim.y / 2;
            walls[2].rect.width = wallDimH.x;
            walls[2].rect.height = wallDimH.y;
            walls[2].color = RAYWHITE;

            //BOTTOM LEFT QUADRANT VERTICAL
            walls[3].rect.x = borderDim.x / 4;
            walls[3].rect.y = border.y + (borderDim.y / 2) + (borderDim.y / 4);
            walls[3].rect.width = wallDimV.x;
            walls[3].rect.height = wallDimV.y;
            walls[3].color = RED;

            //BOTTOM RIGHT QUADRANT VERTICAL
            walls[4].rect.x = border.x + (borderDim.x / 2) + (borderDim.x / 4) - (wallDimV.x / 2);
            walls[4].rect.y = border.y + (borderDim.y / 2);
            walls[4].rect.width = wallDimV.x;
            walls[4].rect.height = wallDimV.y;
            walls[4].color = RED;
        }

        void drawBorder(Vector2 screenDim) {
            Vector2 borderDim = getBorderDimensions(screenDim);

            //SCREEN BORDER
            DrawRectangleLines(border.x, border.y, borderDim.x, borderDim.y, RAYWHITE);
            
            //BORDER QUADRANTS
            DrawLine(border.x, screenDim.y / 2, screenDim.x - border.x, screenDim.y / 2, RAYWHITE);
            DrawLine(screenDim.x / 2, border.y, screenDim.x / 2, screenDim.y - border.y, RAYWHITE);
        }

        void draw(Vector2 screenDim) {
            drawBorder(screenDim);

            for (Wall& wall : walls) {
                wall.draw();
            }
        }
};

typedef struct Triangle {
    Vector2 v1;
    Vector2 v2;
    Vector2 v3;
    Vector2 center;
    int offset = 20;
    int height = 30;
}Triangle;


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

class Player {
    public:
        int speed = 5;
        int angleSpeed = 5;
        int turnAngle = 0;
        Vector2 velocity = {0, 0};
        Rectangle hitbox = {0, 0, 0, 0};
        Triangle playerShape;

        //PLAYER DRAW
        void draw() {
            DrawTriangle(playerShape.v1, playerShape.v2, playerShape.v3, YELLOW);
        }

        //PLAYER SHAPE UPDATE
        void updateShape(Vector2 screenDim) {
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
        void playerMovement() {
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
        void updateHitbox() {
            float left = std::min(std::min(playerShape.v1.x, playerShape.v2.x), playerShape.v3.x);
            float right = std::max(std::max(playerShape.v1.x, playerShape.v2.x), playerShape.v3.x);

            float top = std::min(std::min(playerShape.v1.y, playerShape.v2.y), playerShape.v3.y);
            float bottom = std::max(std::max(playerShape.v1.y, playerShape.v2.y), playerShape.v3.y);

            hitbox = {left, top, right - left, bottom - top};
        }

        //PLAYER HITBOX DRAW
        void drawHitbox() {
            DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, RAYWHITE);
        }
};

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Raycasting Simulation");
    SetTargetFPS(60);
    Player player;
    Arena map;

    while(!WindowShouldClose()) {
        Vector2 screenDim = {(float)GetScreenWidth(), (float)GetScreenHeight()};

        player.playerMovement();
        player.updateShape(screenDim);
        player.updateHitbox();
        
        map.update(screenDim);

        BeginDrawing();
        ClearBackground(BLACK);

        map.draw(screenDim);

        player.draw();
        player.drawHitbox();

        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}