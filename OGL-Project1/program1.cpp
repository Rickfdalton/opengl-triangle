#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


int main()
{
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 400, "Hello Window", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize glad" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    //test
    int nr_attrib;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&nr_attrib);
    cout << "max vertex" << nr_attrib << endl;


    //rendering pipeline
    float vertices[] = {
     0.0f,0.5f,0.0f, 1.0f, 0.0f, 0.0f,
     0.0f,0.0f,0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,0.0f,0.0f, 0.0f, 0.0f, 1.0f, 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0,1,2,   // first triangle
    };


    Shader ourShader("C:/Users/Pc/source/repos/OGL-Project1/OGL-Project1/shader.vs", "C:/Users/Pc/source/repos/OGL-Project1/OGL-Project1/shader.fs");


    unsigned int VBO; // vertex buffer object to store vertices in gpu memory
    glGenBuffers(1, &VBO);


    unsigned int EBO;
    glGenBuffers(1, &EBO);


    //bind VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //configure VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //set color attribute pointers 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);



    //render loop
    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

        ourShader.use();
        ourShader.setFloat("offset", 0.5f);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


       
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;

}