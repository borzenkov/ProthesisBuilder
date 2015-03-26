#define _SCL_SECURE_NO_WARNINGS //The program won't compile without this string

#include <CGAL/Cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/Parameterization_polyhedron_adaptor_3.h>
#include <CGAL/parameterize.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_polyhedron_triangle_primitive.h>
#include <CGAL/aff_transformation_tags.h>

#include <iostream>
#include <fstream>
#include <string>
#include "stdio.h"

typedef std::string string;
typedef std::ifstream ifstream;
typedef CGAL::Cartesian<double> Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Polyhedron::Facet_iterator Facet_iterator;
typedef Polyhedron::Vertex_iterator Vertex_iterator;
typedef Polyhedron::Point_iterator Point_iterator;
typedef Polyhedron::Halfedge_around_facet_circulator Halfedge_facet_circulator;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Vector_3 Vector_3;
typedef Polyhedron::HalfedgeDS HalfedgeDS;
typedef Kernel::Ray_3 Ray;
typedef CGAL::AABB_polyhedron_triangle_primitive<Kernel, Polyhedron> Primitive;
typedef CGAL::AABB_traits<Kernel, Primitive> Traits;
typedef CGAL::AABB_tree<Traits> Tree;
typedef boost::optional< Tree::Intersection_and_primitive_id<Ray>::Type > Ray_intersection;
typedef CGAL::Translation Translation;
typedef CGAL::Aff_transformation_3<Kernel> Aff_transformation_3;

// A modifier creating a triangle with the incremental builder.
template<class HDS>
class polyhedron_builder : public CGAL::Modifier_base<HDS> {
public:
	std::vector<double> &coords;
	std::vector<int>    &tris;
	polyhedron_builder(std::vector<double> &_coords, std::vector<int> &_tris) : coords(_coords), tris(_tris) {}
	void operator()(HDS& hds) {
		typedef typename HDS::Vertex   Vertex;
		typedef typename Vertex::Point Point;
		// create a cgal incremental builder
		CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);
		B.begin_surface(coords.size() / 3, tris.size() / 3);
		// add the polyhedron vertices
		for (int i = 0; i<(int)coords.size(); i += 3){
			B.add_vertex(Point(coords[i + 0], coords[i + 1], coords[i + 2]));
		}
		// add the polyhedron triangles
		for (int i = 0; i<(int)tris.size(); i += 3){
			B.begin_facet();
			B.add_vertex_to_facet(tris[i + 0]);
			B.add_vertex_to_facet(tris[i + 1]);
			B.add_vertex_to_facet(tris[i + 2]);
			B.end_facet();
		}
		// finish up the surface
		B.end_surface();
	}
};

int read_polyhedron_from_off_file(const char* input_filename, Polyhedron &mesh)
{
	std::ifstream stream(input_filename);
	stream >> mesh;
	if (!stream || !mesh.is_valid() || mesh.empty())
	{
		std::cerr << "Error: cannot read OFF file " << input_filename << std::endl;
		return 1;
	}
	return 0;
}

void get_facets_with_equal_z_and_specified_tolerance(double z, double tolerance, Polyhedron &mesh, Polyhedron &rezult)
{
	std::vector<double> coords;
	std::vector<int>    tris;
	int counter_of_points_with_equal_z = 0, index_of_point = -1;
	for (Facet_iterator f = mesh.facets_begin(); f != mesh.facets_end(); ++f) {
		counter_of_points_with_equal_z = 0;
		Halfedge_facet_circulator v = f->facet_begin();
		do
		{
			if ((v->vertex()->point().z() > (z - tolerance)) && (v->vertex()->point().z() < z + tolerance))
			{
				counter_of_points_with_equal_z++;
			}
		} while (++v != f->facet_begin());
		if (counter_of_points_with_equal_z >= 1)
		{
			v = f->facet_begin();
			do
			{
				coords.push_back(v->vertex()->point().x());
				coords.push_back(v->vertex()->point().y());
				coords.push_back(v->vertex()->point().z());
				tris.push_back(++index_of_point);
			} while (++v != f->facet_begin());
		}
	}
	polyhedron_builder<HalfedgeDS> builder(coords, tris);
	rezult.delegate(builder);
}

void create_big_triangle(Polyhedron &big_triangle)
{
	std::vector<double> coords;
	coords.push_back(20);
	coords.push_back(20);
	coords.push_back(10);
	coords.push_back(0);
	coords.push_back(-20);
	coords.push_back(10);
	coords.push_back(-20);
	coords.push_back(20);
	coords.push_back(10);
	std::vector<int> tris;
	tris.push_back(0);
	tris.push_back(1);
	tris.push_back(2);
	polyhedron_builder<HalfedgeDS> builder(coords, tris);
	big_triangle.delegate(builder);
}

//surface_a will be projected onto surface_b with projection_vector and the output surface will be written into surface_a
void get_projection_surface(Polyhedron &surface_a, Polyhedron &surface_b, Vector_3 &projection_vector)
{
	// constructs AABB tree
	Tree jaw_geometry_tree(surface_b.facets_begin(), surface_b.facets_end());

	Point_iterator pi = surface_a.points_begin();
	for (Vertex_iterator vi = surface_a.vertices_begin(); vi != surface_a.vertices_end(); vi++)
	{
		Ray ray(vi->point(), projection_vector);
		// computes first encountered intersection with segment query
		// (generally a point)
		std::vector<Ray_intersection> all_intersections;
		std::vector<Point_3> all_intersection_points;
		std::vector<double> distances;
		if (jaw_geometry_tree.do_intersect(ray))
		{
			jaw_geometry_tree.all_intersections(ray, std::back_inserter(all_intersections));
			for (int i = 0; i < all_intersections.size(); i++)
			{
				all_intersection_points.push_back(*boost::get<Point_3>(&(all_intersections[i]->first)));
			}

			for (int i = 0; i < all_intersection_points.size(); i++)
			{
				distances.push_back(pow(all_intersection_points[i].x() - vi->point().x(), 2) +
					pow(all_intersection_points[i].y() - vi->point().y(), 2) +
					pow(all_intersection_points[i].z() - vi->point().z(), 2));
			}

			int index_of_closest_point = std::min_element(distances.begin(), distances.end()) - distances.begin();
			Vector_3 translation_vector(vi->point(), all_intersection_points[index_of_closest_point]);
			Aff_transformation_3 translation(CGAL::TRANSLATION, translation_vector);
			Point_iterator end = pi;
			end++;
			std::transform(pi, end, pi, translation);
		}
		pi++;
	}
}

int read_my_OFF(const char* file_name, Polyhedron &rezult)
{
	char format[4];
	long int number_of_points, number_of_faces, number_of_lines;
	int number_of_composing_points, index1, index2, index3;
	double x, y, z;
	std::vector<double> coords;
	std::vector<int> tris;
	FILE *f;
	if ((f = fopen(file_name, "r")) != NULL)
	{
		fscanf(f, "%s%d%d%d", format, &number_of_points, &number_of_faces, &number_of_lines);
		for (int i = 0; i < number_of_points; i++)
		{
			fscanf(f, "%f%f%f", &x, &y, &z);
			coords.push_back(x);
			coords.push_back(y);
			coords.push_back(z);
		}
		for (int i = 0; i < number_of_faces; i++)
		{
			fscanf(f, "%d%d%d%d", &number_of_composing_points, &index1, &index2, &index3);
			tris.push_back(index1);
			tris.push_back(index2);
			tris.push_back(index3);
		}
	}
	fclose(f);
	polyhedron_builder<HalfedgeDS> builder(coords, tris);
	rezult.delegate(builder);
	return 0;
}

int main(int argc, char * argv[])
{
	// decode parameters
	if (argc - 1 != 2)
	{
		std::cerr << "Usage: " << argv[0] << " input_file.off" << std::endl;
		return(EXIT_FAILURE);
	}

	// File name is:
	const char* input_filename_prothesis = argv[1];
	const char* input_filename_jaw = argv[2];

	// Read the mesh
	Polyhedron prothesis;
	read_polyhedron_from_off_file(input_filename_prothesis, prothesis);

	Polyhedron prothesis_part;
	get_facets_with_equal_z_and_specified_tolerance(0, 0.001, prothesis, prothesis_part);
	std::ofstream os;
	os.open("C:/FILES/ProthesisBuilder/OUTPUT/prothesis_part.off");
	os << prothesis_part;
	os.close();

	Polyhedron jaw;
	read_polyhedron_from_off_file(input_filename_jaw, jaw);

	Polyhedron big_triangle;
	create_big_triangle(big_triangle);
	os.open("C:/FILES/ProthesisBuilder/OUTPUT/big_triangle.off");
	os << big_triangle;
	os.close();

	Vector_3 projection_vector(0.2, 0.2, -0.9);
	get_projection_surface(prothesis_part, jaw, projection_vector);

	os.open("C:/FILES/ProthesisBuilder/OUTPUT/rezult.off");
	os << prothesis_part;
	os.close();

	std::cout << "Done";

	return 0;
}