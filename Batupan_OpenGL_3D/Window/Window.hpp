#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window
{
public:
	// Constructor and destructor
	Window(const int& width, const int& height, const std::string& title);
	~Window();
	// Functions
	void Close();
	void Update();
	void ShowFps();
	void ShowFps(const bool& windowTitle);
	// Getters
	const bool& IsOpen();
	float& GetAspectRatio();
	// Setters
	void SetMsTitle(const std::string& msTitle);
private:
	// Variables
	GLFWwindow* m_window;
	std::string m_title;
	std::string m_msTitle;
	float		m_aspectRatio;
	int			m_screenWidth;
	int			m_screenHeight;

};

#endif // !WINDOW_HPP