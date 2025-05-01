#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Position, position and velocity of the circle
float centerX = 0.0f;
float centerY = 0.0f;
float velocityX = 0.005f;
float velocityY = 0.005f;
float radius = 0.15f;

void drawCircle(float x, float y, float radius) {
    // Colour of circle
    glColor3f(1.0f, 0.0f, 0.0f); // R G B

    // Draw a circle using a triangle fan
    int numSegments = 100; // Number of segments to approximate the circle

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle

    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * M_PI * i / numSegments; // Current angle
        float posX = x + radius * cos(angle); // X coordinate
        float posY = y + radius * sin(angle); // Y coordinate
        glVertex2f(posX, posY);
    }
    
    glEnd();
}

// Function to render the scene and also draw objects
void render() {
    
    // Set an intitial background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Update the circle's position
    centerX += velocityX;
    centerY += velocityY;

    // Check boundary in the X direction and the Y direction
    if(centerX + radius > 1.0f || centerX - radius < -1.0f) {
        velocityX = -(velocityX);
    }

    if(centerY + radius > 1.0f || centerY - radius < -1.0f) {
        velocityY = -(velocityY);
    }

    // Draw the circle
    drawCircle(centerX, centerY, radius);
}

int main() {
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "ZMMR", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to open GLFW window" << endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        render(); // Draw the scene

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}