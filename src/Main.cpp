#include <cstdlib>
#include <ctime>
#include <string>
#include "Ex08PhongDraw.h"
#include <vitasdk.h>
#include <vitaGL.h>

int main() 
{
	// Initializing graphics device
	vglInit(0x800000);
	
	// Enabling sampling for the analogs
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);

	std::srand(time(nullptr));

	Ex08PhongDraw Scene;

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	while(true) 
	{
		GLfloat currentFrame = (float)sceKernelGetProcessTimeWide() / 1000000.0f;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// TitleUpdateElapsed += DeltaTime;
		// if (TitleUpdateElapsed >= TitleUpdateMaxTime) 
		// {
		// 	int Fps = 1.f / DeltaTime;
		// 	std::string Title = std::format("OpenGL App | DeltaTime: {} - FPS: {}", DeltaTime, Fps);
		// 	Window.SetTitle(Title);
		// 	TitleUpdateElapsed -= TitleUpdateMaxTime;
		// }

		Scene.Update(deltaTime);
		
		vglSwapBuffers(GL_FALSE);
	}
	return 0;	
}