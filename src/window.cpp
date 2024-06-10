#include "window.h"

GameWindow::GameWindow(const char* title, int width, int height) {

    // Declaration
    //--------------------------------------------------------------------------------------

    this->width = width;
    this->height = height;
    this->title = title;
    
    this->flappy = new Bird;
    this->time = 0.0f;

    //--------------------------------------------------------------------------------------
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(this->width, this->height, this->title);
    GameWindow::SetTitleIcon();
    GameWindow::SetBackgroundImage("background.png");
    GameWindow::SetTitleScreen();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose())    // Detect window close button or ESC key
        GameWindow::Update();

    //--------------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}

GameWindow::~GameWindow() {

    delete this->title;
    delete this->flappy;

    UnloadTexture(this->backgroundImage);
    UnloadTexture(this->titleImage);
    UnloadTexture(this->playBtnImage);
    UnloadTexture(this->leaderboardBtnImage);

}

void GameWindow::SetTitleIcon() {

    Image icon = ImageCopy(this->flappy->sprite);

    ImageCrop(&icon, this->flappy->getSpriteDimensions());
    SetWindowIcon(icon);
    UnloadImage(icon);

}

void GameWindow::SetBackgroundImage(const char* imgName) {

    std::string imgPath = this->spritesPath + imgName;

    Image bgImage = LoadImage(imgPath.c_str());
    Image platform = LoadImage("assets/Sprites/platform.png");
    Image background = GenImageColor((this->width / (int)bgImage.width + 1) * bgImage.width, this->height, WHITE);

    this->platformHeight = bgImage.width / 3;
    float ratio = (float)bgImage.width / (float)bgImage.height;

    ImageResize(&bgImage, ratio * this->height, this->height);
    ImageResize(&platform, bgImage.width, bgImage.width / 3);

    for (float i = 0; i < this->width; i += bgImage.width) {
        ImageDraw(&background, bgImage, {0, 0, (float)bgImage.width, (float)bgImage.height}, {i, 0, (float)bgImage.width, (float)bgImage.height}, WHITE);
        ImageDraw(&background, platform, {0, 0, (float)platform.width, (float)platform.height}, {i, (float)this->height - (float)platform.height, (float)platform.width, (float)platform.height}, WHITE);
    }

    this->backgroundImage = LoadTextureFromImage(background);

    UnloadImage(bgImage);
    UnloadImage(platform);
    UnloadImage(background);

}

void GameWindow::SetTitleScreen() {

    Image title = LoadImage("assets/Sprites/title.png");
    Image playBtn = LoadImage("assets/Sprites/play_btn.png");
    Image leaderboardBtn = LoadImage("assets/Sprites/leaderboard_btn.png");

    float ratio = (float)title.height / (float)title.width;
    float ratio1 = (float)playBtn.height / (float)playBtn.width;
    float ratio2 = (float)leaderboardBtn.height / (float)leaderboardBtn.width;

    ImageResize(&title, this->width / 2, ratio * this->width / 2);
    ImageResize(&playBtn, this->width / 8, ratio1 * this->width / 8);
    ImageResize(&leaderboardBtn, this->width / 8, ratio2 * this->width / 8);

    this->titleImage = LoadTextureFromImage(title);
    this->playBtnImage = LoadTextureFromImage(playBtn);
    this->leaderboardBtnImage = LoadTextureFromImage(leaderboardBtn);

    this->flappy->getSprite(this->width);
    this->flappy->position = {(this->flappy->dimensions.x / 2), (float)(this->height / 3) + (this->titleImage.height)};
    this->flappy->originalPosition = this->flappy->position;

    UnloadImage(title);
    UnloadImage(playBtn);
    UnloadImage(leaderboardBtn);

}

void GameWindow::TitleScreen() {

    DrawTexture(this->titleImage, (this->width / 2) - (this->titleImage.width / 2), (this->height / 3) - (this->titleImage.height / 2 + this->platformHeight / 2), WHITE);
    DrawTexture(this->flappy->texture, (this->flappy->dimensions.x / 2), (this->height / 3) + (this->titleImage.height), WHITE);
    DrawTexture(this->playBtnImage, (this->width / 2) - (3 * this->playBtnImage.width / 2), (2 * this->height / 3) - (this->playBtnImage.height / 2), WHITE);
    DrawTexture(this->leaderboardBtnImage, (this->width / 2) + (this->leaderboardBtnImage.width / 2), (2 * this->height / 3) - (this->leaderboardBtnImage.height / 2), WHITE);

}

void GameWindow::Update() {

    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    if (this->onTitleScreen) {
        std::cout << (this->flappy->velocity.y * GetTime()) - (0.5f * this->flappy->gravity * GetTime() * GetTime()) << " " << this->flappy->position.y;

        this->flappy->position.y = this->flappy->originalPosition.y + (this->flappy->velocity.y * GetTime()) - (0.5f * this->flappy->gravity * GetTime() * GetTime());

    }

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(WHITE);
        DrawTexture(this->backgroundImage, 0, 0, WHITE);

        if (this->onTitleScreen) {

            DrawTexture(this->titleImage, (this->width / 2) - (this->titleImage.width / 2), (this->height / 3) - (this->titleImage.height / 2 + this->platformHeight / 2), WHITE);
            DrawTexture(this->flappy->texture, this->flappy->position.x, this->flappy->position.y, WHITE);
            DrawTexture(this->playBtnImage, (this->width / 2) - (3 * this->playBtnImage.width / 2), (2 * this->height / 3) - (this->playBtnImage.height / 2), WHITE);
            DrawTexture(this->leaderboardBtnImage, (this->width / 2) + (this->leaderboardBtnImage.width / 2), (2 * this->height / 3) - (this->leaderboardBtnImage.height / 2), WHITE);

        }

    EndDrawing();
    //----------------------------------------------------------------------------------

}