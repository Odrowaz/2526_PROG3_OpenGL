#include "Ex08PhongDraw.h"
#include "OGLMesh.h"
#include "OGLProgram.h"
#include "OGLTexture.h"

Ex08PhongDraw::Ex08PhongDraw() {
  glClearColor(0.5f, 0.5f, 0.5f, 1.f);

  CubeProgram = new OGLProgram("app0:resources/shaders/light.vert",
                               "app0:resources/shaders/light.frag");
  TrupProgram = new OGLProgram("app0:resources/shaders/phong.vert",
                           "app0:resources/shaders/phong.frag");

  TrupMesh = new OGLMesh("app0:resources/models/stormtrooper.obj");
  CubeMesh = new OGLMesh(
 std::vector<float> {
        //Position     //Uvs
        //FRONT FACE
        -1, -1,  1,     0, 0,  // bottom-left
         1, -1,  1,     1, 0,  // bottom-right
         1,  1,  1,     1, 1,  // top-right  
        -1,  1,  1,     0, 1,  // top-left
        -1, -1,  1,     0, 0,  // bottom-left
         1,  1,  1,     1, 1,  // top-right  
        
        // BACK FACE
         1, -1, -1,     0, 0,  // bottom-left
        -1, -1, -1,     1, 0,  // bottom-right
        -1,  1, -1,     1, 1,  // top-right  
         1,  1, -1,     0, 1,  // top-left
         1, -1, -1,     0, 0,  // bottom-left
        -1,  1, -1,     1, 1,  // top-right  
 
        //LEFT FACE
        -1, -1, -1,     0, 0,    //bottom-left
        -1, -1,  1,     1, 0,    //bottom-right
        -1,  1,  1,     1, 1,    //top-right
        -1,  1, -1,     0, 1,    //top-left 
        -1, -1, -1,     0, 0,    //bottom-left
        -1,  1,  1,     1, 1,    //top-right

        //RIGHT FACE      
         1, -1,  1,     0, 0,    //bottom-left
         1, -1, -1,     1, 0,    //bottom-right
         1,  1, -1,     1, 1,    //top-right
         1,  1,  1,     0, 1,    //top-left 
         1, -1,  1,     0, 0,    //bottom-left
         1,  1, -1,     1, 1,    //top-right

        //TOP FACE      
        -1,  1,  1,     0, 0,    //bottom-left
         1,  1,  1,     1, 0,    //bottom-right
         1,  1, -1,     1, 1,    //top-right
        -1,  1, -1,     0, 1,    //top-left 
        -1,  1,  1,     0, 0,    //bottom-left
         1,  1, -1,     1, 1,    //top-right
         
        //BOTTOM FACE
        -1, -1, -1,     0, 0,    //bottom-left
         1, -1, -1,     1, 0,    //bottom-right
         1, -1,  1,     1, 1,    //top-right
        -1, -1,  1,     0, 1,    //top-left 
        -1, -1, -1,     0, 0,    //bottom-left
         1, -1,  1,     1, 1,    //top-right
      },
      36, {{0, 3, 5, 0}, {1, 2, 5, 3}}
  );

  TrupTexture =
      new OGLTexture("app0:resources/models/stormtrooper.png", GL_TEXTURE0);
  CubeTexture =
      new OGLTexture("app0:resources/textures/wood-box.jpg", GL_TEXTURE1);


  TrupProgram->Bind();
  TrupProgram->SetUniform("trup_tex", 0);

  CubeProgram->Bind();
  CubeProgram->SetUniform("box_tex", 1);

  // 7. Enable Depth Testing
  glEnable(GL_DEPTH_TEST);
  // 8. Enable Cull Face
  glEnable(GL_CULL_FACE);

  // Camera
  Cam = {.Position = glm::vec3(0, 0, 8),
         .Direction = glm::vec3(0, 0, -1),
         .Up = glm::vec3(0, 1, 0),
         .FovY = 60.f,
         .AspectRatio = 960.f / 544.f,
         .ZNear = 0.01f,
         .ZFar = 100.f};

  View = glm::lookAt(Cam.Position, Cam.Position + Cam.Direction, Cam.Up);
  Projection = glm::perspective(glm::radians(Cam.FovY), Cam.AspectRatio,
                                Cam.ZNear, Cam.ZFar);

  TrupProgram->Bind();
  TrupProgram->SetUniform("camera_pos", Cam.Position);
}

Ex08PhongDraw::~Ex08PhongDraw() {
  delete TrupProgram;
  delete CubeProgram;

  delete TrupTexture;
  delete CubeTexture;

  delete TrupMesh;
  delete CubeMesh;
}

void Ex08PhongDraw::Update(float InDeltaTime) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  static float ElapsedTime = 0.f;
  ElapsedTime += InDeltaTime;

  float Angle = 20.f * ElapsedTime;

  glm::mat4 Trooper = glm::mat4(1.f);
  Trooper = glm::translate(Trooper, glm::vec3(2, -3, 0));
  Trooper = glm::rotate(Trooper, glm::radians(-Angle), glm::vec3(0, 1, 0));
  Trooper = glm::scale(Trooper, glm::vec3(1.f));
  glm::mat4 TrooperMvp = Projection * View * Trooper;

  glm::mat4 Trooper2 = glm::mat4(1.f);
  Trooper2 = glm::translate(Trooper2, glm::vec3(-2, -3, 0));
  Trooper2 = glm::rotate(Trooper2, glm::radians(Angle), glm::vec3(0, 1, 0));
  Trooper2 = glm::scale(Trooper2, glm::vec3(1.f));
  glm::mat4 Trooper2Mvp = Projection * View * Trooper2;

  glm::mat4 Cube = glm::mat4(1.f);
  Cube = glm::rotate(Cube, glm::radians(Angle), glm::vec3(0, 1, 0));
  Cube = glm::translate(Cube, glm::vec3(4, 0, 0));
  glm::vec3 LightPos = Cube * glm::vec4(0, 0, 0, 1);
  Cube = glm::scale(Cube, glm::vec3(0.5f));

  glm::mat4 CubeMvp = Projection * View * Cube;

  TrupProgram->Bind();
  TrupProgram->SetUniform("light_pos", LightPos);
  
  TrupMesh->Draw(Trooper, TrooperMvp, TrupProgram);
  TrupMesh->Draw(Trooper2, Trooper2Mvp, TrupProgram);

  CubeProgram->Bind();
  CubeMesh->Draw(Cube, CubeMvp, CubeProgram);
}
