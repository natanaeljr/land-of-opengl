/************************************************************************************************/
/**
 * \file main.cc
 * \brief  Main file.
 * \author Natanael Josue Rabello
 * \copyright Copyright (c) 2019
 * \date 2019-02-23
 */
/************************************************************************************************/

#include "iostream"

#include "land_of_opengl/app.h"

/************************************************************************************************/

int main()
{
    std::cout << "App main." << std::endl;

    landofopengl::App app;
    int ret = app.Launch();

    return ret;
}
