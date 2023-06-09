#include "../include/window.hpp"
#include "../include/mobjet.hpp"
#include "../include/camera.hpp"

#include "../include/shape/map.hpp"

#include <soil2/SOIL2.h>
#include <random>

std::vector<std::string> mfileLoader(char *name);

int main(void)
{
    Window* window = new Window(hauteurJeu, largeurJeu);
    shader* shaderProgram = new shader(1);
    camera* mcamera = new camera(shaderProgram);

    std::vector<map> maps;
    maps.push_back(map(mfileLoader("map"), shaderProgram, GL_STATIC_DRAW, glm::vec3(0.0f, 0.0f, 0.0f)));

    maps[0].setPosition(0, 0.f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window->window)) {
        if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window->window, true);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mcamera->control(window);

        maps[0].drawmap();

        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }
    delete (mcamera);
    delete (shaderProgram);
    delete (window);
    return (0);
}