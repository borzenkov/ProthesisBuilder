 MedBox
 Prothesis builder program
 (c) Victor Borzenkov 2014
#define _SCL_SECURE_NO_WARNINGS //The program won't compile without this string
#define _CRT_SECURE_NO_WARNINGS
#include "ProthesisInputData.h"
#include "Prothesis.h"

int main()
{
	// Create an object for passing inputs to Prothesis builder class
	ProthesisInputData * inputs = new ProthesisInputData();

	//Setting geometric params for the future 3D model.
	//See drawing NewProthesis.dwg for help.


	/*первый набор параметров*/
	inputs->a = 26;
	inputs->b = 19;
	inputs->c = 7;
	inputs->d = 45;
	inputs->e = 42;
	inputs->f = 28;
	inputs->g = 13;
	inputs->h = 57;
	inputs->i = 49;
	inputs->j = 21;
	inputs->k = 17;
	inputs->l = 28;
	inputs->m = 11;
	inputs->n = 7;
	inputs->o = 7;
	inputs->p = 6;
	inputs->q = 2;
	inputs->r = 5;
	inputs->s = 5;
	inputs->t = 15;
	inputs->u = 22;
	inputs->v = 6;
	inputs->w = 6;
	inputs->x = 13;
	inputs->y = -13;
	inputs->z = 7;
	inputs->a1 = 23;
	inputs->b1 = 1;
	inputs->c1 = 10 * 3.14 / 180;
	inputs->d1 = 90 * 3.14 / 180;

	///*второй набор параметров*/
	//inputs->a = 26*0.8;
	//inputs->b = 19*0.8;
	//inputs->c = 7*0.8;
	//inputs->d = 45;
	//inputs->e = 42;
	//inputs->f = 28;
	//inputs->g = 15;
	//inputs->h = 57*1.05;
	//inputs->i = 49;
	//inputs->j = 21;
	//inputs->k = 17;
	//inputs->l = 28;
	//inputs->m = 11;
	//inputs->n = 7;
	//inputs->o = 7;
	//inputs->p = 6*0.8;
	//inputs->q = 2;
	//inputs->r = 6;
	//inputs->s = 5;
	//inputs->t = 15;
	//inputs->u = 22*1.1;
	//inputs->v = 6*0.9;
	//inputs->w = 6;
	//inputs->x = 13;
	//inputs->y = -13;
	//inputs->z = 7*1.1;
	//inputs->a1 = 23*0.9;
	//inputs->b1 = 1 * 1.1;
	//inputs->c1 = 15 * 3.14 / 180;
	//inputs->d1 = 85 * 3.14 / 180;

	///*третий набор параметров*/
	//inputs->a = 26 * 1.1;
	//inputs->b = 19 * 1.1;
	//inputs->c = 7 * 1.1;
	//inputs->d = 45;
	//inputs->e = 42;
	//inputs->f = 28;
	//inputs->g = 13;
	//inputs->h = 57 * 0.9;
	//inputs->i = 49;
	//inputs->j = 21;
	//inputs->k = 17;
	//inputs->l = 28*1.1;
	//inputs->m = 11;
	//inputs->n = 7;
	//inputs->o = 7;
	//inputs->p = 6 * 0.8;
	//inputs->q = 2*0.5;
	//inputs->r = 4;
	//inputs->s = 5;
	//inputs->t = 15;
	//inputs->u = 22*0.9;
	//inputs->v = 6*1.1;
	//inputs->w = 6;
	//inputs->x = 13;
	//inputs->y = -13;
	//inputs->z = 7*1.2;
	//inputs->a1 = 23*1.1;
	//inputs->b1 = 1 * 0.9;
	//inputs->c1 = -10 * 3.14 / 180;
	//inputs->d1 = 95 * 3.14 / 180;

	///*четвертый набор параметров*/
	//inputs->a = 26 ;
	//inputs->b = 19 ;
	//inputs->c = 7 ;
	//inputs->d = 45;
	//inputs->e = 42;
	//inputs->f = 28;
	//inputs->g = 13;
	//inputs->h = 57 ;
	//inputs->i = 49;
	//inputs->j = 21;
	//inputs->k = 17 * 0.5;
	//inputs->l = 28 ;
	//inputs->m = 11 * 1.1;
	//inputs->n = 7;
	//inputs->o = 7;
	//inputs->p = 6 ;
	//inputs->q = 2 ;
	//inputs->r = 5;
	//inputs->s = 5;
	//inputs->t = 15;
	//inputs->u = 22;
	//inputs->v = 6;
	//inputs->w = 6;
	//inputs->x = 13;
	//inputs->y = -13;
	//inputs->z = 7;
	//inputs->a1 = 23*1.2;
	//inputs->b1 = 1*1.2;
	//inputs->c1 = 20 * 3.14 / 180;
	//inputs->d1 = 90 * 3.14 / 180;

	////head params
	////coordinates of points
	//inputs->x1 = 0;
	//inputs->y1 = 0;
	//inputs->x2 = 4.92;
	//inputs->y2 = 6.017;
	//inputs->x3 = 17;
	//inputs->y3 = 5.88;
	//inputs->x4 = 25;
	//inputs->y4 = 0;
	////tangent angels of second and third points(degrees)
	//inputs->tang_ang_deg_2 = 3;
	//inputs->tang_ang_deg_3 = -3;
	////head center displacement
	//inputs->head_center_x_disp = 7.21;
	//inputs->head_center_y_disp = 25;
	//inputs->head_center_z_disp = 3;
	//inputs->head_angle_OX = 20 * 3.14 / 180;
	//inputs->head_angle_OY = 90 * 3.14 / 180;
	//inputs->head_angle_OZ = 0;




	//Updating model's geometry information
	inputs->Update();

	ProthesisBuilder prothesis(inputs);
	prothesis.LightBuild();
	//prothesis.visualize();
	prothesis.WriteToSTLFileLight("C:/FILES/ProthesisBuilder/OUTPUT/Plate.stl");
	delete inputs;
	return 0;
}