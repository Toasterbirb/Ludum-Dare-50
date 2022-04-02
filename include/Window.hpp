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
			void WireButtons(Birb::UI *interface);
			void Render();
	};
};
