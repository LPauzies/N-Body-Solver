#include "graphics.hpp"

Graphics::Graphics(string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre), m_hauteurFenetre(hauteurFenetre), m_fenetre(0){}

Graphics::~Graphics(){
  glfwTerminate();
}


/*
 * Author : Antoine Bourgeois
 * Date : 13/03/2018
 * Input : None
 * Output : Initialise toute les valeurs nécessaire à la création de la fenêtre graphique
 */

bool Graphics::initFenetre(){

  //Declaration de la fonciton de callback d'erreur
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return false;
  }


  // Antialiasing
  glfwWindowHint(GLFW_SAMPLES,4);
  // OpenGL 3.1
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Feature 3.2 +
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);



  m_fenetre = glfwCreateWindow(m_largeurFenetre, m_hauteurFenetre, m_titreFenetre.c_str(), NULL, NULL);

  if (!m_fenetre) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return false;
  }

  // Création du contexte

  glfwMakeContextCurrent(m_fenetre);
  //glfwSetInputMode(m_fenetre,GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  return true;
}

/*
 * Author : Antoine Bourgeois
 * Date : 13/03/2018
 * Input : None
 * Output : Initialise toute les valeurs nécessaire à OpenGL
 */

void Graphics::initGL(){

  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();
  glEnable(GL_PROGRAM_POINT_SIZE);
  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  glPointSize(10);
}


/*
 * Author : Antoine Bourgeois
 * Date : 13/03/2018
 * Input : None
 * Output : Check s'il n'y a pas d'erreur avec les shadders et retourne les erreurs.
 */

void checkShaders(GLint compileStatus,GLuint vs){
  if(compileStatus != GL_TRUE){
      //Récupération de la taille du message
      glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &logLength);
      //Allocation de la mémoire
      logMsg = new char[logLength + 1];
      if(logMsg == NULL)
        {
          printf("Erreur d'allocation de mémoire");
          exit(-1);
        }
      //Initialisation du contenu du message
      memset(logMsg, '\0', logLength+1);
      //Récupération du message
      glGetShaderInfoLog(vs, logLength, &logLength, logMsg);
      //Log du message
      std::cout << "Erreur lors de la compilation du shader : " << std::string(logMsg);
      //Libération de la mémoire et du shader
      delete [] logMsg;
      glDeleteShader(vs);
      exit(-1);
    }
}



/*
 * Author : Antoine Bourgeois
 * Date : 13/03/2018
 * Input : None
 * Output : Met à jour l'affichage de la fenêtre actuel.
 */

void Graphics::fenetreUpDate(NBody nbody){

  mat4 projection;
  mat4 modelview;

  //projection = perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, 0.0, 100.0);

  projection = perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 100.0);
  modelview = mat4(1.0);


  int nbDeBody = nbody.getBodyVector().size();

  // Remplissage du tableau
  int incPoint = 0;
  int i = 0;
    while (i < nbDeBody) {
      points[incPoint] = nbody.getBodyVector()[i].getX();
      incPoint++;
      points[incPoint] = nbody.getBodyVector()[i].getY();
      incPoint++;
      points[incPoint] = nbody.getBodyVector()[i].getZ();
      incPoint++;
      i++;
    }

  // Initialisation du VBO et VAO

  int taillePoint = incPoint;

  cout << taillePoint;

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, taillePoint * sizeof(float), points, GL_STATIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  // Shaders

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  glGetShaderiv(vs, GL_COMPILE_STATUS, &compileStatus);

  checkShaders(compileStatus,vs);
  checkShaders(compileStatus,fs);

  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);
  glLinkProgram(shader_programme);




  while(!glfwWindowShouldClose(m_fenetre)){

    int incPoint = 0;
    int i = 0;

      while (i < nbDeBody) {
        points[incPoint] = nbody.getBodyVector()[i].getX();
        incPoint++;
        points[incPoint] = nbody.getBodyVector()[i].getY();
        incPoint++;
        points[incPoint] = nbody.getBodyVector()[i].getZ();
        incPoint++;
        i++;
      }
    //points[8] += 0.01;
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, taillePoint * sizeof(float), points, GL_STATIC_DRAW);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_programme);

    // Ré-initialisation de la matrice et placement de la caméra

    modelview = lookAt(vec3(1, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));

    // Translation

    //modelview = translate(modelview, vec3(0.001, 0.0, 0.0));

    // Rotation

    //modelview = rotate(modelview, 0.01f, vec3(0.0, 0.01, 0.0));

    // On envoie les matrices au shader

    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "modelview"), 1, GL_FALSE, value_ptr(modelview));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "projection"), 1, GL_FALSE, value_ptr(projection));

    // Dessinage et remplissage des points
    //glDrawArrays(GL_TRIANGLES, 0, nbDeBody);
    glDrawArrays(GL_POINTS, 0, nbDeBody);


    glDisableVertexAttribArray(0);
    glUseProgram(0);
    // update other events like input handling
    glfwPollEvents();
    nbody.updateNBody();

    glfwSwapBuffers(m_fenetre);

  }

}
