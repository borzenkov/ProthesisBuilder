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

	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
	effect->setBlurRadius(6); //Adjust accordingly
	effect->setOffset(3, 3); //Adjust accordingly
	this->ui->pushButton->setGraphicsEffect(effect);
	

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
	
	renderer->ResetCamera();//adds cool effect
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
