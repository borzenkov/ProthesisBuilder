#include "Sia.h"

// This is included here because it is forward declared in
// Sia.h
#include "ui_Sia.h"

// Constructor
Sia::Sia()
{
	this->ui = new Ui_Sia;
	this->ui->setupUi(this);

	QFile file("C:/DEV/StudyingProjects/Sia/SiaStyleSheet.css");
	if (file.open(QFile::ReadOnly))
	{
		QString styleSheet = QLatin1String(file.readAll());
		file.close();
		setStyleSheet(styleSheet);
	}

	// Set up action signals and slots
	connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
	connect(this->ui->in_dx, SIGNAL(valueChanged(int)), this, SLOT(change_dx(int)));
	connect(this->ui->in_dy, SIGNAL(valueChanged(int)), this, SLOT(change_dy(int)));
	connect(this->ui->in_dz, SIGNAL(valueChanged(int)), this, SLOT(change_dz(int)));

	connect(this->ui->origin_x, SIGNAL(valueChanged(int)), this, SLOT(change_origin_x(int)));
	connect(this->ui->origin_y, SIGNAL(valueChanged(int)), this, SLOT(change_origin_y(int)));
	connect(this->ui->origin_z, SIGNAL(valueChanged(int)), this, SLOT(change_origin_z(int)));

	connect(this->ui->angle_around_x, SIGNAL(valueChanged(int)), this, SLOT(change_angle_around_x(int)));
	connect(this->ui->angle_around_y, SIGNAL(valueChanged(int)), this, SLOT(change_angle_around_y(int)));
	connect(this->ui->angle_around_z, SIGNAL(valueChanged(int)), this, SLOT(change_angle_around_z(int)));

	connect(this->ui->head_representation_length_slider, SIGNAL(valueChanged(int)), this, SLOT(change_head_representation_length(int)));

	createHeadRepresentation(7, 2, 2, 10, 5, 1.7, -10);

	axes = vtkSmartPointer<vtkAxesActor>::New();

	// VTK/Qt wedded
	this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

	widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	widget->SetOrientationMarker(axes);
	widget->SetInteractor(this->ui->qvtkWidget->GetInteractor());
	widget->SetViewport(0.0, 0.0, 0.4, 0.4);
	widget->SetEnabled(1);
	//widget->InteractiveOn();
	widget->InteractiveOff();
	
	renderer->ResetCamera();
}

void Sia::change_dx(int value)
{
	updateMyBox(value, this->ui->in_dy->value(), this->ui->in_dz->value());
}

void Sia::change_dy(int value)
{
	updateMyBox(this->ui->in_dx->value(), value, this->ui->in_dz->value());
}

void Sia::change_dz(int value)
{
	updateMyBox(this->ui->in_dx->value(), this->ui->in_dy->value(), value);
}

void Sia::updateMyBox(int dx, int dy, int dz)
{
	BRepPrimAPI_MakeBox mkBox(dx, dy, dz);
	mkBox.Build();
	TopoDS_Shape boxShape = mkBox.Shape();

	IVtkOCC_Shape::Handle newShapeImpl = new IVtkOCC_Shape(boxShape);

	DS->SetShape(newShapeImpl);

	this->ui->qvtkWidget->update();
	renderer->ResetCamera();
}

void Sia::change_origin_x(int value)
{
	boxActor->SetPosition(value, boxActor->GetOrigin()[1], boxActor->GetOrigin()[2]);
	this->ui->qvtkWidget->update();
}

void Sia::change_origin_y(int value)
{
	boxActor->SetPosition(boxActor->GetOrigin()[0], value, boxActor->GetOrigin()[2]);
	this->ui->qvtkWidget->update();
}

void Sia::change_origin_z(int value)
{
	boxActor->SetPosition(boxActor->GetOrigin()[0], boxActor->GetOrigin()[1], value);
	this->ui->qvtkWidget->update();
}
 
void Sia::change_angle_around_x(int value)
{
	boxActor->SetOrientation(value, boxActor->GetOrientation()[1], boxActor->GetOrientation()[2]);
	this->ui->qvtkWidget->update();
}
void Sia::change_angle_around_y(int value)
{
	boxActor->SetOrientation(boxActor->GetOrientation()[0], value, boxActor->GetOrientation()[2]);
	this->ui->qvtkWidget->update();
}
void Sia::change_angle_around_z(int value)
{
	boxActor->SetOrientation(boxActor->GetOrientation()[0], boxActor->GetOrientation()[1], value);
	this->ui->qvtkWidget->update();
}

void Sia::slotExit() 
{
  qApp->exit();
}

void Sia::create_and_show_MyBox()
{
	BRepPrimAPI_MakeBox mkBox(1.0, 1.0, 1.0);
	mkBox.Build();
	TopoDS_Shape boxShape = mkBox.Shape();

	IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(boxShape);
	DS = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
	DS->SetShape(aShapeImpl);

	DMFilter = vtkSmartPointer<IVtkTools_DisplayModeFilter>::New();
	DMFilter->AddInputConnection(DS->GetOutputPort());
	DMFilter->SetDisplayMode(DM_Shading);

	boxMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	boxMapper->SetInputConnection(DMFilter->GetOutputPort());
	boxActor = vtkSmartPointer<vtkActor>::New();
	boxActor->SetMapper(boxMapper);

	// VTK Renderer
	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(boxActor);
}

void Sia::create_and_show_MySphere()
{
	BRepPrimAPI_MakeSphere mkSphere(1);
	mkSphere.Build();
	TopoDS_Shape boxShape = mkSphere.Shape();

	IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(boxShape);
	DS = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
	DS->SetShape(aShapeImpl);

	DMFilter = vtkSmartPointer<IVtkTools_DisplayModeFilter>::New();
	DMFilter->AddInputConnection(DS->GetOutputPort());
	DMFilter->SetDisplayMode(DM_Shading);

	boxMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	boxMapper->SetInputConnection(DMFilter->GetOutputPort());
	boxActor = vtkSmartPointer<vtkActor>::New();
	boxActor->SetMapper(boxMapper);

	// VTK Renderer
	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(boxActor);
}

void Sia::createHeadRepresentation(double head_representation_length,
	double head_representation_A_point_axial_coordinate,
	double head_representation_A_point_radial_coordinate,
	double head_representation_A_point_slope_of_tangent_line,
	double head_representation_B_point_axial_coordinate,
	double head_representation_B_point_radial_coordinate,
	double head_representation_B_point_slope_of_tangent_line)
{
	//головка-тело, полученное вращением вокруг оси симметрии
	//сплайна из 4 точек
	gp_Pnt Pnt1(0, 0, 0);
	gp_Pnt Pnt2(head_representation_A_point_axial_coordinate, head_representation_A_point_radial_coordinate, 0);
	gp_Pnt Pnt3(head_representation_B_point_axial_coordinate, head_representation_B_point_radial_coordinate, 0);
	gp_Pnt Pnt4(head_representation_length, 0, 0);

	gp_Vec Vec(head_representation_length, 0, 0); //¬ектор, задающий ось вращени€ контура
	gp_Dir Dir(Vec);
	gp_Ax1 HeadAxis(Pnt4, Dir);

	double head_representation_A_point_slope_of_tangent_line_rad = (head_representation_A_point_slope_of_tangent_line * M_PI) / 180;
	double head_representation_B_point_slope_of_tangent_line_rad = (head_representation_B_point_slope_of_tangent_line * M_PI) / 180;

	gp_Vec Vec1(0, 1, 0); //¬-р, задающий касательное направление в первой точке сплайна
	gp_Vec Vec2(cos(head_representation_A_point_slope_of_tangent_line_rad), sin(head_representation_A_point_slope_of_tangent_line_rad), 0);
	gp_Vec Vec3(cos(head_representation_B_point_slope_of_tangent_line_rad), sin(head_representation_B_point_slope_of_tangent_line_rad), 0);
	gp_Vec Vec4(-Vec1); //¬-р, задающий касаткльное направление в последней точке сплайна

	TColgp_Array1OfPnt CurvePoles(1, 4);
	CurvePoles(1) = Pnt1;
	CurvePoles(2) = Pnt2;
	CurvePoles(3) = Pnt3;
	CurvePoles(4) = Pnt4;

	TColgp_Array1OfVec tang(1, 4);
	tang(1) = Vec1;
	tang(2) = Vec2;
	tang(3) = Vec3;
	tang(4) = Vec4;

	Handle(TColgp_HArray1OfPnt) points = new TColgp_HArray1OfPnt(1, 4);
	points->SetValue(1, Pnt1);
	points->SetValue(2, Pnt2);
	points->SetValue(3, Pnt3);
	points->SetValue(4, Pnt4);
	GeomAPI_Interpolate curve(points, Standard_False, 0.1);
	curve.Perform();
	Handle(TColStd_HArray1OfBoolean) bools = new TColStd_HArray1OfBoolean(1, 4);
	bools->SetValue(1, Standard_True);
	bools->SetValue(2, Standard_True);
	bools->SetValue(3, Standard_True);
	bools->SetValue(4, Standard_True);
	curve.Load(tang, bools);
	curve.Perform();

	Handle(Geom_BSplineCurve) C = curve.Curve();

	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(C);//не работает без хэндла!!!

	TopoDS_Wire HeadWire = BRepBuilderAPI_MakeWire(E);

	TopoDS_Face HeadFace = BRepBuilderAPI_MakeFace(HeadWire);

	TopoDS_Shape Head = BRepPrimAPI_MakeRevol(HeadFace, HeadAxis).Shape();

	IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(Head);
	DS = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
	DS->SetShape(aShapeImpl);

	DMFilter = vtkSmartPointer<IVtkTools_DisplayModeFilter>::New();
	DMFilter->AddInputConnection(DS->GetOutputPort());
	DMFilter->SetDisplayMode(DM_Wireframe);

	boxMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	boxMapper->SetInputConnection(DMFilter->GetOutputPort());
	boxActor = vtkSmartPointer<vtkActor>::New();
	boxActor->SetMapper(boxMapper);

	// VTK Renderer
	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(boxActor);
}

void Sia::updateHeadRepresentation(double head_representation_length,
	double head_representation_A_point_axial_coordinate,
	double head_representation_A_point_radial_coordinate,
	double head_representation_A_point_slope_of_tangent_line,
	double head_representation_B_point_axial_coordinate,
	double head_representation_B_point_radial_coordinate,
	double head_representation_B_point_slope_of_tangent_line)
{
	//головка-тело, полученное вращением вокруг оси симметрии
	//сплайна из 4 точек
	gp_Pnt Pnt1(0, 0, 0);
	gp_Pnt Pnt2(head_representation_A_point_axial_coordinate, head_representation_A_point_radial_coordinate, 0);
	gp_Pnt Pnt3(head_representation_B_point_axial_coordinate, head_representation_B_point_radial_coordinate, 0);
	gp_Pnt Pnt4(head_representation_length, 0, 0);

	gp_Vec Vec(head_representation_length, 0, 0); //¬ектор, задающий ось вращени€ контура
	gp_Dir Dir(Vec);
	gp_Ax1 HeadAxis(Pnt4, Dir);

	double head_representation_A_point_slope_of_tangent_line_rad = (head_representation_A_point_slope_of_tangent_line * M_PI) / 180;
	double head_representation_B_point_slope_of_tangent_line_rad = (head_representation_B_point_slope_of_tangent_line * M_PI) / 180;

	gp_Vec Vec1(0, 1, 0); //¬-р, задающий касательное направление в первой точке сплайна
	gp_Vec Vec2(cos(head_representation_A_point_slope_of_tangent_line_rad), sin(head_representation_A_point_slope_of_tangent_line_rad), 0);
	gp_Vec Vec3(cos(head_representation_B_point_slope_of_tangent_line_rad), sin(head_representation_B_point_slope_of_tangent_line_rad), 0);
	gp_Vec Vec4(-Vec1); //¬-р, задающий касаткльное направление в последней точке сплайна

	TColgp_Array1OfPnt CurvePoles(1, 4);
	CurvePoles(1) = Pnt1;
	CurvePoles(2) = Pnt2;
	CurvePoles(3) = Pnt3;
	CurvePoles(4) = Pnt4;

	TColgp_Array1OfVec tang(1, 4);
	tang(1) = Vec1;
	tang(2) = Vec2;
	tang(3) = Vec3;
	tang(4) = Vec4;

	Handle(TColgp_HArray1OfPnt) points = new TColgp_HArray1OfPnt(1, 4);
	points->SetValue(1, Pnt1);
	points->SetValue(2, Pnt2);
	points->SetValue(3, Pnt3);
	points->SetValue(4, Pnt4);
	GeomAPI_Interpolate curve(points, Standard_False, 1.0e-7);
	Handle(TColStd_HArray1OfBoolean) bools = new TColStd_HArray1OfBoolean(1, 4);
	bools->SetValue(1, Standard_True);
	bools->SetValue(2, Standard_True);
	bools->SetValue(3, Standard_True);
	bools->SetValue(4, Standard_True);
	curve.Load(tang, bools);
	curve.Perform();

	Handle(Geom_BSplineCurve) C = curve.Curve();

	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(C);//не работает без хэндла!!!

	TopoDS_Wire HeadWire = BRepBuilderAPI_MakeWire(E);

	TopoDS_Face HeadFace = BRepBuilderAPI_MakeFace(HeadWire);

	TopoDS_Shape Head = BRepPrimAPI_MakeRevol(HeadFace, HeadAxis).Shape();
	
	IVtkOCC_Shape::Handle newShapeImpl = new IVtkOCC_Shape(Head);

	DS->SetShape(newShapeImpl);

	this->ui->qvtkWidget->update();
	renderer->ResetCamera();
}

void Sia::change_head_representation_length(int new_length)
{
	updateHeadRepresentation(new_length, 2, 2, 10, 5, 1.7, -10);
}