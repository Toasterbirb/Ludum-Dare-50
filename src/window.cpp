#include "Window.hpp"
#include "Variables.hpp"
#include <birb2d/Entity.hpp>
#include <birb2d/Renderwindow.hpp>
#include <birb2d/Scene.hpp>
#include <birb2d/Rect.hpp>
#include <birb2d/Values.hpp>
#include <birb2d/Line.hpp>

static Window GameWindow;

namespace Game
{
	static int titleBarHeight = 20;
	static void onCloseClick(Game::Window *window)
	{
		ClickSound.play();
		//window->ClearScenes();
		window->DisableScenes();
		Variables::ramUsage -= window->windowRamUsage;
		window->windowClosed = true;
	}

	void Window::DisableScenes()
	{
		windowScene.Deactivate();
		//contentScene.Deactivate();
	}

	static void onCloseMouseDown()
	{
		ClickSound.play();
		//MouseDownSound.play();
		//window->dragOffset = gameWindow->CursorPosition() - Vector2int(window->getWindow().x, window->getWindow().y);
	}

	static void onMouseHover(Entity* closeButton, const Game::Window& window)
	{
		int sizeIncrease = 4;
		closeButton->rect.x = window.originalCloseButtonRect.x - closeButtonHoverSizeIncrease;
		closeButton->rect.y = window.originalCloseButtonRect.y - closeButtonHoverSizeIncrease;
		closeButton->rect.w = window.originalCloseButtonRect.w + closeButtonHoverSizeIncrease * 2;
		closeButton->rect.h = window.originalCloseButtonRect.h + closeButtonHoverSizeIncrease * 2;
	}

	static void onTitleDrag(Game::Window *window, Birb::Window *gameWindow)
	{
		std::cout << "On title mouse drag" << std::endl;
		Vector2int newPosition = gameWindow->CursorPosition() - window->dragOffset;
		window->getWindowScene()->SetPosition(gameWindow->CursorPosition().toFloat());
		window->getContentScene()->SetPosition(gameWindow->CursorPosition().toFloat());
	}

	WindowOpts::WindowOpts()
	{
		title = "";
	}

	WindowOpts::WindowOpts(std::string title, Birb::Rect window)
		: title(title), window(window){};

	Window::Window(WindowOpts options, Random rand)
	{
		closeButtonTexture = Birb::Resources::LoadTexture(closeButtonPath);

		windowRamUsage = rand.RandomInt(10, 250);
		Variables::ramUsage += windowRamUsage;

		windowClosed = false;

		this->options = options;
		this->window = options.window;
		window.color = Colors::LightGray;
		this->windowScene.AddObject(&window);
		this->buildTitleBar();
		this->addLighting();

		this->windowScene.Activate();

		// Put contents of contentScene below titleBar
		//
		// translate (titleBarPadding, titleBarHeight + titleBarPadding);
		// height -= titleBarHeight - (titleBarPadding * 2);
		// width -= titleBarPadding * 2;
		this->contentWindow.h = window.h - titleBarHeight - 10;
		this->contentWindow.w = window.w - 10;
		this->contentScene.AddObject(&contentWindow);
		this->contentScene.Translate({options.window.x + 5, options.window.y + titleBarHeight + 5});
		this->contentScene.Activate();
		windowScene.AddObject(&contentScene);
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

		originalCloseButtonRect = Birb::Rect(titleBar.x + (titleBar.w - 18), (titleBar.y + 3), 14, 14);
		this->closeButton = Birb::Entity("closeButton", originalCloseButtonRect, closeButtonTexture);
		std::function<void()> clickHandler = std::bind(onCloseClick, this);
		//std::function<void()> onMouseDownHandler = std::bind(onCloseMouseDown);
		//std::function<void()> dragHandler = std::bind(onTitleDrag, this, &GameWindow);
		std::function<void()> mouseHoverHandler = std::bind(onMouseHover, &closeButton, *this);
		this->closeButton.clickComponent = EntityComponent::Click();
		this->closeButton.clickComponent.onClick = clickHandler;
		this->closeButton.clickComponent.onHover = mouseHoverHandler;
		//this->closeButton.clickComponent.onDrag = dragHandler;
		//this->closeButton.clickComponent.onMouseDown = onMouseDownHandler;

		this->windowScene.AddObject(&closeButton);


		// Create Entity for titleText to calculate size dynamically
		Birb::Vector2int centerPos(0, 0);
		this->titleText = Birb::Entity("titleBarTitleText", centerPos, Birb::EntityComponent::Text(this->options.title, &DefaultFont, &Birb::Colors::White));

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
		//this->contentScene.Render();
	}

	void Window::ClearScenes()
	{
		this->windowScene.Clear();
		this->windowScene.Deactivate();
		this->contentScene.Clear();
		this->contentScene.Deactivate();
	}

	void Window::AddChildComponent(Birb::Entity entity) {
		contentEntities.push_back(entity);
		this->contentScene.AddObject(&contentEntities.back());
	}

	Vector2int Window::GetContentWindowVector() {
		return Vector2int(contentWindow.x, contentWindow.y);
	}

	Rect Window::getWindow() const
	{
		return window;
	}

	void Window::SetWindowPosition(const Vector2int& newPos)
	{
		window.x = newPos.x;
		window.y = newPos.y;
	}

	Birb::Scene* Window::getWindowScene()
	{
		return &windowScene;
	}

	Birb::Scene* Window::getContentScene()
	{
		return &contentScene;
	}
};
