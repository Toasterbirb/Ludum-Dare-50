#pragma once

#include <birb2d/Scene.hpp>
#include <birb2d/UI.hpp>
#include <birb2d/Random.hpp>
#include "Variables.hpp"
#include <string>

namespace Game
{
	static const std::string closeButtonPath = appInfo.ResLocation + "/sprites/x_button.png";
	static const int closeButtonHoverSizeIncrease = 2;
	static SDL_Texture *closeButtonTexture = Birb::Resources::LoadTexture(closeButtonPath);
	static Audio::SoundFile ClickSound(click_sound_path);
	struct WindowOpts
	{
		WindowOpts();
		WindowOpts(std::string title, Birb::Rect window);
		std::string title;
		Birb::Rect window;
	};
	class Window
	{
		private:
			WindowOpts options;
			Birb::Rect titleBar;
			Birb::Rect window;
			Birb::Rect contentWindow;

			/* Scenes */
			Birb::Scene windowScene;
			Birb::Scene contentScene;

			/* Entities */
			Birb::Entity titleText;
			Birb::Entity closeButton;
			std::vector<Birb::Entity> contentEntities;

			/* Lighting */
			Birb::Line lightLineLeft;
			Birb::Line lightLineTop;
			Birb::Line shadowLineRight;
			Birb::Line shadowLineBottom;


			void buildTitleBar();
			void addLighting();

		public:
			Window(WindowOpts options, Random rand);
			void ClearScenes();
			void DisableScenes();
			Vector2int GetContentWindowVector();
			void AddChildComponent(Birb::Entity entity);
			void WireButtons(Birb::UI *interface);
			void Render();
			Rect getWindow() const;
			Birb::Scene* getWindowScene();
			Birb::Scene* getContentScene();
			int windowRamUsage;
			bool windowClosed;

			Birb::Rect originalCloseButtonRect;

			/* Window dragging  */
			Birb::Vector2int dragOffset;
			void SetWindowPosition(const Vector2int& newPos);
	};
};
