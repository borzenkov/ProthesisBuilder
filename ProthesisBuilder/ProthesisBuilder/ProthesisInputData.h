// MedBox
// ProthesisInputData.h
// (c) Victor Borzenkov 2014

#ifndef __ProthesisInputData_h
#define __ProthesisInputData_h

enum orientation { LEFT, RIGHT };

struct Hole
{
	double x;
	double y;
	double radius;
	double depth;
	bool isActive;
};

// Used to store input parameters for building mandibular joint prothesis
class ProthesisInputData
{
public:
	ProthesisInputData()
	{
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		e = 0;
		f = 0;
		g = 0;
		h = 0;
		i = 0;
		j = 0;
		k = 0;
		l = 0;

		ax = 0;
		ay = 0;
		bx = 0;
		by = 0;
		cx = 0;
		cy = 0;
		dx = 0;
		dy = 0;
		ex = 0;
		ey = 0;
		fx = 0;
		fy = 0;
		PlateThickness = 0;
		x1, y1 = 0;
		x2, y2 = 0;
		x3, y3 = 0;
		x4, y4 = 0;
	}

	// Convenience constructor, fills the internal vars with data provided in form of array
	// inputs[] must be array of double with 21 elements
	ProthesisInputData(double inputs[]);

	// Not implemented
	ProthesisInputData(const ProthesisInputData& inputs)
	{}

	//Updates geometry information for building model
	// Recalculates internal representation of input params
	//Use it after you set/changed input params.
	void Update();

	// Свойства пластинки
	double a;
	double b;
	double c;
	double d;
	double e;
	double f;
	double g;
	double h;
	double i;
	double j;
	double k;
	double l;
	double r, x, y;

	double ax;
	double ay;
	double bx;
	double by;
	double cx;
	double cy;
	double dx;
	double dy;
	double ex;
	double ey;
	double fx;
	double fy;
	double PlateThickness;
	// Свойства головки
	double x1, y1;
	double x2, y2;
	double x3, y3;
	double x4, y4;
	double tang_ang_deg_2;
	double tang_ang_deg_3;
	double tang_ang_rad_2;
	double tang_ang_rad_3;

	double head_center_x_disp;
	double head_center_y_disp;
	double head_center_z_disp;
	double head_angle_OX; //degree
	double head_angle_OY; //degree
	double head_angle_OZ; //degree
	// отверстияs
	Hole holes[6];

	// скругления
	double plateFillets[50];
	double plateFillets2[4];

	double m, n, o, p, q, s, t, u, v, w, z, a1, b1, c1, d1;

	orientation orientation;
};

#endif 