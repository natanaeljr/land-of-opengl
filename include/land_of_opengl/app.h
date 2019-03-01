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
    App();

    /**
     * \brief Default destructor.
     */
    ~App() = default;

    /**
     * \brief Launch the application.
     * \return 0 on sucess, other on error.
     */
    int Run();

   private:
    /**
     * Create OpenGL context window.
     * \return  0 on sucess, other if failure.
     */
    int InitContext();

    /**
     * Destroy OpenGL context window.
     * \return  0 on sucess, other if failure.
     */
    void FinishContext();

    /**
     * \brief Rendering loop.
     * \return  0 on sucess, other if failure.
     */
    int RenderLoop();

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

   private:
    //! GLFW window handle
    GLFWwindow* window;
};

} /* namespace landofopengl */
