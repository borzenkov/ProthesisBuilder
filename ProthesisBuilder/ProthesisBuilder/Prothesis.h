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

#include <CGAL/Cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/parameterize.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_polyhedron_triangle_primitive.h>
#include <CGAL/aff_transformation_tags.h>
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include "stdio.h"
//
//typedef std::string string;
//typedef std::ifstream ifstream;
//typedef CGAL::Cartesian<double> Kernel;
//typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
//typedef Polyhedron::Facet_iterator Facet_iterator;
//typedef Polyhedron::Vertex_iterator Vertex_iterator;
//typedef Polyhedron::Point_iterator Point_iterator;
//typedef Polyhedron::Halfedge_around_facet_circulator Halfedge_facet_circulator;
//typedef Kernel::Point_3 Point_3;
//typedef Kernel::Direction_3 Direction_3;
//typedef Kernel::Vector_3 Vector_3;
//typedef Polyhedron::HalfedgeDS HalfedgeDS;
//typedef Kernel::Ray_3 Ray;
//typedef CGAL::AABB_polyhedron_triangle_primitive<Kernel, Polyhedron> Primitive;
//typedef CGAL::AABB_traits<Kernel, Primitive> Traits;
//typedef CGAL::AABB_tree<Traits> Tree;
//typedef boost::optional< Tree::Intersection_and_primitive_id<Ray>::Type > Ray_intersection;
//typedef CGAL::Translation Translation;
//typedef CGAL::Aff_transformation_3<Kernel> Aff_transformation_3;
//
//// A modifier creating a triangle with the incremental builder.
//template<class HDS>
//class polyhedron_builder : public CGAL::Modifier_base<HDS> {
//public:
//	std::vector<double> &coords;
//	std::vector<int>    &tris;
//	polyhedron_builder(std::vector<double> &_coords, std::vector<int> &_tris) : coords(_coords), tris(_tris) {}
//	void operator()(HDS& hds) {
//		typedef typename HDS::Vertex   Vertex;
//		typedef typename Vertex::Point Point;
//		// create a cgal incremental builder
//		CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);
//		B.begin_surface(coords.size() / 3, tris.size() / 3);
//		// add the polyhedron vertices
//		for (int i = 0; i<(int)coords.size(); i += 3){
//			B.add_vertex(Point(coords[i + 0], coords[i + 1], coords[i + 2]));
//		}
//		// add the polyhedron triangles
//		for (int i = 0; i<(int)tris.size(); i += 3){
//			B.begin_facet();
//			B.add_vertex_to_facet(tris[i + 0]);
//			B.add_vertex_to_facet(tris[i + 1]);
//			B.add_vertex_to_facet(tris[i + 2]);
//			B.end_facet();
//		}
//		// finish up the surface
//		B.end_surface();
//	}
//};


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

private:
	////Creates a polyhedron (containing the adhering surface) projecting the prothesis's plate onto the jaw.
	//void CreateAdheringSurface(Direction_3 &direction, Polyhedron &mesh, Polyhedron &rezult);

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