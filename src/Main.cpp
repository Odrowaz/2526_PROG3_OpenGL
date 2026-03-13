#include <string>
#include <format>
#include "XWindow.h"

int main() 
{
	XWindow Window{800, 600, "Hello OpenGL"};

	while(Window.IsOpened()) 
	{
		static float TitleUpdateMaxTime = 1.f;
		static float TitleUpdateElapsed = 0.f;

		float DeltaTime = Window.GetDeltaTime();
		TitleUpdateElapsed += DeltaTime;
		if (TitleUpdateElapsed >= TitleUpdateMaxTime) 
		{
			int Fps = 1.f / DeltaTime;
			std::string Title = std::format("OpenGL App | DeltaTime: {} - FPS: {}", DeltaTime, Fps);
			Window.SetTitle(Title);
			TitleUpdateElapsed -= TitleUpdateMaxTime;
		}
		
		Window.Update();
	}
	return 0;	
}