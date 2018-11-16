
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

//����
float vertices[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f
};

const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main(){\n"
"     gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"	  vertexColor = vec4(1.0, 0, 0, 1.0); \n"
"}\n";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"uniform vec4 ourColor;\n"
"void main(){\n"
"   FragColor = ourColor;\n"
"}";

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{

	//printf("hihihi\n");
	//system("pause");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//����GLFWҪ�õ����汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�Ӱ�汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//��Ⱦ���ߵ�����

	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("Open Window Failed");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	//Init GLEW
	glewExperimental = true;
	
	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW Failed");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	//�����������Vertex Array Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//���㻺�����Vertex Buffer Object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//������رմ��ھ�һֱ����������
	while (!glfwWindowShouldClose(window))
	{
		//input commands
		processInput(window);

		// rendering commands here
		glClearColor(0, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2 + 0.5;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0, greenValue, 0, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}
