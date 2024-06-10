#pragma once

#include <string>
#include <cstring>
#include <iostream>

#include "bird.h"

class GameWindow {

    private:
        int width;
        int height;
        const char* title;

        std::string spritesPath = "assets/Sprites/";

        Texture2D backgroundImage;
        Texture2D titleImage;
        Texture2D playBtnImage;
        Texture2D leaderboardBtnImage;

        Bird *flappy;
        int platformHeight;
        float time;

        bool onTitleScreen = true;

    public:
        GameWindow(const char* title, int width = 800, int height = 640);
        ~GameWindow();

        void Update();

        bool IsOpen() const;

        void SetTitleIcon();
        void SetSize(int width, int height);

        void SetBackgroundImage(const char* imgName);
        void SetTitleScreen();
        void TitleScreen();

        void SetVSync(bool enabled);
        bool IsVSync() const;

        void* GetNativeWindow() const;

};