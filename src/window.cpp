#include "Window.hpp"
#include "Variables.hpp"
#include <birb2d/Entity.hpp>
#include <birb2d/Scene.hpp>
#include <birb2d/Rect.hpp>
#include <birb2d/Values.hpp>

namespace Game
{
    static int titleBarHeight = 20;

    WindowOpts::WindowOpts(std::string title, Birb::Vector2int dimensions): title(title), dimensions(dimensions){};

    Window::Window(WindowOpts *options)
    {
        this->options = options;
        this->window = Birb::Rect(0, 0, this->options->dimensions.x, this->options->dimensions.y);
        this->windowBorder = Birb::Rect(0, 0, this->options->dimensions.x, this->options->dimensions.y);
        this->scene.AddObject(&window);
        this->scene.AddObject(&windowBorder);
        this->buildTitleBar();
        this->scene.Activate();
    };

    void Window::buildTitleBar() {
        // Create titleBar Rect
        this->titleBar = Birb::Rect(0, 0, this->options->dimensions.x, titleBarHeight);
        titleBar.color = Birb::Colors::LightGray;
        this->scene.AddObject(&titleBar);
        
        // Create Entity for titleText to calculate size dynamically 
        Birb::Vector2int centerPos(0, 0);
        this->titleText = Birb::Entity("titleBarTitleText", centerPos, Birb::EntityComponent::Text(this->options->title, &DefaultFont, &Birb::Colors::Black));

        // Position title text in center of titleBar
        Birb::Vector2int textDimensions;
        Birb::utils::GetTextureDimensions(titleText.sprite, textDimensions.x, textDimensions.y);
        titleText.rect.x = (this->options->dimensions.x / 2.0) - (textDimensions.x / 2.0);
        titleText.rect.y = (titleBarHeight / 2.0) - (textDimensions.y / 2.0);

        // Set rendering priority of text to be above titleBar
        titleText.renderingPriority = 1;

        this->scene.AddObject(&titleText);
    }

    void Window::Render()
    {
        this->scene.Render();
    }
};
