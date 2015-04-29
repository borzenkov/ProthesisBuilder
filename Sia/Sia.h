#ifndef Sia_H
#define Sia_H
 
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
#include <IVtkOCC_Shape.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <IVtkTools_DisplayModeFilter.hxx>

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
	void change_dx(int value);
	void change_dy(int value);
	void change_dz(int value);
	void change_origin_x(int value);
	void change_origin_y(int value);
	void change_origin_z(int value);
	void change_angle_around_x(int value);
	void change_angle_around_y(int value);
	void change_angle_around_z(int value);
	virtual void slotExit();

private:
	vtkSmartPointer<IVtkTools_ShapeDataSource> DS;
	vtkSmartPointer<IVtkTools_DisplayModeFilter> DMFilter;
	vtkSmartPointer<vtkPolyDataMapper> boxMapper;
	vtkSmartPointer<vtkActor> boxActor;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkAxesActor> axes;
	vtkSmartPointer<vtkOrientationMarkerWidget> widget;

	void updateMyBox(int dx, int dy, int dz);
	// Designer form
	Ui_Sia *ui;
};
 
#endif
