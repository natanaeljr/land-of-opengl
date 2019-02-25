/************************************************************************************************/
/**
 * \file app.h
 * \brief Land-of-OpenGL main header.
 * \date 2019-02-23
 * \author Natanael Josue Rabello
 * \copyright Copyright (c) 2019
 */
/************************************************************************************************/

/** Forward-declaration */
typedef struct GLFWwindow GLFWwindow;

/**
 * Land-of-OpenGL namespace.
 */
namespace landofopengl {

/**
 * Land-of-OpenGL Application.
 */
class App {
   public:
    /**
     * \brief Default constructor.
     */
    App() {}

    /**
     * \brief Default destructor.
     */
    ~App() {}

    /**
     * \brief Launch the application.
     * \return 0 on sucess, other on error.
     */
    int Launch();

   private:
    /**
     * \brief Process user input.
     * \param window  GLFW window handle
     */
    void ProcessInput(GLFWwindow* window);

    /**
     * \brief  Callback for handling window resizing.
     * \param window  GLFW window handle
     * \param width   Window width
     * \param height  Window height
     */
    static void FrameBufferSizeCb(GLFWwindow* window, int width, int height);
};

} /* namespace landofopengl */
