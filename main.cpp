#include<iostream>
#include<raylib.h>
#include<vector>
#include<cmath>
#include "Player/Player.h"

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
            

            Vector2 wallDimH = {(borderDim.x / 4), (float)border.x};
            Vector2 wallDimV = {(float)border.y, (borderDim.y / 4)};

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