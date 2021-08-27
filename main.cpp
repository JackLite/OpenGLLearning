#include <iostream>
#include "gl3w.h";
#include "glfw3.h";
#include "vgl.h";
#include "LoadShaders.h";

using namespace std;

void initWindow()
{
	auto glfwInitResult = glfwInit();
	if (glfwInitResult != GLFW_TRUE)
	{
		cout << "GLFW initialization error. Code " << glfwInitResult << "\n";
		exit(glfwInitResult);
	}
}

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;
//--------------------------------------------------------------------
//
// init
//
void init(void)
{
	static const GLfloat vertices[NumVertices][2] =
	{
		{ -0.90, -0.90 }, // Triangle 1
		{ 0.85, -0.90 },
		{ -0.90, 0.85 },
		{ 0.90, -0.85 }, // Triangle 2
		{ 0.90, 0.90 },
		{ -0.85, 0.90 }
	};
	glCreateBuffers(NumBuffers, Buffers);
	glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}

void readInput() {}
void render() {
	static const float black[] = { 0.0f, 1.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

int main()
{
	initWindow();
	auto monitor = glfwGetPrimaryMonitor();
	auto window = glfwCreateWindow(1024, 768, "OpenGL 46", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gl3wInit();
	init();
	while (!glfwWindowShouldClose(window))
	{
		readInput();
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	cout << "Hello, OpenGL 46";
	glfwTerminate();
	return 0;
}