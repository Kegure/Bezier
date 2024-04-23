//
// Created by kegure on 4/12/24.
//
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAX_POINTS 100
#define MAX_TRANS 100
#define MAX_ROTATION 100
int num_points = 0;
bool show_control_polygon = false;
float control_points[MAX_POINTS][2];
int translation[MAX_TRANS][2];
int rotation[MAX_ROTATION];
typedef struct {
    float r;
    float g;
    float b;
} Color;
Color colors[25] = {
        {1.0f, 0.0f, 0.0f},   // Red
        {1.0f, 0.647f, 0.0f}, // Orange
        {1.0f, 0.843f, 0.0f}, // Gold
        {0.941f, 0.902f, 0.549f}, // Khaki
        {0.855f, 0.647f, 0.125f}, // DarkGoldenrod
        {0.824f, 0.706f, 0.549f}, // BurlyWood
        {0.863f, 0.863f, 0.863f}, // Silver
        {0.804f, 0.522f, 0.247f}, // Sienna
        {0.545f, 0.271f, 0.075f}, // SaddleBrown
        {0.8f, 0.522f, 0.247f},   // Tan
        {0.804f, 0.522f, 0.247f}, // Peru
        {0.804f, 0.361f, 0.361f}, // IndianRed
        {1.0f, 0.412f, 0.706f},   // MediumVioletRed
        {1.0f, 0.753f, 0.796f},   // Pink
        {0.737f, 0.561f, 0.561f}, // RosyBrown
        {0.824f, 0.706f, 0.549f}, // SandyBrown
        {1.0f, 0.765f, 0.796f},   // LavenderBlush
        {1.0f, 0.894f, 0.882f},   // MistyRose
        {0.957f, 0.643f, 0.376f}, // PeachPuff
        {1.0f, 0.855f, 0.725f},    // BlanchedAlmond
        {0.937f, 0.502f, 0.502f}, // Coral
        {1.0f, 0.388f, 0.278f},   // Tomato
        {1.0f, 0.627f, 0.478f},   // Salmon
        {0.863f, 0.078f, 0.235f}, // Crimson
        {0.647f, 0.165f, 0.165f}  // Brown
};
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        show_control_polygon = !show_control_polygon; // Toggle visibility
    }
}

int loadControlPoints(const char *filename, float control_points[][2]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return -1; // Return an error code
    }

    int num_points = 0; // Counter for the number of points read
    int num_translation = 0;
    int num_rotations = 0 ;
    char line[100]; // Assuming maximum line length is 100 characters
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v') {
            float x, y;
            if (sscanf(line, "v %f %f", &x, &y) == 2) {
                if (num_points < MAX_POINTS) {
                    control_points[num_points][0] = x;
                    control_points[num_points][1] = y;
                    num_points++;
                } else {
                    printf("Max number of points reached!\n");
                    break;
                }
            } else {
                printf("Error parsing line: %s\n", line);
            }
        } else if (line[0] == 't') {
            int a, b;
            if (sscanf(line, "t %d %d", &a, &b) == 2) {
                translation[num_translation][0] = a;
                translation[num_translation][1] = b;
                num_translation++;

            } else {
                printf("Error parsing line: %s\n", line);
            }
        } else if (line[0] == 'r') {
            int c;
            if (sscanf(line, "r %d", &c) == 1) {
                rotation[num_rotations] = c;
                num_rotations++;

            } else {
                printf("Error parsing line: %s\n", line);
            }
        }
    }
    fclose(file);
    //code just for tests
    for (int i = 0; i < num_points; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%.2f ",control_points[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < num_translation; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%.2d ", translation[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < num_rotations; ++i) {
        printf("%.2d ", rotation[i]);
        printf("\n");
    }
    return num_points; // Return the number of points loaded
}



void draw_axes() {

    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glBegin(GL_LINES);
    glVertex2f(-320.0f, 0.0f);
    glVertex2f(320.0f, 0.0f);
    glEnd();


    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glBegin(GL_LINES);
    glVertex2f(0.0f, -240.0f);
    glVertex2f(0.0f, 240.0f);
    glEnd();
}


void draw_bezier_curve() {
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_LINE_STRIP);

    int num_steps = 100;

    for (int i = 0; i <= num_steps; ++i) {
        float t = static_cast<float>(i) / num_steps;

        float temp_points[MAX_POINTS][2];
        for (int j = 0; j < num_points; ++j) {
            temp_points[j][0] = control_points[j][0];
            temp_points[j][1] = control_points[j][1];
        }

        for (int k = num_points - 1; k > 0; --k) {
            for (int j = 0; j < k; ++j) {
                temp_points[j][0] = (1 - t) * temp_points[j][0] + t * temp_points[j + 1][0];
                temp_points[j][1] = (1 - t) * temp_points[j][1] + t * temp_points[j + 1][1];
            }
        }

        glVertex2f(temp_points[0][0], temp_points[0][1]);
    }

    glEnd();
}

void draw_control_points() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < num_points; ++i) {
        glVertex2f(control_points[i][0], control_points[i][1]);
    }
    glEnd();
}
void draw_control_polygon() {
    glColor3f(0.0f, 0.0f, 0.0f); // Black color

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < num_points; ++i) {
        glVertex2f(control_points[i][0], control_points[i][1]);
    }

    glEnd();
}


int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320.0, 320.0, -240.0, 240.0, -1.0, 1.0); // Adjust the projection matrix
    glMatrixMode(GL_MODELVIEW);
    num_points = loadControlPoints(argv[1], control_points);
    if (num_points == -1) {
        return 1; // Error loading control points
    }
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_axes();
        draw_bezier_curve();
        if (show_control_polygon) {
            draw_control_points();
            draw_control_polygon();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
