#include<raylib.h>
#include "Triangle.h"

class Player {
    public: 
        int speed = 5;
        int angleSpeed = 5;
        int turnAngle = 0;
        Vector2 velocity = {0, 0};
        Rectangle hitbox = {0, 0, 0, 0};
        Triangle playerShape;

        void draw();
        void updateShape(Vector2 screenDim);
        void playerMovement();
        void updateHitbox();
        void drawHitbox();
};