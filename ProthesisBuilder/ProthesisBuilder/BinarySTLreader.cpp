//#include <boost/cstdint.hpp> 
//#include "boost/tuple/tuple.hpp"
//#include <iostream>
//#include <fstream>
//#include <map>
//#include <vector>
//#include <CGAL/Simple_cartesian.h>
//#include <CGAL/compute_average_spacing.h>
//
//typedef CGAL::Simple_cartesian<double> K;
//typedef K::Point_3 Point_3;
//
//int main(int argc, char* argv[])
//{
//
//	std::ifstream obj("C:/FILES/ProthesisBuilder/OUTPUT/Plate_binary.stl", std::ios::in | std::ios::binary);
//	for (int i = 0; i < 80; i++){
//		boost::uint8_t c;
//		obj.read(reinterpret_cast<char*>(&c), sizeof(c));
//		std::cerr << c;
//	}
//	std::cerr << std::endl;
//
//	boost::uint32_t N32;
//	obj.read(reinterpret_cast<char*>(&N32), sizeof(N32));
//	unsigned int N = N32;
//	std::cerr << N << " triangles" << std::endl;
//
//	std::vector<Point_3> points;
//	std::map<Point_3, int> pmap;
//	typedef boost::tuple<int, int, int> Face;
//	std::vector<Face> faces;
//	faces.reserve(N);
//
//
//	int number_of_points = 0;
//	int number_of_snapped_points = 0;
//
//	for (int i = 0; i < N; i++){
//		float normal[3];
//		obj.read(reinterpret_cast<char*>(&normal[0]), sizeof(normal[0]));
//		obj.read(reinterpret_cast<char*>(&normal[1]), sizeof(normal[1]));
//		obj.read(reinterpret_cast<char*>(&normal[2]), sizeof(normal[2]));
//
//
//		int index[3];
//		for (int j = 0; j < 3; j++){
//			float x, y, z;
//
//			obj.read(reinterpret_cast<char*>(&x), sizeof(x));
//			obj.read(reinterpret_cast<char*>(&y), sizeof(y));
//			obj.read(reinterpret_cast<char*>(&z), sizeof(z));
//			Point_3 p(x, y, z);
//			if (pmap.find(p) == pmap.end()){
//				// check brute force if there is a close point
//				bool found_close_point = false;
//				for (int k = 0; k < points.size(); k++){
//					if (sqrt(CGAL::squared_distance(p, points[k])) < 0.00001){
//						index[j] = k;
//						found_close_point = true;
//						number_of_snapped_points++;
//					}
//				}
//				if (!found_close_point){
//					points.push_back(p);
//					index[j] = number_of_points;
//					pmap[p] = number_of_points++;
//				}
//			}
//			else {
//				index[j] = pmap[p];
//			}
//		}
//		faces.push_back(boost::make_tuple(index[0], index[1], index[2]));
//		char c;
//		obj.read(reinterpret_cast<char*>(&c), sizeof(c));
//		obj.read(reinterpret_cast<char*>(&c), sizeof(c));
//	}
//	std::cerr << number_of_snapped_points << " snapped points" << std::endl;
//	std::cout.precision(20);
//
//#if 0
//	CGAL::compute_average_spacing(points.begin(), points.end(), 1);
//	return 0;
//#endif
//
//
//	freopen("C:/FILES/ProthesisBuilder/OUTPUT/OFFfromBinarySTL.OFF", "w", stdout);
//
//	std::cout << "OFF\n" << points.size() << " " << faces.size() << " 0" << std::endl;
//	for (int i = 0; i < points.size(); i++)
//	{
//		std::cout << points[i] << std::endl;
//	}
//
//	for (int i = 0; i < faces.size(); i++)
//	{
//		std::cout << "3 " << boost::get<0>(faces[i]) << " " << boost::get<1>(faces[i]) << " " << boost::get<2>(faces[i]) << std::endl;
//	}
//	std::cin.get();
//	return 0;
//}
