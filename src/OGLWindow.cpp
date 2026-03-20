#include "OGLWindow.h"
#include <stdexcept>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

OGLWindow::OGLWindow(int InWidth, int InHeight, const std::string& InTitle)
    : Width(InWidth), Height(InHeight), Title(InTitle), DeltaTime(0.f)
{
    if (glfwInit() == GLFW_FALSE) 
	{
		throw std::runtime_error("error on glfw initialization!");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	GLFWmonitor* Monitor = NULL; //windowed mode
	RawWindow = glfwCreateWindow(Width, Height, Title.c_str(), Monitor, NULL);
	if (RawWindow == NULL) 
	{
		throw std::runtime_error("error on creating the window!");
	}

	glfwMakeContextCurrent(RawWindow);

	if (gladLoadGL(glfwGetProcAddress) == 0) 
	{
		throw std::runtime_error("error on loading GL functions!");
	}
}

OGLWindow::~OGLWindow() 
{
    glfwDestroyWindow(RawWindow);
}

void OGLWindow::Update() 
{
    static float LastTime = glfwGetTime();
    float CurrentTime = glfwGetTime();
    DeltaTime = CurrentTime - LastTime;
    LastTime = CurrentTime;

    glfwSwapBuffers(RawWindow);
	glfwPollEvents();
}

bool OGLWindow::IsOpened() const 
{
    return !glfwWindowShouldClose(RawWindow);
}

void OGLWindow::SetTitle(const std::string& InTitle)
{
    Title = InTitle;
    glfwSetWindowTitle(RawWindow, Title.c_str());
}

float OGLWindow::GetDeltaTime() const
{
    return DeltaTime;
}

void OGLWindow::SetVSync(bool InEnabled)
{
    // Control VSync: 0 = disable, 1 = enabled (default).
    int Value = InEnabled ? 1 : 0;
    glfwSwapInterval(Value);
}

int OGLWindow::GetWidth() const
{
    return Width;
}

int OGLWindow::GetHeight() const
{
    return Height;
}
