
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//audio

#include <irrKlang.h>
using namespace irrklang; 

#pragma comment(lib, "winmm.lib")
bool	sound = true,
		sound2 = true,
		sound3 = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 100.0f, 700.0f));
float MovementSpeed = 0.01f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;

//ANIMACION MIRANDA
float	movAuto_x = 0.0f,
movAuto_z = 0.0f,
orienta2 = 0.0f,
orienta = 0.0f;
bool	animacion = false,
animacion2 = false,
animacion3 = false,
animacionCola = true,
reco1Cola = true,
reco2Cola = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false,
recorrido5 = false,
recorrido6 = false,
recorrido7 = false,
recorido8 = false,
rpelota1 = true,
rpelota2 = false,
rpelota3 = false,
rpelota4 = false;


//recorrido faro 
bool animacionFaro = true,
salto1 = true,
salto2 = false,
salto3 = false,
salto4 = false;

float faro_x = 180.0f,
faro_y = 150.0f,
faro_z = 70.0f,
pausa = 0.0f;

//animacion delfin
float	pos_x = -400.0f,
pos_y = 0.0f,
pos_z = -200.0f;

float	pos_xx = -350.0f,
pos_yy = 0.0f,
pos_zz = -370.0f;

float		cola_x = 0.0f,
cola_y = 0.0f,
cola_z = 0.0f;


//animacion pelota
float pelotax = -300.0f,
pelotay = 10.0f,
pelotaz = -200.0f,
girapelota = 0.0f;

//FIN ANIMACION MIRANDA



//Keyframes (Manipulación y dibujo)
float	posX = -45.0f,
posY = 5.0f,
posZ = 110.0f,
rotRodIzq = 0.0f,
giroMonito = 0.0f;
float	incX = 0.0f,
incY = 0.0f,
incZ = 0.0f,
rotInc = 0.0f,
giroMonitoInc = 0.0f;

//variables mov pinguinos
float movPingu_x = 0.0f,
movPingu_z = 0.0f,
orientaPingu = 0.0f,
movPingu_x2 = 400.0f,
movPingu_z2 = 30.0f,
orientaPingu2 = 0.0f,
animalaspingu = 0.0f,
alaspingu = 0.0f,
animpataspingu = 0.0f,
pataspingu = 0.0f;

//variables cangrejos
float movcrab_x = -450.0f,
movcrab_z = 450.0f,
movcrab_y = 0.0f,
orientacrab = 0.0f,
animpatascrab = 0.0f,
patasbcrab = 0.0f,
animpinzascrab = 0.0f,
pinzascrab = 0.0f,
movcarrito_x = 0.0f,
movcarrito_z = 450.0f,
orientacarrito = 90.0f,
orientapuerta1 =0.0f,
orientapuerta2 = 0.0f,
animpuerta1=0.0f, 
animpuerta2=0.0f;



//LINEA AGREGADA 3
float movtrabx = 0.0f,
movtrabz = 450.0f,
orientatrab=90.0f,
movtraby=10.0f,
animocto=0.0f;

//animaciones pinguinos
bool animacionP = true,
reco1 = true,
reco2 = false,
reco3 = false,
reco4 = false,
recoo5 = false,
recoo6 = false,
recoo7 = false,
animacionP2 = true,
reco5 = true,
reco6 = false,
reco7 = false,
reco8 = false,
reco9 = false;

//tiburon
float girotibu10 = 0.0f;


//Animacion peces
float orientacola = 0.0f,
orientaalder = 0.0f,
orientaalizq = 0.0f,
movfish1_z = -130.0f,
movfish1_x = 55.0f,
movfish1_y = 5.0f,
orientafish1=0.0f,
animcolafish1=0.0f,
animalaizq=0.0f,
animalader=0.0f;

bool animFish1 = false,
fish1Reco1 = true,
fish1Reco2 = false,
fish1Reco3 = false,
fish1Reco4 = false,
fish1Reco5 = false,
fish1Reco6 = false,
fish1Reco7 = false,
fish1Reco8 = false,
fish1Reco9 = false,
fish1Reco10 = false;

//animación ave
float animAlas = 0.0f,
alasAve = 0.0f,
movAve_x = -350.0f,
movAve_z = 300.0f,
movAve_y = 10.0f,
orientaAve = 0.0f;

bool animaAve = true,
aveReco1 = true,
aveReco2 = false,
aveReco3 = false,
aveReco4 = false,
aveReco5 = false,
aveReco6 = false,
aveReco7 = false,
aveReco8 = false;


//animacion carrito
bool animacionB = false,
re1 = true,
re2 = false,
re3 = false,
re4 = false,
re5 = false,
re6 = false,
re7 = false,
re8 = false,
re9 = false;

//animacion cangrejos
bool animacionC = true,
r1 = true,
r2 = false,
r3 = false,
r4 = false;

//animacion tiburones
float movtibu10_x = 310.0f,
movtibu10_z = -280.0f,
animtibu10 = 0.0f,
animtibu210=0.0f,
orientacolat10 = 0.0f,
orientamant10 = 0.0f;

bool
animtbu10 = false,
tibu10Reco1 = true,
tibu10Reco2 = false,
tibu10Reco3 = false,
tibu10Reco4 = false,
tibu10Reco5 = false,
tibu10Reco6 = false,
tibu10Reco7 = false;





#define MAX_FRAMES 19
int i_max_steps = 60;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 6;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;


	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;


}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;



}

void animate(void)
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotRodIzq += rotInc;
			giroMonito += giroMonitoInc;

			i_curr_steps++;
		}
	}

	//ANIMACION FISH 1
	if (animFish1) {
	//aleta izquierda
			if (animalaizq == 0) {
			orientaalizq += 1.0f;
			if (orientaalizq >= 3) {
				animalaizq = 1;
			}
		}
		else {
			orientaalizq -= 1.0f;
			if (orientaalizq <= 0) {
				animalaizq = 0;
			}
		}

//aleta derecha
			if (animalader == 0) {
				orientaalder += 1.0f;
				if (orientaalder >= 1) {
					animalader = 1;
				}
			}
			else {
				orientaalder -= 1.0f;
				if (orientaalder <= 0) {
					animalader = 0;
				}
			}

//cola
			if (animcolafish1 == 0) {
				orientacola += 1.0f;
				if (orientacola >= 1) {
					animcolafish1 = 1;
				}
			}
			else {
				orientacola -= 1.0f;
				if (orientacola <= 0) {
					animcolafish1 = 0;
				}
			}
	//movimiento de pez
			if (fish1Reco1) {
					movfish1_z += 1.0f;
					orientafish1 = 0.0f;
					if (movfish1_z >= -70.0f) {
						fish1Reco1 = false;
						fish1Reco2 = true;
					}
			}

			if (fish1Reco2) {
				movfish1_x -= 1.0f;
				orientafish1 = -90.0f;
				if (movfish1_x <= 40.0f) {
					fish1Reco2 = false;
					fish1Reco3 = true;
				}
			}


			if (fish1Reco3) {
				movfish1_x -= 0.714f;
				movfish1_y += 1.0f;
				orientafish1 = -55.01;
				if (movfish1_y >= 12.0f) {
					fish1Reco3 = false;
					fish1Reco4 = true;
				}
			}

			if (fish1Reco4) {
				movfish1_x -= 2.5f;
				movfish1_y += 1.0f;
				orientafish1 = -33.12;
				if (movfish1_y >= 14.0f) {
					fish1Reco4 = false;
					fish1Reco5 = true;
				}
			}

			if (fish1Reco5) {
				movfish1_x -= 1.0f;
				orientafish1 = -90.0;
				if (movfish1_x <= 20.0f) {
					fish1Reco5 = false;
					fish1Reco6 = true;
				}
			}


			if (fish1Reco6) {
				movfish1_x -= 2.5f;
				movfish1_y += 1.0f;
				orientafish1 = -90.0;
				if (movfish1_x <= 15.0f) {
					fish1Reco6 = false;
					fish1Reco7 = true;
				}
			}

			if (fish1Reco7) {
				movfish1_x -= 2.5f;
				movfish1_y -= 1.0f;
				orientafish1 = -158.19;
				if (movfish1_x <= 15.0f) {
					fish1Reco7 = false;
					fish1Reco8 = true;
				}
			}

			if (fish1Reco8) {
				movfish1_x -= 2.5f;
				movfish1_y -= 1.0f;
				orientafish1 = -125.53;
				if (movfish1_y <= 5.0f && movfish1_x <= 15) {
					fish1Reco8 = false;
					fish1Reco9 = true;
				}
			}

			if (fish1Reco9) {
				movfish1_x -= 1.0f;
				orientafish1 = -90.0;
				if (movfish1_x <= 8) {
					fish1Reco9 = false;
					fish1Reco10 = true;
				}
			}

			if (fish1Reco10) {
				movfish1_x += 0.7833f;
				movfish1_z -= 1.0f;
				orientafish1 = 141.92;
				if (movfish1_x >= 55) {
					fish1Reco10 = false;
					fish1Reco1 = true;
				}
			}

	
	
	
	

	
	
	}




	//animacion tiburon
	if (animtbu10) {

		//aleta trasera
		if (animtibu10 == 0) {
			orientacolat10 += 0.1f;
			if (orientacolat10 >= 0.3) {
				animtibu10 = 1;
			}
		}
		else {
			orientacolat10 -= 0.1f;
			if (orientacolat10 <= 0.1) {
				animtibu10 = 0;
			}
		}


		//mandibula
		if (animtibu210 == 0) {
			orientamant10 += 0.1f;
			if (orientamant10 >= 1) {
				animtibu210 = 1;
			}
		}
		else {
			orientamant10-= 0.1f;
			if (orientamant10 <= 0) {
				animtibu210 = 0;
			}
		}

	
		if (tibu10Reco1) {
			movtibu10_x += 1.66f;
			movtibu10_z += 1;
			girotibu10 = 59.03f;
			if (movtibu10_x >= 360.0f) {
				tibu10Reco1 = false;
				tibu10Reco2 = true;
			}
		}

		if (tibu10Reco2) {
			movtibu10_x -= 1.66f;
			movtibu10_z += 1;
			girotibu10 = -59.06f;
			if (movtibu10_x <= 310.0f) {
				tibu10Reco2 = false;
				tibu10Reco3 = true;
			}
		}

		if (tibu10Reco3) {
			movtibu10_x += 0.66f;
			movtibu10_z += 1;
			girotibu10 = 59.03f;
			if (movtibu10_x >= 330.0f) {
				tibu10Reco3 = false;
				tibu10Reco4 = true;
			}
		}

		if (tibu10Reco4) {
			movtibu10_x -= 2.0f;
			movtibu10_z += 1;
			girotibu10 = -63.4f;
			if (movtibu10_x <= 310.0f) {
				tibu10Reco4 = false;
				tibu10Reco5 = true;
			}
		}

		if (tibu10Reco5) {
			movtibu10_x = 310.0f;
			movtibu10_z -= 1;
			girotibu10 = -180.0f;
			if (movtibu10_z <= -280.0f) {
				tibu10Reco5 = false;
				tibu10Reco1 = true;
			}
		}






	}







	//animacion Ave
	if (animaAve) {

		//Animacion de alas
		if (animAlas == 0) {
			alasAve += 1.0f;
			if (alasAve >= 20) {
				animAlas = 1;
			}
		}
		else {
			alasAve -= 1.0f;
			if (alasAve <= -30) {
				animAlas = 0;
			}
		}
		//Animacion del recorrido de la ave
		if (aveReco1) {
			movAve_x = -300.0f;
			movAve_z -= 3.0f;
			orientaAve = 180.0f;
			if (movAve_z <= -100.0f) {
				aveReco1 = false;
				aveReco2 = true;
			}
		}
		if (aveReco2) {
			movAve_x += (1.5f * 2.0f);
			movAve_z -= (1.0f * 2.0f);
			orientaAve = 124.0f;
			if (movAve_z <= -300.0f) {
				aveReco2 = false;
				aveReco3 = true;
			}
		}
		if (aveReco3) {
			movAve_x += 3.0f;
			movAve_z = -300.0f;
			orientaAve = 90.0f;
			if (movAve_x >= 300.0f) {
				aveReco3 = false;
				aveReco4 = true;
			}
		}
		if (aveReco4) {
			movAve_x += (2.0f * 2.0f);
			movAve_z += (1.0f * 2.0f);
			orientaAve = 45.0f;
			if (movAve_x >= 500.0f) {
				aveReco4 = false;
				aveReco5 = true;
			}
		}
		if (aveReco5) {
			movAve_x = 500.0f;
			movAve_z += 3.0f;
			orientaAve = 0.0f;
			if (movAve_z >= 50.0f) {
				aveReco5 = false;
				aveReco6 = true;
			}
		}
		if (aveReco6) {
			movAve_x -= (1.14f * 2.0f);
			movAve_z += (1.0f * 2.0f);
			orientaAve = 312.0f;
			if (movAve_x <= 300.0f) {
				aveReco6 = false;
				aveReco7 = true;
			}
		}
		if (aveReco7) {
			movAve_x -= 3.0f;
			movAve_z = 300.0f;
			orientaAve = -90.0f;
			if (movAve_x <= -100.0f) {
				aveReco7 = false;
				aveReco8 = true;
			}
		}
		if (aveReco8) {
			movAve_x -= (0.85f * 2.0f);
			movAve_z -= (1.0f * 2.0f);
			orientaAve = 220.0f;
			if (movAve_x <= -400.0f) {
				aveReco8 = false;
				aveReco1 = true;
			}
		}
	}


	if (animacionP2) {
		//animacion alas

		if (animalaspingu == 0) {//CAMBIAR PIVOTE
			alaspingu += 1.0f;
			if (alaspingu >= 1) {
				animalaspingu = 1;
			}
		}
		else {
			alaspingu -= 1.0f;
			if (alaspingu <= -1) {
				animalaspingu = 0;
			}
		}

		//animacion patas

		if (animpataspingu == 0) {
			pataspingu += 1.0f;
			if (pataspingu >= 25) {
				animpataspingu = 1;
			}
		}
		else {
			pataspingu -= 1.0f;
			if (pataspingu <= -25) {
				animpataspingu = 0;
			}
		}




		//animacion recorrido
		if (reco5) {
			movPingu_x2 = 400.0f;
			movPingu_z2 += 1.0f;
			orientaPingu2 = 0.0f;
			if (movPingu_z2 >= 80.0f) {
				reco5 = false;
				reco6 = true;

			}

		}

		if (reco6) {
			movPingu_x2 += 1.0f;
			movPingu_z2 = 80.0f;
			orientaPingu2 = 90.0f;
			if (movPingu_x2 >= 435.0f) {
				reco6 = false;
				reco7 = true;

			}

		}

		if (reco7) {
			movPingu_x2 -= 0.7f;
			movPingu_z2 -= 1.0f;
			orientaPingu2 = -124.9f;
			if (movPingu_x2 <= 400.0f&&movPingu_z2 <= 30.0f) {
				reco7 = false;
				reco5 = true;

			}

		}

	}


	if (animacionC) {


		if (animpatascrab == 0) {
			patasbcrab += 1.0f;
			if (patasbcrab >= 2) {
				animpatascrab = 1;
			}
		}
		else {
			patasbcrab -= 1.0f;
			if (patasbcrab <= -2) {
				animpatascrab = 0;
			}
		}


		if (reco1) {

			movcrab_x += 1.0f;
			movcrab_z -= 1.0f;
			orientacrab = -45.0f;
			if (movcrab_z <= 400) {
				reco1 = false;
				reco2 = true;
			}
		}


		if (reco2) {
			movcrab_x += 1.0f;
			movcrab_z += 1.0f;
			orientacrab = -90.0f;
			if (movcrab_z >= 450) {
				reco2 = false;
				reco3 = true;
			}

		}


		if (reco3) {
			movcrab_x += 0.4f;
			movcrab_z -= 1.0f;
			orientacrab = -45.0f; //checar angulo
			if (movcrab_z <= 400) {
				reco3 = false;
				reco4 = true;
			}

		}


		if (reco4) {
			movcrab_x -= 0.6f;
			movcrab_z += 1.0f;
			orientacrab = -30.9f;
			if (movcrab_z >= 450) {
				reco4 = false;
				recoo5 = true;

			}

		}

		if (recoo5) {


			if (animpinzascrab == 0) {
				pinzascrab += 1.0f;
				if (pinzascrab >= 5) {
					animpinzascrab = 1;
				}
			}
			else {
				pinzascrab -= 1.0f;
				if (pinzascrab <= -5) {
					animpinzascrab = 0;
				}
			}
			//añadir mov pinzas
			movcrab_y -= 0.5f;
			orientacrab = -30.9f;
			if (movcrab_y <= -10) {
				recoo5 = false;
				recoo6 = true;
			}

		}

		if (recoo6) {
			movcrab_x -= 1.0f;
			if (movcrab_x <= -450) {
				recoo6 = false;
				recoo7 = true;
			}

		}

		if (recoo7) {

			if (animpinzascrab == 0) {
				pinzascrab += 1.0f;
				if (pinzascrab >= 5) {
					animpinzascrab = 1;
				}
			}
			else {
				pinzascrab -= 1.0f;
				if (pinzascrab <= -5) {
					animpinzascrab = 0;
				}
			}
			//añadir mov pinzas


			movcrab_y += 0.5f;
			orientacrab = -30.9f;//checar angulo
			if (movcrab_y >= 0) {
				recoo7 = false;
				reco1 = true;
			}

		}	

	}

	//ANIMACIONES MIRANDA

	if (animacion)
	{
		girapelota += 3.0f;
	}


	//animacion pelota
	if (animacion3)
	{
		if (rpelota1) {
			pelotax += 0.625f * 2;
			pelotaz -= 2.0f;
			girapelota += 3.0f;
			//orienta = 148.0f;
			if (pelotaz >= 0.0f) {
				rpelota1 = false;
				rpelota2 = true;
			}
		}
		if (rpelota2) {
			pelotax -= 2.0f;
			pelotaz = -200.0f;
			//orienta = -90.0f;
			girapelota -= 3.0f;
			if (pelotax <= -300.0f) {
				rpelota2 = false;
				rpelota3 = true;
			}
		}
		if (rpelota3) {
			pelotax += 1.25f * 2;
			pelotaz += 2.0f;
			//orienta = 51.34f;
			girapelota += 3.0f;
			if (pelotax >= 0.0f) {
				rpelota3 = false;
				rpelota1 = true;
			}
		}
	}
	//animacion delfin

	if (animacionFaro) {
		if (salto1) {
			pausa += 0.3f;
			if (pausa >= 10.0f) {
				faro_x = -180.0f;
				faro_y = 150.0f;
				faro_z = 70.0f;
				pausa = 0.0f;
				salto1 = false;
				salto2 = true;
			}
		}
		if (salto2) {
			pausa += 0.3f;
			if (pausa >= 10.0f) {
				faro_x = -180.0f;
				faro_y = 150.0f;
				faro_z = 200.0f;
				pausa = 0.0f;
				salto2 = false;
				salto3 = true;
			}
		}
		if (salto3) {
			pausa += 0.3f;
			if (pausa >= 10.0f) {
				faro_x = 180.0f;
				faro_y = 150.0f;
				faro_z = 200.0f;
				pausa = 0.0f;
				salto3 = false;
				salto4 = true;
			}
		}
		if (salto4) {
			pausa += 0.3f;
			if (pausa >= 10.0f) {
				faro_x = 150.0f;
				faro_y = 150.0f;
				faro_z = 0.0f;
				pausa = 0.0f;
				salto4 = false;
				salto1 = true;
			}
		}

	}
	if (animacionCola) {
		if (reco1Cola) {
			cola_y += 0.01;
			if (cola_y >= 0.15f) {
				reco1Cola = false;
				reco2Cola = true;
			}
		}
		if (reco2Cola) {
			cola_y -= 0.01;
			if (cola_y <= -0.15f) {
				reco2Cola = false;
				reco1Cola = true;
			}
		}
	}

	if (animacion2) {
		if (recorrido1) {
			pos_z -= 0.1f;
			pos_y += 0.4f;

			pos_zz += 0.1f;
			pos_yy += 0.4f;

			orienta = 0.0f;
			if (pos_y >= 20.0f) {
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2) {
			pos_z -= 0.1f;
			pos_y += 0.4f;

			pos_zz += 0.1f;
			pos_yy += 0.4f;

			orienta = 15.0f;
			if (pos_y >= 40.0f) {
				recorrido2 = false;
				recorrido3 = true;
			}
		}
		if (recorrido3) {
			pos_z -= 0.4f;
			pos_y += 0.1f;

			pos_zz += 0.4f;
			pos_yy += 0.1f;

			orienta = 15.0f;
			if (pos_y >= 60.0f) {
				recorrido3 = false;
				recorrido4 = true;
			}
		}
		if (recorrido4) {
			pos_z -= 0.4f;
			pos_y -= 0.1f;

			pos_zz += 0.4f;
			pos_yy -= 0.1f;

			orienta = 60.0f;
			if (pos_y <= 40.0f) {
				recorrido4 = false;
				recorrido5 = true;
			}
		}
		if (recorrido5) {
			pos_z -= 0.1f;
			pos_y -= 0.4f;

			pos_zz += 0.1f;
			pos_yy -= 0.4f;

			orienta = 80.0f;
			if (pos_y <= 20.0f) {
				recorrido5 = false;
				recorrido6 = true;
			}
		}
		if (recorrido6) {
			pos_z += 0.1f;
			pos_y -= 0.4f;

			pos_zz += 0.1f;
			pos_yy -= 0.4f;

			orienta = 150.0f;
			if (pos_y <= 0.0f) {
				recorrido6 = false;
				recorrido7 = true;
			}
		}
		if (recorrido7) {
			pos_z += 0.4f;
			pos_y = 0.0f;

			pos_zz -= 0.4f;
			pos_yy = 0.0f;

			orienta = 180.0f;
			if (pos_z >= -200.0f) {
				pos_zz = -370.0f;
				recorrido7 = false;
				recorrido1 = true;
			}

		}
	}
	//FIN ANIMACIONES MIRANDA


	if (animacionB) {

		//puertas
		if (animpuerta1 == 0) {
			orientapuerta2 += 1.0f;
			if (orientapuerta2 >= 1) {
				animpuerta1 = 1;
			}
		}
		else {
			orientapuerta2 -= 1.0f;
			if (orientapuerta2 <= 0) {
				animpuerta1 = 0;
			}
		}



		//puertas
		if (animpuerta2 == 0) {
			orientapuerta1 += 1.0f;
			if (orientapuerta1 >= 1) {
				animpuerta2 = 1;
			}
		}
		else {
			orientapuerta1 -= 1.0f;
			if (orientapuerta1 <= 0) {
				animpuerta2 = 0;
			}
		}


		if (animocto == 0) {
			movtraby += 0.1f;
			if (movtraby >= 16) {
				animocto = 1;
			}
		}
		else {
			movtraby -= 0.1f;
			if (movtraby <= 10) {
				animocto = 0;
			}
		}





		if (re1) {
			movtrabz -= 3.0f;
			movcarrito_x = 0.0f;
			movcarrito_z -= 3.0f;
			if (movcarrito_z <= 300) {
				re1 = false;
				re2 = true;
			}
		}

		if (re2) {
			movtrabx += 1.5f;
			movtrabz -= 1.0f;
			movcarrito_x += 1.5f;
			movcarrito_z -= 1.0f;
			orientacarrito = 33.69f;
			if (movcarrito_x >= 150) {
				re2 = false;
				re3 = true;
			}


		}

		if (re3) {
			movtrabx = 150.0f;
			movtrabz -= 3.0f;
			movcarrito_x = 150.0f;
			movcarrito_z -= 3.0f;
			orientatrab = 90.0f;
			orientacarrito = 90.0f;
			if (movcarrito_z <= -200) {
				re3 = false;
				re4 = true;
			}

		

		}


		if (re4) {
			movtrabx -= 0.6f;
			movtrabz -= 1.0f;
			movcarrito_x -= 0.6f;
			movcarrito_z -= 1.0f;
			orientacarrito = 120.97f;
			orientatrab= 130.97f;
			if (movcarrito_x <= 0) {
				re4 = false;
				re5 = true;
			}

		}

		if (re5) {
			movtrabx -= 0.6f;   //0.6
			movtrabz += 1.0f;       //1.0 
			movcarrito_x -= 0.6f;
			movcarrito_z += 1.0f;
			orientacarrito = 239.03f;
			orientatrab= 220.03f;
			if (movcarrito_x <= -150.0) {
				re5 = false;
				re6 = true;
			}



		}



		if (re6) {

			movtrabx = -150.0f;
			movtrabz += 3.0f;
			movcarrito_x = -150.0f;
			movcarrito_z += 3.0f;
			orientacarrito = 270.00f;
			orientatrab = 45.0f;
			if (movcarrito_z >= 200.0) {
				re6 = false;
				re7 = true;
			}



		}

		if (re7) {
			movtrabx += 1.5f;
			movtrabz += 1.0f;
			movcarrito_x += 1.5f;
			movcarrito_z += 1.0f;
			orientacarrito = 323.13f;
			orientatrab = 360.13f;
			if (movcarrito_x >= 0.0) {
				re7 = false;
				re2 = true;
			}

		}


	}

}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

int main()
{

	//audio de olas, ambiental para todo el acuario 

	ISoundEngine* engine = createIrrKlangDevice();
	if (!engine)
		return 0;
	engine->play2D("Media/mar.wav", true);
	


	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights_mod.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------
	Model piso("resources/objects/piso/piso.obj");

	Model fuente("resources/objects/Fuente1/f1.obj");
	Model valla("resources/objects/Vallas/valla1.obj");
	Model valla2("resources/objects/Vallas2/valla2.obj");
	Model crab("resources/objects/Crab1/crab1.obj");
	Model ping("resources/objects/pinguino1/pingu.obj");
	Model roc("resources/objects/Roca/roc1.obj");
	Model rocap("resources/objects/RocaP/rocap.obj");
	Model rocap1("resources/objects/RocaP1/rocap1.obj");
	Model cafe("resources/objects/cafeteria/cafe.obj");
	Model plat("resources/objects/plataforma/plat.obj");
	Model banc("resources/objects/banca/banc.obj");
	Model rest("resources/objects/restrooms/rest.obj");
	Model carro("resources/objects/helados/carro.obj");
	Model bin("resources/objects/bote/bin.obj");
	Model jaula("resources/objects/jaula/cge.obj");
	Model tienda("resources/objects/tienda/store.obj");
	Model gate("resources/objects/puerta/gate.obj");
	Model vallae("resources/objects/vallap/vallae.obj");
	Model estanque("resources/objects/estanque/estanq.obj");
	Model pool("resources/objects/pool/poolp.obj");
	Model plant1("resources/objects/plant1/plant1.obj");
	Model plant2("resources/objects/plant2/plant2.obj");
	Model roc2("resources/objects/rocanieve/roc2.obj");

	//ave
	Model cuerpoAve("resources/objects/AveVuela/avecuerpo.obj");
	Model alaDer("resources/objects/AveVuela/alader2.obj");
	Model alaIzq("resources/objects/AveVuela/alaizq2.obj");

	//pinguino en partes
	Model pingu("resources/objects/pinguino2/pingu.obj");
	Model pingupi("resources/objects/pinguino2/pieizq.obj");
	Model pingupd("resources/objects/pinguino2/pieder.obj");
	Model pinguai("resources/objects/pinguino2/alaizq.obj");
	Model pinguad("resources/objects/pinguino2/alader.obj");

	//pinguino en partes
	Model pingu2("resources/objects/pinguino1/pingu.obj");
	Model pingupi2("resources/objects/pinguino1/pieizq.obj");
	Model pingupd2("resources/objects/pinguino1/pieder.obj");
	Model pinguai2("resources/objects/pinguino1/alaizq.obj");
	Model pinguad2("resources/objects/pinguino1/alader.obj");

	//cangrejo partes
	Model crab2("resources/objects/crab2/crb2.obj");
	Model patascrabd("resources/objects/crab2/patasder.obj");
	Model patascrabi("resources/objects/crab2/patasizq.obj");
	Model pinzascrabd("resources/objects/crab2/pinzader.obj");
	Model pinzascrabi("resources/objects/crab2/pinzaizq.obj");


	//Tiburon
	Model tibu10("resources/objects/tibu/tibu10.obj");
	Model colatibu10("resources/objects/tibu/colatbu.obj");
	Model mantibu10("resources/objects/tibu/mandibutibu.obj");



	//carro basura
	Model carrito("resources/objects/carrito/carro.obj");
	Model llantasd("resources/objects/carrito/llanta1.obj");
	Model llantaiz("resources/objects/carrito/llanta2.obj");
	Model llantasi("resources/objects/carrito/llanta3.obj");
	Model llantaid("resources/objects/carrito/llanta4.obj");

	
		//ModelAnim employe("resources/objects/empleado/Thoughtful Head Shake.dae");
		//employe.initShaders(animShader.ID); //aÃ±adir el objeto al shader de animacion

	//LINEA AGREGADA 1
	//ModelAnim trab1("resources/objects/basurero/Push.dae");
	//trab1.initShaders(animShader.ID); //aÃ±adir el objeto al shader de animacion

	Model octopus("resources/objects/octo/octopus.obj");



	Model fish1("resources/objects/Fish/fish1.obj");
	Model fish1cola("resources/objects/Fish/fish1cola.obj");
	Model fish1alder("resources/objects/Fish/fish1alder.obj");
	Model fish1alizq("resources/objects/Fish/fish1alizq.obj");


	Model fish2("resources/objects/Fish/fish2.obj");
	Model fish4("resources/objects/Fish/fish4.obj");
	Model fish5("resources/objects/Fish/fish5.obj");
	Model ave1("resources/objects/aves/ave1.obj");
	Model ave2("resources/objects/aves/ave2.obj");
	Model ave3("resources/objects/aves/ave3.obj");
	Model ave4("resources/objects/aves/ave4.obj");
	Model comida("resources/objects/comida/comida.obj");
	Model tiburon("resources/objects/tiburon/tib.obj");
	Model persona1("resources/objects/personas/persona1.obj");
	Model persona2("resources/objects/personas/persona2.obj");
	Model persona3("resources/objects/personas/persona3.obj");
	Model alberca("resources/objects/pecera/peceraBarda.obj");
	Model lampara("resources/objects/lampara/lampara.obj");	
	Model tiburon2("resources/objects/shark_obj/shark_01.obj");
	Model delfin("resources/objects/delfin/delfin.obj");
	Model colaD("resources/objects/delfin/colaDelfin.obj");
	Model pelota("resources/objects/pelota/13517_Beach_Ball_v2_L3.obj");
	Model puert1("resources/objects/carrito/puertader.obj");
	Model puert2("resources/objects/carrito/puertaizq.obj");
	


	//InicializaciÃ³n de KeyFrames para pelota

	KeyFrame[0].posX = -45.0f;
	KeyFrame[0].posY = 5.0f;
	KeyFrame[0].posZ = 110.0f;


	KeyFrame[1].posX = 45;
	KeyFrame[1].posY = 5;
	KeyFrame[1].posZ = 210;


	KeyFrame[2].posX = 45;
	KeyFrame[2].posY = 5;
	KeyFrame[2].posZ = 110;

	KeyFrame[3].posX = -45;
	KeyFrame[3].posY = 5;
	KeyFrame[3].posZ = 210;

	KeyFrame[4].posX = 0;
	KeyFrame[4].posY = 5;
	KeyFrame[4].posZ = 110;

	KeyFrame[5].posX = -45;
	KeyFrame[5].posY = 5;
	KeyFrame[5].posZ = 110;

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		//iluminacion del escenario
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", glm::vec3(faro_x, faro_y, faro_z));
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(1.0f, 1.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 1.0f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.00000032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setVec3("spotLight[0].position", glm::vec3(150.0f, 170.0f, 0.0f));
		staticShader.setVec3("spotLight[0].direction", glm::vec3(0.0f, -1.0f, 0.0f));
		staticShader.setVec3("spotLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[0].cutOff", glm::cos(glm::radians(10.0f)));
		staticShader.setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(60.0f)));
		staticShader.setFloat("spotLight[0].constant", 1.0f);
		staticShader.setFloat("spotLight[0].linear", 0.0009f);
		staticShader.setFloat("spotLight[0].quadratic", 0.0005f);

		staticShader.setVec3("spotLight[1].position", glm::vec3(-150.0f, 170.0f, 0.0f));
		staticShader.setVec3("spotLight[1].direction", glm::vec3(0.0f, -1.0f, 0.0f));
		staticShader.setVec3("spotLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[1].cutOff", glm::cos(glm::radians(10.0f)));
		staticShader.setFloat("spotLight[1].outerCutOff", glm::cos(glm::radians(60.0f)));
		staticShader.setFloat("spotLight[1].constant", 1.0f);
		staticShader.setFloat("spotLight[1].linear", 0.0009f);
		staticShader.setFloat("spotLight[1].quadratic", 0.0005f);


		staticShader.setVec3("spotLight[2].position", glm::vec3(150.0f, 170.0f, 150.0f));
		staticShader.setVec3("spotLight[2].direction", glm::vec3(0.0f, -1.0f, 0.0f));
		staticShader.setVec3("spotLight[2].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[2].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[2].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[2].cutOff", glm::cos(glm::radians(10.0f)));
		staticShader.setFloat("spotLight[2].outerCutOff", glm::cos(glm::radians(60.0f)));
		staticShader.setFloat("spotLight[2].constant", 1.0f);
		staticShader.setFloat("spotLight[2].linear", 0.0009f);
		staticShader.setFloat("spotLight[2].quadratic", 0.0005f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		glm::mat4 tmp2 = glm::mat4(1.0f);
		//temporal delfin
		glm::mat4 tmp3 = glm::mat4(1.0f);
		glm::mat4 tmp4 = glm::mat4(1.0f);



		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);


		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);

		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

	
		model = glm::translate(glm::mat4(1.0f), glm::vec3(420.0f, 16.0f, 300.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		animShader.setMat4("model", model);
		//employe.Draw(animShader);

		// ------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);


	
		//Àrea de comida
		//comida hamburguesa
		model = glm::translate(glm::mat4(1.0f), glm::vec3(290.0f, 30.0f, 465.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		comida.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(240.0f, 30.0f, 395.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		comida.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(340.0f, 30.0f, 295.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		comida.Draw(staticShader);
//carrito
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.45f));
		staticShader.setMat4("model", model);
		carrito.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.45f));
		staticShader.setMat4("model", model);
		llantasd.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.45f));
		staticShader.setMat4("model", model);
		llantaiz.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.45f));
		staticShader.setMat4("model", model);
		llantasi.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.45f));
		staticShader.setMat4("model", model);
		llantaid.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(orientapuerta1), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.45f));
		staticShader.setMat4("model", model);
		puert1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(orientapuerta2), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.45f));
		staticShader.setMat4("model", model);
		puert2.Draw(staticShader);

		//Octopus
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movtrabx, movtraby, movtrabz));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(orientatrab), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		staticShader.setMat4("model", model);
		octopus.Draw(staticShader);
		
		//Fuente
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 150.0f));
		model = glm::scale(model, glm::vec3(5.1f));
		staticShader.setMat4("model", model);
		fuente.Draw(staticShader);


		//Valla pinguinos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(750.0f, 0.0f, -50.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		valla.Draw(staticShader);

		//Valla cangrejos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		valla2.Draw(staticShader);

		//cangrejos


		model = glm::translate(glm::mat4(1.0f), glm::vec3(-430.0f, 0.0f, 410.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		crab.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 0.0f, 480.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		crab.Draw(staticShader);

		//Octopus



		//cangrejo animado
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcrab_x, movcrab_y, movcrab_z));
		model = glm::rotate(model, glm::radians(orientacrab), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		crab2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcrab_x, movcrab_y, movcrab_z));
		model = glm::rotate(model, glm::radians(patasbcrab), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(orientacrab), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		patascrabd.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcrab_x, movcrab_y, movcrab_z));
		model = glm::rotate(model, glm::radians(patasbcrab), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(orientacrab), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		patascrabi.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcrab_x, movcrab_y, movcrab_z));
		model = glm::rotate(model, glm::radians(pinzascrab), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(orientacrab), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		pinzascrabd.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcrab_x, movcrab_y, movcrab_z));
		model = glm::rotate(model, glm::radians(pinzascrab), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(orientacrab), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		pinzascrabi.Draw(staticShader);



		//ROCAS cangrejos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-390.0f, 0.0f, 460.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		roc.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-420.0f, 0.0f, 460.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		roc.Draw(staticShader);


		//estanque cangrejos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-310.0f, 0.0f, 450.0f));
		model = glm::scale(model, glm::vec3(0.125f));
		staticShader.setMat4("model", model);
		estanque.Draw(staticShader);


		//plantas cangrejos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-350.0f, 0.0f, 430.0f));
		model = glm::scale(model, glm::vec3(0.003f));
		staticShader.setMat4("model", model);
		plant1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-460.0f, 0.0f, 440.0f));
		model = glm::scale(model, glm::vec3(0.003f));
		staticShader.setMat4("model", model);
		plant1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-350.0f, 0.0f, 450.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		plant2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-290.0f, 0.0f, 470.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		plant2.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(450.0f, 0.0f, 70.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		ping.Draw(staticShader);

		//pinguinoanimado 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(450.0f, 0.0f, 70.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		pingu2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(450.0f, 0.0f, 70.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		pingupi2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(450.0f, 0.0f, 70.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		pingupd2.Draw(staticShader);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(450.0f, 0.0f, 70.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-alaspingu), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		pinguai2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(450.0f, 0.0f, 70.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(alaspingu), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		pinguad2.Draw(staticShader);



		//pinguinoanimado 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPingu_x2, 0.0f, movPingu_z2));
		model = glm::rotate(model, glm::radians(orientaPingu2), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		pingu.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPingu_x2, 0.0f, movPingu_z2));
		model = glm::rotate(model, glm::radians(orientaPingu2), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-pataspingu), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		pingupi.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPingu_x2, 0.0f, movPingu_z2));
		model = glm::rotate(model, glm::radians(orientaPingu2), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pataspingu), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		pingupd.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPingu_x2, 0.0f, movPingu_z2));
		model = glm::rotate(model, glm::radians(orientaPingu2), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-alaspingu), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		pinguai.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPingu_x2, 0.0f, movPingu_z2));
		model = glm::rotate(model, glm::radians(orientaPingu2), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(alaspingu), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		pinguad.Draw(staticShader);



		//rocaPinguinos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(390.0f, 0.0f, -5.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		rocap.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(390.0f, 0.0f, -1.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		rocap1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(425.0f, -5.0f, 130.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		roc2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(375.0f, -5.0f, 80.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		roc2.Draw(staticShader);


		//Alberca pinguinos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(390.0f, 0.0f, 150.0f));
		model = glm::scale(model, glm::vec3(10.0f));
		staticShader.setMat4("model", model);
		pool.Draw(staticShader);


		//cafeteria

		model = glm::translate(glm::mat4(1.0f), glm::vec3(420.0f, 16.0f, 300.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		cafe.Draw(staticShader);

		//plataforma

		model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 0.0f, 400.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f));
		staticShader.setMat4("model", model);
		plat.Draw(staticShader);


		//banca
		model = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 18.0f, 470.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		banc.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(350.0f, 18.0f, 300.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		banc.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 18.0f, 400.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		banc.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(350.0f, 18.0f, 400.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		banc.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 18.0f, 300.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		banc.Draw(staticShader);

		//restrooms
		model = glm::translate(glm::mat4(1.0f), glm::vec3(460.0f, 16.0f, 450.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		rest.Draw(staticShader);

		//carro de helados
		model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 17.0f, 250.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		carro.Draw(staticShader);

		//bote de basura
		model = glm::translate(glm::mat4(1.0f), glm::vec3(350.0f, 17.0f, 250.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		bin.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(460.0f, 17.0f, 400.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		bin.Draw(staticShader);

		//jaula
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-410.0f, 0.0f, 250.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(40.0f));
		staticShader.setMat4("model", model);
		jaula.Draw(staticShader);

		//tienda
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(18.0f));
		staticShader.setMat4("model", model);
		tienda.Draw(staticShader);



		//valla delantera
		model = glm::translate(glm::mat4(1.0f), glm::vec3(151.0f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(302.0f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-151.0f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-302.0f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-420.5f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(410.5f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		



		//puerta salida

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		staticShader.setMat4("model", model);
		gate.Draw(staticShader);

		//vallas traseras

		model = glm::translate(glm::mat4(1.0f), glm::vec3(270.0f, 0.0f, -480.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(120.0f, 0.0f, -480.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-30.0f, 0.0f, -480.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-180.0f, 0.0f, -480.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-330.0f, 0.0f, -480.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-420.0f, 0.0f, -480.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(420.0f, 0.0f, -480.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		vallae.Draw(staticShader);


		//alberca 1 delfines
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-330.0f, 0.0f, -280.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.5f));
		staticShader.setMat4("model", model);
		alberca.Draw(staticShader);


		//alberca 2 tiburones
		model = glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 0.0f, -250.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(11.5f));
		staticShader.setMat4("model", model);
		alberca.Draw(staticShader);

		//alberca 3 peces
		model = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 0.0f, -90.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(11.5f));
		staticShader.setMat4("model", model);
		alberca.Draw(staticShader);



		//ave
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movAve_x, 130.0f, movAve_z));
		tmp3 = model = glm::rotate(model, glm::radians(orientaAve), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		cuerpoAve.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movAve_x, 133.0f, movAve_z));
		tmp3 = model = glm::rotate(model, glm::radians(orientaAve), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp3 = model = glm::rotate(model, glm::radians(-alasAve / 2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(25.0f));
		staticShader.setMat4("model", model);
		alaIzq.Draw(staticShader);

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movAve_x, 133.0f, movAve_z));
		tmp3 = model = glm::rotate(model, glm::radians(orientaAve), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp3 = model = glm::rotate(model, glm::radians(alasAve / 2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		alaDer.Draw(staticShader);

	//DELFIN 1

		model = glm::translate(glm::mat4(1.0f), glm::vec3(pos_x, pos_y, pos_z));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		tmp3 = model = glm::rotate(model, glm::radians(orienta), glm::vec3(1.0f, 0.0f, 0.0f));

		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		delfin.Draw(staticShader);

		//cola delfin 1
		model = glm::translate(tmp3, glm::vec3(0.0f, cola_y, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		colaD.Draw(staticShader);

		//DELFIN 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(pos_xx, pos_yy, pos_zz));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp4 = model = glm::rotate(model, glm::radians(orienta), glm::vec3(1.0f, 0.0f, 0.0f));

		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		delfin.Draw(staticShader);

		//cola delfin 2
		model = glm::translate(tmp4, glm::vec3(0.0f, cola_y, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		colaD.Draw(staticShader);


		//pelota 
		model = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
		model = glm::scale(model, glm::vec3(0.3f));
		model = glm::rotate(model, glm::radians(girapelota), glm::vec3(1.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		pelota.Draw(staticShader);



	//peces
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movfish1_x, movfish1_y, movfish1_z));
		model = glm::rotate(model, glm::radians(orientafish1), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		fish1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movfish1_x, movfish1_y, movfish1_z));
		model = glm::rotate(model, glm::radians(orientafish1), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(orientacola), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		fish1cola.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movfish1_x, movfish1_y, movfish1_z));
		model = glm::rotate(model, glm::radians(orientafish1), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(orientaalizq), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		fish1alizq.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movfish1_x, movfish1_y, movfish1_z));
		model = glm::rotate(model, glm::radians(orientafish1), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(orientaalder), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		fish1alder.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(40.0f, 5.0f, -120.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		//fish1.Draw(staticShader);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(25.0f, 5.0f, -130.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		//fish1.Draw(staticShader);

		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-15.0f, 5.0f, -110.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		fish2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-15.0f, 5.0f, -140.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		fish2.Draw(staticShader);

	//Tiburones
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movtibu10_x, -10.0f, movtibu10_z));
		model = glm::rotate(model, glm::radians(girotibu10), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		tibu10.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movtibu10_x, -10.0f, movtibu10_z));
		model = glm::rotate(model, glm::radians(girotibu10), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(orientacolat10), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		colatibu10.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movtibu10_x, -10.0f, movtibu10_z));
		model = glm::rotate(model, glm::radians(girotibu10), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(orientamant10), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		mantibu10.Draw(staticShader);
		


	//Personas
		//persona 1 mujer
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-200.0f, 4.0f, 250.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		//persona1.Draw(staticShader);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-150.0f, 4.0f, -200.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		//persona1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-300.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		//persona2.Draw(staticShader);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 300.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		//persona2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(190.0f, 0.0f, -300.0f));
		model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		//persona2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(190.0f, 2.0f, 200.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		//persona3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-170.0f, 2.0f, 250.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		//persona3.Draw(staticShader);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(180.0f, 2.0f, -100.0f));
		model = glm::rotate(model, glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		//persona3.Draw(staticShader);

		//lamparas
		model = glm::translate(glm::mat4(1.0f), glm::vec3(180.0f, 0.0f, 70.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		lampara.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-180.0f, 0.0f, 70.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		lampara.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(180.0f, 0.0f, 200.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		lampara.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-180.0f, 0.0f, 200.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		lampara.Draw(staticShader);

	
		
		//Aves
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-370.0f, 0.0f, 300.0f));
		model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		ave1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-470.0f, 0.0f, 230.0f));
		model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		//ave1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 30.0f, 250.0f));
		model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		//ave2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-350.0f, 90.0f, 300.0f));
		model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		ave2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 70.0f, 250.0f));
		model = glm::rotate(model, glm::radians(340.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		//ave2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 50.0f, 200.0f));
		model = glm::rotate(model, glm::radians(340.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		//ave3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 90.0f, 200.0f));
		model = glm::rotate(model, glm::radians(300.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		//ave3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-360.0f, 40.0f, 310.0f));
		model = glm::rotate(model, glm::radians(280.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		//ave3.Draw(staticShader);
		
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	skybox.Terminate();
	glfwTerminate();
	engine->drop();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//To Configure Model
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		posZ++;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		posZ--;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		posX--;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		posX++;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		rotRodIzq--;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		rotRodIzq++;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		giroMonito--;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		giroMonito++;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;

	//Torniquetes animacion

	//Animacion peces
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		animFish1 ^= true;


	//animacion tiburon


	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		animtbu10 ^= true;

	//animacion bote
	if (key == GLFW_KEY_9 && action == GLFW_PRESS)
		animacionB ^= true;

	//delfin 
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		animacion2 ^= true;

	//animacion pellota
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		animacion3 ^= true;

/*
	//sonido aves
	if (key == GLFW_KEY_O && action == GLFW_PRESS)
		music();


	//sonido pinguino
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
		music2();
	//sonido delfines
	if (key == GLFW_KEY_K && action == GLFW_PRESS)
		music3();
*/
	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}