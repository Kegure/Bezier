//
// Created by kegure on 4/12/24.
//
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int num_points = 0;

//Variável para controlar a exibição do polígono de controle
bool show_control_polygon = false;

//pontos de controle
std::vector<std::pair<float, float>> controlPoints;

//vetor transformacoes (id, valor)
std::vector<std::pair<char, std::pair<float, float> >> transformations;

//posicao da transformacao atual
int posTransf = 0;

//vetor dos pontos atuais
std::vector<std::pair<float, float>> actualDraw;

//vetor dos pontos antes da transformacao
std::vector<std::pair<float, float>> drawBeforeTransformation;

#define TRANSLATION 't'
#define ROTATION 'r'
#define SCALING 's'
#define SHEARING 'c' //cisalhamento
#define REFLECTION 'm' //mirror

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

void applyTranslationOnDraw(){
    for (auto& point : actualDraw) {
        point.first += transformations[posTransf].second.first;
        point.second += transformations[posTransf].second.second;
    }
}

void applyRotationOnDraw(){
    float angle = transformations[posTransf].second.first * (M_PI / 180.0); // Converter graus para radianos
    for (auto& point : actualDraw) {
        float new_x = point.first * cos(angle) - point.second * sin(angle);
        float new_y = point.first * sin(angle) + point.second * cos(angle);
        point.first = new_x;
        point.second = new_y;
    }
}

void applyScalingOnDraw(){
    for (auto& point : actualDraw) {
        point.first = transformations[posTransf].second.first; // Escala em X
        point.second= transformations[posTransf].second.second; // Escala em Y
    }
}

void applyShearingOnDraw(){
    for (auto& point : actualDraw) {
        float new_x = point.first + transformations[posTransf].second.first * point.second; // Cisalhamento em X
        float new_y = point.second + transformations[posTransf].second.second * point.first; // Cisalhamento em Y
        point.first = new_x;
        point.second = new_y;
    }
}

void applyReflectionOnDraw(){
    for (auto& point : actualDraw) {
        point.first = 2 * transformations[posTransf].second.first - point.first;
        point.second = 2 * transformations[posTransf].second.second - point.second;
    }
}

void applyTransformation(){
    drawBeforeTransformation.assign(actualDraw.begin(), actualDraw.end());
    if(posTransf > transformations.size()){
        posTransf = 0;
        actualDraw.assign(controlPoints.begin(), controlPoints.end());
        return;
    }
    if(transformations[posTransf].first == TRANSLATION){
        applyTranslationOnDraw();

    }else if(transformations[posTransf].first == ROTATION){
        applyRotationOnDraw();

    }else if(transformations[posTransf].first == SCALING){
        applyScalingOnDraw();

    }else if(transformations[posTransf].first == SHEARING){
        applyShearingOnDraw();

    }else if(transformations[posTransf].first == REFLECTION){
        applyReflectionOnDraw();
    }
    posTransf++;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        show_control_polygon = !show_control_polygon; // vizualizar o poligono
    }
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){ //aplicar transformacoes
        applyTransformation();
    }
}

int loadControlPoints(const char *filename) {
    float x, y;
    int degrees;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return -1; // Return an error code
    }

    char line[100]; // Assuming maximum line length is 100 characters
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v') {
            if (sscanf(line, "v %f %f", &x, &y) == 2) {
                controlPoints.emplace_back(x, y);
                num_points++;
            } else {
                printf("Error parsing line: %s\n", line);
            }

        } else if (line[0] == 't') {
            if (sscanf(line, "t %f %f", &x, &y) == 2) {
                transformations.emplace_back(TRANSLATION, std::make_pair(x,y));
            } else {
                printf("Error parsing line: %s\n", line);
            }

        } else if (line[0] == 'r') {
            if (sscanf(line, "r %d", &degrees) == 1) {
                transformations.emplace_back(ROTATION, std::make_pair(degrees,0));
            } else {
                printf("Error parsing line: %s\n", line);
            }
        } else if (line[0] == 's') {
            if (sscanf(line, "s %f %f", &x, &y) == 2) {
                transformations.emplace_back(SCALING, std::make_pair(x,y));
            } else {
                printf("Error parsing line: %s\n", line);
            }

        } else if (line[0] == 'c') {
            if (sscanf(line, "c %f %f", &x, &y) == 2) {
                transformations.emplace_back(SHEARING, std::make_pair(x,y));
            } else {
                printf("Error parsing line: %s\n", line);
            }

        } else if (line[0] == 'm') {
            if (sscanf(line, "m %f %f", &x, &y) == 2) {
                transformations.emplace_back(REFLECTION, std::make_pair(x,y));
            } else {
                printf("Error parsing line: %s\n", line);
            }
        }
    }
    fclose(file);

    //mostrar os dados obtidos pelo arquivo de entrada no terminal

    printf("Pontos de controle:\n");
    for (const auto& coord : controlPoints) {
        printf("Ponto: (X: %.1f, Y: %.1f)\n", coord.first, coord.second);
    }

    for (const auto& transf: transformations) {
        if(transf.first == TRANSLATION){
            printf("Valores de translacao: (X: %.1f, Y: %.1f)\n", transf.second.first, transf.second.first);
        }
        else if(transf.first == ROTATION){
            printf("Valor do grau da rotacao: %.1f\n",transf.second.first);
        }
        else if(transf.first == SCALING){
            printf("Valores de mudanca de escala: (X: %.1f, Y: %.1f)\n", transf.second.first, transf.second.first);
        }
        else if(transf.first == SHEARING){
            printf("Valores de cisalhamento: (X: %.1f, Y: %.1f)\n", transf.second.first, transf.second.first);
        }
    }

    return 0;
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

int binomialCoefficient(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;

    int result = 1;
    for (int i = 1; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

void draw_bezier_curve(std::vector<std::pair<float, float>> pointsForDraw, Color curveColor) {
    glColor3f(curveColor.r, curveColor.g, curveColor.b); // Red color

    int num_steps = 100;

    for (size_t k = 0; k < num_points / 4; ++k) {
        glBegin(GL_LINE_STRIP);

        for (int i = 0; i <= num_steps; ++i) {
            float t = static_cast<float>(i) / num_steps;

            float p[2] = {0.0f, 0.0f};
            for (int j = 0; j < 4; ++j) {
                float blend_factor = binomialCoefficient(4 - 1, j) * pow(1 - t, 4 - 1 - j) * pow(t, j);
                p[0] += blend_factor * pointsForDraw[k * 4 + j].first;
                p[1] += blend_factor * pointsForDraw[k * 4 + j].second;
            }

            glVertex2f(p[0], p[1]);
        }

        glEnd();
    }
}

// Function to compute binomial coefficient (n choose k)
void draw_control_points(std::vector<std::pair<float, float>> pointsForDraw) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < num_points; ++i) {
        glVertex2f(pointsForDraw[i].first, pointsForDraw[i].second);
    }
    glEnd();
}

void draw_control_polygon(std::vector<std::pair<float, float>> pointsForDraw) {
    glColor3f(0.0f, 0.0f, 0.0f); // Black color

    // Draw lines between the control points in segments of four
    for (int i = 0; i < num_points; i += 4) {
        glBegin(GL_LINE_STRIP);
        int end = std::min(i + 4, num_points); // Ensure we don't go beyond the number of points
        for (int j = i; j < end; ++j) {
            glVertex2f(pointsForDraw[j].first, pointsForDraw[j].second);
        }
        glEnd();
    }
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

    if (loadControlPoints(argv[1]) == -1) {
        return 1; // Error loading control points
    }
    actualDraw.assign(controlPoints.begin(), controlPoints.end());
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_axes();
        if(!drawBeforeTransformation.empty()){
            draw_bezier_curve(drawBeforeTransformation, colors[10]);
        }
        draw_bezier_curve(actualDraw, colors[2]);

        if (show_control_polygon) {
            if(!drawBeforeTransformation.empty()){
                draw_control_points(drawBeforeTransformation);
                draw_control_polygon(drawBeforeTransformation);
            }
            draw_control_points(actualDraw);
            draw_control_polygon(actualDraw);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
