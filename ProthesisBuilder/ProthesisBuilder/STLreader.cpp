#include <CGAL/Modifier_base.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Polyhedron_traits_with_normals_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <fstream>
#include <string>

#include <boost/tuple/tuple.hpp>

typedef CGAL::Cartesian<double> Kernel;
typedef Kernel::Point_3 Point_3;
typedef std::vector<Point_3> Points_3;
typedef boost::tuple<int, int, int> Facet;
typedef std::vector<Facet> Surface;
typedef CGAL::Polyhedron_traits_with_normals_3<Kernel> Polyhedron_traits_with_normals_3;
typedef CGAL::Polyhedron_3<Polyhedron_traits_with_normals_3> Polyhedron;

bool isASCII(std::string file_name)
{
	int c;
	std::ifstream input(file_name);
	while ((c = input.get()) != EOF && c <= 127)
		;
	if (c == EOF) {
		return true;
	}
	else return false;
}

template <class HDS>
class Build_from_stl : public CGAL::Modifier_base<HDS> {
	int counter;
	Points_3 meshPoints;
	Surface mesh;
	std::string file_name;

public:

	std::string name, color;


	Build_from_stl(std::string file_name)
		: counter(0), file_name(file_name)
	{}

	void operator()(HDS& hds) {
		if (!read(file_name, meshPoints, mesh)) return;

		CGAL::Polyhedron_incremental_builder_3<Polyhedron::HalfedgeDS> B(hds);
		B.begin_surface(meshPoints.size(), mesh.size());
		typedef typename Points_3::size_type size_type;

		for (size_type i = 0; i < meshPoints.size(); i++){
			B.add_vertex(meshPoints[i]);
		}
		for (size_type i = 0; i < mesh.size(); i++){
			B.begin_facet();
			B.add_vertex_to_facet(mesh[i].template get<0>());
			B.add_vertex_to_facet(mesh[i].template get<1>());
			B.add_vertex_to_facet(mesh[i].template get<2>());
			B.end_facet();
		}
		if (B.error())
		{
			std::cerr << "An error occured while creating a Polyhedron" << std::endl;
			B.rollback();
		}

		B.end_surface();
	}

	bool read(std::string file_name, Points_3& points, Surface& surface, int /*offset*/ = 0)
	{
		if (isASCII(file_name))
		{
			std::ifstream input(file_name);
			input.clear();
			input.seekg(0, input.beg);
			std::string s, solid("solid"), facet("facet"), outer("outer"), loop("loop"), vertex("vertex"), endloop("endloop"), endsolid("endsolid");
			std::map<Point_3, int> vertex_index;
			int index = 0;
			int ijk[3];
			Point_3 p;

			input >> s;
			if (s == solid)
			{
				std::getline(input, s);
			}
			else
			{
				std::cerr << "We expect keyword 'solid'" << std::endl;
				return false;
			}
			while (input >> s)
			{
				if (s == endsolid)
				{
					//std::cerr << "found endsolid" << std::endl;
				}
				else if (s == facet)
				{
					//std::cerr << "found facet" << std::endl;
					std::getline(input, s); // ignore the normal
					input >> s;
					if (s != outer)
					{
						std::cerr << "Expect 'outer' and got " << s << std::endl;
						return false;
					}
					input >> s;
					if (s != loop)
					{
						std::cerr << "Expect 'loop' and got " << s << std::endl;
						return false;
					}
					int count = 0;
					do
					{
						input >> s;
						if (s == vertex)
						{
							//      std::cerr << "found vertex" << std::endl;
							if (count < 3)
							{
								input >> p;
								if (vertex_index.find(p) == vertex_index.end())
								{
									ijk[count] = index;
									vertex_index[p] = index++;
									points.push_back(p);
								}
								else
								{
									ijk[count] = vertex_index[p];
								}
								++count;
							}
							else
							{
								std::cerr << "We can only read triangulated surfaces" << std::endl;
								return false;
							}
						}
					} while (s != endloop);
					surface.push_back(boost::make_tuple(ijk[0], ijk[1], ijk[2]));
				}
			}
			return true;
		}
		else
		{
			std::ifstream obj(file_name, std::ios::in | std::ios::binary);
			obj.clear();
			obj.seekg(0, obj.beg);
			for (int i = 0; i < 80; i++){
				boost::uint8_t c;
				obj.read(reinterpret_cast<char*>(&c), sizeof(c));
				std::cerr << c;
			}
			std::cerr << std::endl;

			boost::uint32_t N32;
			obj.read(reinterpret_cast<char*>(&N32), sizeof(N32));
			unsigned int N = N32;
			std::cerr << N << " triangles" << std::endl;

			//std::vector<Point_3> points;
			std::map<Point_3, int> pmap;
			typedef boost::tuple<int, int, int> Face;
			//std::vector<Face> faces;
			//faces.reserve(N);


			int number_of_points = 0;
			int number_of_snapped_points = 0;

			for (int i = 0; i < N; i++){
				float normal[3];
				obj.read(reinterpret_cast<char*>(&normal[0]), sizeof(normal[0]));
				obj.read(reinterpret_cast<char*>(&normal[1]), sizeof(normal[1]));
				obj.read(reinterpret_cast<char*>(&normal[2]), sizeof(normal[2]));


				int index[3];
				for (int j = 0; j < 3; j++){
					float x, y, z;

					obj.read(reinterpret_cast<char*>(&x), sizeof(x));
					obj.read(reinterpret_cast<char*>(&y), sizeof(y));
					obj.read(reinterpret_cast<char*>(&z), sizeof(z));
					Point_3 p(x, y, z);
					if (pmap.find(p) == pmap.end()){
						// check brute force if there is a close point
						bool found_close_point = false;
						for (int k = 0; k < points.size(); k++){
							if (sqrt(CGAL::squared_distance(p, points[k])) < 0.00001){
								index[j] = k;
								found_close_point = true;
								number_of_snapped_points++;
							}
						}
						if (!found_close_point){
							points.push_back(p);
							index[j] = number_of_points;
							pmap[p] = number_of_points++;
						}
					}
					else {
						index[j] = pmap[p];
					}
				}
				surface.push_back(boost::make_tuple(index[0], index[1], index[2]));
				char c;
				obj.read(reinterpret_cast<char*>(&c), sizeof(c));
				obj.read(reinterpret_cast<char*>(&c), sizeof(c));
			}
			std::cerr << number_of_snapped_points << " snapped points" << std::endl;
			std::cout.precision(20);

			freopen("C:/FILES/ProthesisBuilder/OUTPUT/OFFfromBinarySTL.OFF", "w", stdout);

			std::cout << "OFF\n" << points.size() << " " << surface.size() << " 0" << std::endl;
			for (int i = 0; i < points.size(); i++)
			{
				std::cout << points[i] << std::endl;
			}

			for (int i = 0; i < surface.size(); i++)
			{
				std::cout << "3 " << boost::get<0>(surface[i]) << " " << boost::get<1>(surface[i]) << " " << boost::get<2>(surface[i]) << std::endl;
			}
		}

	}

};


int readSTL(std::string file_name, Polyhedron &output)
{
	// Open file
	std::ifstream in(file_name);
	if (!in) {
		std::cerr << "Error! Cannot open file " << file_name << std::endl;
		return 1;
	}


	// Try to read STL file in a polyhedron
	Build_from_stl<Polyhedron::HalfedgeDS> builder(file_name);
	output.delegate(builder);
	if (!output.is_valid()){
		std::cerr << "Error: Invalid polyhedron" << std::endl;
		return 1;
	}

	if (output.empty()){
		return 1;
	}
	return 0;
}

void main()
{
	std::string file_name = "C:/FILES/ProthesisBuilder/OUTPUT/Plate_binary.stl";
	Polyhedron plate;
	readSTL(file_name, plate);
	std::ofstream os;
	os.open("C:/FILES/ProthesisBuilder/OUTPUT/okuet.off");
	os << plate;
	std::cin.get();
}