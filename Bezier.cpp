//
// Created by kegure on 4/12/24.
//
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Control points of the Bezier curve
float control_points[][2] = {
        {-0.8f, -0.5f},
        {-0.4f, 0.6f},
        {0.4f, -0.3f},
        {0.8f, 0.7f}
};

// Index of the currently selected control point (-1 if none)
int selected_point = -1;

// Mouse callback function for handling mouse clicks
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            float x = (float)(2 * xpos / SCREEN_WIDTH - 1);
            float y = (float)(-2 * ypos / SCREEN_HEIGHT + 1);

            // Check if mouse click is within a certain distance of a control point
            for (int i = 0; i < 4; i++) {
                float dx = x - control_points[i][0];
                float dy = y - control_points[i][1];
                if (dx * dx + dy * dy < 0.02) {
                    selected_point = i; // Set the selected point index
                    break;
                }
            }
        } else if (action == GLFW_RELEASE) {
            selected_point = -1; // Reset selected point index when mouse button is released
        }
    }
}

// Mouse callback function for handling mouse movement
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (selected_point != -1) {
        float x = (float)(2 * xpos / SCREEN_WIDTH - 1);
        float y = (float)(-2 * ypos / SCREEN_HEIGHT + 1);
        control_points[selected_point][0] = x;
        control_points[selected_point][1] = y;
    }
}

// Draw X and Y axes
void draw_axes() {
    // Draw X axis
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glEnd();

    // Draw Y axis
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glBegin(GL_LINES);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();
}

// Draw Bezier curve
void draw_bezier_curve() {
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1; t += 0.01) {
        float x = 0, y = 0;
        for (int i = 0; i < 4; i++) {
            float basis = 1;
            for (int j = 0; j < 4; j++) {
                if (i != j) {
                    basis *= (t - j) / (i - j);
                }
            }
            x += basis * control_points[i][0];
            y += basis * control_points[i][1];
        }
        glVertex2f(x, y);
    }
    glEnd();
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bezier Curve", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_axes();
        draw_bezier_curve();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
