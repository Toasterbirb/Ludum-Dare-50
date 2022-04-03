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
	static void onCloseClick(Game::Window *window)
	{
		ClickSound.play();
		window->ClearScenes();
	}

	WindowOpts::WindowOpts(std::string title, Birb::Rect window)
		: title(title), window(window){};

	Window::Window(WindowOpts *options)
	{
		this->options = options;
		this->window = options->window;
		window.color = Colors::LightGray;
		this->windowScene.AddObject(&window);
		this->buildTitleBar();

		this->windowScene.Activate();

		//this->contentWindow = options->window;

		// Put contents of contentScene below titleBar
		//
		// translate (titleBarPadding, titleBarHeight + titleBarPadding);
		// height -= titleBarHeight - (titleBarPadding * 2);
		// width -= titleBarPadding * 2;
		this->contentWindow.h = window.h - titleBarHeight - 10;
		this->contentWindow.w = window.w - 10;
		this->contentScene.AddObject(&contentWindow);
		this->contentScene.Translate(Vector2f(options->window.x + 5, options->window.y + titleBarHeight + 5));
		this->contentScene.Activate();
		this->addLighting();
	};

	void Window::addLighting() {
		/* Lighting (lines) */
		lightLineLeft = Birb::Line(Birb::Vector2f(window.x, window.y), Birb::Vector2f(window.x, window.y + window.h));
		lightLineLeft.color = Colors::White;
		lightLineLeft.renderingPriority = 2;
		lightLineLeft.thickness = 2;

		lightLineTop = Birb::Line(Birb::Vector2f(window.x, window.y), Birb::Vector2f(window.x + window.w, window.y));
		lightLineTop.color = Colors::White;
		lightLineTop.renderingPriority = 2;
		lightLineTop.thickness = 2;

		shadowLineRight = Birb::Line(Birb::Vector2f(window.x + window.w, window.y), Birb::Vector2f(window.x + window.w, window.y + window.h));
		shadowLineRight.color = Colors::Black;
		shadowLineRight.renderingPriority = 2;
		shadowLineRight.thickness = 2;

		shadowLineBottom = Birb::Line(Birb::Vector2f(window.x, window.y + window.h), Birb::Vector2f(window.x + window.w, window.y + window.h));
		shadowLineBottom.color = Colors::Black;
		shadowLineBottom.renderingPriority = 2;
		shadowLineBottom.thickness = 2;

		windowScene.AddObject(&lightLineLeft);
		windowScene.AddObject(&lightLineTop);
		windowScene.AddObject(&shadowLineRight);
		windowScene.AddObject(&shadowLineBottom);

	}

	void Window::buildTitleBar() {
		// Create titleBar Rect
		this->titleBar = Birb::Rect(window.x + 5, window.y + 5, window.w - 10, titleBarHeight);
		titleBar.color = 0x010081;
		this->windowScene.AddObject(&titleBar);

		this->closeButton = Birb::Entity("closeButton", Birb::Rect(titleBar.x + (titleBar.w - 18), (titleBar.y + 3), 14, 14), closeButtonTexture);
		std::function<void()> clickHandler = std::bind(onCloseClick, this);
		this->closeButton.clickComponent = EntityComponent::Click(clickHandler);

		this->windowScene.AddObject(&closeButton);

		// Create Entity for titleText to calculate size dynamically
		Birb::Vector2int centerPos(0, 0);
		this->titleText = Birb::Entity("titleBarTitleText", centerPos, Birb::EntityComponent::Text(this->options->title, &DefaultFont, &Birb::Colors::White));

		// Position title text in center of titleBar
		Birb::Vector2int textDimensions = Birb::utils::GetTextureDimensions(titleText.sprite);
		titleText.CenterRelativeTo(titleBar);

		// Set rendering priority of text to be above titleBar
		titleText.renderingPriority = 1;

		this->windowScene.AddObject(&titleText);
	}

	void Window::WireButtons(Birb::UI *interface)
	{
		interface->AddButton(&this->closeButton);
	}

	void Window::Render()
	{
		this->windowScene.Render();
		this->contentScene.Render();
	}

	void Window::ClearScenes()
	{
		this->windowScene.Clear();
		this->windowScene.Deactivate();
		this->contentScene.Clear();
		this->contentScene.Deactivate();
	}

	void Window::AddChildComponent(Birb::Entity *entity) {
		this->contentScene.AddObject(entity);
	}

	Vector2int Window::GetContentWindowVector() {
		return Vector2int(contentWindow.x, contentWindow.y);
	}
};
