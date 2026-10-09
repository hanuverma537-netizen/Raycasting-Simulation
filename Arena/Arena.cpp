#include "Arena.h"

//ARENA CLASS FUNCTIONS

Arena::Arena() {
    walls.resize(5);
}

//BORDER DIMENSIONS
Vector2 Arena::getBorderDimensions(Vector2 screenDim) {
    return {
        (float)screenDim.x - (border.x * 2), 
        (float)screenDim.y - (border.y * 2)
    };
}

//WALL UPDATE
void Arena::update(Vector2 screenDim) {
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

//BORDER DRAW
void Arena::drawBorder(Vector2 screenDim) {
    Vector2 borderDim = getBorderDimensions(screenDim);

    //SCREEN BORDER
    DrawRectangleLines(border.x, border.y, borderDim.x, borderDim.y, RAYWHITE);
    
    //BORDER QUADRANTS
    DrawLine(border.x, screenDim.y / 2, screenDim.x - border.x, screenDim.y / 2, RAYWHITE);
    DrawLine(screenDim.x / 2, border.y, screenDim.x / 2, screenDim.y - border.y, RAYWHITE);
}

//DRAW ARENA
void Arena::drawArena(Vector2 screenDim) {
    drawBorder(screenDim);

    for (Wall& wall : walls) {
        wall.drawWall();
    }
}