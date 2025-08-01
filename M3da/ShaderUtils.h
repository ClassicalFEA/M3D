
// momo ModernOpenGL_Start

// ---------------
// ShaderUtils.h
// ---------------

#pragma once
#include <GL/glew.h>
#include <string>

void InitGraphicsShaders();
void SyncLegacyViewToModern(double dW, double dH, double wpSize, const float* legacyMatrix);
void DrawFilledTriangle();
void DrawWireTriangle();
void RestoreLegacyGraphics();
void BuildLegacyCompatibleProjectionMatrix(GLfloat* projOut);

std::string LoadShaderSource(const char* filePath);
GLuint CompileShader(GLenum shaderType, const std::string& source);
GLuint CreateShaderProgramFromFiles(const char* vertPath, const char* fragPath);
GLuint CreateShaderProgram(GLuint vertShader, GLuint fragShader);
GLuint CreateFilledTriangleVAO();
GLuint CreateWireTriangleVAO();

extern float oglViewMatrix[16];
extern double oglViewWidth;
extern double oglViewHeight;
extern double oglWPSize;

extern float uiTransMulX, uiTransMulY, uiTransMulZ;
extern float scaleX, scaleY, scaleZ;
extern float offsetX, offsetY, offsetZ;
extern float zoomScale, rotationDeg, depthShift;
extern int alignMode;

extern GLuint g_mainShaderProgram;

extern GLuint m_FilledTriangleVAO;
extern GLuint m_WireTriangleVAO;

// momo ModernOpenGL_End
