#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

// Librairies

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Fichier

#include "../reader/reader.hpp"
#include "../body/Body.hpp"
#include "../nbody/NBody.hpp"
#include "../reader/reader.hpp"

// Namespace

using namespace std;
using namespace glm;

class Graphics{
  private:
    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;
    GLFWwindow* m_fenetre;
  public:
    Graphics(string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~Graphics();
    bool initFenetre();
    void initGL();
    void fenetreUpDate(NBody nbody);
};

//--------------- Variables ----------------------

GLint compileStatus = GL_TRUE;
char* logMsg = NULL;
int logLength =0;

// ----------- Shadders -------------

const char* vertex_shader =
"#version 330 core \n"
"in vec3 in_Vertex;"
"uniform mat4 projection;"
"uniform mat4 modelview;"
"void main() {"
"  gl_Position = projection * modelview * vec4(in_Vertex, 10.0);"
"}";
/*
//"in vec3 in_Vertex;"
//"in vec3 in_Color;"
"in vec3 position;"
//"uniform mat4 projection;"
//"uniform mat4 modelview;"
//"void main() {"
  // Position finale du vertex en 3D
  "gl Position = position;"
//"  gl_Position = projection * modelview * vec4(in_Vertex, 1.0);"
  // Envoie de la couleur au fragment Shaders
//  "color = in_Color;"
"}"; */



const char* fragment_shader =
"#version 330 core \n"
"out vec4 frag_colour;"
"void main() {"
"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
"}";

// ------------ Initialisation des points ------------

float points[] = {

};

//  ------------  Fonctions ---------------------


/*
 * Author : Antoine Bourgeois
 * Date : 13/03/2018
 * Input : None
 * Output : Effectue une action en fonction de la touche enfoncer sur le clavier.
 */

void keyboard(int key, int action) {
	if(key == 'Q' && action == GLFW_PRESS) {
		glfwTerminate();
		exit(0);
	}
}


#endif
