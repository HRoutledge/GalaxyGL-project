#include "visuals.h"

/*GLOBAL VARIABLES*/
const unsigned int width = 2560;
const unsigned int height = 1440;
/*GLOBAL VARIABLES END!*/

/*FUNCTION DECLARATION*/
void framebuffer_size_callback(GLFWwindow* GLwindow, int width, int height);
void keyinput(GLFWwindow* GLwindow);
void setscreen();
/*FUNCTION DECLARATION END!*/


int main()
{
	/*BEGIN GENERAL LIBRARY INITIALIZATION!*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*create openGL window context*/
	GLFWwindow* GLwindow = glfwCreateWindow(width, height, "galaxyGL", NULL, NULL);
	if (GLwindow == NULL)
	{
		std::cout << "computer says no" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(GLwindow);
	glfwSetFramebufferSizeCallback(GLwindow, framebuffer_size_callback);

	/*copy pasted from learnopenGL.com, it's only loading up glad so it's fine*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	/*END OF GENERAL LIBRARY INITIALIZATION!*/

	/*CALLING CLASSES*/
	srand(time(NULL));
	galaxy G1;
	graphics gfx;
	G1.makegalaxy();
	gfx.installshaders();
	G1.setprimarycolor();
	/*END OF CALLING CLASSES!*/

	/*GENERATE BUFFERS*/
	glGenBuffers(1, &gfx.pVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gfx.pVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(G1.pCloud) * G1.getSOA(), G1.pCloud, GL_STATIC_DRAW);
	/*END OF GENERATE BUFFERS!*/

	/*SETUP VERTEX ARRAY OBJECTS*/
	glGenVertexArrays(1, &gfx.pVAO);
	glBindVertexArray(gfx.pVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
	/*END OF SETUP VERTEX ARRARY OBJECTS!*/


	glm::vec3 galaxycolor(G1.r, G1.g, G1.b); //sets primary color of generated galaxy
	GLint galaxycolorUniformLocation = glGetUniformLocation(gfx.programID, "galaxycolor");
	glUniform3fv(galaxycolorUniformLocation, 1, glm::value_ptr(galaxycolor));


	/*VIEW MATRIX*/
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(0.5f, 0.4f, 0.5f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, -1.0f));

	GLint viewMatrixUniformLocation =
		glGetUniformLocation(gfx.programID, "view");

	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(view));
	/*END OF VIEW MATRIX!*/

	float rotspeedrand = lerandfunc(-3.0f, -10.0f); //random rotational value used in generating galaxy

	//START RENDER LOOP!
	while (!glfwWindowShouldClose(GLwindow))
	{

		keyinput(GLwindow); //check for user key input
		setscreen(); //enable openGL depth & color buffer

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(70.0f), (float)width / height, 0.1f, 1.0f);
		glm::mat4 translationMatrix = glm::translate(projectionMatrix, glm::vec3(+0.5f, +0.5f, -1.0f));
		glm::mat4 trans = glm::rotate(translationMatrix, glm::radians((float)glfwGetTime()) * rotspeedrand, glm::vec3(0.0f, 0.0f, 1.0f));

		GLint transMatrixUniformLocation =
			glGetUniformLocation(gfx.programID, "trans");

		glUniformMatrix4fv(transMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(trans));

		glPointSize(lerandfunc(15, 18));
		glDrawArrays(GL_POINTS, 0, G1.getSOA());

		glfwSwapBuffers(GLwindow);
		glfwPollEvents();

	}//END RENDER LOOP!

	/*SHUT PROGRAM DOWN*/
	delete[] G1.pCloud; //clean up memory
	glUseProgram(0);
	glDeleteProgram(gfx.programID);
	glfwTerminate();
	return 0;
}

void keyinput(GLFWwindow* GLwindow)
{
	/*this function processes key */

	if (glfwGetKey(GLwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(GLwindow, true);

}

void framebuffer_size_callback(GLFWwindow* GLwindow, int width, int height)
{
	/*this function enables the user to resize the window*/

	glViewport(0, 0, width, height);
}

void setscreen()
{
	/*this function sets basic info needed for drawing the screen*/

	glClearColor(0.04f, 0.04f, 0.06f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

}