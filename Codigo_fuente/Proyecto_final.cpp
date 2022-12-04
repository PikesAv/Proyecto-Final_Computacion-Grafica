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

//Variables para poder animar la textura
float toffsetu = 0.0f;
float toffsetv = 0.0f;

//Variables globales para el movimiento del personaje principal
//Lily
float MrotABrazoL , MrotBrazoL , MrotPiernaL, MrotPieL;//movimientos
bool rotABL, rotBL,rotPL,rotPiesL;//banderas
float rotLilyOffset;
//Nero
float MrotABrazoN, MrotBrazoN, MrotPiernaN;
bool rotABN, rotBN;//banderas
float rotNeroOffset;
//Koharu
float MrotABrazoK, MrotBrazoK, MrotPiernaK, MrotPieK;//movimientos
bool rotABK, rotBK, rotPK, rotPiesK; //banderas
float rotKoharuOffset;
//koshiro
float MrotABrazoKS, MrotBrazoKS, MrotPiernaKS, MrotPieKS;//movimientos
bool rotABKS, rotBKS, rotPKS, rotPiesKS; //banderas
float rotKoshiroOffset;
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
Texture faro;

//Texturas utilizadas
Texture Edificio;
Texture marmol;

//Texturas animadas
Texture Firework_O;
Texture Firework_P;
Texture Firework_R;
Texture Firework_G;

//Modelos entorno
Model Camino_M;
Model cartel_M;
Model Farola;
Model Carpa;
Model Farola1;
Model Mesa_B;
Model Silla_R;

//Modelos personajes
//
//Arturia Pendragon (Lily)
Model Lily_AnteBrazo;
Model Lily_AnteBrazo_2;
Model Lily_Brazo;
Model Lily_Brazo_2;
Model Lily_Pierna;
Model Lily_Pierna_2;
Model Lily_Pie;
Model Lily_Pie_2;
Model Lily_Cabeza;
Model Lily_Cuerpo;

//Nero 
Model Nero_Cuerpo;
Model Nero_AnteBrazo;
Model Nero_AnteBrazo_2;
Model Nero_Brazo;
Model Nero_Brazo_2;
//koshiro
Model koshiro_AnteBrazo;
Model koshiro_AnteBrazo_2;
Model koshiro_Brazo;
Model koshiro_Brazo_2;
Model koshiro_Pierna;
Model koshiro_Pierna_2;
Model koshiro_Pie;
Model koshiro_Pie_2;
Model koshiro_Cuerpo;

//koharu
Model Koharu_AnteBrazo;
Model Koharu_AnteBrazo_2;
Model Koharu_Brazo;
Model Koharu_Brazo_2;
Model Koharu_Pierna;
Model Koharu_Pierna_2;
Model Koharu_Pie;
Model Koharu_Pie_2;
Model Koharu_Cuerpo;

//Escenario
Model escenario;
Model Bateria;
Model Guitarra;
Model Micro;

//Modelos FoodTrucks
Model Ftruck1;
Model Ftruck2;
Model Ftruck3;
Model Ftruck4;
Model Ftruck5;

//Modelos Comida Mexicana
Model Comex1;


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
	//average normals
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
	//average normals
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

void CreaTextura() {
	unsigned int texturaIndices[] = {
	0, 1, 2,
	0, 2, 3,
	};

	GLfloat texturaVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
	};

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(texturaVertices, texturaIndices, 32, 6);
	meshList.push_back(obj6);
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
	CreaTextura();

	//Camara
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 1.5f, 0.5f);

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
	faro = Texture("Textures/tlamp.tga");
	faro.LoadTextureA();

	//Texturas animadas
	Firework_G = Texture("Textures/Animadas/Firework_green.tga");
	Firework_G.LoadTextureA();
	Firework_O = Texture("Textures/Animadas/Firework_orange.tga");
	Firework_O.LoadTextureA();
	Firework_P = Texture("Textures/Animadas/Firework_purple.tga");
	Firework_P.LoadTextureA();
	Firework_R = Texture("Textures/Animadas/Firework_red.tga");
	Firework_R.LoadTextureA();


	//Declaracion de modelos utilizados
	//
	cartel_M = Model();
	cartel_M.LoadModel("Models/Construccion/maistro.obj");
	Farola = Model();
	Farola.LoadModel("Models/Farola_2/Farola_2.obj");
	Carpa = Model();
	Carpa.LoadModel("Models/Carpa/Carpa.obj");
	Farola1 = Model();
	Farola1.LoadModel("Models/Farola_3/farola_3.obj");
	Silla_R = Model();
	Silla_R.LoadModel("Models/Silla/Silla_roja.obj");
	Mesa_B = Model();
	Mesa_B.LoadModel("Models/Mesa/Mesa_blanca.obj");
	
	//Artoria Pendragon (Lily)
	//Lily_AnteBrazo = Model();
	//Lily_AnteBrazo.LoadModel("Models/Lily/Lily_AnteBrazo_1.obj");
	//Lily_AnteBrazo_2 = Model();
	//Lily_AnteBrazo_2.LoadModel("Models/Lily/Lily_AnteBrazo_2.obj");
	//Lily_Brazo = Model();
	//Lily_Brazo.LoadModel("Models/Lily/Lily_Brazo_1.obj");
	//Lily_Brazo_2 = Model();
	//Lily_Brazo_2.LoadModel("Models/Lily/Lily_Brazo_2.obj");
	//Lily_Pierna = Model();
	//Lily_Pierna.LoadModel("Models/Lily/Lily_Pierna_1.obj");
	//Lily_Pierna_2 = Model();
	//Lily_Pierna_2.LoadModel("Models/Lily/Lily_Pierna_2.obj");
	//Lily_Pie = Model();
	//Lily_Pie.LoadModel("Models/Lily/LilY_Pie_1.obj");
	//Lily_Pie_2 = Model();
	//Lily_Pie_2.LoadModel("Models/Lily/Lily_Pie_2.obj");
	//Lily_Cabeza = Model();
	//Lily_Cabeza.LoadModel("Models/Lily/Lily_Cabeza.obj");
	//Lily_Cuerpo = Model();
	//Lily_Cuerpo.LoadModel("Models/Lily/Lily_Cuerpo.obj");

	//nero
	//Nero_Cuerpo = Model();
	//Nero_Cuerpo.LoadModel("Models/Nero/nero_cuerpo.obj");
	//Nero_AnteBrazo = Model();
	//Nero_AnteBrazo.LoadModel("Models/Nero/nero_antebrazo_1.obj");
	//Nero_AnteBrazo_2 = Model();
	//Nero_AnteBrazo_2.LoadModel("Models/Nero/nero_antebrazo_2.obj");
	//Nero_Brazo = Model();
	//Nero_Brazo.LoadModel("Models/Nero/nero_brazo_1.obj");
	//Nero_Brazo_2 = Model();
	//Nero_Brazo_2.LoadModel("Models/Nero/nero_brazo_2.obj");

	//koshiro
	//koshiro_AnteBrazo = Model();
	//koshiro_AnteBrazo.LoadModel("Models/koshiro/Koshiro_ABrazo_1.obj");
	//koshiro_AnteBrazo_2 = Model();
	//koshiro_AnteBrazo_2.LoadModel("Models/koshiro/Koshiro_ABrazo_2.obj");
	//koshiro_Brazo = Model();
	//koshiro_Brazo.LoadModel("Models/koshiro/Koshiro_Brazo_1.obj");
	//koshiro_Brazo_2 = Model();
	//koshiro_Brazo_2.LoadModel("Models/koshiro/Koshiro_Brazo_2.obj");
	//koshiro_Pierna = Model();
	//koshiro_Pierna.LoadModel("Models/koshiro/Koshiro_Pierna_1.obj");
	//koshiro_Pierna_2 = Model();
	//koshiro_Pierna_2.LoadModel("Models/koshiro/Koshiro_Pierna_2.obj");
	//koshiro_Pie = Model();
	//koshiro_Pie.LoadModel("Models/koshiro/Koshiro_Pie_1.obj");
	//koshiro_Pie_2 = Model();
	//koshiro_Pie_2.LoadModel("Models/koshiro/Koshiro_Pie_2.obj");
	//koshiro_Cuerpo = Model();
	//koshiro_Cuerpo.LoadModel("Models/koshiro/Koshiro_Cuerpo.obj");

	//Koharu
	//Koharu_AnteBrazo = Model();
	//Koharu_AnteBrazo.LoadModel("Models/Koharu/Koharu_AnteBrazo_1.obj");
	//Koharu_AnteBrazo_2 = Model();
	//Koharu_AnteBrazo_2.LoadModel("Models/Koharu/Koharu_AnteBrazo_2.obj");
	//Koharu_Brazo = Model();
	//Koharu_Brazo.LoadModel("Models/Koharu/Koharu_Brazo_1.obj");
	//Koharu_Brazo_2 = Model();
	//Koharu_Brazo_2.LoadModel("Models/Koharu/Koharu_Brazo_2.obj");
	//Koharu_Pierna = Model();
	//Koharu_Pierna.LoadModel("Models/Koharu/Koharu_Pierna_1.obj");
	//Koharu_Pierna_2 = Model();
	//Koharu_Pierna_2.LoadModel("Models/Koharu/Koharu_Pierna_2.obj");
	//Koharu_Pie = Model();
	//Koharu_Pie.LoadModel("Models/Koharu/Koharu_Pie_1.obj");
	//Koharu_Pie_2 = Model();
	//Koharu_Pie_2.LoadModel("Models/Koharu/Koharu_Pie_2.obj");
	//Koharu_Cuerpo = Model();
	//Koharu_Cuerpo.LoadModel("Models/Koharu/Koharu_Cuerpo.obj");

	//FoodTrucks
	//Ftruck1 = Model();
	//Ftruck1.LoadModel("Models/FoodTrucks/Ft1/ft1.obj");
	//Ftruck2 = Model();
	//Ftruck2.LoadModel("Models/FoodTrucks/Ft2/ft2.obj");
	//Ftruck3 = Model();
	//Ftruck3.LoadModel("Models/FoodTrucks/Ft3/yatai.obj");
	//Ftruck4 = Model();
	//Ftruck4.LoadModel("Models/FoodTrucks/Ft4/gerobak.obj");
	//Ftruck5 = Model();
	//Ftruck5.LoadModel("Models/FoodTrucks/Ft5/ft5.obj");


	//Comida Mexicana
	//Comex1 = Model();
	//Comex1.LoadModel("Models/Comida Mex/Puesto1/comex1.obj");

	//Escenario
	escenario = Model();
	escenario.LoadModel("Models/Escenario/Escenario.obj");
	//Bateria = Model();
	//Bateria.LoadModel("Models/Escenario/Bateria.obj");
	//Guitarra = Model();
	//Guitarra.LoadModel("Models/Escenario/guitarra_uno.obj");
	//Micro = Model();
	//Micro.LoadModel("Models/Escenario/Micro.obj");

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
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	
	//Animaciones
	//---------------------------------------//
	//Lily
	MrotABrazoL = 0.0f;
	MrotBrazoL = 0.0f;
	MrotPiernaL = 0.0f;
	rotLilyOffset = 1.0f;
	rotABL = true;
	rotBL = true;
	rotPL = true;
	//rotPieL = true;
	//Nero
	MrotABrazoN = 0.0f;
	MrotBrazoN = 0.0f;
	rotNeroOffset = 1.0f;
	rotABN = true;
	rotBN = true;
	//Koharu
	MrotABrazoK = 0.0f;
	MrotBrazoK = 0.0f;
	MrotPiernaK = 0.0f;
	rotKoharuOffset = 1.0f;
	rotABK = true;
	rotBK = true;
	rotPK = true;
	//Koshiro
	MrotABrazoKS = 0.0f;
	MrotBrazoKS = 0.0f;
	MrotPiernaKS = 0.0f;
	rotKoshiroOffset = 1.0f;
	rotABKS = true;
	rotBKS = true;
	rotPKS = true;
	//---------------------------------------//
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

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
		uniformTextureOffset = shaderList[0].getOffsetLocation();


		//Ciclo de Día y Noche
		//luz direccional, sólo 1 y siempre debe de existir
		//Sera la luz que ilumine al mundo que tengamos
		mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
			ciclo_dia, 1.0,//Va a servir para manejar el ciclo dia y noche
			1.0f, 0.0f, -1.0f);

		//Lily
		//antebrazos
		if (rotABL)
		{
			if (MrotABrazoL < 40.0f)
			{
				MrotABrazoL += rotLilyOffset * deltaTime;
			}
			else
			{
				rotABL = false;
			}
		}
		if (!rotABL)
		{
			if (MrotABrazoL > -40.0f)
			{
				MrotABrazoL -= rotLilyOffset * deltaTime;
			}
			else
			{
				rotABL = true;
			}
		}
		//brazos
		if (rotBL)
		{
			if (MrotBrazoL < 30.0f)
			{
				MrotBrazoL += rotLilyOffset/2 * deltaTime;
			}
			else
			{
				rotBL = false;
			}
		}
		if (!rotBL)
		{
			if (MrotBrazoL > -20.0f)
			{
				MrotBrazoL -= rotLilyOffset/2 * deltaTime;
			}
			else
			{
				rotBL = true;
			}
		}
		//piernas
		if (rotPL)
		{
			if (MrotPiernaL < 25.0f)
			{
				MrotPiernaL += rotLilyOffset * deltaTime;
			}
			else
			{
				rotPL = false;
			}
		}
		if (!rotPL)
		{
			if (MrotPiernaL > -25.0f)
			{
				MrotPiernaL -= rotLilyOffset * deltaTime;
			}
			else
			{
				rotPL = true;
			}
		}
		// pies
		if (rotPiesL)
		{
			if (MrotPieL < 20.0f)
			{
				MrotPieL += rotLilyOffset/2 * deltaTime;
			}
			else
			{
				rotPiesL = false;
			}
		}
		if (!rotPiesL)
		{
			if (MrotPieL > 0.0f)
			{
				MrotPieL -= rotLilyOffset/2 * deltaTime;
			}
			else
			{
				rotPiesL = true;
			}
		}
		//
		//Nero
		//Antebrazo
		if (rotABN)
		{
			if (MrotABrazoN < 50.0f)
			{
				MrotABrazoN += rotNeroOffset * deltaTime;
			}
			else
			{
				rotABN = false;
			}
		}
		if (!rotABN)
		{
			if (MrotABrazoN > -10.0f)
			{
				MrotABrazoN -= rotNeroOffset * deltaTime;
			}
			else
			{
				rotABN = true;
			}
		}
		//Brazo
		if (rotBN)
		{
			if (MrotBrazoN < 40.0f)
			{
				MrotBrazoN += rotNeroOffset * deltaTime;
			}
			else
			{
				rotBN = false;
			}
		}
		if (!rotBN)
		{
			if (MrotBrazoN > 0.0f)
			{
				MrotBrazoN -= rotNeroOffset * deltaTime;
			}
			else
			{
				rotBN = true;
			}
		}
		//---------------------------------------------------------------//
		//Koharu
		//Antebrazo
		if (rotABK)
		{
			if (MrotABrazoK < 50.0f)
			{
				MrotABrazoK += rotKoharuOffset * deltaTime;
			}
			else
			{
				rotABK = false;
			}
		}
		if (!rotABK)
		{
			if (MrotABrazoK > -40.0f)
			{
				MrotABrazoK -= rotKoharuOffset * deltaTime;
			}
			else
			{
				rotABK = true;
			}
		}
		//Brazo
		if (rotBK)
		{
			if (MrotBrazoK < 40.0f)
			{
				MrotBrazoK += rotKoharuOffset * deltaTime;
			}
			else
			{
				rotBK = false;
			}
		}
		if (!rotBK)
		{
			if (MrotBrazoK > -20.0f)
			{
				MrotBrazoK -= rotKoharuOffset * deltaTime;
			}
			else
			{
				rotBK = true;
			}
		}
		//----------------------------------------------------------//
		//Koshiro
		//Antebrazo
		if (rotABKS)
		{
			if (MrotABrazoKS < 30.0f)
			{
				MrotABrazoKS += rotKoshiroOffset * deltaTime;
			}
			else
			{
				rotABKS = false;
			}
		}
		if (!rotABKS)
		{
			if (MrotABrazoKS > -20.0f)
			{
				MrotABrazoKS -= rotKoshiroOffset * deltaTime;
			}
			else
			{
				rotABKS = true;
			}
		}
		//Brazo
		if (rotBKS)
		{
			if (MrotBrazoKS < 40.0f)
			{
				MrotBrazoKS += rotKoshiroOffset * deltaTime;
			}
			else
			{
				rotBKS = false;
			}
		}
		if (!rotBKS)
		{
			if (MrotBrazoKS > -20.0f)
			{
				MrotBrazoKS -= rotKoshiroOffset * deltaTime;
			}
			else
			{
				rotBKS = true;
			}
		}
		//


		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//Inicializacion de las luces de tipo spotlight
		//spotLights[0].SetFlash(glm::vec3(40.0f, 15.0f, -50.0f), glm::vec3(0.0f, -1.0f, 0.0f));

		//spotLights[1].SetFlash(glm::vec3(20.0f, 15.0f, -50.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		//
		//spotLights[2].SetFlash(glm::vec3(0.0f, 15.0f, -50.0f), glm::vec3(0.0f, -1.0f, 0.0f));

		//spotLights[3].SetFlash(glm::vec3(-20.0f, 15.0f, -50.0f), glm::vec3(0.0f, -1.0f, 0.0f));

		//spotLights[4].SetFlash(glm::vec3(-40.0f, 15.0f, -50.0f), glm::vec3(0.0f, -1.0f, 0.0f));

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		//shaderList[0].SetPointLights(pointLights, pointLightCount);
		//shaderList[0].SetSpotLights(spotLights, spotLightCount);

		//Matrices para el coche del previo
		glm::mat4 modelCoche_previo(1.0);
		glm::mat4 modelCofre_previo(1.0);

		//Matrices para el persona principal
		//lily
		glm::mat4 modelaux_cuerpoL(1.0);
		glm::mat4 modelaux_brazoL(1.0);
		glm::mat4 modelaux_brazo2L(1.0);
		glm::mat4 modelaux_piernaL(1.0);
		glm::mat4 modelaux_pierna2L(1.0);
		//------------------------------
		//nero
		glm::mat4 modelaux_cuerpoN(1.0);
		glm::mat4 modelaux_brazoN(1.0);
		glm::mat4 modelaux_brazo2N(1.0);
		//-----------------------------
		//koharu
		glm::mat4 modelaux_cuerpoK(1.0);
		glm::mat4 modelaux_brazoK(1.0);
		glm::mat4 modelaux_brazo2K(1.0);
		glm::mat4 modelaux_piernaK(1.0);
		glm::mat4 modelaux_pierna2K(1.0);
		//-----------------------------
		//koshiro
		glm::mat4 modelaux_cuerpoKS(1.0);
		glm::mat4 modelaux_brazoKS(1.0);
		glm::mat4 modelaux_brazo2KS(1.0);
		glm::mat4 modelaux_piernaKS(1.0);
		glm::mat4 modelaux_pierna2KS(1.0);

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		
		//BLENDING: Util para la tranparencia o Traslucidez
		//Para poder hacer adecuadamente la transparencia de un objeto, se debe de poner
		//primero los modelos a utilizar y despues colocar el mesh en numérico
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		////------------Personajes-----------//
		//// Arturia Pendragon (Lily)
		////Cuerpo
		//model = glm::mat4(1.0);
		//color = glm::vec3(0.0f, 0.0f, 0.3f);
		//model = glm::translate(model, glm::vec3(0.0f, 2.7f, 20.0f + mainWindow.getmovlily()));
		//modelaux_cuerpoL = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Lily_Cuerpo.RenderModel();

		////Brazo Izquierdo
		//model = modelaux_cuerpoL;
		//model = glm::translate(model, glm::vec3(0.49f, 1.61f, -0.1f));
		//model = glm::rotate(model, glm::radians(MrotABrazoL), glm::vec3(-1.0f, 0.0f, 0.0f));
		//modelaux_brazoL = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Lily_AnteBrazo.RenderModel();

		//model = modelaux_brazoL;
		//model = glm::translate(model, glm::vec3(0.77f, -1.02f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, glm::radians((MrotBrazoL)), glm::vec3(-1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Lily_Brazo.RenderModel();

		////Brazo Derecho
		//model = modelaux_cuerpoL;
		//model = glm::translate(model, glm::vec3(-0.49f, 1.61f, -0.1f));
		//model = glm::rotate(model, glm::radians(MrotABrazoL), glm::vec3(1.0f, 0.0f, 0.0f));
		//modelaux_brazo2L = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Lily_AnteBrazo_2.RenderModel();

		//model = modelaux_brazo2L;
		//model = glm::translate(model, glm::vec3(-0.77f, -1.02f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, glm::radians((MrotBrazoL)), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Lily_Brazo_2.RenderModel();

		////Pie Izquierdo
		//model = modelaux_cuerpoL;
		//model = glm::translate(model, glm::vec3(0.3f, -0.4f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotPiernaL)), glm::vec3(-1.0f, 0.0f, 0.0f));
		//modelaux_piernaL = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Lily_Pierna.RenderModel();

		//model = modelaux_piernaL;
		//model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotPieL)), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Lily_Pie.RenderModel();

		////Pie Derecho
		//model = modelaux_cuerpoL;
		//model = glm::translate(model, glm::vec3(-0.3f, -0.4f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotPiernaL)), glm::vec3(1.0f, 0.0f, 0.0f));
		//modelaux_pierna2L = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Lily_Pierna_2.RenderModel();

		//model = modelaux_pierna2L;
		////model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotPieL)), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Lily_Pie_2.RenderModel();

		////Cabeza
		//model = modelaux_cuerpoL;
		//model = glm::translate(model, glm::vec3(0.0f, 2.49f, 0.02f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Lily_Cabeza.RenderModel();
		///* Arturia Pendragon (Lily) final*/
		//// -------------------------------------------------------------------------------------------//
		//
		//// Nero saber
		//// ------------------------------------------------------------------------------------------//
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 5.0f+4.5f, 0.0f));
		//modelaux_cuerpoN = model;
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Nero_Cuerpo.RenderModel();

		//////Micro
		//model = modelaux_cuerpoN;
		//model = glm::translate(model, glm::vec3(0.0f, -4.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		////model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Micro.RenderModel();


		////brazo der
		//model = modelaux_cuerpoN;
		//model = glm::translate(model, glm::vec3(0.65f, 0.35f, -0.02f));
		//model = glm::rotate(model, -30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotABrazoN)), glm::vec3(0.0f, -1.0f, -1.0f));
		//modelaux_brazoN = model;
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Nero_AnteBrazo.RenderModel();

		//model = modelaux_brazoN;
		//model = glm::translate(model, glm::vec3(0.7f, -0.5f, -0.02f));
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		//model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotBrazoN/2)), glm::vec3(0.0f, 1.0f, -1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Nero_Brazo.RenderModel();

		////brazo izq
		//model = modelaux_cuerpoN;
		//model = glm::translate(model, glm::vec3(-0.65f, 0.35f, -0.02f));
		//model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotABrazoN)), glm::vec3(0.0f, 1.0f, 1.0f));
		//modelaux_brazo2N = model;
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Nero_AnteBrazo_2.RenderModel();

		//model = modelaux_brazo2N;
		//model = glm::translate(model, glm::vec3(-0.7f, -0.5f, -0.02f));
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		//model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotBrazoN/2)), glm::vec3(0.0f, -1.0f, -1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Nero_Brazo_2.RenderModel();
		//// Nero saber 
		//// ------------------------------------------------------------------------------------------//

		////koharu
		//// ------------------------------------------------------------------------------------------//

		//////Cuerpo
		//model = glm::mat4(1.0);
		//color = glm::vec3(0.0f, 0.0f, 0.3f);
		//model = glm::translate(model, glm::vec3(4.0f, 5.0f + 3.0f, -5.0f));
		//modelaux_cuerpoK = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Koharu_Cuerpo.RenderModel();

		//////Bateria
		//model = modelaux_cuerpoK;
		//model = glm::translate(model, glm::vec3(2.0f, -3.0f, 5.0f));
		//model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		////model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Bateria.RenderModel();


		////Brazo Izquierdo
		//model = modelaux_cuerpoK;
		//model = glm::translate(model, glm::vec3(0.43f, -0.15f, -0.05f));
		//model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, -60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotABrazoK)), glm::vec3(0.0f, 0.0f, 1.0f));
		//modelaux_brazoK = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Koharu_AnteBrazo.RenderModel();

		//model = modelaux_brazoK;
		//model = glm::translate(model, glm::vec3(0.71f, -0.01f, -0.06f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotBrazoK/2)), glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Koharu_Brazo.RenderModel();

		////Brazo Derecho
		//model = modelaux_cuerpoK;
		//model = glm::translate(model, glm::vec3(-0.43f, -0.15f, -0.05f));
		//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, 60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotABrazoK)), glm::vec3(0.0f, 0.0f, 1.0f));
		//modelaux_brazo2K = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Koharu_AnteBrazo_2.RenderModel();

		//model = modelaux_brazo2K;
		//model = glm::translate(model, glm::vec3(-0.7f, -0.01f, -0.06f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotBrazoK/2)), glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Koharu_Brazo_2.RenderModel();


		////Pie Izquierdo
		//model = modelaux_cuerpoK;
		//model = glm::translate(model, glm::vec3(0.3f, -1.9f, 0.0f));
		//model = glm::rotate(model, -75 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotBrazoK / 2)), glm::vec3(1.0f, 0.0f, 0.0f));
		////model = glm::rotate(model, glm::radians((MrotPierna)), glm::vec3(-1.0f, 0.0f, 0.0f));
		//modelaux_piernaK = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Koharu_Pierna.RenderModel();

		//model = modelaux_piernaK;
		//model = glm::translate(model, glm::vec3(-0.02f, -1.05f, 0.0f));
		//model = glm::rotate(model, 60 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotBrazoK / 2)), glm::vec3(1.0f, 0.0f, 1.0f));
		////model = glm::rotate(model, glm::radians((MrotPie)), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Koharu_Pie.RenderModel();

		////Pie Derecho
		//model = modelaux_cuerpoK;
		//model = glm::translate(model, glm::vec3(-0.3f, -1.9f, 0.0f));
		//model = glm::rotate(model, -75 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		////model = glm::rotate(model, glm::radians((MrotPierna)), glm::vec3(1.0f, 0.0f, 0.0f));
		//modelaux_pierna2K = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Koharu_Pierna_2.RenderModel();

		//model = modelaux_pierna2K;
		////model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.05f, -1.05f, 0.0f));
		//model = glm::rotate(model, 60 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		////model = glm::rotate(model, glm::radians((MrotPie)), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Koharu_Pie_2.RenderModel();

		////// ------------------------------------------------------------------------------------------//
		////
		////Koshiro
		//// ------------------------------------------------------------------------------------------//
		//model = glm::mat4(1.0);
		////color = glm::vec3(0.0f, 0.0f, 0.3f);
		//model = glm::translate(model, glm::vec3(-4.0f, 5.0f + 3.55f, -5.0f));
		//modelaux_cuerpoKS = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////koshiro_Cuerpo.RenderModel();

		//////Guitarra
		//model = modelaux_cuerpoKS;
		//model = glm::translate(model, glm::vec3(0.8f, -1.3f, 0.7f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, -35 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////Guitarra.RenderModel();

		////Brazo Izquierdo
		//model = modelaux_cuerpoKS;
		//model = glm::translate(model, glm::vec3(0.47f, 0.01f, -0.05f));
		//model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//modelaux_brazoKS = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////koshiro_AnteBrazo.RenderModel();

		//model = modelaux_brazoKS;
		//model = glm::translate(model, glm::vec3(0.85f, 0.05f, -0.06f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, glm::radians((MrotBrazoKS/2)), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, -45 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//
		////model = glm::rotate(model, glm::radians((MrotBrazo)), glm::vec3(-1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////koshiro_Brazo.RenderModel();

		////Brazo Derecho
		//model = modelaux_cuerpoKS;
		//model = glm::translate(model, glm::vec3(-0.47f, 0.01f, -0.05f));
		//model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		////model = glm::rotate(model, glm::radians((MrotPie)), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians((MrotABrazoKS)), glm::vec3(0.0f, 0.0f, 1.0f));
		//modelaux_brazo2KS = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////koshiro_AnteBrazo_2.RenderModel();

		//model = modelaux_brazo2KS;
		//model = glm::translate(model, glm::vec3(-0.85f, 0.05f, -0.06f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		////model = glm::rotate(model, -45 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians((MrotBrazoKS/3)), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::rotate(model, -20 * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		//
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////koshiro_Brazo_2.RenderModel();

		////Pie Izquierdo
		//model = modelaux_cuerpoKS;
		//model = glm::translate(model, glm::vec3(0.37f, -2.35f, -0.05f));
		////model = glm::rotate(model, glm::radians((MrotPierna)), glm::vec3(-1.0f, 0.0f, 0.0f));
		//modelaux_piernaKS = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////koshiro_Pierna.RenderModel();

		//model = modelaux_piernaKS;
		//model = glm::translate(model, glm::vec3(-0.02f, -0.85f, 0.0f));
		////model = glm::rotate(model, glm::radians((MrotPie)), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////koshiro_Pie.RenderModel();

		////Pie Derecho
		//model = modelaux_cuerpoKS;
		//model = glm::translate(model, glm::vec3(-0.37f, -2.35f, -0.05f));
		////model = glm::rotate(model, glm::radians((MrotPierna)), glm::vec3(1.0f, 0.0f, 0.0f));
		//modelaux_pierna2KS = model;
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////koshiro_Pierna_2.RenderModel();

		//model = modelaux_pierna2KS;
		////model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.02f, -0.85f, 0.0f));
		////model = glm::rotate(model, glm::radians((MrotPie)), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////koshiro_Pie_2.RenderModel();


		//--------------------------------------------Festival-----------------------------------------//
		//Codigo para las carpas a utilizar
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-60.0f, -8.5f, 140.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Carpa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -8.0f, 122.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.3f, 0.35f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carpa.RenderModel();

		//Codigo para la carga de los modelos de las farolas a utilizar en el festival
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, -1.95f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.85f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, -1.95f, 167.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.85f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(102.0f, -1.95f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.85f, 0.75f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(102.0f, -1.95f, 170.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.85f, 0.75f));
		model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -3.95f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 4.0f, 2.5f));
		//model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Farola1.RenderModel();
		//faro.UseTexture();

		//Piso de cada una de las secciones del festival
		//Modelos correspondientes al puesto de tortas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -1.8f, -30.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera.UseTexture();
		meshList[3]->RenderMesh();

		//Modelos correspondientes al puesto de comida alemana
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -1.8f, 137.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -1.8f, 137.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		//Modelos correspondientes al puesto de tacos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -1.8f, 30.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pasto.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f, -1.8f, 12.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, -1.8f, 30.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f, -1.8f, 30.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, -1.8f, 12.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f, -1.8f, 48.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, -1.8f, 48.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Silla_R.RenderModel();

		//Modelos correspondientes al puesto de bebidas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f, -1.8f, 75.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f, -1.8f, 102.5f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(85.0f, -1.8f, 99.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(85.0f, -1.8f, 86.9f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(85.0f, -1.8f, 74.6f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		//Modelos correspondientes al puesto de mariscos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, -1.8f, 137.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera_2.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(87.0f, -1.8f, 113.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -1.8f, 113.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(68.0f, -1.8f, 113.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, -1.8f, 113.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(87.0f, -1.8f, 133.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(79.0f, -1.8f, 133.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(87.0f, -1.8f, 153.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(79.0f, -1.8f, 153.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Silla_R.RenderModel();

		//Seccion de comida internacional
		//Secc
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.8f, 137.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera_3.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(27.0f, -1.8f, 117.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa_B.RenderModel();


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
		//FoodTrucks
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, -1.95f, 80.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Ftruck1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, -1.95f, 20.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Ftruck2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, -1.95f, 150.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Ftruck3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-125.0f, -1.95f, 80.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Ftruck4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-125.0f, -1.95f, -40.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Ftruck5.RenderModel();

		//Comida Mexicana
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(65.0f, -1.95f, -10.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Comex1.RenderModel();

		//Escenario
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		escenario.RenderModel();

		//Instrumentos
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 1.0f, 10.0f));
		//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		////model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Bateria.RenderModel();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 1.0f, 30.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		////model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Guitarra.RenderModel();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 1.0f, 5.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		////model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Micro.RenderModel();


		//Textura animada de los fuegos artificiales
		//textura con movimiento
		//Importantes porque la variable uniform no podemos modificarla directamente
		//toffsetu += 0.001;
		//toffsetv -= 0.001;
		////para que no se desborde la variable
		////Movimiento en el eje x
		//if (toffsetu > 1.0)
		//	toffsetu = 0.0;
		////Movimiento en el eje y
		//if (toffsetv < 0.0)
		//	toffsetv = 1;

		////Carga de la textura del agua
		//toffset = glm::vec2(0.0f, toffsetv);
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(10.0f, 2.0f, -6.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Firework_G.UseTexture();
		////Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[8]->RenderMesh();

		//toffset = glm::vec2(0.0f, toffsetv);
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(20.0f, 2.0f, -6.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Firework_O.UseTexture();
		////Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[8]->RenderMesh();

		//toffset = glm::vec2(0.0f, toffsetv);
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(30.0f, 2.0f, -6.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Firework_R.UseTexture();
		////Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[8]->RenderMesh();

		//toffset = glm::vec2(0.0f, toffsetv);
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(40.0f, 2.0f, -6.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Firework_P.UseTexture();
		////Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[8]->RenderMesh();

				
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
