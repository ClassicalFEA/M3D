
// momo ModernOpenGL_Start

// ----------------
// ShaderUtils.cpp
// ----------------

#include "ShaderUtils.h"
#include "stdafx.h"
#include "M3Da.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <cstring>
#include <windows.h>
#include <vector>
#include <string>
#include <atlstr.h>

void UpdateTriangleTranslationFromUI() {
	//// CString allText = ReadText();
	CString allText = ""; //note: change this line to upper line when active
	std::vector<float> values;

	CT2A ascii(allText);
	std::istringstream iss(ascii.m_psz);
	std::string line;

	while (std::getline(iss, line)) {
		try {
			float val = std::stof(line);
			values.push_back(val);
		} catch (...) {
			values.push_back(1.0f);
		}
	}

	while (values.size() < 13)
		values.push_back(1.0f);

	uiTransMulX = values[0];
	uiTransMulY = values[1];
	uiTransMulZ = values[2];
	scaleX = values[3];
	scaleY = values[4];
	scaleZ = values[5];
	offsetX = values[6];
	offsetY = values[7];
	offsetZ = values[8];
	zoomScale = values[9];
	rotationDeg = values[10];
	alignMode = static_cast<int>(values[11]);
	depthShift = values[12];
}

float oglViewMatrix[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1};
double oglViewWidth = 1.0, oglViewHeight = 1.0, oglWPSize = 1.0;

float uiTransMulX = 1.0f, uiTransMulY = 1.0f, uiTransMulZ = 1.0f;
float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;
float offsetX = 0.0f, offsetY = 0.0f, offsetZ = 0.0f;
float zoomScale = 1.0f, rotationDeg = 0.0f, depthShift = 0.0f;
int alignMode = 0;

GLuint g_mainShaderProgram = 0;

GLuint m_FilledTriangleVAO = 0;
GLuint m_WireTriangleVAO = 0;

std::string LoadShaderSource(const char* filePath) {
	std::ifstream shaderFile(filePath);
	if (!shaderFile.is_open()) {
		throw std::runtime_error(std::string("Could not open shader file: ") + filePath);
	}
	std::stringstream buffer;
	buffer << shaderFile.rdbuf();
	return buffer.str();
}

GLuint CompileShader(GLenum shaderType, const std::string& source) {
	GLuint shader = glCreateShader(shaderType);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		OutputDebugStringA(infoLog);
		throw std::runtime_error("Shader compilation failed");
	}
	return shader;
}

GLuint CreateShaderProgramFromFiles(const char* vertPath, const char* fragPath) {
	std::string vertCode = LoadShaderSource(vertPath);
	std::string fragCode = LoadShaderSource(fragPath);

	GLuint vertShader = CompileShader(GL_VERTEX_SHADER, vertCode);
	GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, fragCode);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		OutputDebugStringA(infoLog);
		throw std::runtime_error("Shader linking failed");
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	return program;
}

void InitGraphicsShaders() {
	g_mainShaderProgram = CreateShaderProgramFromFiles("shaders/default.vert", "shaders/default.frag");
	m_FilledTriangleVAO = CreateFilledTriangleVAO();
	m_WireTriangleVAO = CreateWireTriangleVAO();
}

static void BuildMVPMatrix(float* mvpOut) {
	float rad = rotationDeg * 3.1415926f / 180.0f;
	float cosA = cosf(rad);
	float sinA = sinf(rad);

	float scaleMat[16] = {
	    scaleX * zoomScale, 0, 0, 0,
	    0, scaleY * zoomScale, 0, 0,
	    0, 0, scaleZ * zoomScale, 0,
	    0, 0, 0, 1};

	float rotMat[16] = {
	    cosA, -sinA, 0, 0,
	    sinA, cosA, 0, 0,
	    0, 0, 1, 0,
	    0, 0, 0, 1};

	float model[16];
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			model[i * 4 + j] =
			    rotMat[i * 4 + 0] * scaleMat[0 * 4 + j] +
			    rotMat[i * 4 + 1] * scaleMat[1 * 4 + j] +
			    rotMat[i * 4 + 2] * scaleMat[2 * 4 + j] +
			    rotMat[i * 4 + 3] * scaleMat[3 * 4 + j];

	float mv[16];
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			mv[i * 4 + j] =
			    model[i * 4 + 0] * oglViewMatrix[0 * 4 + j] +
			    model[i * 4 + 1] * oglViewMatrix[1 * 4 + j] +
			    model[i * 4 + 2] * oglViewMatrix[2 * 4 + j] +
			    model[i * 4 + 3] * oglViewMatrix[3 * 4 + j];

	mv[12] = mv[12] * uiTransMulX + offsetX;
	mv[13] = mv[13] * uiTransMulY + offsetY;
	mv[14] = mv[14] * uiTransMulZ + offsetZ + depthShift;

	GLfloat proj[16];
	BuildLegacyCompatibleProjectionMatrix(proj);

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			mvpOut[i * 4 + j] =
			    proj[i * 4 + 0] * mv[0 * 4 + j] +
			    proj[i * 4 + 1] * mv[1 * 4 + j] +
			    proj[i * 4 + 2] * mv[2 * 4 + j] +
			    proj[i * 4 + 3] * mv[3 * 4 + j];
}

void SyncLegacyViewToModern(double dW, double dH, double wpSize, const float* legacyMatrix) {
	UpdateTriangleTranslationFromUI();
	oglViewWidth = dW;
	oglViewHeight = dH;
	oglWPSize = wpSize;
	memcpy(oglViewMatrix, legacyMatrix, sizeof(float) * 16);
}

void DrawWireTriangle() {
	GLfloat mvp[16];
	BuildMVPMatrix(mvp);

	GLfloat lineVertices[] = {
	    -100.0f, 100.0f, 0.0f,
	    -150.0f, 0.0f, 0.0f,
	    -150.0f, 0.0f, 0.0f,
	    -50.0f, 0.0f, 0.0f,
	    -50.0f, 0.0f, 0.0f,
	    -100.0f, 100.0f, 0.0f};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glUseProgram(g_mainShaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(g_mainShaderProgram, "uMVP"), 1, GL_FALSE, mvp);
	glUniform3f(glGetUniformLocation(g_mainShaderProgram, "uColor"), 0.0f, 1.0f, 0.0f);
	glDrawArrays(GL_LINES, 0, 6);

	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void DrawFilledTriangle() {
	GLfloat mvp[16];
	BuildMVPMatrix(mvp);

	GLfloat vertices[] = {
	    -100.0f, 98.0f, 0.0f,
	    -148.26794919243112270647255365849f, 1.0f, 0.0f,
	    -51.732050807568877293527446341506f, 1.0f, 0.0f};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glUseProgram(g_mainShaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(g_mainShaderProgram, "uMVP"), 1, GL_FALSE, mvp);
	glUniform3f(glGetUniformLocation(g_mainShaderProgram, "uColor"), 1.0f, 0.0f, 0.2f);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void RestoreLegacyGraphics() {
	glUseProgram(0);
}

GLuint CreateShaderProgram(GLuint vertShader, GLuint fragShader) {
	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		OutputDebugStringA(infoLog);
		throw std::runtime_error("Shader linking failed");
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	return program;
}

GLuint CreateFilledTriangleVAO() {
	GLfloat vertices[] = {
	    -100.0f, 98.0f, 0.0f,
	    -148.26794919243112270647255365849f, 1.0f, 0.0f,
	    -51.732050807568877293527446341506f, 1.0f, 0.0f};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
	return vao;
}

GLuint CreateWireTriangleVAO() {
	GLfloat lineVertices[] = {
	    -100.0f, 100.0f, 0.0f,
	    -150.0f, 0.0f, 0.0f,
	    -150.0f, 0.0f, 0.0f,
	    -50.0f, 0.0f, 0.0f,
	    -50.0f, 0.0f, 0.0f,
	    -100.0f, 100.0f, 0.0f};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);

	return vao;
}

void BuildLegacyCompatibleProjectionMatrix(GLfloat* projOut) {
	float dW = static_cast<float>(oglViewWidth);
	float dH = static_cast<float>(oglViewHeight);
	float depth = static_cast<float>(20.0 * oglWPSize);

	float l = -dW;
	float r = dW;
	float b = -dH;
	float t = dH;
	float n = -depth;
	float f = depth;

	float ortho[16] = {
	    2.0f / (r - l), 0, 0, 0,
	    0, 2.0f / (t - b), 0, 0,
	    0, 0, -2.0f / (f - n), 0,
	    -(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n), 1.0f};

	memcpy(projOut, ortho, sizeof(float) * 16);
}

// momo ModernOpenGL_End
