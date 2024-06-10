#include "bird.h"

Bird::Bird() {

    this->originalPosition = {0, 0};
    this->position = {0, 0};
    this->velocity = {0, 50};
    this->gravity = 0.5f;
    this->rotation = 0.0f;
    this->radius = 30.0f;

    this->sprite = LoadImage("assets/Sprites/bird.png");
    this->dimensions = {84, 60};
    this->pixelDistance = 54;
    this->state = 1;

}

Bird::~Bird() {

    UnloadImage(this->sprite);
    UnloadTexture(this->texture);

}

void Bird::getSprite() {

    Image tempBirdie = ImageCopy(this->sprite);

    ImageCrop(&tempBirdie, this->getSpriteDimensions());

    this->texture = LoadTextureFromImage(tempBirdie);

    UnloadImage(tempBirdie);

}

void Bird::getSprite(int screenwidth) {

    Image tempBirdie = ImageCopy(this->sprite);
    float ratio = (float)tempBirdie.height / (float)tempBirdie.width;

    ImageCrop(&tempBirdie, this->getSpriteDimensions());
    ImageResize(&tempBirdie, screenwidth / 16, ratio * screenwidth / 4);

    this->texture = LoadTextureFromImage(tempBirdie);

    UnloadImage(tempBirdie);

}