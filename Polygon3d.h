
#ifndef __3DFIER__Polygon3D__
#define __3DFIER__Polygon3D__

#include "definitions.h"
#include "geomtools.h"
#include <random>


class Polygon3d
{
public:
  Polygon3d  (Polygon2* p, std::string pid);
  ~Polygon3d ();

  virtual bool          threeDfy() = 0;
  virtual bool          add_elevation_point(double x, double y, double z) = 0;
  virtual std::string   get_lift_type() = 0;
  virtual std::string   get_3d_citygml() = 0;
  virtual std::string   get_3d_csv() = 0;
  virtual std::string   get_obj_v() = 0;
  virtual std::string   get_obj_f(int offset) = 0;
  virtual int           get_number_vertices() = 0;

  std::string  get_id();
  Polygon2*    get_Polygon2();
  Box          get_bbox2d();

protected:
  Polygon2*    _p2;
  std::string  _id;
};

//---------------------------------------------

class Polygon3dBlock : public Polygon3d 
{
public:
  Polygon3dBlock (Polygon2* p, std::string pid, std::string lifttype); 
  
  bool            threeDfy();
  bool            add_elevation_point(double x, double y, double z);
  std::string     get_3d_citygml();
  std::string     get_3d_csv();
  std::string     get_obj_v();
  std::string     get_obj_f(int offset);
  float           get_roof_height();
  float           get_floor_height();
  std::string     get_lift_type();
  int             get_number_vertices();
private:
  bool                  _is3d;

  std::vector<float>    _zvaluesinside;
  std::vector<float>    _vertexelevations;
  std::string           _lifttype;
  std::vector<Point3>   _vertices;
  std::vector<Triangle> _triangles;
  std::vector<Segment>  _segments;
  bool assign_elevation_to_vertex(double x, double y, double z);
  bool build_CDT();
};


//---------------------------------------------

class Polygon3dBoundary : public Polygon3d
{
public:
  Polygon3dBoundary (Polygon2* p, std::string pid);
  
  bool            threeDfy();
  bool            add_elevation_point(double x, double y, double z);
  std::string     get_3d_citygml();
  std::string     get_3d_csv();
  std::string     get_obj_v();
  std::string     get_obj_f(int offset);
  std::string     get_lift_type();
  int             get_number_vertices();
private:
  std::vector<Point3>   _lidarpts;
  std::vector<Point3>   _vertices;
  std::vector<Triangle> _triangles;
  std::vector<Segment>  _segments;
};


//---------------------------------------------

class Polygon3dTin : public Polygon3d
{
public:
  Polygon3dTin (Polygon2* p, std::string pid, std::string lifttype);
  
  bool            threeDfy();
  bool            add_elevation_point(double x, double y, double z);
  std::string     get_3d_citygml();
  std::string     get_3d_csv();
  std::string     get_obj_v();
  std::string     get_obj_f(int offset);
  std::string     get_lift_type();
  int             get_number_vertices();
private:
  std::string           _lifttype;
  int                   _thin;
  Polygon3              _p3;
  std::vector<Point3>   _lidarpts;
  std::vector<Point3>   _vertices;  //-- output of Triangle
  std::vector<Triangle> _triangles; //-- output of Triangle
  std::vector<Segment>  _segments;  //-- output of Triangle
};


#endif /* defined(__boo__Polygon3D__) */
