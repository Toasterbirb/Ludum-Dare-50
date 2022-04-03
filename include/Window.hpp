#pragma once

#include <birb2d/Scene.hpp>
#include <birb2d/UI.hpp>
#include "Variables.hpp"
#include <string>

namespace Game
{
	static std::string closeButtonPath = appInfo.ResLocation + "/sprites/x_button.png";
	static SDL_Texture *closeButtonTexture = Birb::Resources::LoadTexture(closeButtonPath);
	static Audio::SoundFile ClickSound(click_sound_path);
	struct WindowOpts
	{
		WindowOpts(std::string title, Birb::Rect window);
		std::string title;
		Birb::Rect window;
	};
	class Window
	{
		private:
			WindowOpts *options;
			Birb::Rect titleBar;
			Birb::Rect window;
			Birb::Rect contentWindow;
			Birb::Entity pogText;
			Birb::Scene windowScene;
			Birb::Scene contentScene;
			Birb::Entity closeButton;
			Birb::Entity titleText;
			Birb::Line lightLineLeft;
			Birb::Line lightLineTop;
			Birb::Line shadowLineRight;
			Birb::Line shadowLineBottom;
			void buildTitleBar();
			void addLighting();

		public:
			Window(WindowOpts *options);
			void ClearScenes();
			Vector2int GetContentWindowVector();
			void AddChildComponent(Birb::Entity *entity);
			void WireButtons(Birb::UI *interface);
			void Render();
	};
};
