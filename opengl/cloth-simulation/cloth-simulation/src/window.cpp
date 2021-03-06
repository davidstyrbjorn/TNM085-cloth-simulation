#include"../include/imgui/imgui.h"       // Det h�r m�ste vara h�gst upp annars skiter den ner sig
#include"../include/imgui/imgui_glfw.h"

#include"../include/window.h"
#include"../include/input.h"

#define GLEW_STATIC
#include<GL/glew.h>

#include<GLFW/glfw3.h>

#include<iostream>

Window::Window(int x, int y, std::string title) : windowSize(x, y), rightMouseDown(false)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		std::cout << "Something went wrong" << std::endl;
	}
	
	//Creates window
	glfwWindow = glfwCreateWindow(windowSize.x, windowSize.y, title.c_str() , NULL, NULL);
	glfwMakeContextCurrent(glfwWindow);
	
	// Initalize glew now that a opengl context is created
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to Initalize GLEW, OpenGL will not work" << std::endl;
	}

	// Set the window user pointer, mainly so the Input class can use it
	glfwSetWindowUserPointer(glfwWindow, this);

	// Input callbacks
	glfwSetKeyCallback(glfwWindow, key_callback);
	glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);
	glfwSetScrollCallback(glfwWindow, scroll_callback);
	glfwSetCharCallback(glfwWindow, character_callback);
	glfwSetWindowSizeCallback(glfwWindow, window_size_callback);

	// Initalize ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(glfwWindow, false);

	if (!glfwWindow)
	{
		std::cout << "Window failed to open" << std::endl;
	}
}

Window::~Window()
{
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();

	ImGui_ImplGlfwGL3_Shutdown();
}


void Window::Clear(glm::vec4 Color)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(Color.r, Color.g, Color.b, Color.a); // set the color

	// ImGui new frame, calls ImGui::NewFrame()
	ImGui_ImplGlfwGL3_NewFrame();
}

void Window::Display()
{
	// Make ImGui Render its data
	ImGui::Render();

	eventList.clear();
	glfwPollEvents();
	glfwSwapBuffers(glfwWindow);

}

std::vector<Event>& Window::GetPolledEvents()
{
	return eventList;
}

glm::vec2 Window::GetRelativeMousePosition()
{
	double x, y;
	glfwGetCursorPos(glfwWindow, &x, &y);
	return { x, y };
}

bool Window::IsKeyDown(int keycode)
{
	return keys[keycode];
}

bool Window::IsRightMouseDown() const
{
	return rightMouseDown;
}

bool Window::IsOpen()
{
	return !glfwWindowShouldClose(glfwWindow);
}

void Window::error_callback(int error, const char* description)
{
	std::cout << description << std::endl;
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//ImGui Callback
	ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mods);

	// Check for the viable event types we support
	if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		Event e;
		e.key = key;
		e.type = action == GLFW_PRESS ? EventType::key_down : EventType::key_released;

		// Add the event
		Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));
		temp->GetPolledEvents().push_back(e);

		// Set the keys current state in the big keys list
		temp->keys[key] = action == GLFW_PRESS ? true : false;
	}
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//ImGui Callback
	ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);

	// Check for the viable event types we support
	if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		Event e;
		e.button = button;
		e.type = action == GLFW_PRESS ? EventType::mouse_down : EventType::mouse_released;


		// Add the event
		Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));
		temp->GetPolledEvents().push_back(e);
		
		// Mouse down modify

		temp->rightMouseDown = (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT) ? true : false;
	}
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfwGL3_ScrollCallback(window, xoffset, yoffset);
}

void Window::character_callback(GLFWwindow* window, unsigned int codepoint)
{
	ImGui_ImplGlfwGL3_CharCallback(window, codepoint);
}

void Window::window_size_callback(GLFWwindow* window, int width, int height)
{
	Event e;
	e.type = EventType::window_resized;
	e.size = { width, height };

	glViewport(0, 0, width, height);

	// Add the event
	Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));
	temp->GetPolledEvents().push_back(e);
}
