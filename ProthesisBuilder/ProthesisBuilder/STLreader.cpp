//#include <CGAL/Modifier_base.h>
//#include <CGAL/Polyhedron_incremental_builder_3.h>
//#include <CGAL/Cartesian.h>
//#include <CGAL/Polyhedron_traits_with_normals_3.h>
//#include <CGAL/Polyhedron_3.h>
//#include <CGAL/IO/Polyhedron_iostream.h>
//#include <fstream>
//#include <string>
//
//#include <boost/tuple/tuple.hpp>
//
//typedef CGAL::Cartesian<double> Kernel;
//typedef Kernel::Point_3 Point_3;
//typedef std::vector<Point_3> Points_3;
//typedef boost::tuple<int, int, int> Facet;
//typedef std::vector<Facet> Surface;
//typedef CGAL::Polyhedron_traits_with_normals_3<Kernel> Polyhedron_traits_with_normals_3;
//typedef CGAL::Polyhedron_3<Polyhedron_traits_with_normals_3> Polyhedron;
//
//template <class HDS>
//class Build_from_stl : public CGAL::Modifier_base<HDS> {
//	std::istream& is;
//	int counter;
//	Points_3 meshPoints;
//	Surface mesh;
//
//public:
//
//	std::string name, color;
//
//
//	Build_from_stl(std::istream& is_)
//		: is(is_), counter(0)
//	{}
//
//	void operator()(HDS& hds) {
//		if (!read(is, meshPoints, mesh)) return;
//
//		CGAL::Polyhedron_incremental_builder_3<Polyhedron::HalfedgeDS> B(hds);
//		B.begin_surface(meshPoints.size(), mesh.size());
//		typedef typename Points_3::size_type size_type;
//
//		for (size_type i = 0; i < meshPoints.size(); i++){
//			B.add_vertex(meshPoints[i]);
//		}
//		for (size_type i = 0; i < mesh.size(); i++){
//			B.begin_facet();
//			B.add_vertex_to_facet(mesh[i].template get<0>());
//			B.add_vertex_to_facet(mesh[i].template get<1>());
//			B.add_vertex_to_facet(mesh[i].template get<2>());
//			B.end_facet();
//		}
//		if (B.error())
//		{
//			std::cerr << "An error occured while creating a Polyhedron" << std::endl;
//			B.rollback();
//		}
//
//		B.end_surface();
//	}
//
//	bool
//		read(std::istream& input, Points_3& points, Surface& surface, int /*offset*/ = 0)
//	{
//			std::string s, solid("solid"), facet("facet"), outer("outer"), loop("loop"), vertex("vertex"), endloop("endloop"), endsolid("endsolid");
//
//			std::map<Point_3, int> vertex_index;
//			int index = 0;
//			int ijk[3];
//			Point_3 p;
//
//			input >> s;
//			if (s == solid){
//				std::getline(input, s);
//			}
//			else {
//				std::cerr << "We expect keyword 'solid'" << std::endl;
//				return false;
//			}
//
//			while (input >> s){
//				if (s == endsolid){
//					//std::cerr << "found endsolid" << std::endl;
//				}
//				else if (s == facet){
//					//std::cerr << "found facet" << std::endl;
//					std::getline(input, s); // ignore the normal
//					input >> s;
//					if (s != outer){
//						std::cerr << "Expect 'outer' and got " << s << std::endl;
//						return false;
//					}
//					input >> s;
//					if (s != loop){
//						std::cerr << "Expect 'loop' and got " << s << std::endl;
//						return false;
//					}
//					int count = 0;
//					do {
//						input >> s;
//						if (s == vertex){
//							//      std::cerr << "found vertex" << std::endl;
//							if (count < 3){
//								input >> p;
//								if (vertex_index.find(p) == vertex_index.end()){
//									ijk[count] = index;
//									vertex_index[p] = index++;
//									points.push_back(p);
//								}
//								else {
//									ijk[count] = vertex_index[p];
//								}
//								++count;
//							}
//							else {
//								std::cerr << "We can only read triangulated surfaces" << std::endl;
//								return false;
//							}
//						}
//					} while (s != endloop);
//
//					surface.push_back(boost::make_tuple(ijk[0], ijk[1], ijk[2]));
//				}
//			}
//			return true;
//		}
//
//};
//
//int readSTL(std::string file_name, Polyhedron &output)
//{
//	// Open file
//	std::ifstream in(file_name);
//	if (!in) {
//		std::cerr << "Error! Cannot open file " << file_name << std::endl;
//		return 0;
//	}
//
//	// Try to read STL file in a polyhedron
//	Build_from_stl<Polyhedron::HalfedgeDS> builder(in);
//	output.delegate(builder);
//	if (!output.is_valid()){
//		std::cerr << "Error: Invalid polyhedron" << std::endl;
//		return 0;
//	}
//
//	if (output.empty()){
//		return 0;
//	}
//}
//
////void main()
////{
////	std::string file_name = "C:/FILES/ProthesisBuilder/OUTPUT/Plate.stl";
////	Polyhedron plate;
////	readSTL(file_name, plate);
////
////	std::ofstream os;
////	os.open("C:/FILES/ProthesisBuilder/OUTPUT/STLreader_works_OK.off");
////	os << plate;
////}