/**
 * \file app.h
 * \brief Land-of-OpenGL main header.
 * \date 2019-02-23
 * \author Natanael Josue Rabello
 * \copyright Copyright (c) 2019
 */

#ifndef LAND_OF_OPENGL_APP_H_
#define LAND_OF_OPENGL_APP_H_

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

   protected:
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
    static void FramebufferSizeCb(GLFWwindow* window, int width, int height);
};

} /* namespace landofopengl */

#endif /* LAND_OF_OPENGL_APP_H_ */
