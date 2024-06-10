#pragma once

#include "raylib.h"

class Bird {

    public:
        Vector2 originalPosition;
        Vector2 position;
        Vector2 velocity;
        float gravity;
        float rotation;
        float radius;
        
        Image sprite;
        Texture2D texture;
        Vector2 dimensions;
        int pixelDistance;
        int state;

        Bird();
        ~Bird();

        void getSprite();
        void getSprite(int screenWidth);

        void setPosition(Vector2 position) {
            this->position = position;
        }

        Rectangle getSpriteDimensions() const {
            return {(float)this->state * (this->dimensions.x + this->pixelDistance), 0, this->dimensions.x, this->dimensions.y};
        }

};