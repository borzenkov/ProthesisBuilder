//// MedBox
//// Prothesis.cpp
//// (c) Victor Borzenkov 2014
//
//#include "Prothesis.h"
//
//void ProthesisBuilder::Build()
//{
//	// TODO: wrap all debug output in ifs 
//	// TODO: and create a boolean field in this class for debug mode
//	std::cout << "MakePlate started" << std::endl;
//	MakePlate();
//	std::cout << "MakePlate ended" << std::endl;
//	std::cout << "MakeHead started" << std::endl;
//	MakeHead();
//	std::cout << "MakeHead ended" << std::endl;
//	std::cout << "PositionHead started" << std::endl;
//	PositionHead();
//	std::cout << "PositionHead ended" << std::endl;
//	std::cout << "MakeJunction started" << std::endl;
//	MakeJunction();
//	std::cout << "MakeJunction ended" << std::endl;
//	std::cout << "UnitePlateAndJunction started" << std::endl;
//	UnitePlateAndJunction();
//	std::cout << "UnitePlateAndJunction ended" << std::endl;
//
//	std::cout << "UnitePlateJunctionAndHead started" << std::endl;
//	UnitePlateJunctionAndHead();
//	std::cout << "UnitePlateJunctionAndHead ended" << std::endl;
//	std::cout << "MakeFillets started" << std::endl;
//	//MakeFillets();
//	std::cout << "MakeFillets ended" << std::endl;
//	std::cout << "MakeHoles started" << std::endl;
//	//MakeHoles(Prothesis);
//	std::cout << "MakeHoles ended";
//}
//
//ProthesisBuilder::ProthesisBuilder(ProthesisInputData* inputs)
//{
//	InputParams = inputs;
//}
//
//void ProthesisBuilder::LightBuild()
//{
//	std::cout << "MakePlate started" << std::endl;
//	MakePlate();
//	std::cout << "MakePlate ended" << std::endl;
//	/*std::cout << "MakeHoles started" << std::endl;
//	MakeHoles(Plate);
//	std::cout << "MakeHoles ended";*/
//	std::cout << "MakeHead started" << std::endl;
//	MakeHead();
//	std::cout << "MakeHead ended" << std::endl;
//	std::cout << "PositionHead started" << std::endl;
//	PositionHead();
//	std::cout << "PositionHead ended" << std::endl;
//	std::cout << "MakeJunction started" << std::endl;
//	MakeJunction();
//	std::cout << "MakeJunction ended" << std::endl;
//	///*std::cout << "UnitePlateAndJunction started" << std::endl;
//	//UnitePlateAndJunction();
//	//std::cout << "UnitePlateAndJunction ended" << std::endl;*/
//	//std::cout << "UnitePlateAndJunction started" << std::endl;
//	//UniteJunctionAndHead();
//	//std::cout << "UnitePlateAndJunction ended" << std::endl;
//	//std::cout << "MakeFillets started" << std::endl;
//	////MakeFillets(Plate);
//	//std::cout << "MakeFillets ended" << std::endl;
//}
//
//void ProthesisBuilder::TestBuild()
//{
//	std::cout << "MakePlate started" << std::endl;
//	MakePlate();
//	std::cout << "MakePlate ended" << std::endl;
//	std::cout << "MakeHead started" << std::endl;
//	MakeHead();
//	std::cout << "MakeHead ended" << std::endl;
//	std::cout << "PositionHead started" << std::endl;
//	PositionHead();
//	std::cout << "PositionHead ended" << std::endl;
//	std::cout << "MakeJunction started" << std::endl;
//	MakeJunction();
//	std::cout << "MakeJunction ended" << std::endl;
//	std::cout << "UnitePlateAndJunction started" << std::endl;
//	UnitePlateAndJunction();
//	std::cout << "UnitePlateAndJunction ended" << std::endl;
//	std::cout << "MakeFillets started" << std::endl;
//	MakeFillets(PlateAndJunction);
//	std::cout << "MakeFillets ended" << std::endl;
//	std::cout << "MakeHoles started" << std::endl;
//	MakeHoles(Plate);
//	std::cout << "MakeHoles ended";
//
//	TopoDS_Compound aRes;
//	BRep_Builder aBuilder;
//	aBuilder.MakeCompound(aRes);
//	aBuilder.Add(aRes, PlateAndJunction);
//	aBuilder.Add(aRes, Head);
//	std::cout << "Writing...";
//	StlAPI_Writer a;
//	a.SetCoefficient(0.001);
//	/*a.RelativeMode() = Standard_False;
//	a.SetDeflection(0.001);*/
//	a.Write(aRes, "lol.stl");
//}
//
//void ProthesisBuilder::UniteJunctionAndHead()
//{
//	BRepAlgoAPI_Fuse fuse(Junction, Head);
//	fuse.Build();
//	JunctionAndHead = fuse.Shape();
//}
//
//void ProthesisBuilder::UnitePlateJunctionAndHead()
//{
//	BRepAlgoAPI_Fuse fuse(PlateAndJunction, Head);
//	fuse.Build();
//	Prothesis = fuse.Shape();
//}
//
//void ProthesisBuilder::UnitePlateAndJunction()
//{
//	BRepAlgoAPI_Fuse fuse(Plate, Junction);
//	fuse.Build();
//	PlateAndJunction = fuse.Shape();
//}
//
//void ProthesisBuilder::MakeFillets(TopoDS_Shape &x)
//{
////	// Body : Apply Fillets
////	BRepFilletAPI_MakeFillet mkFillet(PlateAndJunction);
////	TopExp_Explorer anEdgeExplorer(PlateAndJunction, TopAbs_EDGE);
////	//for (int i = 0; i < 10; i++)
////	//{
////	//	TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
////	//	//Add edge to fillet algorithm
////	//	if(InputParams->plateFillets[i])
////	//		mkFillet.Add(InputParams->plateFillets[i], anEdge);
////	//	anEdgeExplorer.Next();
////	//}
////	////PlateAndJunction = mkFillet.Shape();
////
////	////BRepFilletAPI_MakeFillet mkFillet1(PlateAndJunction);
////	////TopExp_Explorer anEdgeExplorer1(PlateAndJunction, TopAbs_EDGE);
////	//for (int i = 0; i < 4; i++)
////	//{
////	//	TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
////	//	//Add edge to fillet algorithm
////	//	if(InputParams->plateFillets2[i])
////	//		mkFillet.Add(InputParams->plateFillets2[i], anEdge);
////	//	anEdgeExplorer.Next();
////	//}
////	//PlateAndJunction = mkFillet.Shape();
////
////	double plateFillets[100]; 
////	memset(plateFillets, /*0.0*/InputParams->k, sizeof(plateFillets));
////	plateFillets[0]
////		= plateFillets[1]
////		= plateFillets[4]
////		= plateFillets[9]
////		= InputParams->h; // for big fillets
////	plateFillets[10]
////		= plateFillets[13]
////		= InputParams->k; // for small fillets
//	BRepFilletAPI_MakeFillet mkFillet(x);
//	TopExp_Explorer anEdgeExplorer(x, TopAbs_EDGE);
//	int i = 0;
//	while (anEdgeExplorer.More())
//	{
//		i++;
//		TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
//		if (i < 5)
//		mkFillet.Add(InputParams->q, anEdge);
//		anEdgeExplorer.Next();
//	}
//	x = mkFillet.Shape();
//}
//
//void ProthesisBuilder::MakeHoles(TopoDS_Shape &x)
//{
//	//Creating cylindrical hole. j/2 is the radius, l is the height.
//	BRepPrimAPI_MakeCylinder hole(InputParams->p / 2, InputParams->r);
//
//	//Creating transforming object.
//	gp_Trsf myTrsf;
//
//	//Creating translation vector.
//	gp_Vec myVec;
//	myVec.SetZ(0);//2D sketch
//
//	//Since our model has 4 cylindrical holes we are going to
//	//place holes and then drill them 4 times.
//	for (int i = 0; i < 4; i++)
//	{
//		//Place
//		myVec.SetX(InputParams->holes[i].x);
//		myVec.SetY(InputParams->holes[i].y);
//
//		myTrsf.SetTranslation(myVec);
//
//		//this object will return new shape after calling .Shape().
//		BRepBuilderAPI_Transform xform(hole.Shape(), myTrsf);
//		//Drill if isActive=true
//
//		BRepAlgoAPI_Cut cutAlgo(x, xform.Shape());
//		cutAlgo.Build();
//		x = cutAlgo.Shape();
//	}
//
//	MakePrismaticHole(x);
//}
//
//void ProthesisBuilder::MakePrismaticHole(TopoDS_Shape &x)
//{
//	//Get contour
//	TopoDS_Wire contour = MakePrismaticHoleContour();
//	
//	//Position contour
//	gp_Trsf myTrsf;
//	gp_Vec myVec;
//	myVec.SetX(InputParams->b);
//	myVec.SetY(InputParams->f);
//	myVec.SetZ(0);
//	myTrsf.SetTranslation(myVec);
//	BRepBuilderAPI_Transform xform(contour, myTrsf);
//	contour = TopoDS::Wire(xform.Shape());
//
//	//Creating the prism
//	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(contour);
//	gp_Vec aPrismVec(0, 0, InputParams->PlateThickness+1);//+1 т.к. какой-то алгоритм тупит и не удаляет крайний фейс призмы
//	TopoDS_Shape PrismaticHole = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);
//
//	//Cutting the hole
//	BRepAlgoAPI_Cut cutAlgo(x, PrismaticHole);
//	cutAlgo.Build();
//	x = cutAlgo.Shape();
//}
//
//TopoDS_Wire ProthesisBuilder::MakePrismaticHoleContour()
//{
//	gp_Pnt aPnt1(-InputParams->p/2, 0, 0);
//	gp_Pnt aPnt2(0, InputParams->p / 2, 0);
//	gp_Pnt aPnt3(InputParams->p / 2, 0, 0);
//	gp_Pnt aPnt4(InputParams->p / 2, -(InputParams->f - InputParams->j), 0);
//	gp_Pnt aPnt5(0, -(InputParams->f - InputParams->j + InputParams->p / 2), 0);
//	gp_Pnt aPnt6(-InputParams->p / 2, -(InputParams->f - InputParams->j), 0);
//
//	Handle(Geom_TrimmedCurve) aArcOfCircle1 = GC_MakeArcOfCircle(aPnt1, aPnt2, aPnt3);
//	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(aPnt3, aPnt4);
//	Handle(Geom_TrimmedCurve) aArcOfCircle2 = GC_MakeArcOfCircle(aPnt4, aPnt5, aPnt6);
//	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(aPnt6, aPnt1);
//
//	TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge(aArcOfCircle1);
//	TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge(aSegment1);
//	TopoDS_Edge aEdge3 = BRepBuilderAPI_MakeEdge(aArcOfCircle2);
//	TopoDS_Edge aEdge4 = BRepBuilderAPI_MakeEdge(aSegment2);
//	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(aEdge1, aEdge2, aEdge3, aEdge4);
//
//	return aWire;
//}
//
//void ProthesisBuilder::WriteToSTLFile(Standard_CString name)
//{
//	std::cout << "Writing...";
//	StlAPI_Writer a;
//	a.SetCoefficient(0.0001);
//	/*a.RelativeMode() = Standard_False;
//	a.SetDeflection(0.001);*/
//	a.Write(Prothesis, name);
//}
//
//void ProthesisBuilder::WriteToSTLFileLight(Standard_CString name)
//{
//	//TopoDS_Compound aRes;
//	//BRep_Builder aBuilder;
//	//aBuilder.MakeCompound(aRes);
//	//aBuilder.Add(aRes, JunctionAndHead);
//	//aBuilder.Add(aRes, Plate);
//	std::cout << "Writing...";
//	StlAPI_Writer a;
//	a.ASCIIMode();
//	//a.SetCoefficient(0.01); //черновое
//	a.SetCoefficient(0.0001);  //чистовое
//	/*a.RelativeMode() = Standard_False;
//	a.SetDeflection(0.001);*/
//	a.Write(Plate, name);
//}
//
//void ProthesisBuilder::MakeHead()
//{
//	//головка-тело, полученное вращением вокруг оси симметрии
//	//сплайна из 4 точек
//	gp_Pnt Pnt1(0, 0, 0);
//	gp_Pnt Pnt2(InputParams->s, 0, InputParams->v);
//	gp_Pnt Pnt3(InputParams->t, 0, InputParams->w);
//	gp_Pnt Pnt4(InputParams->u, 0, 0);
//
//	gp_Vec Vec(InputParams->u, 0, 0); //Вектор, задающий ось вращения контура
//	gp_Dir Dir(Vec);
//	gp_Ax1 HeadAxis(Pnt4, Dir);
//
//	gp_Vec Vec1(0, 0, 1); //В-р, задающий касательное направление в первой точке сплайна
//	gp_Vec Vec2(cos(InputParams->tang_ang_rad_2), 0, sin(InputParams->tang_ang_rad_2));
//	gp_Vec Vec3(cos(InputParams->tang_ang_rad_3), 0, sin(InputParams->tang_ang_rad_3));
//	gp_Vec Vec4(-Vec1); //В-р, задающий касаткльное направление в последней точке сплайна
//
//	TColgp_Array1OfPnt CurvePoles(1, 4);
//	CurvePoles(1) = Pnt1;
//	CurvePoles(2) = Pnt2;
//	CurvePoles(3) = Pnt3;
//	CurvePoles(4) = Pnt4;
//
//	TColgp_Array1OfVec tang(1, 4);
//	tang(1) = Vec1;
//	tang(2) = Vec2;
//	tang(3) = Vec3;
//	tang(4) = Vec4;
//
//	Handle(TColgp_HArray1OfPnt) points = new TColgp_HArray1OfPnt(1, 4);
//	points->SetValue(1, Pnt1);
//	points->SetValue(2, Pnt2);
//	points->SetValue(3, Pnt3);
//	points->SetValue(4, Pnt4);
//	GeomAPI_Interpolate curve(points, Standard_False, 1.0e-7);
//	curve.Perform();
//	Handle(TColStd_HArray1OfBoolean) bools = new TColStd_HArray1OfBoolean(1, 4);
//	bools->SetValue(1, Standard_True);
//	bools->SetValue(2, Standard_True);
//	bools->SetValue(3, Standard_True);
//	bools->SetValue(4, Standard_True);
//	curve.Load(tang, bools);
//	curve.Perform();
//
//	Handle(Geom_BSplineCurve) C = curve.Curve();
//
//	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(C);//не работает без хэндла!!!
//
//	HeadWire = BRepBuilderAPI_MakeWire(E);
//
//	TopoDS_Face HeadFace = BRepBuilderAPI_MakeFace(HeadWire);
//
//	Head = BRepPrimAPI_MakeRevol(HeadFace, HeadAxis).Shape();
//
//	//Creating the contour to be used in making loft
//	TopoDS_Wire aWire(HeadWire);
//	gp_Trsf aTrsf;
//	aTrsf.SetMirror(gp::OX());
//	BRepBuilderAPI_Transform aBRepTrsf(aWire, aTrsf);
//	TopoDS_Shape aMirroredShape = aBRepTrsf.Shape();
//	TopoDS_Wire aMirroredWire = TopoDS::Wire(aMirroredShape);
//
//	BRepBuilderAPI_MakeWire mkWire;
//	mkWire.Add(aWire);
//	mkWire.Add(aMirroredWire);
//	completedHeadWire = mkWire.Wire();
//}
//
//void ProthesisBuilder::MakeJunction()
//{
//	//создать первый контур(на пластинке)
//	CreateFirstJunctionContour();
//	CreateSecondJunctionContour();
//	//Creating middle contour
//	CreateMiddleJunctionContour();
//	CreateThirdJunctionContour();
//	//лофт
//	BRepOffsetAPI_ThruSections loft(Standard_True, Standard_False, /*1.0e-06*/1);
//	BRepOffsetAPI_ThruSections loft2(Standard_True, Standard_False, /*1.0e-06*/1);
//	loft.UseSmoothing();
//	loft.AddWire(FirstJunctionContour);
//	loft.AddWire(MiddleJunctionContour);
//	/*loft2.AddWire(SecondJunctionContour);*/
//	/*loft.AddWire(SecondJunctionContour);*/
//	loft.AddWire(ThirdJunctionContour);
//	loft.AddWire(completedHeadWire);
//	loft.Build();
//	Junction = loft.Shape();
//	/*Junction2 = loft2.Shape();*/
//
//	//BRepFilletAPI_MakeFillet mkFillet1(Junction);
//	//TopExp_Explorer anEdgeExplorer1(Junction, TopAbs_EDGE);
//	//while (anEdgeExplorer1.More()){
//	//	TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer1.Current());
//	//	//Add edge to fillet algorithm
//	//	mkFillet1.Add(0.5, anEdge);
//	//	anEdgeExplorer1.Next();
//	//}
//	//Junction = mkFillet1.Shape();
//}
//
//void ProthesisBuilder::MakePlate()
//{
//	ProthesisInputData* ip = InputParams;
//	gp_Pnt a(ip->ax, ip->ay, 0);
//	gp_Pnt b(ip->bx, ip->by, 0);
//	gp_Pnt c(ip->cx, ip->cy, 0);
//	gp_Pnt d(ip->dx, ip->dy, 0);
//	gp_Pnt e(ip->ex, ip->ey, 0);
//	gp_Pnt f(ip->fx, ip->fy, 0);
//
//	Handle(Geom_TrimmedCurve) abSegment = GC_MakeSegment(a, b);
//	Handle(Geom_TrimmedCurve) bcSegment = GC_MakeSegment(b, c);
//	Handle(Geom_TrimmedCurve) cdSegment = GC_MakeSegment(c, d);
//	Handle(Geom_TrimmedCurve) deSegment = GC_MakeSegment(d, e);
//	Handle(Geom_TrimmedCurve) efSegment = GC_MakeSegment(e, f);
//	Handle(Geom_TrimmedCurve) faSegment = GC_MakeSegment(f, a);
//
//	TopoDS_Edge abEdge = BRepBuilderAPI_MakeEdge(abSegment);
//	TopoDS_Edge bcEdge = BRepBuilderAPI_MakeEdge(bcSegment);
//	TopoDS_Edge cdEdge = BRepBuilderAPI_MakeEdge(cdSegment);
//	TopoDS_Edge deEdge = BRepBuilderAPI_MakeEdge(deSegment);
//	TopoDS_Edge efEdge = BRepBuilderAPI_MakeEdge(efSegment);
//	TopoDS_Edge faEdge = BRepBuilderAPI_MakeEdge(faSegment);
//
//	/*СКРУГЛЕНИЕ*/
//	gp_Pln aPlane(gp::XOY());
//	//скругление в точке А
//	ChFi2d_FilletAPI filletAlg(faEdge, abEdge, aPlane);
//	filletAlg.Perform(ip->n);
//	TopoDS_Edge A_fillet = filletAlg.Result(a, faEdge, abEdge);
//
//	//скругление в точке В
//	ChFi2d_FilletAPI filletAlg2(abEdge, bcEdge, aPlane);
//	filletAlg2.Perform(ip->n);
//	TopoDS_Edge B_fillet = filletAlg2.Result(b, abEdge, bcEdge);
//
//	//скругление в точке C
//	ChFi2d_FilletAPI filletAlg3(bcEdge, cdEdge, aPlane);
//	filletAlg3.Perform(ip->n);
//	TopoDS_Edge C_fillet = filletAlg3.Result(c, bcEdge, cdEdge);
//
//	//скругление в точке F
//	ChFi2d_FilletAPI filletAlg4(faEdge, efEdge, aPlane);
//	filletAlg4.Perform(ip->n);
//	TopoDS_Edge F_fillet = filletAlg4.Result(f, faEdge, efEdge);
//	/*КОНЕЦ СКРУГЛЕНИЯ*/
//
//	BRepBuilderAPI_MakeWire Wire0(abEdge, B_fillet, bcEdge, C_fillet);
//	Wire0.Add(cdEdge);
//	Wire0.Add(deEdge);
//	Wire0.Add(efEdge);
//	Wire0.Add(F_fillet);
//	Wire0.Add(faEdge);
//	Wire0.Add(A_fillet);
//	TopoDS_Wire Wire = Wire0;
//
//	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(Wire);
//	gp_Vec aPrismVec(0, 0, ip->PlateThickness);
//	Plate = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);
//}
//
////void ProthesisBuilder::Build()
////{
////	BRep_Builder Builder;
////	Builder.MakeCompound(Prothesis);
////	Builder.Add(Prothesis, Head);
////	Builder.Add(Prothesis, PlateAndJunction);
////}
//
//void ProthesisBuilder::CreateFirstJunctionContour()
//{
//	ProthesisInputData* ip = InputParams;
//	// Profile : Define Support Points
//	gp_Pnt PntD(ip->dx, ip->dy, 0);
//	gp_Pnt PntE(ip->ex, ip->ey, 0);
//	gp_Pnt PntG(ip->ex, ip->ey, ip->PlateThickness);
//	gp_Pnt PntH(ip->dx, ip->dy, ip->PlateThickness);
//
//	// Profile : Define the Geometry
//	Handle(Geom_TrimmedCurve) deSegment = GC_MakeSegment(PntD, PntE);
//	Handle(Geom_TrimmedCurve) egSegment = GC_MakeSegment(PntE, PntG);
//	Handle(Geom_TrimmedCurve) ghSegment = GC_MakeSegment(PntG, PntH);
//	Handle(Geom_TrimmedCurve) hdSegment = GC_MakeSegment(PntH, PntD);
//	// Profile : Define the Topology
//	TopoDS_Edge deEdge = BRepBuilderAPI_MakeEdge(deSegment);
//	TopoDS_Edge egEdge = BRepBuilderAPI_MakeEdge(egSegment);
//	TopoDS_Edge ghEdge = BRepBuilderAPI_MakeEdge(ghSegment);
//	TopoDS_Edge hdEdge = BRepBuilderAPI_MakeEdge(hdSegment);
//
//
//	///*СКРУГЛЕНИЕ*/
//	//gp_Pln aPlane(gp::ZOX());
//	//aPlane.SetLocation(PntD);
//	////скругление в точке D
//	//ChFi2d_FilletAPI filletAlg(deEdge, hdEdge, aPlane);
//	//filletAlg.Perform(ip->q);
//	//TopoDS_Edge D_fillet = filletAlg.Result(PntD, deEdge, hdEdge);
//
//	////скругление в точке E
//	//ChFi2d_FilletAPI filletAlg2(deEdge, egEdge, aPlane);
//	//filletAlg2.Perform(ip->q);
//	//TopoDS_Edge E_fillet = filletAlg2.Result(PntE, deEdge, egEdge);
//
//	////скругление в точке G
//	//ChFi2d_FilletAPI filletAlg3(egEdge, ghEdge, aPlane);
//	//filletAlg3.Perform(ip->q);
//	//TopoDS_Edge G_fillet = filletAlg3.Result(PntG, egEdge, ghEdge);
//
//	////скругление в точке H
//	//ChFi2d_FilletAPI filletAlg4(ghEdge, hdEdge, aPlane);
//	//filletAlg4.Perform(ip->q);
//	//TopoDS_Edge H_fillet = filletAlg4.Result(PntH, ghEdge, hdEdge);
//	///*КОНЕЦ СКРУГЛЕНИЯ*/
//
//	///*BRepBuilderAPI_MakeWire Wire0(deEdge, egEdge, ghEdge, hdEdge);*/
//	//BRepBuilderAPI_MakeWire Wire0(deEdge, E_fillet, egEdge, G_fillet);
//	//Wire0.Add(ghEdge);
//	//Wire0.Add(H_fillet);
//	//Wire0.Add(hdEdge);
//	//Wire0.Add(D_fillet);
//
//	BRepBuilderAPI_MakeWire Wire0(deEdge, egEdge, ghEdge, hdEdge);
//	
//	FirstJunctionContour = Wire0;
//}
//
//void ProthesisBuilder::CreateSecondJunctionContour()
//{
//	//Draw
//	ProthesisInputData* ip = InputParams;
//	// Profile : Define Support Points
//	gp_Pnt Pnt1(-6,0,-5);
//	gp_Pnt Pnt2(6,0,-5);
//	gp_Pnt Pnt3(6, 0, 5);
//	gp_Pnt Pnt4(-6, 0, 5);
//
//	// Profile : Define the Geometry
//	Handle(Geom_TrimmedCurve) Segment1 = GC_MakeSegment(Pnt1, Pnt2);
//	Handle(Geom_TrimmedCurve) Segment2 = GC_MakeSegment(Pnt2, Pnt3);
//	Handle(Geom_TrimmedCurve) Segment3 = GC_MakeSegment(Pnt3, Pnt4);
//	Handle(Geom_TrimmedCurve) Segment4 = GC_MakeSegment(Pnt4, Pnt1);
//	// Profile : Define the Topology
//	TopoDS_Edge Edge1 = BRepBuilderAPI_MakeEdge(Segment1);
//	TopoDS_Edge Edge2 = BRepBuilderAPI_MakeEdge(Segment2);
//	TopoDS_Edge Edge3 = BRepBuilderAPI_MakeEdge(Segment3);
//	TopoDS_Edge Edge4 = BRepBuilderAPI_MakeEdge(Segment4);
//	SecondJunctionContour = BRepBuilderAPI_MakeWire(Edge1, Edge2, Edge3, Edge4);
//	//Place
//	gp_Vec b((InputParams->ex + InputParams->dx) / 2, InputParams->ey, InputParams->PlateThickness / 2);
//	gp_Vec disp(InputParams->z, InputParams->a1, InputParams->b1);
//	gp_Vec x = b + disp;
//	gp_Trsf myTrsf_center_translation;
//	myTrsf_center_translation.SetTranslation(x);
//	BRepBuilderAPI_Transform newForm(SecondJunctionContour, myTrsf_center_translation);
//	SecondJunctionContour = TopoDS::Wire(newForm.Shape());
//	//Rotate properly
//	gp_Trsf myTrsf_angle_OX;
//	gp_Trsf myTrsf_angle_OY;
//	gp_Trsf myTrsf_angle_OZ;
//	gp_Dir x_dir(1, 0, 0);
//	gp_Dir y_dir(0, 1, 0);
//	gp_Dir z_dir(0, 0, 1);
//	gp_Ax1 A1(HeadCenter, x_dir);
//	gp_Ax1 A2(HeadCenter, y_dir);
//	gp_Ax1 A3(HeadCenter, z_dir);
//	myTrsf_angle_OX.SetRotation(A1, InputParams->c1);
//	A2.Transform(myTrsf_angle_OX);
//	A3.Transform(myTrsf_angle_OX);
//	myTrsf_angle_OY.SetRotation(A2, InputParams->d1);
//	A1.Transform(myTrsf_angle_OY);
//	A3.Transform(myTrsf_angle_OY);
//	myTrsf_angle_OZ.SetRotation(A3, 0);
//	A1.Transform(myTrsf_angle_OZ);
//	A2.Transform(myTrsf_angle_OZ);
//	BRepBuilderAPI_Transform newWireForm(SecondJunctionContour, myTrsf_angle_OX);
//	BRepBuilderAPI_Transform newWireForm1(newWireForm.Shape(), myTrsf_angle_OY);
//	BRepBuilderAPI_Transform newWireForm2(newWireForm1.Shape(), myTrsf_angle_OZ);
//	SecondJunctionContour = TopoDS::Wire(newWireForm2.Shape());
//	//Displace properly
//	gp_Trsf myTrsf;
//	float delta = -12;
//	gp_Dir dir(thirdJunctionContourDisplacementDirection.Direction());
//	gp_Vec vec_x(dir);
//	vec_x.Scale(delta);
//	myTrsf.SetTranslation(vec_x);
//	BRepBuilderAPI_Transform headWireForm(SecondJunctionContour, myTrsf);
//	SecondJunctionContour = TopoDS::Wire(headWireForm.Shape());
//}
//
//void ProthesisBuilder::CreateThirdJunctionContour()
//{
//	ThirdJunctionContour = completedHeadWire;
//	gp_Trsf myTrsf;
//	float delta = -3;
//	gp_Dir dir(thirdJunctionContourDisplacementDirection.Direction());
//	gp_Vec x(dir);
//	x.Scale(delta);
//	myTrsf.SetTranslation(x);
//	BRepBuilderAPI_Transform headWireForm(ThirdJunctionContour, myTrsf);
//	ThirdJunctionContour = TopoDS::Wire(headWireForm.Shape());
//}
//
//void ProthesisBuilder::CreateMiddleJunctionContour()
//{
//	double delta = 3;
//	//Calculate ctg's
//	double ctgalpha1 = (InputParams->ex - InputParams->fx) / (InputParams->ey - InputParams->fy);
//	double ctgalpha2 = (InputParams->dx - InputParams->cx) / (InputParams->dy - InputParams->cy);
//	//Calculate new Xes
//	double new_ex = InputParams->ex + delta * ctgalpha1;
//	double new_dx = InputParams->dx + delta * ctgalpha2;
//	//Draw the contour
//	ProthesisInputData* ip = InputParams;
//	// Profile : Define Support Points
//	gp_Pnt PntD(new_dx, ip->dy + delta, 0);
//	gp_Pnt PntE(new_ex, ip->ey + delta, 0);
//	gp_Pnt PntG(new_ex, ip->ey + delta, ip->PlateThickness);
//	gp_Pnt PntH(new_dx, ip->dy + delta, ip->PlateThickness);
//
//	// Profile : Define the Geometry
//	Handle(Geom_TrimmedCurve) deSegment = GC_MakeSegment(PntD, PntE);
//	Handle(Geom_TrimmedCurve) egSegment = GC_MakeSegment(PntE, PntG);
//	Handle(Geom_TrimmedCurve) ghSegment = GC_MakeSegment(PntG, PntH);
//	Handle(Geom_TrimmedCurve) hdSegment = GC_MakeSegment(PntH, PntD);
//	// Profile : Define the Topology
//	TopoDS_Edge deEdge = BRepBuilderAPI_MakeEdge(deSegment);
//	TopoDS_Edge egEdge = BRepBuilderAPI_MakeEdge(egSegment);
//	TopoDS_Edge ghEdge = BRepBuilderAPI_MakeEdge(ghSegment);
//	TopoDS_Edge hdEdge = BRepBuilderAPI_MakeEdge(hdSegment);
//
//	///*СКРУГЛЕНИЕ*/
//	//gp_Pln aPlane(gp::ZOX());
//	//aPlane.SetLocation(PntD);
//	////скругление в точке D
//	//ChFi2d_FilletAPI filletAlg(deEdge, hdEdge, aPlane);
//	//filletAlg.Perform(ip->q);
//	//TopoDS_Edge D_fillet = filletAlg.Result(PntD, deEdge, hdEdge);
//
//	////скругление в точке E
//	//ChFi2d_FilletAPI filletAlg2(deEdge, egEdge, aPlane);
//	//filletAlg2.Perform(ip->q);
//	//TopoDS_Edge E_fillet = filletAlg2.Result(PntE, deEdge, egEdge);
//
//	////скругление в точке G
//	//ChFi2d_FilletAPI filletAlg3(egEdge, ghEdge, aPlane);
//	//filletAlg3.Perform(ip->q);
//	//TopoDS_Edge G_fillet = filletAlg3.Result(PntG, egEdge, ghEdge);
//
//	////скругление в точке H
//	//ChFi2d_FilletAPI filletAlg4(ghEdge, hdEdge, aPlane);
//	//filletAlg4.Perform(ip->q);
//	//TopoDS_Edge H_fillet = filletAlg4.Result(PntH, ghEdge, hdEdge);
//	///*КОНЕЦ СКРУГЛЕНИЯ*/
//
//	///*BRepBuilderAPI_MakeWire Wire0(deEdge, egEdge, ghEdge, hdEdge);*/
//	//BRepBuilderAPI_MakeWire Wire0(deEdge, E_fillet, egEdge, G_fillet);
//	//Wire0.Add(ghEdge);
//	//Wire0.Add(H_fillet);
//	//Wire0.Add(hdEdge);
//	//Wire0.Add(D_fillet);
//
//	BRepBuilderAPI_MakeWire Wire0(deEdge, egEdge, ghEdge, hdEdge);
//
//	MiddleJunctionContour = Wire0;
//	
//	/*gp_Trsf myTrsf;
//	gp_Vec myVec(1,1,0);
//	myTrsf.SetTranslation(myVec);
//	BRepBuilderAPI_Transform xform(FirstJunctionContour, myTrsf);
//	MiddleJunctionContour = TopoDS::Wire(xform.Shape());*/
//}
//
//void ProthesisBuilder::PositionHead()
//{
//	//Для позиционирования головки ввожу дополнительный элемент: 
//	//центр, его нужно трансформировать совместно с головкой
//	HeadCenter.SetX(InputParams->u / 2);
//	HeadCenter.SetY(0);
//	HeadCenter.SetZ(0);
//	//Вычисляем вектор x для перемещения головки
//	gp_Vec a(HeadCenter.X(), 0, 0);
//	gp_Vec b((InputParams->ex + InputParams->dx) / 2, InputParams->ey, InputParams->PlateThickness / 2);
//	gp_Vec disp(InputParams->z, InputParams->a1, InputParams->b1);
//	gp_Vec x = b + disp - a;
//
//	gp_Trsf myTrsf_center_translation;
//	gp_Trsf myTrsf_angle_OX;
//	gp_Trsf myTrsf_angle_OY;
//	gp_Trsf myTrsf_angle_OZ;
//	myTrsf_center_translation.SetTranslation(x);
//	BRepBuilderAPI_Transform xform(Head, myTrsf_center_translation);
//	BRepBuilderAPI_Transform headWireForm(completedHeadWire, myTrsf_center_translation);
//	Head = xform.Shape();
//	completedHeadWire = TopoDS::Wire(headWireForm.Shape());
//	HeadCenter.Transform(myTrsf_center_translation);
//
//	gp_Dir x_dir(1, 0, 0);
//	gp_Dir y_dir(0, 1, 0);
//	gp_Dir z_dir(0, 0, 1);
//	gp_Ax1 A1(HeadCenter, x_dir); 
//	gp_Ax1 A2(HeadCenter, y_dir);
//	gp_Ax1 A3(HeadCenter, z_dir);
//	myTrsf_angle_OX.SetRotation(A1, 0);
//	A2.Transform(myTrsf_angle_OX);
//	A3.Transform(myTrsf_angle_OX);
//	myTrsf_angle_OY.SetRotation(A2, InputParams->d1);
//	A1.Transform(myTrsf_angle_OY);
//	A3.Transform(myTrsf_angle_OY);
//	myTrsf_angle_OZ.SetRotation(A3, InputParams->c1);
//	A1.Transform(myTrsf_angle_OZ);
//	A2.Transform(myTrsf_angle_OZ);
//	thirdJunctionContourDisplacementDirection = A2;
//
//	BRepBuilderAPI_Transform yform(Head, myTrsf_angle_OX);
//	BRepBuilderAPI_Transform yform1(yform.Shape(), myTrsf_angle_OY);
//	BRepBuilderAPI_Transform yform2(yform1.Shape(), myTrsf_angle_OZ);
//	Head = yform2.Shape();
//	BRepBuilderAPI_Transform newWireForm(completedHeadWire, myTrsf_angle_OX);
//	BRepBuilderAPI_Transform newWireForm1(newWireForm.Shape(), myTrsf_angle_OY);
//	BRepBuilderAPI_Transform newWireForm2(newWireForm1.Shape(), myTrsf_angle_OZ);
//	completedHeadWire = TopoDS::Wire(newWireForm2.Shape());
//}
//
//TopoDS_Wire ProthesisBuilder::FindIntersection()
//{
//	Standard_Real tol = 0.01;
//	BRepBuilderAPI_MakeWire brepMake;
//	ShapeFix_ShapeTolerance FTol;
//	TopExp_Explorer ExpEdges;
//
//	TopoDS_Shape planeShape = BRepBuilderAPI_MakeFace(HeadPlane).Face();
//	BRepAlgo_Section sectionalg(Head, planeShape);
//
//	TopoDS_Shape section = sectionalg.Shape();
//
//	Handle(ShapeExtend_WireData) sbwd1 = new ShapeExtend_WireData();
//	for (ExpEdges.Init(section, TopAbs_EDGE); ExpEdges.More(); ExpEdges.Next())
//	{
//		const TopoDS_Edge& Edge = TopoDS::Edge(ExpEdges.Current());
//		sbwd1->Add(Edge);
//	}
//
//	Handle(ShapeFix_Wire) sfw = new ShapeFix_Wire;
//	sfw->Load(sbwd1);
//	sfw->Perform();
//	//Reorder edges is very important
//	sfw->FixReorder();
//	sfw->SetMaxTolerance(tol);
//
//	for (int i = 1; i <= sfw->NbEdges(); i++)
//	{
//		TopoDS_Edge Edge = sfw->WireData()->Edge(i);
//		FTol.SetTolerance(Edge, tol, TopAbs_VERTEX);
//		brepMake.Add(Edge);
//	}
//
//	TopoDS_Wire wire = brepMake.Wire();
//	return wire;
//}
//
////void ProthesisBuilder::visualize()
////
////{
////	TopoDS_Compound aRes;
////	BRep_Builder aBuilder;
////	aBuilder.MakeCompound(aRes);
////	aBuilder.Add(aRes, Plate);
////	aBuilder.Add(aRes, Junction);
////	aBuilder.Add(aRes, Head);
////
////	IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(aRes);
////
////	vtkSmartPointer<IVtkTools_ShapeDataSource> DS = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
////
////	DS->SetShape(aShapeImpl); //?
////
////	vtkSmartPointer<IVtkTools_DisplayModeFilter> DMFilter = vtkSmartPointer<IVtkTools_DisplayModeFilter>::New();
////
////	DMFilter->AddInputConnection(DS->GetOutputPort());
////
////	DMFilter->SetDisplayMode(DM_Shading);
////
////	vtkSmartPointer<vtkDataSetMapper> M = vtkSmartPointer<vtkDataSetMapper>::New();
////	M->SetInputConnection(DMFilter->GetOutputPort());
////
////
////	vtkSmartPointer<vtkActor> Actor = vtkSmartPointer<vtkActor>::New();
////	Actor->SetMapper(M);
////
////
////	// Create a renderer, render window, and interactor
////	vtkSmartPointer<vtkRenderer> renderer =
////		vtkSmartPointer<vtkRenderer>::New();
////	vtkSmartPointer<vtkRenderWindow> renderWindow =
////		vtkSmartPointer<vtkRenderWindow>::New();
////	renderWindow->AddRenderer(renderer);
////	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
////		vtkSmartPointer<vtkRenderWindowInteractor>::New();
////	renderWindowInteractor->SetRenderWindow(renderWindow);
////	// Add the actors to the scene
////
////	renderer->AddActor(Actor);
////	
////	renderer->SetBackground(.3, .2, .1);
////
////	// Render and interact
////	renderWindow->Render();
////	renderWindowInteractor->Start();
////}
//
