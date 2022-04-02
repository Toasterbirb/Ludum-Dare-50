#pragma once

#include <birb2d/Scene.hpp>
#include <birb2d/UI.hpp>
#include <string>

namespace Game
{
    struct WindowOpts
    {
        WindowOpts(std::string title, Birb::Vector2int dimensions);
        std::string title;
        Birb::Vector2int dimensions;
    };
    class Window
    {
    private:
        WindowOpts *options;
        Birb::Scene scene;
        Birb::Rect titleBar;
        Birb::Rect window;
        Birb::Rect windowBorder;
        Birb::Entity titleText;
        Birb::Line lightLineLeft;
        Birb::Line lightLineTop;
        Birb::Line shadowLineRight;
        Birb::Line shadowLineBottom;
        void buildTitleBar();

    public:
        Window(WindowOpts *options);
        void Render();
    };
};
