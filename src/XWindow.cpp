#include "XWindow.h"
#include <stdexcept>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

XWindow::XWindow(int InWidth, int InHeight, const std::string& InTitle)
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

XWindow::~XWindow() 
{
    glfwDestroyWindow(RawWindow);
}

void XWindow::Update() 
{
    static float LastTime = glfwGetTime();
    float CurrentTime = glfwGetTime();
    DeltaTime = CurrentTime - LastTime;
    LastTime = CurrentTime;

    glfwSwapBuffers(RawWindow);
	glfwPollEvents();
}

bool XWindow::IsOpened() const 
{
    return !glfwWindowShouldClose(RawWindow);
}

void XWindow::SetTitle(const std::string& InTitle)
{
    Title = InTitle;
    glfwSetWindowTitle(RawWindow, Title.c_str());
}

float XWindow::GetDeltaTime() const
{
    return DeltaTime;
}

void XWindow::SetVSync(bool InEnabled)
{
    // Control VSync: 0 = disable, 1 = enabled (default).
    int Value = InEnabled ? 1 : 0;
    glfwSwapInterval(Value);
}

int XWindow::GetWidth() const
{
    return Width;
}

int XWindow::GetHeight() const
{
    return Height;
}
