#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


//vertex shader source code
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" //set aPos to the input, set vertices to be in position 0
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" //the output of a vertex shader is gl_Position
"}\0";

GLuint vertexShader; //uint to store the sahder source code in

//fragment shader source code
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"\nFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const GLchar* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"\nFragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";




GLuint fragmentShader;
GLuint fragmentShader2;

GLuint shaderProgram;
GLuint shaderProgram2;

GLuint VAO;
GLuint VBO;

GLuint VAO2;
GLuint VBO2;

//vertices to make a triangle hopefully
float vertices[] = { -1.0f, -0.5f, 0.0f,
					  0.0f, -0.5f, 0.0f,
					 -0.5f,  0.5f, 0.0f
					  
				      
};

float vertices2[] = {
					  0.0f, -0.5f, 0.0f,
					  1.0f, -0.5f, 0.0f,
					  0.5f,  0.5f, 0.0f

};




//resize window function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//input function
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	//initialize and configure window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	
	//set window to be the one we are working on
	glfwMakeContextCurrent(window);

	
	//Load GLAD, ensure it's working
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	//set GL to work properly and dynamically with the window (stretchy stuff)
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//compile the vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	//check if compile worked
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}
	else
	{
		std::cout << "VERTEX SUCCESS!\n";
	}

	//do the same thing with the fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}
	else
	{
		std::cout << "FRAGMENT SUCCESS!\n";
	}

	//make shaderProgram be a shader program object
	shaderProgram = glCreateProgram();
	shaderProgram2 = glCreateProgram();

	//attach and link shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	//make sure it worked
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}
	else
	{
		std::cout << "PROGRAM SUCCESS!";
	}

	//use it
	glUseProgram(shaderProgram);

	//delete shaders now that they have been copied over to shaderProgram
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//set up Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);



	//Bind all the buffers to the right buffer objects
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//tell opengl how to read the buffers
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//set attribute array to the 0 position
	glEnableVertexAttribArray(0);

	// unbind buffer (everything has been registered in Vertex Attribute Pointer)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	//Do it again with the second buffer
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);



	//Bind all the buffers to the right buffer objects
	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);

	//tell opengl how to read the buffers
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//set attribute array to the 1 position
	glEnableVertexAttribArray(0);

	// unbind buffer (everything has been set up in VAO2)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//rendering commands
		glClearColor(.27f, 0.38f, 0.92f, 1.0f); //set glclearcolor
		glClear(GL_COLOR_BUFFER_BIT);	//apply glclearcolor


		//Set orange shader
		glUseProgram(shaderProgram);

		//set VAO to first triangle and draw it
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//set yellow shader
		glUseProgram(shaderProgram2);

		//set VAO to seconf triangle and draw it
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate(); //terminate program


	return 0;
}
