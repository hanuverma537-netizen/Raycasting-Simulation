#include<raylib.h>
#include<vector>
#include "Border.h"
#include "Wall.h"

class Arena {
    public:
        Border border;
        std::vector<Wall> walls;

        //CLASS CONSTRUCTOR
        Arena();

        Vector2 getBorderDimensions(Vector2 screenDim);
        void update(Vector2 screenDim);
        void drawBorder(Vector2 screenDim);
        void drawArena(Vector2 screenDim);
};