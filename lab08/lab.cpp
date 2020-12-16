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
#include <texture.h>
#include "FountainEmitter.h"
#include "OrbitEmitter.h"
//TODO delete the includes afterwards
#include <chrono>
using namespace std::chrono;
//

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace std;
using namespace glm;

// Function prototypes
void initialize();
void createContext();
void mainLoop();
void free();

#define W_WIDTH 1024
#define W_HEIGHT 768
#define TITLE "Lab 08"

// Global variables
GLFWwindow* window;
Camera* camera;
GLuint particleShaderProgram, normalShaderProgram;
GLuint projectionMatrixLocation, viewMatrixLocation, modelMatrixLocation, projectionAndViewMatrix;
GLuint translationMatrixLocation, rotationMatrixLocation, scaleMatrixLocation;
GLuint monkeyTexture, diffuceColorSampler, fireTexture;

glm::vec3 slider_emitter_pos(0.0f, 10.0f, 0.0f);
int particles_slider= 10000;
void pollKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

bool game_paused = false;

void renderHelpingWindow() {
    static int counter = 0;

    ImGui::Begin("Helper Window");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

    ImGui::SliderFloat("x position", &slider_emitter_pos[0], -30.0f, 30.0f);
    ImGui::SliderFloat("y position", &slider_emitter_pos[1], -30.0f, 30.0f);
    ImGui::SliderFloat("z position", &slider_emitter_pos[2], -30.0f, 30.0f);
    ImGui::SliderInt("particles", &particles_slider, 0, 20000);


    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Performance %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
 
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void createContext() {
    particleShaderProgram = loadShaders(
        "ParticleShader.vertexshader",
        "ParticleShader.fragmentshader");

    normalShaderProgram = loadShaders(
        "StandardShading.vertexshader",
        "StandardShading.fragmentshader");

    projectionAndViewMatrix = glGetUniformLocation(particleShaderProgram, "PV");

    translationMatrixLocation = glGetUniformLocation(normalShaderProgram, "T");
    rotationMatrixLocation = glGetUniformLocation(normalShaderProgram, "R");
    scaleMatrixLocation = glGetUniformLocation(normalShaderProgram, "S");

    modelMatrixLocation = glGetUniformLocation(normalShaderProgram, "M");

    viewMatrixLocation = glGetUniformLocation(normalShaderProgram, "V");
    projectionMatrixLocation = glGetUniformLocation(normalShaderProgram, "P");


    diffuceColorSampler = glGetUniformLocation(particleShaderProgram, "texture0");
    monkeyTexture = loadSOIL("suzanne_diffuse.bmp");
    fireTexture = loadSOIL("fire.png");
    glfwSetKeyCallback(window, pollKeyboard);
}

void free() {
    glDeleteProgram(particleShaderProgram);
    glfwTerminate();
}

void mainLoop() {
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    camera->position = vec3(0, 5, 30);
    auto* monkey = new Drawable("suzanne.obj");
    auto* quad = new Drawable("quad.obj");

    OrbitEmitter orb_emitter(monkey,  2000, 10.0f, 60.0f);

    OrbitEmitter orb_emitter2(monkey,  800, 20.0f, 40.0f);

    FountainEmitter f_emitter(monkey,  particles_slider);

    //FountainEmitter f_emmiter2(monkey,  5500);

    float t = glfwGetTime();
    do {
        f_emitter.changeParticleNumber(particles_slider);
        f_emitter.emitter_pos = slider_emitter_pos;

        float currentTime = glfwGetTime();
        float dt = currentTime - t;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(particleShaderProgram);

        // camera
        camera->update();
        mat4 projectionMatrix = camera->projectionMatrix;
        mat4 viewMatrix = camera->viewMatrix;

        auto PV = projectionMatrix * viewMatrix;
        glUniformMatrix4fv(projectionAndViewMatrix, 1, GL_FALSE, &PV[0][0]);


        //*/ Use particle based drawing
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, monkeyTexture);
        glUniform1i(diffuceColorSampler, 0);
        if(!game_paused) {
            f_emitter.updateParticles(currentTime, dt, camera->position);
            //orb_emitter.updateParticles(currentTime, dt);
            //orb_emitter2.updateParticles(currentTime, dt);
        }
        f_emitter.renderParticles(0);
        //orb_emitter.renderParticles(0);
        //orb_emitter2.renderParticles(0);
        //*/
        
        
        /*// Use standard drawing procedure
        glUseProgram(normalShaderProgram);
        monkey->bind();
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
        for (int i = 0; i < slider_emitter_pos; i++) {
            auto p = f_emmiter.p_attributes[i];
            //auto modelMatrix = glm::scale(mat4(1.0f), vec3(4.0f, 4.0f, 4.0f));
            auto r = glm::rotate(glm::mat4(), 1.0f, glm::vec3(0,1,0));
            auto s = glm::scale(glm::mat4(), glm::vec3(1,1,1));
            auto t = glm::translate(glm::mat4(), glm::vec3(RAND*30-60, RAND * 30 - 60, RAND * 30 - 60));
            
            glUniformMatrix4fv(translationMatrixLocation, 1, GL_FALSE, &t[0][0]);
            glUniformMatrix4fv(rotationMatrixLocation, 1, GL_FALSE, &r[0][0]);
            glUniformMatrix4fv(scaleMatrixLocation, 1, GL_FALSE, &s[0][0]);

            
            auto modelMatrix = t * r * s;
            glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
            
            monkey->draw();
        }
        //*/

        renderHelpingWindow();
        glfwPollEvents();
        glfwSwapBuffers(window);
        t = currentTime;

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
    // glEnable(GL_CULL_FACE);
    // glFrontFace(GL_CW);
    // glFrontFace(GL_CCW);

    // enable point size when drawing points
    glEnable(GL_PROGRAM_POINT_SIZE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Log
    logGLParameters();

    // Create camera
    camera = new Camera(window);

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
                                 camera->onMouseMove(xpos, ypos);
                             }
    );
}
void pollKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Task 2.1:
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        game_paused = !game_paused;
    }

    if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            camera->active = true;
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            camera->active = false;
        }

    }
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