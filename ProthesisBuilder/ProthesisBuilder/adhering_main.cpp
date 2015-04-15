#define _SCL_SECURE_NO_WARNINGS //The program won't compile without this string
#define _CRT_SECURE_NO_WARNINGS

#include <CGAL/Cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/parameterize.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_polyhedron_triangle_primitive.h>
#include <CGAL/aff_transformation_tags.h>
#include <CGAL/Polyhedron_traits_with_normals_3.h>

#include <iostream>
#include <fstream>
#include <string>
#include "stdio.h"

typedef std::string string;
typedef std::ifstream ifstream;
typedef CGAL::Cartesian<double> Kernel;
typedef CGAL::Polyhedron_traits_with_normals_3<Kernel> Polyhedron_traits_with_normals_3;
typedef CGAL::Polyhedron_3<Polyhedron_traits_with_normals_3/*Kernel*/> Polyhedron;
typedef Polyhedron::Facet_iterator Facet_iterator;
typedef Polyhedron::Vertex_iterator Vertex_iterator;
typedef Polyhedron::Point_iterator Point_iterator;
typedef Polyhedron::Edge_iterator Edge_iterator;
typedef Polyhedron::Plane_iterator Plane_iterator;
typedef Polyhedron::Halfedge_iterator Halfedge_iterator;
typedef Polyhedron::Halfedge_around_facet_circulator Halfedge_facet_circulator;
typedef Polyhedron::Halfedge_around_vertex_circulator Halfedge_around_vertex_circulator;
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
typedef Kernel::Direction_3 Direction_3;

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
	//	 add the polyhedron triangles
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

struct Normal_vector {
	template <class Facet>
	typename Facet::Plane_3 operator()(Facet& f) {
		typename Facet::Halfedge_handle h = f.halfedge();
		 Facet::Plane_3 is the normal vector type. We assume the
		 CGAL Kernel here and use its global functions.
		return CGAL::cross_product(
			h->next()->vertex()->point() - h->vertex()->point(),
			h->next()->next()->vertex()->point() - h->next()->vertex()->point());
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
	for (Facet_iterator f = mesh.facets_begin(); f != mesh.facets_end(); ++f)
	{
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
void get_projection_surface(Polyhedron &surface_a, Tree &surface_b_geometry_tree, Vector_3 &projection_vector)
{
	Point_iterator pi = surface_a.points_begin();
	for (Vertex_iterator vi = surface_a.vertices_begin(); vi != surface_a.vertices_end(); vi++)
	{
		
			Ray ray(vi->point(), projection_vector);
			std::vector<Ray_intersection> all_intersections;
			std::vector<Point_3> all_intersection_points;
			std::vector<double> distances;
			if (surface_b_geometry_tree.do_intersect(ray))
			{
				surface_b_geometry_tree.all_intersections(ray, std::back_inserter(all_intersections));
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

void project_point_onto_surface(Point_iterator &pi, Tree &surface_geometry_tree, Vector_3 &projection_vector)
{
	Ray ray(*pi, projection_vector);
	std::vector<Ray_intersection> all_intersections;
	std::vector<Point_3> all_intersection_points;
	std::vector<double> distances;
	if (surface_geometry_tree.do_intersect(ray))
	{
		surface_geometry_tree.all_intersections(ray, std::back_inserter(all_intersections));
		for (int i = 0; i < all_intersections.size(); i++)
		{
			all_intersection_points.push_back(*boost::get<Point_3>(&(all_intersections[i]->first)));
		}

		for (int i = 0; i < all_intersection_points.size(); i++)
		{
			distances.push_back(pow(all_intersection_points[i].x() - pi->x(), 2) +
				pow(all_intersection_points[i].y() - pi->y(), 2) +
				pow(all_intersection_points[i].z() - pi->z(), 2));
		}

		int index_of_closest_point = std::min_element(distances.begin(), distances.end()) - distances.begin();
		Vector_3 translation_vector(*pi, all_intersection_points[index_of_closest_point]);
		Aff_transformation_3 translation(CGAL::TRANSLATION, translation_vector);
		Point_iterator end = pi;
		end++;
		std::transform(pi, end, pi, translation);
	}
}

void CreateAdheringSurface(Direction_3 &direction, Vector_3 projection_vector, Polyhedron &prothesis_mesh,
	Polyhedron &jaw_mesh, Polyhedron &rezult1, Polyhedron &rezult2)
{
	std::vector<double> coordsOfFirstGroup;
	std::vector<int>    trisOfFirstGroup;
	std::vector<double> coordsOfSecondGroup;
	std::vector<int>    trisOfSecondGroup;
	std::vector<double> coordsOfThirdGroup;
	std::vector<int>    trisOfThirdGroup;
	std::vector<double> coordsOfFourthGroup;
	std::vector<int>    trisOfFourthGroup;
	
	int indexOfPointInFirstGroup = -1;
	int indexOfPointInSecondGroup = -1;
	int indexOfPointInThirdGroup = -1;
	int indexOfPointInFourthGroup = -1;
	Normal_vector normal_vector;
	Vector_3 normal;
	Halfedge_facet_circulator fc;
	Plane_iterator pi = prothesis_mesh.facets_begin();
	for (Facet_iterator fi = prothesis_mesh.facets_begin(); fi != prothesis_mesh.facets_end(); ++fi)
	{
		normal = normal_vector(*fi);
		if (normal.direction() == direction)
		{
			fc = fi->facet_begin();
			do
			{
				coordsOfFirstGroup.push_back(fc->vertex()->point().x());
				coordsOfFirstGroup.push_back(fc->vertex()->point().y());
				coordsOfFirstGroup.push_back(fc->vertex()->point().z());
				trisOfFirstGroup.push_back(++indexOfPointInFirstGroup);
			} while (++fc != fi->facet_begin());
		}
		else if (normal.direction() != -direction)
		{
			if (abs(normal * direction.vector()) < 0.001)
			{
				fc = fi->facet_begin();
				do
				{
					coordsOfSecondGroup.push_back(fc->vertex()->point().x());
					coordsOfSecondGroup.push_back(fc->vertex()->point().y());
					coordsOfSecondGroup.push_back(fc->vertex()->point().z());
					trisOfSecondGroup.push_back(++indexOfPointInSecondGroup);
				} while (++fc != fi->facet_begin());
			}
			else if (normal * direction.vector() > 0)
			{
				fc = fi->facet_begin();
				do
				{
					coordsOfFirstGroup.push_back(fc->vertex()->point().x());
					coordsOfFirstGroup.push_back(fc->vertex()->point().y());
					coordsOfFirstGroup.push_back(fc->vertex()->point().z());
					trisOfFirstGroup.push_back(++indexOfPointInFirstGroup);
				} while (++fc != fi->facet_begin());
			}
		}
	}

	polyhedron_builder<HalfedgeDS> builder1(coordsOfFirstGroup, trisOfFirstGroup);
	rezult1.delegate(builder1);
	polyhedron_builder<HalfedgeDS> builder2(coordsOfSecondGroup, trisOfSecondGroup);
	rezult2.delegate(builder2);
	// constructs AABB tree
	Tree jaw_geometry_tree(jaw_mesh.facets_begin(), jaw_mesh.facets_end());
	jaw_geometry_tree.accelerate_distance_queries();
	std::cout << "AB started" << std::endl;
	jaw_geometry_tree.build();
	std::cout << "AB ended" << std::endl;
	for (Point_iterator pi1 = rezult1.points_begin(); pi1 != rezult1.points_end(); pi1++)
	{
		for (Point_iterator pi2 = rezult2.points_begin(); pi2 != rezult2.points_end(); pi2++)
		{
			if (pi1->x() == pi2->x() && pi1->y() == pi2->y() && pi1->z() == pi2->z())
			{
				project_point_onto_surface(pi2, jaw_geometry_tree, projection_vector);
			}
		}
	}
	get_projection_surface(rezult1, jaw_geometry_tree, projection_vector);
}

void main(int argc, char * argv[])
{
	// decode parameters
	if (argc - 1 != 2)
	{
		std::cerr << "Usage: " << argv[0] << " input_file.off" << std::endl;
	}

	// File name is:
	const char* input_filename_prothesis = argv[1];
	const char* input_filename_jaw = argv[2];

	// Read the mesh
	Polyhedron prothesis;
	read_polyhedron_from_off_file(input_filename_prothesis, prothesis);

	Polyhedron jaw;
	read_polyhedron_from_off_file(input_filename_jaw, jaw);

	Polyhedron rezult1;
	Polyhedron rezult2;
	Polyhedron rezult3;
	Polyhedron rezult4;

	Direction_3 direction(0, 0, -1);
	Vector_3 projection_vector(0.2, 0.2, -0.9);
	CreateAdheringSurface(direction, projection_vector, prothesis, jaw, rezult1, rezult2);
	std::ofstream os;
	os.open("C:/FILES/ProthesisBuilder/OUTPUT/rezult1.off");
	os << rezult1;
	os.close();
	os.open("C:/FILES/ProthesisBuilder/OUTPUT/rezult2.off");
	os << rezult2;
	os.close();
	os.open("C:/FILES/ProthesisBuilder/OUTPUT/rezult3.off");
	os << rezult3;
	os.close();

	std::cout << "Done";
}