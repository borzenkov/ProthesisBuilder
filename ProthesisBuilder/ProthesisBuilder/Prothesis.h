// MedBox
// Prothesis.h
// (c) Victor Borzenkov 2014

#ifndef __Prothesis_h
#define __Prothesis_h

#include "ProthesisInputData.h"

#include <iostream>
#include <TopoDS_Shape.hxx>
#include <gp_Pnt.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <GC_MakeSegment.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <gp_Ax1.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array1OfVec.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <TColStd_HArray1OfBoolean.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <StlAPI_Writer.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <Geom_Plane.hxx>
#include <ShapeFix_ShapeTolerance.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepAlgo_Section.hxx>
#include <gp_Pln.hxx>
#include <ShapeExtend_WireData.hxx>
#include <TopoDS.hxx>
#include <ShapeFix_Wire.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <ChFi2d_FilletAPI.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <cmath>

////for visulizing
//#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
//#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)
//#include "TopoDS_Shape.hxx"
//#include "BRepPrimAPI_MakeSphere.hxx"
//#include "IVtkOCC_Shape.hxx"
//#include "IVtkTools_ShapeDataSource.hxx"
//#include "IVtkTools_DisplayModeFilter.hxx"
//#include "vtkPolyDataMapper.h"
//#include "vtkActor.h"
//#include "vtkRenderer.h"
//#include "vtkRenderWindow.h"
//#include "vtkRenderWindowInteractor.h"
//#include "vtkDataSetMapper.h"


class ProthesisBuilder
{
protected:
	
public:
	/*void visualize();*/

	ProthesisBuilder(ProthesisInputData* inputs);
	
	ProthesisBuilder()
	{
	}

	// 
	void WriteToSTLFile(Standard_CString name);

	void WriteToSTLFileLight(Standard_CString name);

	void Build();

	//Building without boolean fuse = faster building
	void LightBuild();

	void TestBuild();

	//Creates adhering surface projecting the prothesis's plate onto the jaw 
	void CreateAdheringSurface(); /*YOU STOPPED HERE*/

private:
	TopoDS_Shape Prothesis;
	void MakeHead();
	void MakeHoles(TopoDS_Shape &);
	void MakeJunction();
	void MakePlate();
	
	void CreateFirstJunctionContour();
	void CreateSecondJunctionContour();
	void CreateThirdJunctionContour();
	void CreateMiddleJunctionContour();
	void PositionHead();
	void MakeFillets(TopoDS_Shape &);
	TopoDS_Wire FindIntersection();
	void MakePrismaticHole(TopoDS_Shape &);
	TopoDS_Wire MakePrismaticHoleContour();
	void UnitePlateAndJunction();
	void UnitePlateJunctionAndHead();
	void UniteJunctionAndHead();
	
	ProthesisInputData * InputParams;
	TopoDS_Shape Head;
	TopoDS_Shape PlateAndJunction;
	TopoDS_Shape JunctionAndHead;
	gp_Pnt HeadCenter;
	gp_Pln HeadPlane;
	TopoDS_Wire HeadWire;
	TopoDS_Wire completedHeadWire;
	TopoDS_Wire ThirdJunctionContour;
	gp_Ax1 thirdJunctionContourDisplacementDirection;
	TopoDS_Shape Junction;
	TopoDS_Shape Junction2;
	TopoDS_Shape Plate;
	TopoDS_Wire FirstJunctionContour;
	TopoDS_Wire MiddleJunctionContour;
	TopoDS_Wire SecondJunctionContour;
};

#endif 