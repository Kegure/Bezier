#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

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
Color colors[2] = {
        {0.87451f, 0.18824f, 0.47451f},//rosa
        {1.0f, 1.0f, 1.0f} // branco


};
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void applyTranslationOnDraw() {
    for (auto& point : actualDraw) {
        point.first += transformations[posTransf].second.first;
        point.second += transformations[posTransf].second.second;
    }
}

void applyRotationOnDraw() {
    float pi = static_cast<float>(M_PI);
    float angle = transformations[posTransf].second.first * (pi / 180.0); // Converter graus para radianos
    float x0, y0; //ponto a ser rotacionado em torno

    std::cout << "Digite x0: ";
    std::cin >> x0;

    std::cout << "Digite y0: ";
    std::cin >> y0;

    for (auto& point : actualDraw) {
        float new_x = (point.first - x0) * cos(angle) - (point.second - y0) * sin(angle);
        float new_y = (point.first - x0) * sin(angle) + (point.second - y0) * cos(angle);
        point.first = new_x;
        point.second = new_y;
    }
}

void applyScalingOnDraw() { //precisa modificar

    for (auto& point : actualDraw) {
        point.first *= transformations[posTransf].second.first; 
        point.second *= transformations[posTransf].second.second; 
    }
}

void applyShearingOnDraw() {//precisa modificar

    for (auto& point : actualDraw) {
        float new_x = point.first + transformations[posTransf].second.first * point.second; 
        float new_y = point.second + transformations[posTransf].second.second * point.first; 
        point.first = new_x;
        point.second = new_y;
    }
}

void applyReflectionOnDraw() {
    for (auto& point : actualDraw) {
        point.first = 2 * transformations[posTransf].second.first - point.first;
        point.second = 2 * transformations[posTransf].second.second - point.second;
    }
}

void applyTransformation() {
    drawBeforeTransformation.assign(actualDraw.begin(), actualDraw.end());
    if (posTransf >= transformations.size()) {
        posTransf = 0;
        actualDraw.assign(controlPoints.begin(), controlPoints.end());
        return;
    }
    else if (transformations[posTransf].first == TRANSLATION) {
        applyTranslationOnDraw();

    }else if (transformations[posTransf].first == ROTATION) {
        applyRotationOnDraw();

    }else if (transformations[posTransf].first == SCALING) {
        applyScalingOnDraw();

    }else if (transformations[posTransf].first == SHEARING) {
        applyShearingOnDraw();
    }else if (transformations[posTransf].first == REFLECTION) {
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
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) { //aplicar transformacoes
        applyTransformation();
    }
}

int loadControlPoints(const char* filename) {
    float x, y;
    int degrees;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return -1; 
    }

    char line[100]; 
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v') {
            if (sscanf(line, "v %f %f", &x, &y) == 2) {
                controlPoints.emplace_back(x, y);
                num_points++;
            }
            else {
                printf("Error parsing line: %s\n", line);
            }

        }
        else if (line[0] == 't') {
            if (sscanf(line, "t %f %f", &x, &y) == 2) {
                transformations.emplace_back(TRANSLATION, std::make_pair(x, y));
            }
            else {
                printf("Error parsing line: %s\n", line);
            }

        }
        else if (line[0] == 'r') {
            if (sscanf(line, "r %d", &degrees) == 1) {
                transformations.emplace_back(ROTATION, std::make_pair(degrees, 0));
            }
            else {
                printf("Error parsing line: %s\n", line);
            }
        }
        else if (line[0] == 's') {
            if (sscanf(line, "s %f %f", &x, &y) == 2) {
                transformations.emplace_back(SCALING, std::make_pair(x, y));
            }
            else {
                printf("Error parsing line: %s\n", line);
            }

        }
        else if (line[0] == 'c') {
            if (sscanf(line, "c %f %f", &x, &y) == 2) {
                transformations.emplace_back(SHEARING, std::make_pair(x, y));
            }
            else {
                printf("Error parsing line: %s\n", line);
            }

        }
        else if (line[0] == 'm') {
            if (sscanf(line, "m %f %f", &x, &y) == 2) {
                transformations.emplace_back(REFLECTION, std::make_pair(x, y));
            }
            else {
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

    for (const auto& transf : transformations) {
        if (transf.first == TRANSLATION) {
            printf("Valores de translacao: (X: %.1f, Y: %.1f)\n", transf.second.first, transf.second.second);
        }
        else if (transf.first == ROTATION) {
            printf("Valor do grau da rotacao: %.1f\n", transf.second.first);
        }
        else if (transf.first == SCALING) {
            printf("Valores de mudanca de escala: (X: %.1f, Y: %.1f)\n", transf.second.first, transf.second.second);
        }
        else if (transf.first == SHEARING) {
            printf("Valores de cisalhamento: (X: %.1f, Y: %.1f)\n", transf.second.first, transf.second.second);
        }
        else if (transf.first == REFLECTION) {
            printf("Valores de reflexao: (X: %.1f, Y: %.1f)\n", transf.second.first, transf.second.second);
        }
    }

    return 0;
}

void draw_axes() {
    glColor3f(0.21569f, 0.62745f, 0.37255f); // verde 
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(-320.0f, 0.0f);
    glVertex2f(320.0f, 0.0f);
    glVertex2f(300.0f, 20.0f);
    glVertex2f(320.0f, 0.0f);
    glVertex2f(300.0f, -20.0f);
    glVertex2f(320.0f, 0.0f);
    glEnd();


    glColor3f(0.23922f, 0.12941f, 0.76863f); // azul
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -240.0f);
    glVertex2f(0.0f, 240.0f);
    glVertex2f(-20.0f, 220.0f);
    glVertex2f(0.0f, 240.0f);
    glVertex2f(20.0f, 220.0f);
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

void draw_bezier_curve() {
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_LINE_STRIP);

    int num_steps = 100;

    for (size_t k = 0; k < num_points / 4; ++k) {
        glBegin(GL_LINE_STRIP);

        for (int i = 0; i <= num_steps; ++i) {
            float t = static_cast<float>(i) / num_steps;

        float p[2] = {0.0f, 0.0f};
        for (int j = 0; j < num_points; ++j) {
            float blend_factor = binomialCoefficient(num_points - 1, j) * pow(1 - t, num_points - 1 - j) * pow(t, j);
            p[0] += blend_factor * control_points[j][0];
            p[1] += blend_factor * control_points[j][1];
        }

            glVertex2f(p[0], p[1]);
        }

    glEnd();
}

void draw_control_points(std::vector<std::pair<float, float>> pointsForDraw) {
    glColor3f(1.0f, 0.5f, 0.8f); //rosa
    glPointSize(5.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < num_points; ++i) {
        glVertex2f(pointsForDraw[i].first, pointsForDraw[i].second);
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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //background preto
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320.0, 320.0, -240.0, 240.0, -1.0, 1.0); 
    glMatrixMode(GL_MODELVIEW);

    if (loadControlPoints(argv[1]) == -1) {
        return 1; 
    }
    actualDraw.assign(controlPoints.begin(), controlPoints.end());
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_axes();
        if (posTransf != 0) {
            draw_bezier_curve(drawBeforeTransformation, colors[1]);
        }
        draw_bezier_curve(actualDraw, colors[0]);

        if (show_control_polygon) {
            draw_control_points(actualDraw);
            draw_control_polygon(actualDraw);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}