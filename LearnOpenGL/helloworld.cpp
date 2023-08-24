#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"

using namespace std;

float vertices[] = {
	 0.5f, 0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
};
unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

float firstTri[] = {
	-0.9f, -0.5f, 0.0f,
	0.0f, -0.5f, 0.0f,
	-0.45f, 0.5f, 0.0f,
};
float secondTri[] = {
	0.0f, -0.5f, 0.0f,
	0.9f, -0.5f, 0.0f,
	0.45f, 0.5f, 0.0f,
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
	//gl����
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//window ����
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//GLAD �ʱ�ȭ
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initalize GLAD" << endl;
		return -1;
	}

	//Shader shader("./triangle.vs", "./triangleOrange.fs");
	//Shader vertexColorShader("./triangle.vs", "./triangleVertexColor.fs");
	Shader uniformShader("./triangle.vs", "./triangleUniform.fs");

	////Vertex Buffer Object(VBO), Vertex Array Object ����
	//unsigned int VAO, VBO, EBO; //Vertex Buffer Object, Vertex Array Object, Element Buffer Object
	//glGenVertexArrays(1, &VAO); //VAO ��� ����
	//glGenBuffers(1, &VBO); //VBO ���� ����
	//glGenBuffers(1, &EBO); //EBO ���� ����
	//glBindVertexArray(VAO); //VAO ���ε�
	//glBindBuffer(GL_ARRAY_BUFFER, VBO); //GL_ARRAY_BUFFER�� VBO ���ε�
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //GL_ELEMENT_ARRAY_BUFFER�� EBO ���ε�
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //GL_ARRAY_BUFFER�� vertices ������ ����
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //GL_ELEMENT_ARRAY_BUFFER�� indices ������ ����

	//VBOs, VAOs
	unsigned int VAOs[2], VBOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	//first triangle
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTri), firstTri, GL_STATIC_DRAW);
	//���� �Ӽ� ����(first triangle)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//second triangle
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTri), secondTri, GL_STATIC_DRAW);
	//���� �Ӽ� ����(second triangle)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//shader.use();
		//vertexColorShader.use();
		uniformShader.use();
		
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		uniformShader.setFloat("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//���ҽ� ����
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);*/
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	glfwTerminate();
	return 0;
}

//window ������ ũ�� ���� �� �ݹ�
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//�Է� �߻��� �ݹ�
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}