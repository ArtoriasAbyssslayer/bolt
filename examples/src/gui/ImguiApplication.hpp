#pragma once

#include "SDLApplication3d.hpp"

class ImguiApplication : public SDLApplication3d {
public:
    ImguiApplication(int width, int height);
    virtual ~ImguiApplication();

    virtual void run() override;
    virtual void handleEvent(const SDL_Event&) override;
    virtual void drawImgui() {}
};
