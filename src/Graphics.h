#pragma once
#include "SDL.h"
#include "drawable.h"

class Graphics {
    public:
        void SetWindowSize(int width, int height);
        void SetDrawables(const std::vector< Drawable > drawables );
        bool Render();


    private:



};
