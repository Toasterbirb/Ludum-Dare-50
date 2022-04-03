#include "Window.hpp"
#include "Variables.hpp"
#include <birb2d/Entity.hpp>
#include <birb2d/Renderwindow.hpp>
#include <birb2d/Scene.hpp>
#include <birb2d/Rect.hpp>
#include <birb2d/Values.hpp>
#include <birb2d/Line.hpp>

namespace Game
{
	static int titleBarHeight = 20;
	static void onCloseClick(Birb::Scene *scene)
	{
		ClickSound.play();
		scene->Clear();
		scene->Deactivate();
	}

	WindowOpts::WindowOpts(std::string title, Birb::Vector2int dimensions): title(title), dimensions(dimensions){};

	Window::Window(WindowOpts *options)
	{
		this->options = options;
		this->window = Birb::Rect(10, 10, this->options->dimensions.x, this->options->dimensions.y);
		this->windowBorder = Birb::Rect(window.x, window.y, this->options->dimensions.x, this->options->dimensions.y);
		windowBorder.color = Colors::LightGray;
		this->scene.AddObject(&window);
		this->scene.AddObject(&windowBorder);

		this->buildTitleBar();
		this->addLighting();

		this->scene.Activate();
	};

	void Window::addLighting() {
		/* Lighting (lines) */
		lightLineLeft = Birb::Line(Birb::Vector2f(window.x, window.y), Birb::Vector2f(window.x, window.y + window.h));
		lightLineLeft.color = Colors::White;
		lightLineLeft.renderingPriority = 2;
		lightLineLeft.thickness = 1;

		lightLineTop = Birb::Line(Birb::Vector2f(window.x, window.y), Birb::Vector2f(window.x + window.w, window.y));
		lightLineTop.color = Colors::White;
		lightLineTop.renderingPriority = 2;
		lightLineTop.thickness = 1;

		shadowLineRight = Birb::Line(Birb::Vector2f(window.x + window.w, window.y), Birb::Vector2f(window.x + window.w, window.y + window.h));
		shadowLineRight.color = Colors::Black;
		shadowLineRight.renderingPriority = 2;
		shadowLineRight.thickness = 1;

		shadowLineBottom = Birb::Line(Birb::Vector2f(window.x, window.y + window.h), Birb::Vector2f(window.x + window.w, window.y + window.h));
		shadowLineBottom.color = Colors::Black;
		shadowLineBottom.renderingPriority = 2;
		shadowLineBottom.thickness = 1;

		scene.AddObject(&lightLineLeft);
		scene.AddObject(&lightLineTop);
		scene.AddObject(&shadowLineRight);
		scene.AddObject(&shadowLineBottom);

	}

	void Window::buildTitleBar() {
		// Create titleBar Rect
		this->titleBar = Birb::Rect(window.x + 5, window.y + 5, this->options->dimensions.x - 10, titleBarHeight);
		titleBar.color = 0x010081;
		this->scene.AddObject(&titleBar);

		this->closeButton = Birb::Entity("closeButton", Birb::Rect(titleBar.x + (titleBar.w - 18), (titleBar.y + 3), 14, 14), closeButtonTexture);
		std::function<void()> clickHandler = std::bind(onCloseClick, &this->scene);
		this->closeButton.clickComponent = EntityComponent::Click(clickHandler);

		this->scene.AddObject(&closeButton);

		// Create Entity for titleText to calculate size dynamically
		Birb::Vector2int centerPos(0, 0);
		this->titleText = Birb::Entity("titleBarTitleText", centerPos, Birb::EntityComponent::Text(this->options->title, &DefaultFont, &Birb::Colors::White));

		// Position title text in center of titleBar
		Birb::Vector2int textDimensions = Birb::utils::GetTextureDimensions(titleText.sprite);
		titleText.CenterRelativeTo(titleBar);

		// Set rendering priority of text to be above titleBar
		titleText.renderingPriority = 1;

		this->scene.AddObject(&titleText);
	}

	void Window::WireButtons(Birb::UI *interface) {
		interface->AddButton(&this->closeButton);
	}

	void Window::Render()
	{
		this->scene.Render();
	}

};
