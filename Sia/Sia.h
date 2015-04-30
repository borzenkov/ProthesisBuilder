#ifndef Sia_H
#define Sia_H
 
# define M_PI 3.14159265358979323846

#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>

#include <QMainWindow>
#include <QFile>
#include <QGraphicsDropShadowEffect>

#define WNT
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <IVtkOCC_Shape.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <IVtkTools_DisplayModeFilter.hxx>

/*Libraries for head creation*/
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array1OfVec.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <TColStd_HArray1OfBoolean.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>

// Forward Qt class declarations
class Ui_Sia;
 
class Sia : public QMainWindow
{
	Q_OBJECT
public:
	// Constructor/Destructor
	Sia(); 
	~Sia() {};
 
public slots:
	void change_dx(int);
	void change_dy(int);
	void change_dz(int);
	void change_origin_x(int);
	void change_origin_y(int);
	void change_origin_z(int);
	void change_angle_around_x(int);
	void change_angle_around_y(int);
	void change_angle_around_z(int);
	void change_head_representation_length(int);
	virtual void slotExit();

private:
	vtkSmartPointer<IVtkTools_ShapeDataSource> DS;
	vtkSmartPointer<IVtkTools_DisplayModeFilter> DMFilter;
	vtkSmartPointer<vtkPolyDataMapper> boxMapper;
	vtkSmartPointer<vtkActor> boxActor;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkAxesActor> axes;
	vtkSmartPointer<vtkOrientationMarkerWidget> widget;

	void create_and_show_MyBox();
	void create_and_show_MySphere();
	void updateMyBox(int dx, int dy, int dz);
	void createHeadRepresentation(double, double, double, double, double, double, double);
	void updateHeadRepresentation(double, double, double, double, double, double, double);
	// Designer form
	Ui_Sia *ui;
};
 
#endif
