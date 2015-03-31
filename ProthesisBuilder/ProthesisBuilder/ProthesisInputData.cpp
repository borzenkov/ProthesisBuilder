//// MedBox
//// ProthesisInputData.cpp
//// (c) Victor Borzenkov 2014
//
//#include "ProthesisInputData.h"
//# define M_PI 3.14159265358979323846  
//
//void ProthesisInputData::Update()
//{
//	//Point A is an origin point so its coordinates are zeros.
//	ax = 0;
//	ay = 0;
//	bx = a;
//	by = k;
//	cx = a;
//	cy = i;
//	dx = l;
//	dy = h;
//	ex = m;
//	ey = h;
//	fx = 0;
//	fy = d;
//	PlateThickness = r;
//	tang_ang_deg_2 = x;
//	tang_ang_deg_3 = y;
//
//	tang_ang_rad_2 = (tang_ang_deg_2 * M_PI) / 180;
//	tang_ang_rad_3 = (tang_ang_deg_3 * M_PI) / 180;
//
//	holes[0].x = c;
//	holes[0].y = g;
//	holes[1].x = c;
//	holes[1].y = f;
//	holes[2].x = c;
//	holes[2].y = e;
//	holes[3].x = b;
//	holes[3].y = e;
//
//
//	//// h = create fillet with radius equal to h
//	//// 0 = no need for fillet on this edge (possibly because the edge is extracted twice)
//	//plateFillets[0] = h;
//	//plateFillets[1] = h;
//	//plateFillets[2] = 0;
//	//plateFillets[3] = 0;
//	//plateFillets[4] = h;
//	//plateFillets[5] = 0; // don't make a fillet on this edge because it produces error
//	//plateFillets[6] = 0;
//	//plateFillets[7] = 0;
//	//plateFillets[8] = 0; // don't make a fillet on this edge because it produces error
//	//plateFillets[9] = h;
//
//	//plateFillets2[0] = k;
//	//plateFillets2[1] = 0;//hz
//	//plateFillets2[2] = 0;//hz
//	//plateFillets2[3] = k;
//}
//
//ProthesisInputData::ProthesisInputData(double inputs[])
//{
//	// Find a drawing with these parameters here:
//	// TODO: Vitya, fill the address!!!
//
//	// Свойства пластинки
//	ax = inputs[0];
//	ay = inputs[1];
//	bx = inputs[2];
//	by = inputs[3];
//	cx = inputs[4];
//	cy = inputs[5];
//	dx = inputs[6];
//	dy = inputs[7];
//	ex = inputs[8];
//	ey = inputs[9];
//	fx = inputs[10];
//	fy = inputs[11];
//	PlateThickness = inputs[12];
//	// Свойства головки
//	x1 = inputs[13];
//	y1 = inputs[14];
//	x2 = inputs[15];
//	y2 = inputs[16];
//	x3 = inputs[17];
//	y3 = inputs[18];
//	x4 = inputs[19];
//	y4 = inputs[20];
//}