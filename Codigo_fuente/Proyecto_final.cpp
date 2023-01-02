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
#include <random>

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

//para el sonido
#include <Irrklang/irrKlang.h>
using namespace irrklang;

const float toRadians = 3.14159265f / 180.0f;

//Variables para poder animar la textura
float toffsetu = 0.0f;
float toffsetv = 0.0f;

//Variables globales para el movimiento del personaje principal
//Lily
//Movimientos
float MrotABrazoL, MrotBrazoL, MrotPiernaL, MrotPieL, MAvanzaLX, MAvanzaLZ, Mrota;
int Cgiros;
//Banderas
bool rotABL, rotBL, rotPL, rotPiesL, AvanzaLX, AvanzaLZ;
float rotLilyOffset;
float rotLilyOffsetM;

//Variables globales para el movimiento de los demás personajes
//Nero
//Movimientos
float MrotABrazoN, MrotBrazoN, MrotPiernaN;
//Banderas
bool rotABN, rotBN;
float rotNeroOffset;
//Koharu
//Movmientos
float MrotABrazoK, MrotBrazoK, MrotPiernaK, MrotPieK;
//Banderas
bool rotABK, rotBK, rotPK, rotPiesK;
float rotKoharuOffset;
//koshiro
//Movimientos
float MrotABrazoKS, MrotBrazoKS, MrotPiernaKS, MrotPieKS;
//Banderas
bool rotABKS, rotBKS, rotPKS, rotPiesKS;
float rotKoshiroOffset;

//Variables externas para la seleccion de cada opcion
extern int bandera;
extern bool ActivadorRL, ActivadorML, ActivadorN, ActivadorKS, ActivadorK,change, luces, esce;

//Variables correspondientes para el ciclo del día y noche
int conta_dia;
float ciclo_dia;

//Variable correspondiente al show de luces en el escenario
int conta_show;
float show = 0.0f;

//Variables para la animación por KeyFrame
//float toffsetu = 0.0f;
//float toffsetv = 0.0f;
float reproduciranimacionN, habilitaranimacionN, reproduciranimacionK, habilitaranimacionK,
guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

//Texturas utilizadas en el festival
Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture Piso_madera;
Texture Piso_madera_2;
Texture Piso_madera_3;
Texture Piso_madera_4;
Texture pasto;
Texture faro;

//Texturas utilizadas en el acuario
Texture Edificio;
Texture Recepcion;
Texture Ventanal;
Texture marmol;
Texture Pared_blanca;
Texture Cristal;
Texture Entradas;
Texture Azul_gradiente;
Texture Techo_acuario;
Texture Fauna_marina;
Texture Informacion1;
Texture Informacion2;
Texture Pared_tunel;

//Texturas animadas
Texture Firework_O;
Texture Firework_P;
Texture Firework_R;
Texture Firework_G;

//----------------------------------------------Modelos para el Festival---------------------------------------//
Model Camino_M;
Model cartel_M;
//Faros
Model Farola;
Model Farola1;
//Carpas
Model Carpa;
//Mobiliario
Model Mesa_B;
Model Silla_R;
Model Reflector;
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
Model FtruckSP;
//Modelos Comida Mexicana
Model Comex1;

//----------------------------------------------Modelos para el Acuario---------------------------------------//
//Modelos de Estructuras
Model Escalera;
Model Acuario_cilindro;
Model Medio_cilindro;
Model Espectaculo;
//Modelos infografias e imagenes
Model Pinguino_inf;
Model Peces_inf;
Model Cangrejo_inf;
Model Orca_inf;
Model Tiburon_inf;
Model EstrellaM_inf1;
Model EstrellaM_inf2;
Model Grap;
//Modelos de peces utilizados

//Modelos de Decoración
Model Calendario_azt;
Model Ballena_img;
Model Pinguino_img;
Model Orca_img;
Model Tiburon_img;
Model Pez_img;
Model No_flash;
Model Piano;
Model Neptuno;
Model HabitatP;
Model coral1;
Model coral2;
Model coral3;
Model coral4;

//----------------------------------------------Modelos de personajes----------------------------------------//
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
//padoru
Model Padoru;
//extras
Model Lucy;
Model vik;
Model elf;
Model Shrek;

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

//PARA INPUT CON KEYFRAMES 
void inputKeyframes(bool* keys);

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

//Creacion de la habitaciones de la recepcion
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
		//-0.5f, -0.5f, -0.5f,	0.02f,  0.26f,		0.0f,	0.0f,	1.0f,
		//0.5f, -0.5f, -0.5f,		0.33f,	0.26f,		0.0f,	0.0f,	1.0f,
		//0.5f,  0.5f, -0.5f,		0.33f,	0.72f,		0.0f,	0.0f,	1.0f,
		//-0.5f,  0.5f, -0.5f,	0.02f,	0.72f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.02f,  0.26f,		-1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.33f,	0.26f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.33f,	0.72f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.02f,	0.72f,		-1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		//-0.5f, -0.5f,  0.5f,	0.5f,  1.0f,		0.0f,	-1.0f,	0.0f,
		//0.5f,  -0.5f,  0.5f,	0.83f,	1.0f,		0.0f,	-1.0f,	0.0f,
		// 0.5f,  -0.5f,  -0.5f,	0.83f,	0.74f,		0.0f,	-1.0f,	0.0f,
		//-0.5f, -0.5f,  -0.5f,	0.5f,	0.74f,		0.0f,	-1.0f,	0.0f,

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
		//-0.5f, -0.5f, -0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,
		//0.5f, -0.5f, -0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,
		//0.5f,  0.5f, -0.5f,		1.0f,	0.5f,		0.0f,	0.0f,	1.0f,
		//-0.5f,  0.5f, -0.5f,	0.0f,	0.5f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f,	0.5f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	0.5f,		-1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		//-0.5f, -0.5f,  0.5f,	0.5f,  1.0f,		0.0f,	-1.0f,	0.0f,
		//0.5f,  -0.5f,  0.5f,	0.83f,	1.0f,		0.0f,	-1.0f,	0.0f,
		// 0.5f,  -0.5f,  -0.5f,	0.83f,	0.74f,		0.0f,	-1.0f,	0.0f,
		//-0.5f, -0.5f,  -0.5f,	0.5f,	0.74f,		0.0f,	-1.0f,	0.0f,

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

//Creacion de las peceras
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
		0.5f, -0.5f,  -0.5f,	1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	1.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		1.0f,	1.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,	1.0f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	1.0f,		-1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	-1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	-1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 //-0.5f, 0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		 //0.5f,  0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	-1.0f,	0.0f,
		 // 0.5f, 0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	-1.0f,	0.0f,
		 //-0.5f, 0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(dado);
}

//Creacion de la habitacion principal del acuario
void CrearPlantabaja()
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
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		//-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,	//0
		//0.5f, -0.5f,  0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,	//1
		//0.5f,  0.5f,  0.5f,		1.0f,	1.0f,		0.0f,	0.0f,	1.0f,	//2
		//-0.5f,  0.5f,  0.5f,	0.0f,	1.0f,		0.0f,	0.0f,	1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	1.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		1.0f,	1.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,	1.0f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	1.0f,		-1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	-1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	-1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 //-0.5f, 0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		 //0.5f,  0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	-1.0f,	0.0f,
		 // 0.5f, 0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	-1.0f,	0.0f,
		 //-0.5f, 0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	-1.0f,	0.0f,

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

//----------------------------------------------KeyFrames----------------------------------------//
bool animacion = false;
//Keyframes nero
float posXNero = 2.0, posYNero = 5.0, posZNero = -3.0;
float	movNero_x = 0.0f, movNero_y = 0.0f, movNero_z = 0.0f;
float giroNero = 0;
//Keyframes koshiro
float posXkoshiro = 2.0, posYkoshiro = 5.0, posZkoshiro = -3.0;
float	movkoshiro_x = 0.0f, movkoshiro_y = 0.0f, movkoshiro_z = 0.0f;
float girokoshiro = 0;

#define MAX_FRAMES 30
int i_max_steps = 90;
int i_curr_steps_N = 10;
int i_curr_steps_K = 30;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movNero_x;		//Variable para PosicionX
	float movNero_y;		//Variable para PosicionY
	float movNero_z;		//Variable para PosicionZ
	float movNero_xInc;		//Variable para IncrementoX
	float movNero_yInc;		//Variable para IncrementoY
	float movNero_zInc;		//Variable para IncrementoZ
	float giroNero;
	float giroNeroInc;
	//koshiro
	float movkoshiro_x;		//Variable para PosicionX
	float movkoshiro_y;		//Variable para PosicionY
	float movkoshiro_z;		//Variable para PosicionZ
	float movkoshiro_xInc;		//Variable para IncrementoX
	float movkoshiro_yInc;		//Variable para IncrementoY
	float movkoshiro_zInc;		//Variable para IncrementoZ
	float girokoshiro;
	float girokoshiroInc;
}FRAME;

FRAME KeyFrameN[MAX_FRAMES];
FRAME KeyFrameK[MAX_FRAMES];
int FrameIndexN = 10;			//introducir datos
int FrameIndexK =25;
bool play = false;
//bool playK = false;
int playIndexN = 0;
int playIndexK = 0;

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndexN);
	printf("frameindex %d\n", FrameIndexK);


	KeyFrameN[FrameIndexN].movNero_x = movNero_x;
	KeyFrameN[FrameIndexN].movNero_y = movNero_y;
	KeyFrameN[FrameIndexN].movNero_z = movNero_z;
	KeyFrameN[FrameIndexN].giroNero = giroNero;

	KeyFrameK[FrameIndexK].movkoshiro_x = movkoshiro_x;
	KeyFrameK[FrameIndexK].movkoshiro_y = movkoshiro_y;
	KeyFrameK[FrameIndexK].movkoshiro_z = movkoshiro_z;
	KeyFrameK[FrameIndexK].girokoshiro = girokoshiro;

	FrameIndexN++;
	FrameIndexK++;
}

void resetElements(void)
{
	//nero
	movNero_x = KeyFrameN[0].movNero_x;
	movNero_y = KeyFrameN[0].movNero_y;
	movNero_z = KeyFrameN[0].movNero_z;
	giroNero = KeyFrameN[0].giroNero;
	//koshiro
	movkoshiro_x = KeyFrameK[0].movkoshiro_x;
	movkoshiro_y = KeyFrameK[0].movkoshiro_y;
	movkoshiro_z = KeyFrameK[0].movkoshiro_z;
	giroNero = KeyFrameK[0].giroNero;
}

void interpolation(void)
{
	KeyFrameN[playIndexN].movNero_xInc = (KeyFrameN[playIndexN + 1].movNero_x - KeyFrameN[playIndexN].movNero_x) / i_max_steps;
	KeyFrameN[playIndexN].movNero_yInc = (KeyFrameN[playIndexN + 1].movNero_y - KeyFrameN[playIndexN].movNero_y) / i_max_steps;
	KeyFrameN[playIndexN].movNero_zInc = (KeyFrameN[playIndexN + 1].movNero_z - KeyFrameN[playIndexN].movNero_z) / i_max_steps;
	KeyFrameN[playIndexN].giroNeroInc = (KeyFrameN[playIndexN + 1].giroNero - KeyFrameN[playIndexN].giroNero) / i_max_steps;

	//koshiro
	KeyFrameK[playIndexK].movkoshiro_xInc = (KeyFrameK[playIndexK + 1].movkoshiro_x - KeyFrameK[playIndexK].movkoshiro_x) / i_max_steps;
	KeyFrameK[playIndexK].movkoshiro_yInc = (KeyFrameK[playIndexK + 1].movkoshiro_y - KeyFrameK[playIndexK].movkoshiro_y) / i_max_steps;
	KeyFrameK[playIndexK].movkoshiro_zInc = (KeyFrameK[playIndexK + 1].movkoshiro_z - KeyFrameK[playIndexK].movkoshiro_z) / i_max_steps;
	KeyFrameK[playIndexK].girokoshiroInc = (KeyFrameK[playIndexK + 1].girokoshiro - KeyFrameK[playIndexK].girokoshiro) / i_max_steps;

}

void animate(void)
{
	//Movimiento del objeto
	if (play)
	{
		if (i_curr_steps_N >= i_max_steps) //end of animation between frames?
		{
			playIndexN++;
			printf("playindexN : %d\n", playIndexN);
			if (playIndexN > FrameIndexN - 2)	//end of total animation?
			{
				printf("Frame indexN= %d\n", FrameIndexN);
				printf("termina anim\n");
				playIndexN = 0;
				//play = false;
			}
			else //Next frame interpolations
			{
				//printf("entro aquí\n");
				i_curr_steps_N = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//printf("se quedó aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation Nero
			movNero_x += KeyFrameN[playIndexN].movNero_xInc;
			movNero_y += KeyFrameN[playIndexN].movNero_yInc;
			movNero_z += KeyFrameN[playIndexN].movNero_zInc;
			giroNero += KeyFrameN[playIndexN].giroNeroInc;
			i_curr_steps_N++;
		}

		if (i_curr_steps_K >= i_max_steps) //end of animation between frames?
		{
			playIndexK++;
			printf("playindexK : %d\n", playIndexK);
			if (playIndexK > FrameIndexK - 2)	//end of total animation?
			{
				printf("Frame indexK= %d\n", FrameIndexK);
				printf("termina anim\n");
				playIndexK = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				//printf("entro aquí\n");
				i_curr_steps_K = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//printf("se quedó aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation koshiro
			movkoshiro_x += KeyFrameK[playIndexK].movkoshiro_xInc;
			movkoshiro_y += KeyFrameK[playIndexK].movkoshiro_yInc;
			movkoshiro_z += KeyFrameK[playIndexK].movkoshiro_zInc;
			girokoshiro += KeyFrameK[playIndexK].girokoshiroInc;
			i_curr_steps_K++;
		}

	}
}


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine) {
		printf("XD");
	}
	//engine->play2D("Gucci Bucket Hat.mp3", true);

	CreateObjects();
	CrearDado();
	CreateShaders();
	CrearRecepcion();
	CrearEntrada();
	CrearPlantabaja();
	CreaTextura();

	//Camara
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 1.5f, 0.5f);

	//Declaracion de texturas
	//Festival
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
	
	//Acuario
	pisoTexture = Texture("Textures/Pisos/Floor_texture.tga");
	pisoTexture.LoadTextureA();
	marmol = Texture("Textures/Pisos/marmol.tga");
	marmol.LoadTextureA();
	Recepcion = Texture("Textures/Paredes/Recepcion_textura.tga");
	Recepcion.LoadTextureA();
	Ventanal = Texture("Textures/Paredes/Ventana.tga");
	Ventanal.LoadTextureA();
	Cristal = Texture("Textures/cilindro_textura.tga");
	Cristal.LoadTextureA();
	Entradas = Texture("Textures/Entradas.tga");
	Entradas.LoadTextureA();
	Edificio = Texture("Textures/Build_texture.tga");
	Edificio.LoadTextureA();
	Pared_blanca = Texture("Textures/Pared_blanca.tga");
	Pared_blanca.LoadTextureA();
	Azul_gradiente = Texture("Textures/Azul_gradiente.tga");
	Azul_gradiente.LoadTextureA();
	Techo_acuario = Texture("Textures/Techo_acuario.tga");
	Techo_acuario.LoadTextureA();
	Fauna_marina = Texture("Textures/Fauna_marina.tga");
	Fauna_marina.LoadTextureA();
	Informacion1 = Texture("Textures/Informacion.tga");
	Informacion1.LoadTextureA();
	Informacion2 = Texture("Textures/Informacion_2.tga");
	Informacion2.LoadTextureA();
	Pared_tunel = Texture("Textures/Pared_tunel.tga");
	Pared_tunel.LoadTextureA();

	//Texturas animadas
	//Firework_G = Texture("Textures/Animadas/Firework_green.tga");
	//Firework_G.LoadTextureA();
	//Firework_O = Texture("Textures/Animadas/Firework_orange.tga");
	//Firework_O.LoadTextureA();
	//Firework_P = Texture("Textures/Animadas/Firework_purple.tga");
	//Firework_P.LoadTextureA();
	//Firework_R = Texture("Textures/Animadas/Firework_red.tga");
	//Firework_R.LoadTextureA();


	//Declaracion de modelos utilizados
	//Festival
	cartel_M = Model();
	cartel_M.LoadModel("Models/Construccion/maistro.obj");
	/*Farola = Model();
	Farola.LoadModel("Models/Farola_2/Farola_2.obj");
	Carpa = Model();
	Carpa.LoadModel("Models/Carpa/Carpa.obj");
	Farola1 = Model();
	Farola1.LoadModel("Models/Farola_3/farola_3.obj");
	Silla_R = Model();
	Silla_R.LoadModel("Models/Silla/Silla_roja.obj");
	Mesa_B = Model();
	Mesa_B.LoadModel("Models/Mesa/Mesa_blanca.obj");*/
	Reflector = Model();
	Reflector.LoadModel("Models/Reflector/Reflector.obj");

	//FoodTrucks/Comida Mex
	//Comida Mexicana
	/*Comex1 = Model();
	Comex1.LoadModel("Models/Comida Mex/Puesto1/comex1.obj");
	Ftruck1 = Model();
	Ftruck1.LoadModel("Models/FoodTrucks/Ft1/ft1.obj");
	Ftruck2 = Model();
	Ftruck2.LoadModel("Models/FoodTrucks/Ft2/ft2.obj");
	Ftruck3 = Model();
	Ftruck3.LoadModel("Models/FoodTrucks/Ft3/yatai.obj");
	Ftruck4 = Model();
	Ftruck4.LoadModel("Models/FoodTrucks/Ft4/gerobak.obj");
	Ftruck5 = Model();
	Ftruck5.LoadModel("Models/FoodTrucks/Ft5/ft5.obj");
	FtruckSP = Model();
	FtruckSP.LoadModel("Models/FoodTrucks/Especial/ftsp.obj");*/

	//Escenario
	//escenario = Model();
	//escenario.LoadModel("Models/Escenario/Escenario.obj");
	/*Bateria = Model();
	Bateria.LoadModel("Models/Escenario/Bateria.obj");
	Guitarra = Model();
	Guitarra.LoadModel("Models/Escenario/guitarra_uno.obj");
	Micro = Model();
	Micro.LoadModel("Models/Escenario/Micro.obj");*/

	//Acuario
	//Infografias e imagenes
	//Pinguino_inf = Model();
	//Pinguino_inf.LoadModel("Models/Pinguinos/Pinguino_inf.obj");
	//Cangrejo_inf = Model();
	//Cangrejo_inf.LoadModel("Models/Cangrejo/Cangrejo_inf.obj");
	//Orca_inf = Model();
	//Orca_inf.LoadModel("Models/Orcas/Orca_inf.obj");
	//Tiburon_inf = Model();
	//Tiburon_inf.LoadModel("Models/Tiburones/Tiburon_inf.obj");
	//Peces_inf = Model();
	//Peces_inf.LoadModel("Models/Peces/Peces_inf.obj");
	//EstrellaM_inf1 = Model();
	//EstrellaM_inf1.LoadModel("Models/Estrella de mar/estrellasinfo.obj");
	//EstrellaM_inf2 = Model();
	//EstrellaM_inf2.LoadModel("Models/Estrella de mar/estrellasinfo2.obj");
	//Grap = Model();
	//Grap.LoadModel("Models/Carteles/Grap.obj");

	//coral1 = Model();
	//coral1.LoadModel("Models/Corales/11-exported.obj");
	//coral2 = Model();
	//coral2.LoadModel("Models/Corales/mesh-90.obj");
	//coral3 = Model();
	//coral3.LoadModel("Models/Corales/coralf.obj");
	//coral4 = Model();
	//coral4.LoadModel("Models/Corales/corals.obj");

	//Calendario_azt = Model();
	//Calendario_azt.LoadModel("Models/Carteles/Calendario_azteca.obj");
	Pinguino_img = Model();
	Pinguino_img.LoadModel("Models/Carteles/Pinguino_imagen.obj");
	Ballena_img = Model();
	Ballena_img.LoadModel("Models/Carteles/Ballena_imagen.obj");
	Orca_img = Model();
	Orca_img.LoadModel("Models/Carteles/Orca_imagen.obj");
	Tiburon_img = Model();
	Tiburon_img.LoadModel("Models/Carteles/Tiburon_imagen.obj");
	Pez_img = Model();
	Pez_img.LoadModel("Models/Carteles/Pez_imagen.obj");
	No_flash = Model();
	No_flash.LoadModel("Models/Carteles/No_fotos.obj");
	//Estructuras
	Acuario_cilindro = Model();
	Acuario_cilindro.LoadModel("Models/Acuario_cilindro/Acuario_cilindro.obj");
	Medio_cilindro = Model();
	Medio_cilindro.LoadModel("Models/Acuario_cilindro/Medio_cilindro.obj");
	/*Espectaculo = Model();
	Espectaculo.LoadModel("Models/Decoraciones/espec.obj");
	HabitatP = Model();
	HabitatP.LoadModel("Models/Habitat/Habitat.obj");*/

	//Escaleras
	Escalera = Model();
	Escalera.LoadModel("Models/Escaleras/Escaleras.obj");
	//Decoracion
	/*Piano = Model();
	Piano.LoadModel("Models/Decoraciones/piano.obj");
	Neptuno = Model();
	Neptuno.LoadModel("Models/Decoraciones/neptuno.obj");*/


	////Artoria Pendragon (Lily)
	/*Lily_AnteBrazo = Model();
	Lily_AnteBrazo.LoadModel("Models/Lily/Lily_AnteBrazo_1.obj");
	Lily_AnteBrazo_2 = Model();
	Lily_AnteBrazo_2.LoadModel("Models/Lily/Lily_AnteBrazo_2.obj");
	Lily_Brazo = Model();
	Lily_Brazo.LoadModel("Models/Lily/Lily_Brazo_1.obj");
	Lily_Brazo_2 = Model();
	Lily_Brazo_2.LoadModel("Models/Lily/Lily_Brazo_2.obj");
	Lily_Pierna = Model();
	Lily_Pierna.LoadModel("Models/Lily/Lily_Pierna_1.obj");
	Lily_Pierna_2 = Model();
	Lily_Pierna_2.LoadModel("Models/Lily/Lily_Pierna_2.obj");
	Lily_Pie = Model();
	Lily_Pie.LoadModel("Models/Lily/LilY_Pie_1.obj");
	Lily_Pie_2 = Model();
	Lily_Pie_2.LoadModel("Models/Lily/Lily_Pie_2.obj");
	Lily_Cabeza = Model();
	Lily_Cabeza.LoadModel("Models/Lily/Lily_Cabeza.obj");
	Lily_Cuerpo = Model();
	Lily_Cuerpo.LoadModel("Models/Lily/Lily_Cuerpo.obj");*/

	////nero
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

	////koshiro
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

	////Koharu
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
	////padoru
	//Padoru = Model();
	//Padoru.LoadModel("Models/PAdoru/Nero_Padoru.obj");

	////extras
	//Lucy = Model();
	//Lucy.LoadModel("Models/Lucy/Lucy.obj");
	//vik = Model();
	//vik.LoadModel("Models/vik/vik.obj");
	//elf = Model();
	//elf.LoadModel("Models/elf/elf.obj");
	//Shrek = Model();
	//Shrek.LoadModel("Models/Shrek/Shrek.obj");

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
	pointLights[0] = PointLight(0.0f, 0.0f, 0.0f,
		0.5f, 0.5f,
		20.0f, 1.5f, -30.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[1] = PointLight(0.0f, 0.0f, 0.0f,
		0.5f, 0.5f,
		0.0f, 1.5f, -30.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[2] = PointLight(0.0f, 0.0f, 0.0f,
		0.5f, 0.5f,
		-20.0f, 1.5f, -30.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//Contador de luces del tipo spotlight
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.2f, 1.0f,
		5.0f, 10.0f, 0.0f,
		-15.0f, -5.0f, -1.0f,
		1.0f, 0.01f, 0.01f,
		15.0f);
	spotLightCount++;

	spotLights[1] = SpotLight(1.0f, 0.0f, 1.0f,
		0.2f, 1.0f,
		5.0f, 10.0f, 0.0f,
		-15.0f, -5.0f, -1.0f,
		1.0f, 0.01f, 0.01f,
		15.0f);
	spotLightCount++;

	spotLights[2] = SpotLight(0.0f, 0.5f, 0.5f,
		0.2f, 1.0f,
		5.0f, 10.0f, 0.0f,
		-15.0f, -5.0f, -1.0f,
		1.0f, 0.01f, 0.01f,
		15.0f);
	spotLightCount++;

	spotLights[3] = SpotLight(0.5f, 0.5f, 0.0f,
		0.2f, 1.0f,
		5.0f, 10.0f, 0.0f,
		-15.0f, -5.0f, -1.0f,
		1.0f, 0.01f, 0.01f,
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
	Mrota = 0.0f;
	rotLilyOffset = 1.0f;
	rotLilyOffsetM = 0.1f;
	MAvanzaLX = 0.0f;
	MAvanzaLZ = 0.0f;
	AvanzaLX = true;
	AvanzaLZ = false;
	rotABL = true;
	rotBL = true;
	rotPL = true;
	Cgiros = 0;
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

	glm::vec3 posNero = glm::vec3(2.0f, 0.0f, 0.0f);
	//glm::vec3 poskoshiro = glm::vec3(-4.0f, 5.0f + 3.55f, -5.0f);kjh
	
	//----------------------------------------------KeyFrames de los personajes----------------------------------------//
	//Nero
	KeyFrameN[0].movNero_x = 0.0f;
	KeyFrameN[0].movNero_y = 0.0f;
	KeyFrameN[0].movNero_z = 0.0f;
	KeyFrameN[0].giroNero = 0.0f;


	KeyFrameN[1].movNero_x = 1.0f;
	KeyFrameN[1].movNero_y = 0.0f;
	KeyFrameN[1].movNero_z = 2.0f;
	KeyFrameN[1].giroNero = 0.0f;


	KeyFrameN[2].movNero_x = 2.0f;
	KeyFrameN[2].movNero_y = 0.0f;
	KeyFrameN[2].movNero_z = 0.0f;
	KeyFrameN[2].giroNero = 0.0f;


	KeyFrameN[3].movNero_x = 3.0f;
	KeyFrameN[3].movNero_y = 0.0f;
	KeyFrameN[3].movNero_z = -2.0f;
	KeyFrameN[3].giroNero = -180.0f;

	KeyFrameN[4].movNero_x = 3.0f;
	KeyFrameN[4].movNero_y = 2.0f;
	KeyFrameN[4].movNero_z = 0.0f;
	KeyFrameN[4].giroNero = -180;

	KeyFrameN[5].movNero_x = 3.0f;
	KeyFrameN[5].movNero_y = 0.0f;
	KeyFrameN[5].movNero_z = 0.0f;
	KeyFrameN[5].giroNero = 180.0f;

	KeyFrameN[6].movNero_x = 3.0f;
	KeyFrameN[6].movNero_y = 0.0f;
	KeyFrameN[6].movNero_z = -2.0f;
	KeyFrameN[6].giroNero = 180.0f;

	KeyFrameN[7].movNero_x = 2.0f;
	KeyFrameN[7].movNero_y = 0.0f;
	KeyFrameN[7].movNero_z = 0.0f;
	KeyFrameN[7].giroNero = 0.f;

	KeyFrameN[8].movNero_x = 1.0f;
	KeyFrameN[8].movNero_y = 0.0f;
	KeyFrameN[8].movNero_z = 2.0f;
	KeyFrameN[8].giroNero = 0.0f;

	KeyFrameN[9].movNero_x = 0.0f;
	KeyFrameN[9].movNero_y = 0.0f;
	KeyFrameN[9].movNero_z = 0.0f;
	KeyFrameN[9].giroNero = 0.0f;

	//Koshiro

	KeyFrameK[0].movkoshiro_x = 0.0f;
	KeyFrameK[0].movkoshiro_y = 0.0f;
	KeyFrameK[0].movkoshiro_z = 0.0f;
	KeyFrameK[0].girokoshiro = 0.0f;


	KeyFrameK[1].movkoshiro_x = 0.0f;
	KeyFrameK[1].movkoshiro_y = 0.0f;
	KeyFrameK[1].movkoshiro_z = 1.0f;
	KeyFrameK[1].girokoshiro = 0.0f;


	KeyFrameK[2].movkoshiro_x = 0.0f;
	KeyFrameK[2].movkoshiro_y = 0.0f;
	KeyFrameK[2].movkoshiro_z = 2.0f;
	KeyFrameK[2].girokoshiro = 0.0f;


	KeyFrameK[3].movkoshiro_x = 0.0f;
	KeyFrameK[3].movkoshiro_y = 0.0f;
	KeyFrameK[3].movkoshiro_z = 3.0f;
	KeyFrameK[3].girokoshiro = 0.0f;

	KeyFrameK[4].movkoshiro_x = 0.0f;
	KeyFrameK[4].movkoshiro_y = 0.0f;
	KeyFrameK[4].movkoshiro_z = 4.0f;
	KeyFrameK[4].girokoshiro = 0;

	KeyFrameK[5].movkoshiro_x = 0.0f;
	KeyFrameK[5].movkoshiro_y = 0.0f;
	KeyFrameK[5].movkoshiro_z = 6.0f;
	KeyFrameK[5].girokoshiro = 0.0f;

	KeyFrameK[6].movkoshiro_x = 0.0f;
	KeyFrameK[6].movkoshiro_y = 0.0f;
	KeyFrameK[6].movkoshiro_z = 8.0f;
	KeyFrameK[6].girokoshiro = 0.0f;

	KeyFrameK[7].movkoshiro_x = 0.0f;
	KeyFrameK[7].movkoshiro_y = 0.0f;
	KeyFrameK[7].movkoshiro_z =8.0f;
	KeyFrameK[7].girokoshiro = 90.0f;

	KeyFrameK[8].movkoshiro_x = 1.0f;
	KeyFrameK[8].movkoshiro_y = 1.0f;
	KeyFrameK[8].movkoshiro_z = 8.0f;
	KeyFrameK[8].girokoshiro = 90.0f;

	KeyFrameK[9].movkoshiro_x = 2.0f;
	KeyFrameK[9].movkoshiro_y = 0.0f;
	KeyFrameK[9].movkoshiro_z = 8.0f;
	KeyFrameK[9].giroNero = 90.0f;

	KeyFrameK[10].movkoshiro_x = 3.0f;
	KeyFrameK[10].movkoshiro_y = 0.0f;
	KeyFrameK[10].movkoshiro_z = 8.0f;
	KeyFrameK[10].giroNero = 90.0f;

	KeyFrameK[11].movkoshiro_x = 4.0f;
	KeyFrameK[11].movkoshiro_y = 0.0f;
	KeyFrameK[11].movkoshiro_z = 8.0f;
	KeyFrameK[11].giroNero = 90.0f;

	KeyFrameK[12].movkoshiro_x = 5.0f;
	KeyFrameK[12].movkoshiro_y = 0.0f;
	KeyFrameK[12].movkoshiro_z = 8.0f;
	KeyFrameK[12].giroNero = 90.0f;

	KeyFrameK[13].movkoshiro_x = 6.0f;
	KeyFrameK[13].movkoshiro_y = 0.0f;
	KeyFrameK[13].movkoshiro_z = 8.0f;
	KeyFrameK[13].giroNero = 90.0f;

	KeyFrameK[14].movkoshiro_x = 7.0f;
	KeyFrameK[14].movkoshiro_y = 1.0f;
	KeyFrameK[14].movkoshiro_z = 8.0f;
	KeyFrameK[14].giroNero = -180.0f;

	KeyFrameK[15].movkoshiro_x = 6.0f;
	KeyFrameK[15].movkoshiro_y = 0.0f;
	KeyFrameK[15].movkoshiro_z = 8.0f;
	KeyFrameK[15].giroNero = -180.0f;

	KeyFrameK[16].movkoshiro_x = 5.0f;
	KeyFrameK[16].movkoshiro_y = 0.0f;
	KeyFrameK[16].movkoshiro_z = 8.0f;
	KeyFrameK[16].giroNero = -180.0f;

	KeyFrameK[17].movkoshiro_x = 4.0f;
	KeyFrameK[17].movkoshiro_y = 0.0f;
	KeyFrameK[17].movkoshiro_z = 8.0f;
	KeyFrameK[17].giroNero = -180.0f;

	KeyFrameK[18].movkoshiro_x = 3.0f;
	KeyFrameK[18].movkoshiro_y = 0.0f;
	KeyFrameK[18].movkoshiro_z = 8.0f;
	KeyFrameK[18].giroNero = -180.0f;

	KeyFrameK[19].movkoshiro_x = 2.0f;
	KeyFrameK[19].movkoshiro_y = 0.0f;
	KeyFrameK[19].movkoshiro_z = 8.0f;
	KeyFrameK[19].giroNero = -180.0f;

	KeyFrameK[20].movkoshiro_x = 1.0f;
	KeyFrameK[20].movkoshiro_y = 1.0f;
	KeyFrameK[20].movkoshiro_z = 8.0f;
	KeyFrameK[20].giroNero = -180.0f;

	KeyFrameK[21].movkoshiro_x = 0.0f;
	KeyFrameK[21].movkoshiro_y = 0.0f;
	KeyFrameK[21].movkoshiro_z = 8.0f;
	KeyFrameK[21].giroNero = -180.0f;

	KeyFrameK[22].movkoshiro_x = 0.0f;
	KeyFrameK[22].movkoshiro_y = 0.0f;
	KeyFrameK[22].movkoshiro_z = 8.0f;
	KeyFrameK[22].giroNero = 90.0f;

	KeyFrameK[23].movkoshiro_x = 0.0f;
	KeyFrameK[23].movkoshiro_y = 0.0f;
	KeyFrameK[23].movkoshiro_z = 4.0f;
	KeyFrameK[23].giroNero = 0.0f;

	KeyFrameK[24].movkoshiro_x = 0.0f;
	KeyFrameK[24].movkoshiro_y = 0.0f;
	KeyFrameK[24].movkoshiro_z = 0.0f;
	KeyFrameK[24].giroNero = 0.0f;

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		
		//para keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Camaras
		/*if (change) {
			if (Mrota < 90.0f) {
				camera = Camera(glm::vec3(MAvanzaLZ, 8.0f, 10.5f + MAvanzaLX), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f - Mrota, -35.0f, 3.0f, 0.5f);
			}
			else if (Mrota > 90.0f && Mrota < 180.0f) {
				camera = Camera(glm::vec3(-10.0f + MAvanzaLZ, 8.0f, 20.0f + MAvanzaLX), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f - Mrota, -35.0f, 3.0f, 0.5f);
			}
			else if (Mrota > 180.0f && Mrota <270.0f) {
				camera = Camera(glm::vec3(0.0f + MAvanzaLZ, 8.0f, 30.0f + MAvanzaLX), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f - Mrota, -35.0f, 3.0f, 0.5f);
			}
			else if (Mrota > 270.0f && Mrota < 360.0f) {
				camera = Camera(glm::vec3(10.0f + MAvanzaLZ, 8.0f, 20.0f + MAvanzaLX), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f - Mrota, -35.0f, 3.0f, 0.5f);
			}

		}
		if (!change) {
				camera = Camera(glm::vec3(-150.0f, 150.0f, -150.0f), glm::vec3(0.0f, 1.0f, 0.0f), 55.0f, -45.0f, 1.5f, 0.5f);
		}*/
		

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
		//mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		//	ciclo_dia, 1.0,//Va a servir para manejar el ciclo dia y noche
		//	1.0f, 0.0f, -1.0f);

		mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
			0.1, 1.0,//Va a servir para manejar el ciclo dia y noche
			1.0f, 0.0f, -1.0f);

		
		//----------------------------------------------Animaciones----------------------------------------//
		//Recorrido de Lily por el festival
		if (AvanzaLX && !AvanzaLZ && Cgiros == 0 && ActivadorRL)
		{
			if (MAvanzaLX < 80.0f)
			{
				MAvanzaLX += rotLilyOffsetM * deltaTime;
			}
			else
			{
				AvanzaLX = false;
				Cgiros = 1;
			}
		}
		if (!AvanzaLX && !AvanzaLZ && Cgiros == 1)
		{
			if (Mrota < 90.0f)
			{
				Mrota += (rotLilyOffsetM*2) * deltaTime;
			}
			else
			{
				AvanzaLZ = true;
			}
		}
		if (!AvanzaLX && AvanzaLZ && Cgiros == 1)
		{
			if (MAvanzaLZ < 45.0f)
			{
				MAvanzaLZ += rotLilyOffsetM * deltaTime;
			}
			else
			{
				AvanzaLZ = false;
				Cgiros = 2;
			}
		}
		if (!AvanzaLX && !AvanzaLZ && Cgiros == 2)
		{
			if (Mrota < 180.0f)
			{
				Mrota += (rotLilyOffsetM * 2) * deltaTime;
			}
			else
			{
				AvanzaLX = true;
			}
		}

		if (AvanzaLX && !AvanzaLZ && Cgiros == 2)
		{
			if (MAvanzaLX > -85.0f)
			{
				MAvanzaLX -= rotLilyOffsetM * deltaTime;
			}
			else
			{
				AvanzaLX = false;
				Cgiros = 3;
			}
		}

		if (!AvanzaLX && !AvanzaLZ && Cgiros == 3)
		{
			if (Mrota < 270.0f)
			{
				Mrota += (rotLilyOffsetM * 2) * deltaTime;
			}
			else
			{
				AvanzaLZ = true;
			}
		}
		if (!AvanzaLX && AvanzaLZ && Cgiros == 3)
		{
			if (MAvanzaLZ > -75.0f)
			{
				MAvanzaLZ -= rotLilyOffsetM * deltaTime;
			}
			else
			{
				AvanzaLZ = false;
				Cgiros = 4;
			}
		}
		if (!AvanzaLX && !AvanzaLZ && Cgiros == 4)
		{
			if (Mrota < 360.0f)
			{
				Mrota += (rotLilyOffsetM * 2) * deltaTime;
			}
			else
			{
				AvanzaLX = true;
				Cgiros = 4;
				Mrota = 0.0f;
			}
		}
		if (AvanzaLX && !AvanzaLZ && Cgiros == 4)
		{
			if (MAvanzaLX < 80.0f)
			{
				MAvanzaLX += rotLilyOffsetM * deltaTime;
			}
			else
			{
				AvanzaLX = false;
				Cgiros = 5;
			}
		}
		if (!AvanzaLX && !AvanzaLZ && Cgiros == 5)
		{
			if (Mrota < 90.0f)
			{
				Mrota += (rotLilyOffsetM * 2) * deltaTime;
			}
			else
			{
				AvanzaLZ = true;
			}
		}
		if (!AvanzaLX && AvanzaLZ && Cgiros == 5)
		{
			if (MAvanzaLZ < 0.0f)
			{
				MAvanzaLZ += rotLilyOffsetM * deltaTime;
			}
			else
			{
				AvanzaLZ = false;
				Cgiros = 6;
			}
		}
		if (!AvanzaLX && !AvanzaLZ && Cgiros == 6)
		{
			if (Mrota < 180.0f)
			{
				Mrota += (rotLilyOffsetM * 2) * deltaTime;
			}
			else
			{
				AvanzaLX = true;
			}
		}
		if (AvanzaLX && !AvanzaLZ && Cgiros == 6)
		{
			if (MAvanzaLX > 0.0f)
			{
				MAvanzaLX -= rotLilyOffsetM * deltaTime;
			}
			else
			{
				AvanzaLX = false;
				Cgiros = 7;
			}
		}
		if (!AvanzaLX && !AvanzaLZ && Cgiros == 7)
		{
			if (Mrota > -0.0f)
			{
				Mrota -= (rotLilyOffsetM * 2) * deltaTime;
			}
			else
			{
				AvanzaLX = true;
				Cgiros = 0;
				ActivadorRL = false; 
				ActivadorML = false;
			}
		}
		//movimiento en antebrazos
		if (rotABL && ActivadorML)
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
		if (!rotABL && ActivadorML)
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
		//Movimiento en brazos
		if (rotBL && ActivadorML)
		{
			if (MrotBrazoL < 30.0f)
			{
				MrotBrazoL += rotLilyOffset / 2 * deltaTime;
			}
			else
			{
				rotBL = false;
			}
		}
		if (!rotBL && ActivadorML)
		{
			if (MrotBrazoL > -20.0f)
			{
				MrotBrazoL -= rotLilyOffset / 2 * deltaTime;
			}
			else
			{
				rotBL = true;
			}
		}
		//Movimiento en piernas
		if (rotPL && ActivadorML)
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
		if (!rotPL && ActivadorML)
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
		//Movimiento en pies
		if (rotPiesL && ActivadorML)
		{
			if (MrotPieL < 20.0f)
			{
				MrotPieL += rotLilyOffset / 2 * deltaTime;
			}
			else
			{
				rotPiesL = false;
			}
		}
		if (!rotPiesL && ActivadorML)
		{
			if (MrotPieL > 0.0f)
			{
				MrotPieL -= rotLilyOffset / 2 * deltaTime;
			}
			else
			{
				rotPiesL = true;
			}
		}
		//Animación de Nero
		//Movimiento en el Antebrazo
		if (rotABN && ActivadorN)
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
		if (!rotABN && ActivadorN)
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
		//Movimiento en el Brazo
		if (rotBN && ActivadorN)
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
		if (!rotBN && ActivadorN)
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
		//Animación de Koharu
		//Movmiento en el Antebrazo
		if (rotABK && ActivadorK)
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
		if (!rotABK && ActivadorK)
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
		//Movimiento en el Brazo
		if (rotBK && ActivadorK)
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
		if (!rotBK && ActivadorK)
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
		//Animación Koshiro
		//Movimiento en el Antebrazo
		if (rotABKS && ActivadorKS)
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
		if (!rotABKS && ActivadorKS)
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
		//Movimiento en el Brazo
		if (rotBKS && ActivadorKS)
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
		if (!rotBKS && ActivadorKS)
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
		//Movimiento en las piernas
		if (rotPKS && ActivadorKS)
		{
			if (MrotPiernaKS < 20.0f)
			{
				MrotPiernaKS += rotKoshiroOffset * deltaTime;
			}
			else
			{
				rotPKS = false;
			}
		}
		if (!rotPKS && ActivadorKS)
		{
			if (MrotPiernaKS > -20.0f)
			{
				MrotPiernaKS -= rotKoshiroOffset * deltaTime;
			}
			else
			{
				rotPKS = true;
			}
		}
		//Movimineto en los pies
		if (rotPiesKS && ActivadorKS)
		{
			if (MrotPieKS < 20.0f)
			{
				MrotPieKS += rotKoshiroOffset / 2 * deltaTime;
			}
			else
			{
				rotPiesKS = false;
			}
		}
		if (!rotPiesKS && ActivadorKS)
		{
			if (MrotPieKS > 0.0f)
			{
				MrotPieKS -= rotKoshiroOffset / 2 * deltaTime;
			}
			else
			{
				rotPiesKS = true;
			}
		}

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

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		//shaderList[0].SetSpotLights(spotLights, spotLightCount);
		// 
		//Inicializacion de las luces de tipo spotlight para hacer el show de luces
		//Inicialización de las luces de tipo pointlghts
		//----------------------------------------------Ciclo Día y Noche----------------------------------------//
		//if (ciclo_dia < 0.55) {
		//	shaderList[0].SetPointLights(pointLights, pointLightCount);
		//}
		//else {
		//	shaderList[0].SetPointLights(pointLights, 0);
		//}
		//----------------------------------------------Luces en el Festival----------------------------------------//
		if (luces) {
			if (conta_show == 1) {
				show = static_cast <float> (rand() % 24) / 4;
				if (show <= 1.0f) {
					shaderList[0].SetSpotLights(spotLights, spotLightCount - 2);
					spotLights[0].SetFlash(glm::vec3(10.0f, 7.7f, 10.0f), glm::vec3(-0.8f, 0.0f, -0.8f));
				}
				else if (show > 1.0f && show <= 2.0f) {
					shaderList[0].SetSpotLights(spotLights, spotLightCount - 2);
					spotLights[1].SetFlash(glm::vec3(-10.0f, 7.7f, 10.0f), glm::vec3(0.8f, 0.0f, -0.8f));
				}
				else if (show > 2.0f && show <= 3.0f) {
					shaderList[0].SetSpotLights(spotLights, spotLightCount - 2);
					spotLights[2].SetFlash(glm::vec3(10.0f, 6.7f, -10.0f), glm::vec3(-0.8f, 0.0f, 0.8f));
				}
				else if (show > 3.0f && show <= 4.0f) {
					shaderList[0].SetSpotLights(spotLights, spotLightCount - 2);
					spotLights[3].SetFlash(glm::vec3(-10.0f, 6.7f, -12.0f), glm::vec3(0.8f, 0.0f, 0.8f));
				}
				else if (show > 4.0f && show <= 5.0f) {
					shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
					spotLights[1].SetFlash(glm::vec3(-10.0f, 7.7f, 10.0f), glm::vec3(0.8f, 0.0f, -0.8f));
					spotLights[3].SetFlash(glm::vec3(-10.0f, 6.7f, -12.0f), glm::vec3(0.8f, 0.0f, 0.8f));
				}
				else if (show > 5.0f && show <= 6.0f) {
					shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
					spotLights[0].SetFlash(glm::vec3(10.0f, 7.7f, 10.0f), glm::vec3(-0.8f, 0.0f, -0.8f));
					spotLights[2].SetFlash(glm::vec3(10.0f, 6.7f, -10.0f), glm::vec3(-0.8f, 0.0f, 0.8f));
				}
			}
			if (conta_show == 35) {
				conta_show = 0;
			}
			conta_show += 1;
		}
		if (!luces) {
			shaderList[0].SetSpotLights(spotLights, 0);
		}
		
		//Luces de la recepcion del acuario
		if (camera.getCameraPosition().y >= 0) {
			//Recepcion
			if ((camera.getCameraPosition().x >= -60 && camera.getCameraPosition().x <= 60)
				&& (camera.getCameraPosition().z <= 200  && camera.getCameraPosition().z >= -259))
			{
				pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,
					0.5f, 0.5f,
					0.0f, 10.0f, -185.0f,
					0.2f, 0.05f, 0.001f);
				pointLightCount++;

				pointLights[1] = PointLight(1.0f, 1.0f, 1.0f,
					0.5f, 0.5f,
					0.0f, 10.0f, -225.0f,
					0.2f, 0.05f, 0.001f);
				pointLightCount++;
			}
			//Escaleras
			if ((camera.getCameraPosition().x >= -60 && camera.getCameraPosition().x <= 60)
				&& (camera.getCameraPosition().z <= -260 && camera.getCameraPosition().z >= -400))
			{
				pointLights[0] = PointLight(0.1f, 0.0f, 0.8f,
					0.2f, 0.5f,
					0.0f, 10.0f, -300.0f,
					0.2f, 0.01f, 0.0001f);
				pointLightCount++;

				pointLights[1] = PointLight(0.9f, 0.0f, 0.0f,
					0.2f, 0.5f,
					-20.0f, 10.0f, -375.0f,
					0.2f, 0.01f, 0.0001f);
				pointLightCount++;

				pointLights[2] = PointLight(0.5f, 0.2f, 0.8f,
					0.2f, 0.5f,
					20.0f, 10.0f, -375.0f,
					0.2f, 0.01f, 0.0001f);
				pointLightCount++;
			}
		}
		if (camera.getCameraPosition().y <= 0) {
			if ((camera.getCameraPosition().x >= 60 && camera.getCameraPosition().x <= 160)
				&& (camera.getCameraPosition().z <= 200 && camera.getCameraPosition().z >= -400))
			{
				pointLights[0] = PointLight(0.4f, 0.6f, 1.0f,
					0.2f, 0.5f,
					140.0f, 5.0f, -320.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[1] = PointLight(0.1f, 0.2f, 1.0f,
					0.2f, 0.5f,
					140.0f, 5.0f, -180.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[2] = PointLight(0.4f, 0.6f, 1.0f,
					0.2f, 0.5f,
					0.0f, 5.0f, -150.0f,
					0.2f, 0.01f, 0.001f);
				pointLightCount++;
			}

			if ((camera.getCameraPosition().x >= -60 && camera.getCameraPosition().x <= 60)
				&& (camera.getCameraPosition().z <= -120 && camera.getCameraPosition().z >= -250))
			{
				pointLights[0] = PointLight(0.4f, 0.6f, 1.0f,
					0.2f, 0.5f,
					-5.0f, 5.0f, -150.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[1] = PointLight(0.1f, 0.2f, 1.0f,
					0.2f, 0.5f,
					-5.0f, 5.0f, -250.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[2] = PointLight(0.4f, 0.6f, 1.0f,
					0.2f, 0.5f,
					-5.0f, 5.0f, -70.0f,
					0.2f, 0.01f, 0.001f);
				pointLightCount++;
			}

			if ((camera.getCameraPosition().x >= -60 && camera.getCameraPosition().x <= -20)
				&& (camera.getCameraPosition().z <= -120 && camera.getCameraPosition().z >= -250))
			{
				pointLights[0] = PointLight(0.4f, 0.6f, 1.0f,
					0.2f, 0.5f,
					-100.0f, 5.0f, -350.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[1] = PointLight(0.1f, 0.2f, 1.0f,
					0.2f, 0.5f,
					-100.0f, 5.0f, -250.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[2] = PointLight(0.4f, 0.6f, 1.0f,
					0.2f, 0.5f,
					-100.0f, 5.0f, -150.0f,
					0.2f, 0.01f, 0.001f);
				pointLightCount++;
			}


			if ((camera.getCameraPosition().x >= 0 && camera.getCameraPosition().x <= 60)
				&& (camera.getCameraPosition().z <= 200 && camera.getCameraPosition().z >= -120))
			{
				pointLights[0] = PointLight(0.4f, 0.6f, 1.0f,
					0.2f, 0.5f,
					60.0f, 5.0f, -70.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[1] = PointLight(0.1f, 0.2f, 1.0f,
					0.5f, 0.5f,
					-5.0f, 5.0f, -250.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[2] = PointLight(0.4f, 0.6f, 1.0f,
					0.5f, 0.5f,
					60.0f, 5.0f, 100.0f,
					0.2f, 0.01f, 0.001f);
				pointLightCount++;
			}

			if ((camera.getCameraPosition().x >= -60 && camera.getCameraPosition().x <= 0)
				&& (camera.getCameraPosition().z <= 200 && camera.getCameraPosition().z >= -120))
			{
				pointLights[0] = PointLight(0.4f, 0.6f, 1.0f,
					0.2f, 0.5f,
					-60.0f, 5.0f, -70.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[1] = PointLight(0.1f, 0.2f, 1.0f,
					0.5f, 0.5f,
					-5.0f, 5.0f, -250.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[2] = PointLight(0.4f, 0.6f, 1.0f,
					0.5f, 0.5f,
					-60.0f, 5.0f, 100.0f,
					0.2f, 0.01f, 0.001f);
				pointLightCount++;
			}

			if ((camera.getCameraPosition().x >= -60 && camera.getCameraPosition().x <= 0)
				&& (camera.getCameraPosition().z <= 200 && camera.getCameraPosition().z >= -70))
			{
				pointLights[0] = PointLight(0.4f, 0.6f, 1.0f,
					0.2f, 0.5f,
					60.0f, 5.0f, 100.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[1] = PointLight(0.1f, 0.2f, 1.0f,
					0.5f, 0.5f,
					-5.0f, 5.0f, 30.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[2] = PointLight(0.4f, 0.6f, 1.0f,
					0.5f, 0.5f,
					-60.0f, 5.0f, 100.0f,
					0.2f, 0.01f, 0.001f);
				pointLightCount++;
			}

			if ((camera.getCameraPosition().x >= 0 && camera.getCameraPosition().x <= 60)
				&& (camera.getCameraPosition().z <= 200 && camera.getCameraPosition().z >= -70))
			{
				pointLights[0] = PointLight(0.4f, 0.6f, 1.0f,
					0.2f, 0.5f,
					60.0f, 5.0f, 100.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[1] = PointLight(0.1f, 0.2f, 1.0f,
					0.5f, 0.5f,
					-5.0f, 5.0f, 30.0f,
					0.2f, 0.001f, 0.001f);
				pointLightCount++;

				pointLights[2] = PointLight(0.4f, 0.6f, 1.0f,
					0.5f, 0.5f,
					-60.0f, 5.0f, 100.0f,
					0.2f, 0.01f, 0.001f);
				pointLightCount++;
			}

		}

		//if ((camera.getCameraPosition().x >= -40 && camera.getCameraPosition().x <= 40)
		//	&& (camera.getCameraPosition().z >= -40 && camera.getCameraPosition().z <= 40))
		//{
		//	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		//		0.5f, 0.5f,
		//		20.0f, 1.5f, -30.0f,
		//		0.3f, 0.2f, 0.1f);
		//	pointLightCount++;

		//	pointLights[1] = PointLight(0.5f, 0.0f, 0.5f,
		//		0.5f, 0.5f,
		//		0.0f, 1.5f, -30.0f,
		//		0.3f, 0.2f, 0.1f);
		//	pointLightCount++;

		//	pointLights[2] = PointLight(0.0f, 0.5f, 0.5f,
		//		0.5f, 0.5f,
		//		-20.0f, 1.5f, -30.0f,
		//		0.3f, 0.2f, 0.1f);
		//	pointLightCount++;
		//}
		//else
		//{
		//	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,
		//		0.5f, 0.5f,
		//		60.0f, 1.5f, -30.0f,
		//		0.3f, 0.2f, 0.1f);
		//	pointLightCount++;
		//}

		////Luces del tipo pointlight en la planta baja del acuario
		//if ((camera.getCameraPosition().x >= -40 && camera.getCameraPosition().x <= 40)
		//	&& (camera.getCameraPosition().y >= 0 && camera.getCameraPosition().y <= 40)
		//	&& (camera.getCameraPosition().z >= -40 && camera.getCameraPosition().z <= 40)) 
		//{
		//	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		//		0.5f, 0.5f,
		//		20.0f, 1.5f, -30.0f,
		//		0.3f, 0.2f, 0.1f);
		//	pointLightCount++;
		//}
		//else
		//{
		//	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,
		//		0.5f, 0.5f,
		//		60.0f, 1.5f, -30.0f,
		//		0.3f, 0.2f, 0.1f);
		//	pointLightCount++;
		//	//shaderList[0].SetPointLights(pointLights, 0);

		//}

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

		//--------------------------------------------Piso Exterior------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -0.5f, 20.0f));
		model = glm::scale(model, glm::vec3(14.5f, 0.0f, 18.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[2]->RenderMesh();

		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);

		//BLENDING: Util para la tranparencia o Traslucidez
		//Para poder hacer adecuadamente la transparencia de un objeto, se debe de poner
		//primero los modelos a utilizar y despues colocar el mesh en numérico
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//--------------------Instanciamiento de Personajes en el escenario (Festival)--------------------------//
		 //Arturia Pendragon (Lily)
		//Cuerpo
		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 0.0f, 0.3f);
		model = glm::translate(model, glm::vec3(0.0f + MAvanzaLZ, 2.7f, 20.0f + MAvanzaLX));
		model = glm::rotate(model, glm::radians(Mrota), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux_cuerpoL = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lily_Cuerpo.RenderModel();

		//Brazo Izquierdo
		model = modelaux_cuerpoL;
		model = glm::translate(model, glm::vec3(0.49f, 1.61f, -0.1f));
		model = glm::rotate(model, glm::radians(MrotABrazoL), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelaux_brazoL = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lily_AnteBrazo.RenderModel();

		model = modelaux_brazoL;
		model = glm::translate(model, glm::vec3(0.77f, -1.02f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians((MrotBrazoL)), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lily_Brazo.RenderModel();

		//Brazo Derecho
		model = modelaux_cuerpoL;
		model = glm::translate(model, glm::vec3(-0.49f, 1.61f, -0.1f));
		model = glm::rotate(model, glm::radians(MrotABrazoL), glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux_brazo2L = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lily_AnteBrazo_2.RenderModel();

		model = modelaux_brazo2L;
		model = glm::translate(model, glm::vec3(-0.77f, -1.02f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians((MrotBrazoL)), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lily_Brazo_2.RenderModel();

		//Pie Izquierdo
		model = modelaux_cuerpoL;
		model = glm::translate(model, glm::vec3(0.3f, -0.4f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotPiernaL)), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelaux_piernaL = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lily_Pierna.RenderModel();

		model = modelaux_piernaL;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotPieL)), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lily_Pie.RenderModel();

		//Pie Derecho
		model = modelaux_cuerpoL;
		model = glm::translate(model, glm::vec3(-0.3f, -0.4f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotPiernaL)), glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux_pierna2L = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lily_Pierna_2.RenderModel();

		model = modelaux_pierna2L;
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotPieL)), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lily_Pie_2.RenderModel();

		//Cabeza
		model = modelaux_cuerpoL;
		model = glm::translate(model, glm::vec3(0.0f, 2.49f, 0.02f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lily_Cabeza.RenderModel();
		
		//Nero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f+4.5f, 0.0f));
		modelaux_cuerpoN = model;
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Nero_Cuerpo.RenderModel();
		//Micro
		model = modelaux_cuerpoN;
		model = glm::translate(model, glm::vec3(0.0f, -4.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		//model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Micro.RenderModel();
		//brazo der
		model = modelaux_cuerpoN;
		model = glm::translate(model, glm::vec3(0.65f, 0.35f, -0.02f));
		model = glm::rotate(model, -30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotABrazoN)), glm::vec3(0.0f, -1.0f, -1.0f));
		modelaux_brazoN = model;
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Nero_AnteBrazo.RenderModel();

		model = modelaux_brazoN;
		model = glm::translate(model, glm::vec3(0.7f, -0.5f, -0.02f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotBrazoN/2)), glm::vec3(0.0f, 1.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Nero_Brazo.RenderModel();

		//brazo izq
		model = modelaux_cuerpoN;
		model = glm::translate(model, glm::vec3(-0.65f, 0.35f, -0.02f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotABrazoN)), glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux_brazo2N = model;
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Nero_AnteBrazo_2.RenderModel();

		model = modelaux_brazo2N;
		model = glm::translate(model, glm::vec3(-0.7f, -0.5f, -0.02f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotBrazoN/2)), glm::vec3(0.0f, -1.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Nero_Brazo_2.RenderModel();

		//koharu
		//Cuerpo
		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 0.0f, 0.3f);
		model = glm::translate(model, glm::vec3(4.0f, 5.0f + 3.0f, -5.0f));
		modelaux_cuerpoK = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Koharu_Cuerpo.RenderModel();
		//Bateria
		model = modelaux_cuerpoK;
		model = glm::translate(model, glm::vec3(2.0f, -3.0f, 5.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		//model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bateria.RenderModel();
		//Silla humilde
		model = modelaux_cuerpoK;
		model = glm::translate(model, glm::vec3(0.0f, -4.5f, -0.5f));
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
		//model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		//Brazo Izquierdo
		model = modelaux_cuerpoK;
		model = glm::translate(model, glm::vec3(0.43f, -0.15f, -0.05f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotABrazoK)), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux_brazoK = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Koharu_AnteBrazo.RenderModel();

		model = modelaux_brazoK;
		model = glm::translate(model, glm::vec3(0.71f, -0.01f, -0.06f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotBrazoK/2)), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Koharu_Brazo.RenderModel();

		//Brazo Derecho
		model = modelaux_cuerpoK;
		model = glm::translate(model, glm::vec3(-0.43f, -0.15f, -0.05f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotABrazoK)), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux_brazo2K = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Koharu_AnteBrazo_2.RenderModel();

		model = modelaux_brazo2K;
		model = glm::translate(model, glm::vec3(-0.7f, -0.01f, -0.06f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotBrazoK/2)), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Koharu_Brazo_2.RenderModel();

		//Pie Izquierdo
		model = modelaux_cuerpoK;
		model = glm::translate(model, glm::vec3(0.3f, -1.9f, 0.0f));
		model = glm::rotate(model, -75 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotBrazoK / 2)), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotPierna)), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelaux_piernaK = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Koharu_Pierna.RenderModel();

		model = modelaux_piernaK;
		model = glm::translate(model, glm::vec3(-0.02f, -1.05f, 0.0f));
		model = glm::rotate(model, 60 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotBrazoK / 2)), glm::vec3(1.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians((MrotPie)), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Koharu_Pie.RenderModel();

		//Pie Derecho
		model = modelaux_cuerpoK;
		model = glm::translate(model, glm::vec3(-0.3f, -1.9f, 0.0f));
		model = glm::rotate(model, -75 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotPierna)), glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux_pierna2K = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Koharu_Pierna_2.RenderModel();

		model = modelaux_pierna2K;
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.05f, -1.05f, 0.0f));
		model = glm::rotate(model, 60 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotPie)), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Koharu_Pie_2.RenderModel();

		//Koshiro
		model = glm::mat4(1.0);
		//poskoshiro = glm::vec3(posXkoshiro + movkoshiro_x, posYkoshiro + movkoshiro_y, posZkoshiro + movkoshiro_z);
		//model = glm::translate(model, poskoshiro);
		model = glm::translate(model, glm::vec3(-4.0f+ movkoshiro_x, 5.0f + 3.55f + movkoshiro_y, -5.0f + movkoshiro_z));
		model = glm::rotate(model, girokoshiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux_cuerpoKS = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		koshiro_Cuerpo.RenderModel();

		//Guitarra
		model = modelaux_cuerpoKS;
		model = glm::translate(model, glm::vec3(0.8f, -1.3f, 0.7f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -35 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Guitarra.RenderModel();

		//Brazo Izquierdo
		model = modelaux_cuerpoKS;
		model = glm::translate(model, glm::vec3(0.47f, 0.01f, -0.05f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux_brazoKS = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		koshiro_AnteBrazo.RenderModel();

		model = modelaux_brazoKS;
		model = glm::translate(model, glm::vec3(0.85f, 0.05f, -0.06f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians((MrotBrazoKS/2)), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((MrotBrazo)), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		koshiro_Brazo.RenderModel();

		//Brazo Derecho
		model = modelaux_cuerpoKS;
		model = glm::translate(model, glm::vec3(-0.47f, 0.01f, -0.05f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians((MrotPie)), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians((MrotABrazoKS)), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux_brazo2KS = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		koshiro_AnteBrazo_2.RenderModel();

		model = modelaux_brazo2KS;
		model = glm::translate(model, glm::vec3(-0.85f, 0.05f, -0.06f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, -45 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians((MrotBrazoKS/3)), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, -20 * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		koshiro_Brazo_2.RenderModel();

		//Pie Izquierdo
		model = modelaux_cuerpoKS;
		model = glm::translate(model, glm::vec3(0.37f, -2.35f, -0.05f));
		model = glm::rotate(model, glm::radians((MrotPiernaKS)), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelaux_piernaKS = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		koshiro_Pierna.RenderModel();

		model = modelaux_piernaKS;
		model = glm::translate(model, glm::vec3(-0.02f, -0.85f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotPieKS)), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		koshiro_Pie.RenderModel();

		//Pie Derecho
		model = modelaux_cuerpoKS;
		model = glm::translate(model, glm::vec3(-0.37f, -2.35f, -0.05f));
		model = glm::rotate(model, glm::radians((MrotPiernaKS)), glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux_pierna2KS = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		koshiro_Pierna_2.RenderModel();

		model = modelaux_pierna2KS;
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.02f, -0.85f, 0.0f));
		model = glm::rotate(model, glm::radians((MrotPieKS)), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		koshiro_Pie_2.RenderModel();

		//KeyFrame de Nero (padoru)
		model = glm::mat4(1.0);
		posNero = glm::vec3(posXNero + movNero_x, posYNero + movNero_y, 10+.0f + posZNero + movNero_z);
		model = glm::translate(model, posNero);
		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
		model = glm::rotate(model, giroNero * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Padoru.RenderModel();

		//Extras
		//----------------------------------------Primera fila-------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-7.5f, 0.0f, 15.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lucy.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 15.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vik.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.5f, 0.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		elf.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 15.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vik.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.5f, 0.0f, 15.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lucy.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 15.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vik.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(7.5f, 0.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		elf.RenderModel();

		//-------------------------------------Segunda fila----------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lucy.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.5f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vik.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		elf.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lucy.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.5f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vik.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		elf.RenderModel();

		//------------------------------------------Tercera fila-----------------------------------------------//
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, 0.0f, 25.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lucy.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.5f, 0.0f, 25.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vik.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 25.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		elf.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 25.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lucy.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.5f, 0.0f, 25.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vik.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, 0.0f, 25.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		elf.RenderModel();

		//shrek
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, 0.0f, 40.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Shrek.RenderModel();


		//--------------------------------------------Construcción del Festival------------------------------------------------//
		//Carpas a utilizar
		//Bebidas internacionales
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-54.0f, -2.0f, 148.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 1.0f, 1.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carpa.RenderModel();

		//Mariscos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -2.0f, 110.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carpa.RenderModel();

		//Farolas en el festival
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
		model = glm::translate(model, glm::vec3(102.0f, -1.95f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.85f, 0.75f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(102.0f, -1.95f, 170.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.85f, 0.75f));
		model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -3.95f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 4.0f, 2.5f));
		//model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Farola1.RenderModel();
		//faro.UseTexture();

		//Piso de cada una de las secciones del festival
		//Comida Nacional
		//Puesto de tortas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -0.45f, -15.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera.UseTexture();
		//meshList[3]->RenderMesh();
		//Puesto de Tacos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -0.45f, 35.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pasto.UseTexture();
		//meshList[3]->RenderMesh();
		//Puestos de Mariscos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, -0.45f, 137.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera_2.UseTexture();
		//meshList[3]->RenderMesh();
		
		//Comida Internacional
		//Comida alemana
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -0.45f, -30.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera.UseTexture();
		//meshList[3]->RenderMesh();
		//Comida Española
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.45f, 137.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera_3.UseTexture();
		//meshList[3]->RenderMesh();
		//Comida Japonesa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-112.0f, -0.45f, 137.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera_4.UseTexture();
		//meshList[3]->RenderMesh();

		//---------Modelos correspondientes a las sillas y mesas-----------//
		//puesto de tacos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f, -0.5f, 12.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, -0.5f, 30.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f, -0.5f, 30.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, -0.5f, 12.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f, -0.5f, 48.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, -0.5f, 48.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		//Bebidas nacionales
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f, -0.5f, 75.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f, -0.5f, 102.5f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(85.0f, -0.5f, 99.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(85.0f, -0.5f, 86.9f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(85.0f, -0.5f, 74.6f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		//Puesto de mariscos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(87.0f, -0.5f, 113.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -0.5f, 113.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(68.0f, -0.5f, 113.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, -0.5f, 113.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(87.0f, -0.5f, 133.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(79.0f, -0.5f, 133.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(87.0f, -0.5f, 153.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(79.0f, -0.5f, 153.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		//Modelos correspondientes al seccion del pozole
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -0.5f, 117.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -0.5f, 137.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -0.5f, 157.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.0f, -0.5f, 110.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		//Seccion de comida internacional
		//Comida española
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, -0.5f, 117.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, -0.5f, 137.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, -0.5f, 157.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		//Bebidas internacionales
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.0f, -0.5f, 113.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.0f, -0.5f, 133.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.0f, -0.5f, 153.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-41.0f, -0.5f, 162.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-54.0f, -0.5f, 162.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-67.0f, -0.5f, 162.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, -0.5f, 162.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-82.0f, -0.5f, 113.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-82.0f, -0.5f, 133.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-82.0f, -0.5f, 153.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		//Comida Peruana
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, -0.5f, 60.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.0f, -0.5f, 65.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-107.0f, -0.5f, 65.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, -0.5f, 55.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, -0.5f, 95.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_B.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, -0.5f, 100.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.17f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_R.RenderModel();

		//Comida japonesa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-112.0f, -0.45f, 77.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pasto.UseTexture();
		//meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-112.0f, -0.45f, -43.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera.UseTexture();
		//meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-112.0f, -0.45f, 17.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso_madera_2.UseTexture();
		//meshList[3]->RenderMesh();

		//------------------------------------FoodTrucks-----------------------------//
		//Comida Peruana
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, -1.0f, 80.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ftruck1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-125.0f, -0.5f, 80.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ftruck4.RenderModel();

		//Comida Italiana
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-112.0f, -0.4f, 20.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ftruck2.RenderModel();

		//Comida Japonesa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, -0.5f, 150.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ftruck3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, -0.5f, 125.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ftruck3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-105.0f, -0.5f, 150.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ftruck3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-105.0f, -0.5f, 125.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ftruck3.RenderModel();

		//Comida alemana
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-125.0f, -0.5f, -60.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ftruck5.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-125.0f, 0.0f, -30.0f));
		model = glm::scale(model, glm::vec3(2.3f, 2.3f, 2.3f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FtruckSP.RenderModel();

		//Comida Española
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(45.0f, -0.5f, 155.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -35 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ftruck4.RenderModel();

		//Comida Mexicana
		//Tacos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(85.0f, -0.5f, 25.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Comex1.RenderModel();

		//Tortas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(85.0f, -0.5f, -30.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Comex1.RenderModel();

		//Mariscos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(65.0f, -0.5f, 155.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ftruck5.RenderModel();

		//----------------------------Escenario-----------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		escenario.RenderModel();

		//Reflectores
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 6.7f, 10.0f));
		model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Reflector.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 6.7f, 10.0f));
		model = glm::rotate(model, 225 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Reflector.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 6.7f, -10.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Reflector.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 6.7f, -12.0f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Reflector.RenderModel();

		//Textura animada de los fuegos artificiales
		//textura con movimiento
		//Importantes porque la variable uniform no podemos modificarla directamente
		toffsetu += 0.001;
		toffsetv -= 0.01;
		//para que no se desborde la variable
		//Movimiento en el eje x
		if (toffsetu > 1.0)
			toffsetu = 0.0;
		//Movimiento en el eje y
		if (toffsetv < 0.0)
			toffsetv = 1;

		//Carga de la textura de los fuegos artificiales
		toffset = glm::vec2(0.0f, toffsetv);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(11.0f, 5.3f, 11.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Firework_G.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();

		toffset = glm::vec2(0.0f, toffsetv);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(11.0f, 9.5f, 11.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Firework_G.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();

		toffset = glm::vec2(0.0f, toffsetv);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(11.0f, 5.3f, -12.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Firework_O.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();

		toffset = glm::vec2(0.0f, toffsetv);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(11.0f, 9.5f, -12.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Firework_O.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();

		toffset = glm::vec2(0.0f, toffsetv);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, 5.3f, 11.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Firework_R.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();

		toffset = glm::vec2(0.0f, toffsetv);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, 9.5f, 11.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Firework_R.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();

		toffset = glm::vec2(0.0f, toffsetv);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, 5.3f, -12.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Firework_P.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();

		toffset = glm::vec2(0.0f, toffsetv);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, 9.5f, -12.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Firework_P.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();

		//--------------------------------------------Acuario-----------------------------------------//
		//Codigo para la creacion del acuario
		//Piso de la recepcion
		toffset = glm::vec2(0.0f, 0.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.1f, -210.0f));
		model = glm::scale(model, glm::vec3(5.0f, 0.0f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		marmol.UseTexture();
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 80.6f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Edificio.UseTexture();
		coral1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 80.6f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Edificio.UseTexture();
		coral2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 80.6f, 100.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Edificio.UseTexture();
		coral3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 100.6f, -200.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Edificio.UseTexture();
		coral4.RenderModel();

		//Recepcion
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 14.6f, -210.0f));
		model = glm::scale(model, glm::vec3(100.0f, 30.0f, 100.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio.UseTexture();
		meshList[5]->RenderMesh();

		//Paredes de la recepcion
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 14.2f, -210.0f));
		model = glm::scale(model, glm::vec3(99.5f, 29.5f, 99.5f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Recepcion.UseTexture();
		meshList[6]->RenderMesh();

		//Entrada principal (ventanal)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 14.8f, -160.0f));
		model = glm::scale(model, glm::vec3(100.0f, 30.0f, 0.1f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ventanal.UseTexture();
		meshList[7]->RenderMesh();
		
		// Entrada/salida del Acuario
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 14.6f, -259.3f));
		model = glm::scale(model, glm::vec3(100.0f, 30.0f, 0.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Entradas.UseTexture();
		meshList[7]->RenderMesh();

		//Cubiulo Escaleras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 14.6f, -330.0f));
		model = glm::scale(model, glm::vec3(100.0f, 30.0f, 140.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio.UseTexture();
		meshList[5]->RenderMesh();

		//Paredes de las escaleras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 14.2f, -329.5f));
		model = glm::scale(model, glm::vec3(99.5f, 29.5f, 141.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Recepcion.UseTexture();
		meshList[6]->RenderMesh();

		//Pared de las escaleras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 14.8f, -397.5f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f, 31.0f, 0.1f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fauna_marina.UseTexture();
		meshList[7]->RenderMesh();

		//Pared con informacion 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(49.5f, 14.8f, -329.4f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(140.0f, 31.0f, 0.1f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Informacion1.UseTexture();
		meshList[7]->RenderMesh();

		//Pared con informacion 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-49.5f, 14.8f, -329.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(140.0f, 31.0f, 0.1f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Informacion2.UseTexture();
		meshList[7]->RenderMesh();

		//Piso del cubiculo
		toffset = glm::vec2(0.0f, 0.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.1f, -280.0f));
		model = glm::scale(model, glm::vec3(5.0f, 0.0f, 7.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		marmol.UseTexture();
		meshList[2]->RenderMesh();

		//Escaleras que conectan a la recepcion con el acuario
		//Entrada
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -33.3f, -372.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.7f, 1.5f, 1.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Escalera.RenderModel();

		//Salida
		//Escaleras que conectan a la recepcion con el acuario
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-33.0f, -33.3f, -372.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.7f, 1.5f, 1.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Escalera.RenderModel();

		//Acuario parte de la planta baja
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -17.1f, -115.0f));
		model = glm::scale(model, glm::vec3(300.0f, 33.0f, 565.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pared_blanca.UseTexture();
		meshList[8]->RenderMesh();

		//Techo de la planta baja
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.5f, -1.0f, -114.7f));
		model = glm::scale(model, glm::vec3(300.0f, 0.0f, 566.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Techo_acuario.UseTexture();
		meshList[7]->RenderMesh();

		//Entrada/salidad del escenario exterior
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -17.1f, 167.4f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(300.0f, 33.0f, 0.1f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pared_tunel.UseTexture();
		meshList[7]->RenderMesh();


		// Paredes de la planta baja
		//Divisiones principales
		//Division a
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -17.1f, -310.0f));
		model = glm::scale(model, glm::vec3(178.6f, 33.0f, 0.1f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pared_blanca.UseTexture();
		meshList[7]->RenderMesh();

		//Division b
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(90.0f, -17.1f, -110.0f));
		model = glm::scale(model, glm::vec3(120.0f, 33.0f, 0.1f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pared_blanca.UseTexture();
		meshList[7]->RenderMesh();

		//Division c
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, -17.1f, -197.2f));
		model = glm::scale(model, glm::vec3(50.0f, 33.0f, 0.1f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pared_blanca.UseTexture();
		meshList[7]->RenderMesh();

		//Division d
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-103.0f, -17.1f, -110.0f));
		model = glm::scale(model, glm::vec3(93.0f, 33.0f, 0.1f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pared_blanca.UseTexture();
		meshList[7]->RenderMesh();

		//Division e
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, -17.1f, -353.8f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(87.3f, 33.0f, 0.1f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pared_blanca.UseTexture();
		meshList[7]->RenderMesh();

		////Cubo para el NP Nero
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -60.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(60.0f, 60.0f, 60.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////marmol.UseTexture();
		////Edificio.UseTexture();
		////meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(75.5f, 6.0f, -200.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cartel_M.RenderModel();

		//Carga de las infografias
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-149.0f, -17.3f, -60.0f));
		model = glm::scale(model, glm::vec3(3.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinguino_inf.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, -33.0f, -110.3f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 3.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cangrejo_inf.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, -33.0f, -110.3f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 3.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tiburon_inf.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, -33.0f, -110.3f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 3.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peces_inf.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, -17.0f, -109.5f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 3.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Orca_inf.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, -32.0f, -200.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.8f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EstrellaM_inf1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, -32.0f, -275.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.8f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EstrellaM_inf2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, -32.0f, -109.5f));
		model = glm::scale(model, glm::vec3(2.0f, 1.8f, 3.0f));
		//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Grap.RenderModel();

		//Carga de las imagenes
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 14.0f, -303.5f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Calendario_azt.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, 8.0f, -259.5f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 3.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ballena_img.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 2.5f, -252.0f));
		model = glm::scale(model, glm::vec3(3.0f, 8.0f, 8.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinguino_img.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 8.0f, -205.0f));
		model = glm::scale(model, glm::vec3(3.0f, 8.0f, 8.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Orca_img.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 8.0f, -220.0f));
		model = glm::scale(model, glm::vec3(3.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tiburon_img.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 8.0f, -255.0f));
		model = glm::scale(model, glm::vec3(3.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pez_img.RenderModel();

		//Cartel correspondiente a la zona de la pecera del comienzo del recorrido
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, -27.0f, -310.5f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 3.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		No_flash.RenderModel();

		//Cartel correspondiente a las peceras centrales del recorrido
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -27.0f, -309.5f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 3.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		No_flash.RenderModel();

		//Cartel correspondiente a la zona de la pecera mas grande
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(38.5f, -27.0f, 167.1f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 3.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		No_flash.RenderModel();

		//Cartel correspondiente a la zona de los pinguinos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-149.5f, -27.0f, -80.0f));
		model = glm::scale(model, glm::vec3(3.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		No_flash.RenderModel();

		//Carga de las peceras
		//Peces pequeños (Pecera 1)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(139.1f, -18.01f, -250.0f));
		model = glm::scale(model, glm::vec3(20.0f, 30.0f, 249.f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cristal.UseTexture();
		meshList[7]->RenderMesh();

		//Tiburones (Pecera 2)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, -18.01f, -253.5f));
		model = glm::scale(model, glm::vec3(48.0f, 30.0f, 112.4f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cristal.UseTexture();
		meshList[7]->RenderMesh();

		//Pecera 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, -18.01f, -253.5f));
		model = glm::scale(model, glm::vec3(48.0f, 30.0f, 112.4f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cristal.UseTexture();
		meshList[7]->RenderMesh();

		//Pecera tubular
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -24.0f, -55.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.20f, 0.4f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Acuario_cilindro.RenderModel();

		//Tunel
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.8f, -15.0f, 111.5f));
		model = glm::rotate(model, 05 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.143f, 0.15f, 0.66f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Medio_cilindro.RenderModel();

		//Peceras del tunel (Pecera 6)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.5f, -15.0f, 91.0f));
		model = glm::scale(model, glm::vec3(15.0f, 30.0f, 152.5f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cristal.UseTexture();
		meshList[7]->RenderMesh();

		//Pecera 7
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-29.5f, -15.0f, 91.0f));
		model = glm::scale(model, glm::vec3(15.0f, 30.0f, 152.5f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cristal.UseTexture();
		meshList[7]->RenderMesh();

		//Pecera ultra enorme
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(107.0f, -50.5f, 66.5f));
		model = glm::scale(model, glm::vec3(85.0f, 100.0f, 200.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cristal.UseTexture();
		meshList[7]->RenderMesh();

		//Modelos de Decoracion
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(45.0f, 0.2f, -200.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Piano.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, -1.5f, -170.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		///Neptuno.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, -60.0f, 280.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Espectaculo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-98.0f, -25.0f, 115.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.5f, 3.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HabitatP.RenderModel();

		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	engine->drop();
	return 0;
}

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_SPACE])
	{
		if (reproduciranimacionN < 1)
		{
			if (play == false && (FrameIndexN > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndexN = 0;
				i_curr_steps_N = 0;
				reproduciranimacionN++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacionN = 0;

			}
			else
			{
				play = false;
			}
		}

		if (reproduciranimacionK < 1)
		{
			if (play == false && (FrameIndexK > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndexK = 0;
				i_curr_steps_K = 0;
				reproduciranimacionK++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacionK = 0;

			}
			else
			{
				play = false;
			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacionN < 1)
		{
			reproduciranimacionN = 0;
		}

		if (habilitaranimacionK < 1)
		{
			reproduciranimacionK = 0;
		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			printf("movAvion_x es: %f\n", movNero_x);
			//printf("movAvion_y es: %f\n", movAvion_y);
			printf(" \npresiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1)
		{
			guardoFrame = 0;
		}
	}


	if (keys[GLFW_KEY_1])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movNero_x += 1.0f;
			printf("\n movAvion_x es: %f\n", movNero_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n reinicia con 2\n");
		}

	}
	if (keys[GLFW_KEY_2])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
		}
	}

}