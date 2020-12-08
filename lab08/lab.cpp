// Include C++ headers
#include <iostream>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Shader loading utilities and other
#include <common/shader.h>
#include <common/util.h>
#include <common/camera.h>
#include <model.h>
#include "ParticleEmitter.h"
using namespace std;
using namespace glm;

// Function prototypes
void initialize();
void createContext();
void mainLoop();
void free();

#define W_WIDTH 1024
#define W_HEIGHT 768
#define TITLE "Lab 07"

// Global variables
GLFWwindow* window;
Camera* camera;
GLuint shaderProgram;
GLuint projectionMatrixLocation, viewMatrixLocation, modelMatrixLocation;

// Standard acceleration due to gravity
#define g 9.80665f

void createContext() {
    shaderProgram = loadShaders(
        "StandardShading.vertexshader",
        "StandardShading.fragmentshader");

    projectionMatrixLocation = glGetUniformLocation(shaderProgram, "P");
    viewMatrixLocation = glGetUniformLocation(shaderProgram, "V");
    modelMatrixLocation = glGetUniformLocation(shaderProgram, "M");

}

void free() {
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

void mainLoop() {
    Drawable* monkey = new Drawable("suzanne.obj");
    ParticleEmitter emitter(monkey, 100);
    float t = glfwGetTime();
    vec3 lightPos = vec3(10, 10, 10);
    GLuint particles_position_buffer;
    glGenBuffers(1, &particles_position_buffer);
   
    do {
        float currentTime = 5 + glfwGetTime();
        std::vector<glm::vec4> particle_pos = std::vector<glm::vec4>(int(currentTime), glm::vec4());
        std::cout << particle_pos.size() << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
        glInvalidateBufferData(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, int(currentTime) * 4 * sizeof(GLfloat), &particle_pos[0], GL_STREAM_DRAW);


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // camera
        camera->update();
        mat4 projectionMatrix = camera->projectionMatrix;
        mat4 viewMatrix = camera->viewMatrix;
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

        auto model = mat4(1.0f);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &model[0][0]);

        monkey->draw();
        //emitter.renderParticles();

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);
}

void initialize() {
    // Initialize GLFW
    if (!glfwInit()) {
        throw runtime_error("Failed to initialize GLFW\n");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(W_WIDTH, W_HEIGHT, TITLE, NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw runtime_error(string(string("Failed to open GLFW window.") +
                            " If you have an Intel GPU, they are not 3.3 compatible." +
                            "Try the 2.1 version.\n"));
    }
    glfwMakeContextCurrent(window);

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw runtime_error("Failed to initialize GLEW\n");
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Hide the mouse and enable unlimited movement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, W_WIDTH / 2, W_HEIGHT / 2);

    // Gray background color
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
    // glFrontFace(GL_CW);
    // glFrontFace(GL_CCW);

    // enable point size when drawing points
    glEnable(GL_PROGRAM_POINT_SIZE);

    // Log
    logGLParameters();

    // Create camera
    camera = new Camera(window);

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
                                 camera->onMouseMove(xpos, ypos);
                             }
    );
}

int main(void) {
    try {
        initialize();
        createContext();
        mainLoop();
        free();
    } catch (exception& ex) {
        cout << ex.what() << endl;
        getchar();
        free();
        return -1;
    }

    return 0;
}