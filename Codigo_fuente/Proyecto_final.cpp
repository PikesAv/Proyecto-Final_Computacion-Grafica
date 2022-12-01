/*
Facultad de ingenieria
Computacion grafica e interaccion humano-computadora
Semestre 2023-1

Grupo 3.
Equipo 1.
Integrantes del equipo.
	-Chavez García Jesús Ángel
	-Hernández Hernández Pedro Daniel
	-Marín Barrera Jorge Jair
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <Windows.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//Variables globales para el movimiento del personaje principal
float MrotABrazo , MrotBrazo , MrotPierna, MrotPie, rotPie;
bool rotAB, rotB,rotP;
float rotlilitOffset;
//Variable externa para la eleccion del caso
//de la luz del coche
extern int bandera;

//Variable correspondiente para el ciclo del día y noche
int conta_dia;

float ciclo_dia;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

//Texturas
Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture Recepcion;
Texture Ventanal;
Texture Piso_madera;
Texture Piso_madera_2;
Texture Piso_madera_3;
Texture Piso_madera_4;
Texture pasto;

//Texturas utilizadas
Texture Edificio;
Texture marmol;


//Modelos
Model Camino_M;
Model cartel_M;
Model Farola;
Model Carpa;

//Arturia Pendragon (Lily)
Model Lilit_AnteBrazo;
Model Lilit_AnteBrazo_2;
Model Lilit_Brazo;
Model Lilit_Brazo_2;
Model Lilit_Pierna;
Model Lilit_Pierna_2;
Model Lilit_Pie;
Model Lilit_Pie_2;
Model Lilit_Cabeza;
Model Lilit_Cuerpo;

//Skybox
Skybox skybox;
Skybox skyboxNight;

//materiales
Material Material_brillante;
Material Material_opaco;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,			0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	115.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 115.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		115.0f, 115.0f,		0.0f, -1.0f, 0.0f
	};

	unsigned int floorIndices2[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices2[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,			0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	60.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 60.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		60.0f, 60.0f,		0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(floorVertices2, floorIndices2, 32, 6);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj5);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);
}

void CrearDado()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		//-0.5f, -0.5f,  0.5f,	0.02f,  0.26f,		0.0f,	0.0f,	1.0f,	//0
		//0.5f, -0.5f,  0.5f,		0.33f,	0.26f,		0.0f,	0.0f,	1.0f,	//1
		//0.5f,  0.5f,  0.5f,		0.33f,	0.72f,		0.0f,	0.0f,	1.0f,	//2
		//-0.5f,  0.5f,  0.5f,	0.02f,	0.72f,		0.0f,	0.0f,	1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.02f,  0.26f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.33f,	0.26f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.33f,	0.72f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.02f,	0.72f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.02f,  0.26f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.33f,	0.26f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.33f,	0.72f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.02f,	0.72f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.02f,  0.26f,		-1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.33f,	0.26f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.33f,	0.72f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.02f,	0.72f,		-1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.5f,  1.0f,		0.0f,	-1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.83f,	1.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.83f,	0.74f,		0.0f,	-1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.5f,	0.74f,		0.0f,	-1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.5f,  1.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.83f,	1.0f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.83f,	0.74f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.5f,	0.74f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(dado);
}

void CrearRecepcion()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		//-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,	//0
		//0.5f, -0.5f,  0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,	//1
		//0.5f,  0.5f,  0.5f,		1.0f,	0.5f,		0.0f,	0.0f,	1.0f,	//2
		//-0.5f,  0.5f,  0.5f,	0.0f,	0.5f,		0.0f,	0.0f,	1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	1.0f,	0.5f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	0.5f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		1.0f,	0.5f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,	0.5f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f,	0.5f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	0.5f,		-1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.5f,  1.0f,		0.0f,	-1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.83f,	1.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.83f,	0.74f,		0.0f,	-1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.5f,	0.74f,		0.0f,	-1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.0f,  0.5f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f,	0.5f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(dado);
}

void CrearEntrada()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,	//0
		0.5f, -0.5f,  0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,	//1
		0.5f,  0.5f,  0.5f,		1.0f,	1.0f,		0.0f,	0.0f,	1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.0f,	1.0f,		0.0f,	0.0f,	1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		1.0f,	1.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,	1.0f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	0.f,		-1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.0f,	0.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.0f,	0.0f,		0.0f,	-1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.0f,	0.0f,		0.0f,	-1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,	0.0f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.0f,	0.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.0f,	0.0f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(dado);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearDado();
	CreateShaders();
	CrearRecepcion();
	CrearEntrada();

	//Camara
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	//Declaracion de texturas
	pisoTexture = Texture("Textures/Pisos/Floor_texture.tga");
	pisoTexture.LoadTextureA();
	marmol = Texture("Textures/Pisos/marmol.tga");
	marmol.LoadTextureA();
	Recepcion = Texture("Textures/Paredes/Recepcion_textura.tga");
	Recepcion.LoadTextureA();
	Ventanal = Texture("Textures/Paredes/Ventana.tga");
	Ventanal.LoadTextureA();

	Edificio = Texture("Textures/Build_texture.tga");
	Edificio.LoadTextureA();
	Piso_madera = Texture("Textures/Pisos/Wood_floor.tga");
	Piso_madera.LoadTextureA();
	Piso_madera_2 = Texture("Textures/Pisos/Wood_floor_2.tga");
	Piso_madera_2.LoadTextureA();
	Piso_madera_3 = Texture("Textures/Pisos/Wood_floor_3.tga");
	Piso_madera_3.LoadTextureA();
	Piso_madera_4 = Texture("Textures/Pisos/Wood_floor_4.tga");
	Piso_madera_4.LoadTextureA();
	pasto = Texture("Textures/Pisos/grass-lawn-texture.tga");
	pasto.LoadTextureA();

	//Declaracion de modelos utilizados 
	cartel_M = Model();
	cartel_M.LoadModel("Models/Construccion/maistro.obj");
	Farola = Model();
	Farola.LoadModel("Models/Farola_2/Farola_2.obj");
	Carpa = Model();
	Carpa.LoadModel("Models/Carpa/Carpa.obj");

	//Artoria Pendragon (Lily)
	Lilit_AnteBrazo = Model();
	Lilit_AnteBrazo.LoadModel("Models/Lilit_AnteBrazo.obj");
	Lilit_AnteBrazo_2 = Model();
	Lilit_AnteBrazo_2.LoadModel("Models/Lilit_AnteBrazo_2.obj");
	Lilit_Brazo = Model();
	Lilit_Brazo.LoadModel("Models/Lilit_Brazo.obj");
	Lilit_Brazo_2 = Model();
	Lilit_Brazo_2.LoadModel("Models/Lilit_Brazo_2.obj");
	Lilit_Pierna = Model();
	Lilit_Pierna.LoadModel("Models/Lilit_Pierna.obj");
	Lilit_Pierna_2 = Model();
	Lilit_Pierna_2.LoadModel("Models/Lilit_Pierna_2.obj");
	Lilit_Pie = Model();
	Lilit_Pie.LoadModel("Models/Lilit_Pie.obj");
	Lilit_Pie_2 = Model();
	Lilit_Pie_2.LoadModel("Models/Lilit_Pie_2.obj");
	Lilit_Cabeza = Model();
	Lilit_Cabeza.LoadModel("Models/Lilit_Cabeza.obj");
	Lilit_Cuerpo = Model();
	Lilit_Cuerpo.LoadModel("Models/Lilit_Cuerpo.obj");

	std::vector<std::string> skyboxFaces;
	std::vector<std::string> skyboxFacesNight;

	//Skybox utilizados
	skyboxFaces.push_back("Textures/Skybox/Day/Day_sky_right.tga");//Right
	skyboxFaces.push_back("Textures/Skybox/Day/Day_sky_left.tga");//Left
	skyboxFaces.push_back("Textures/Skybox/Day/Day_sky_bottom.tga");//Top
	skyboxFaces.push_back("Textures/Skybox/Day/Day_sky_top.tga");//Bottom
	skyboxFaces.push_back("Textures/Skybox/Day/Day_sky_front.tga");//Back
	skyboxFaces.push_back("Textures/Skybox/Day/Day_sky_back.tga");//Front

	skyboxFacesNight.push_back("Textures/Skybox/Night/Night_sky_right.tga");//Right
	skyboxFacesNight.push_back("Textures/Skybox/Night/Night_sky_left.tga");//Left
	skyboxFacesNight.push_back("Textures/Skybox/Night/Night_sky_bottom.tga");//Top
	skyboxFacesNight.push_back("Textures/Skybox/Night/Night_sky_top.tga");//Bottom
	skyboxFacesNight.push_back("Textures/Skybox/Night/Night_sky_front.tga");//Back
	skyboxFacesNight.push_back("Textures/Skybox/Night/Night_sky_back.tga");//Front

	skybox = Skybox(skyboxFaces);
	skyboxNight = Skybox(skyboxFacesNight);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	//contador de luces del tipo pointlight
	unsigned int pointLightCount = 0;
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.5f, 0.5f,
		20.0f, 1.5f, -30.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[1] = PointLight(0.5f, 0.0f, 0.5f,
		0.5f, 0.5f,
		0.0f, 1.5f, -30.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[2] = PointLight(0.0f, 0.5f, 0.5f,
		0.5f, 0.5f,
		-20.0f, 1.5f, -30.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;


	unsigned int spotLightCount = 0;
	//Contador de luces del tipo spotlight
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.1f, 1.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	spotLights[1] = SpotLight(1.0f, 0.0f, 1.0f,
		0.1f, 1.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	spotLights[2] = SpotLight(0.0f, 0.5f, 0.5f,
		0.1f, 1.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	spotLights[3] = SpotLight(0.5f, 0.5f, 0.0f,
		0.1f, 1.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	spotLights[4] = SpotLight(0.0f, 0.0f, 0.5f,
		0.1f, 1.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	
	//Animaciones
	
	//Lily
	MrotABrazo = 0.0f;
	MrotBrazo = 0.0f;
	MrotPierna = 0.0f;
	rotPie = 0.0f;
	rotlilitOffset = 1.0f;
	rotAB = true;
	rotB = true;
	rotP = true;
	rotPie = true;
	//
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		//Cambio de Skybox para el ciclo de día y noche
		if (conta_dia < 6000) {
			if (ciclo_dia <= 1.0) {
				ciclo_dia += 0.001;
			}
			if (ciclo_dia > 0.55) {
				skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
			}
			else {
				skyboxNight.DrawSkybox(camera.calculateViewMatrix(), projection);
			}
		}
		else {
			if (ciclo_dia >= 0.085) {
				ciclo_dia -= 0.001;
			}
			if (conta_dia == 12000) {
				conta_dia = 0;
			}
			if (ciclo_dia < 0.55) {
				skyboxNight.DrawSkybox(camera.calculateViewMatrix(), projection);
			}
			else {
				skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
			}
		}
		conta_dia += 1;

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//Ciclo de Día y Noche
		//luz direccional, sólo 1 y siempre debe de existir
		//Sera la luz que ilumine al mundo que tengamos
		mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
			ciclo_dia, 1.0,//Va a servir para manejar el ciclo dia y noche
			1.0f, 0.0f, -1.0f);

		//Lily
		//antebrazos
		if (rotAB)
		{
			if (MrotABrazo < 40.0f)
			{
				MrotABrazo += rotlilitOffset * deltaTime;
			}
			else
			{
				rotAB = false;
			}
		}
		if (!rotAB)
		{
			if (MrotABrazo > -40.0f)
			{
				MrotABrazo -= rotlilitOffset * deltaTime;
			}
			else
			{
				rotAB = true;
			}
		}
		//brazos
		if (rotB)
		{
			if (MrotBrazo < 20.0f)
			{
				MrotBrazo += rotlilitOffset/2 * deltaTime;
			}
			else
			{
				rotB = false;
			}
		}
		if (!rotB)
		{
			if (MrotBrazo > -20.0f)
			{
				MrotBrazo -= rotlilitOffset/2 * deltaTime;
			}
			else
			{
				rotB = true;
			}
		}
		//piernas
		if (rotP)
		{
			if (MrotPierna < 25.0f)
			{
				MrotPierna += rotlilitOffset * deltaTime;
			}
			else
			{
				rotP = false;
			}
		}
		if (!rotP)
		{
			if (MrotPierna > -25.0f)
			{
				MrotPierna -= rotlilitOffset * deltaTime;
			}
			else
			{
				rotP = true;
			}
		}
		// pies
		if (rotPie)
		{
			if (MrotPie < 0.0f)
			{
				MrotPie += rotlilitOffset/2 * deltaTime;
			}
			else
			{
				rotPie = false;
			}
		}
		if (!rotAB)
		{
			if (MrotPie > 25.0f)
			{
				MrotPie -= rotlilitOffset/2 * deltaTime;
			}
			else
			{
				rotPie = true;
			}
		}
		//


		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//Inicializacion de las luces de tipo spotlight
		spotLights[0].SetFlash(glm::vec3(40.0f, 15.0f, -50.0f), glm::vec3(0.0f, -1.0f, 0.0f));

		spotLights[1].SetFlash(glm::vec3(20.0f, 15.0f, -50.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		
		spotLights[2].SetFlash(glm::vec3(0.0f, 15.0f, -50.0f), glm::vec3(0.0f, -1.0f, 0.0f));

		spotLights[3].SetFlash(glm::vec3(-20.0f, 15.0f, -50.0f), glm::vec3(0.0f, -1.0f, 0.0f));

		spotLights[4].SetFlash(glm::vec3(-40.0f, 15.0f, -50.0f), glm::vec3(0.0f, -1.0f, 0.0f));

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		//Matrices para el coche del previo
		glm::mat4 modelCoche_previo(1.0);
		glm::mat4 modelCofre_previo(1.0);

		//Matrices para el persona principal
		glm::mat4 modelaux_cuerpo(1.0);
		glm::mat4 modelaux_brazo(1.0);
		glm::mat4 modelaux_brazo2(1.0);
		glm::mat4 modelaux_pierna(1.0);
		glm::mat4 modelaux_pierna2(1.0);

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(25.0f, 1.0f, 25.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		
		//BLENDING: Util para la tranparencia o Traslucidez
		//Para poder hacer adecuadamente la transparencia de un objeto, se debe de poner
		//primero los modelos a utilizar y despues colocar el mesh en numérico
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		//------------Personajes-----------//
		// Arturia Pendragon (Lily)
		//Cuerpo
		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 0.0f, 0.3f);
		model = glm::translate(model, glm::vec3(0.0f, 2.7f, 0.0f + mainWindow.getmovlily()));
		modelaux_cuerpo = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lilit_Cuerpo.RenderModel();

		//Brazo Izquierdo
		model = modelaux_cuerpo;
		model = glm::translate(model, glm::vec3(0.49f, 1.61f, -0.1f));
		model = glm::rotate(model, glm::radians(MrotABrazo), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelaux_brazo = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lilit_AnteBrazo.RenderModel();

		model = modelaux_brazo;
		model = glm::translate(model, glm::vec3(0.77f, -1.02f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians((MrotBrazo)), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lilit_Brazo.RenderModel();

		//Brazo Derecho
		model = modelaux_cuerpo;
		model = glm::translate(model, glm::vec3(-0.49f, 1.61f, -0.1f));
		model = glm::rotate(model, glm::radians(MrotABrazo), glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux_brazo2 = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lilit_AnteBrazo_2.RenderModel();

		model = modelaux_brazo2;
		model = glm::translate(model, glm::vec3(-0.77f, -1.02f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians((MrotBrazo)), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lilit_Brazo_2.RenderModel();

		//Pie Izquierdo
		model = modelaux_cuerpo;
		model = glm::translate(model, glm::vec3(0.3f, -0.4f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotPierna)), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelaux_pierna = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lilit_Pierna.RenderModel();

		model = modelaux_pierna;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotPie)), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lilit_Pie.RenderModel();

		//Pie Derecho
		model = modelaux_cuerpo;
		model = glm::translate(model, glm::vec3(-0.3f, -0.4f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotPierna)), glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux_pierna2 = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lilit_Pierna_2.RenderModel();

		model = modelaux_pierna2;
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotPie)), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//LilitTexture.UseTexture();
		Lilit_Pie_2.RenderModel();

		//Cabeza
		model = modelaux_cuerpo;
		model = glm::translate(model, glm::vec3(0.0f, 2.49f, 0.02f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lilit_Cabeza.RenderModel();

		//--------------------------------------------Festival-----------------------------------------//
		//Codigo para las carpas a utilizar
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-65.0f, -5.8f, 145.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.18f, 0.2f, 0.18f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carpa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(52.0f, -5.8f, 122.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.35f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carpa.RenderModel();

		//Codigo para la carga de los modelos de las farolas a utilizar en el festival
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, -1.95f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.85f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, -1.95f, 167.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.85f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Farola.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(75.0f, -1.95f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.85f, 0.75f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(75.0f, -1.95f, 167.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.85f, 0.75f));
		model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Farola.RenderModel();

		//Piso de cada una de las secciones del festival
		//Seccion de comida nacional
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(52.0f, -1.8f, -30.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(52.0f, -1.8f, 137.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(52.0f, -1.8f, 30.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pasto.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, -1.8f, 137.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera_2.UseTexture();
		meshList[3]->RenderMesh();

		//Seccion de comida internacional
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.8f, 137.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera_3.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-112.0f, -1.8f, 137.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera_4.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-112.0f, -1.8f, 77.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pasto.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-112.0f, -1.8f, -43.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-112.0f, -1.8f, 17.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera_2.UseTexture();
		meshList[3]->RenderMesh();

		//Codigo para la creación del recinto que tendrá el festival de comida
		//--------------------------------------------Acuario-----------------------------------------//
		//Piso de la recepcion
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.8f, 0.0f));
		model = glm::scale(model, glm::vec3(7.5f, 0.0f, 7.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		marmol.UseTexture();
		//meshList[2]->RenderMesh();

		//Recepcion
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 13.1f, 0.0f));
		model = glm::scale(model, glm::vec3(150.0f, 30.0f, 150.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio.UseTexture();
		//meshList[5]->RenderMesh();

		//Paredes de la recepcion
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 12.8f, 0.0f));
		model = glm::scale(model, glm::vec3(149.0f, 29.5f, 149.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Recepcion.UseTexture();
		//meshList[6]->RenderMesh();

		//Entrada principal (ventanal)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 13.14f, 74.9f));
		model = glm::scale(model, glm::vec3(150.0f, 30.0f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ventanal.UseTexture();
		//meshList[7]->RenderMesh();

		//Acuario parte de la planta blaja
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -18.01f, 0.0f));
		model = glm::scale(model, glm::vec3(300.0f, 30.0f, 250.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio.UseTexture();
		meshList[5]->RenderMesh();

		
		//Cubo para el NP Nero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -60.0f, 0.0f));
		model = glm::scale(model, glm::vec3(60.0f, 60.0f, 60.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//marmol.UseTexture();
		//Edificio.UseTexture();
		//meshList[4]->RenderMesh();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(75.5f, 6.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cartel_M.RenderModel();
				
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
