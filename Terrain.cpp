/*
  3dfier: takes 2D GIS datasets and "3dfies" to create 3D city models.
  
  Copyright (C) 2015-2016  3D geoinformation research group, TU Delft

  This file is part of 3dfier.

  3dfier is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  3dfier is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with 3difer.  If not, see <http://www.gnu.org/licenses/>.

  For any information or further details about the use of 3dfier, contact
  Hugo Ledoux 
  <h.ledoux@tudelft.nl>
  Faculty of Architecture & the Built Environment
  Delft University of Technology
  Julianalaan 134, Delft 2628BL, the Netherlands
*/


#include "Terrain.h"
#include <algorithm>


Terrain::Terrain (char *wkt, std::string pid, int simplification, float innerbuffer)
: TIN(wkt, pid, simplification, innerbuffer)
{}


bool Terrain::lift() {
  //-- lift vertices to their median of lidar points
  TopoFeature::lift_each_boundary_vertices(0.5);
  return true;
}


bool Terrain::add_elevation_point(double x, double y, double z, float radius, LAS14Class lasclass, bool lastreturn) {
  bool toadd = false;
  if (_simplification <= 1)
    toadd = true;
  else {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, _simplification);
    if (dis(gen) == 1)
      toadd = true;
  }
  if (toadd && lastreturn && lasclass == LAS_GROUND) {
    Point2 p(x, y);
    if (bg::within(p, *(_p2)) && (this->get_distance_to_boundaries(p) > _innerbuffer)) {
      _lidarpts.push_back(Point3(x, y, z));
    }
    assign_elevation_to_vertex(x, y, z, radius);
  }
  return toadd;
}


std::string Terrain::get_mtl() {
  return "usemtl Terrain\n";
}


TopoClass Terrain::get_class() {
  return TERRAIN;
}

bool Terrain::is_hard() {
  return false;
}


std::string Terrain::get_citygml() {
  return "<EMPTY/>";
}


bool Terrain::get_shape(OGRLayer* layer) {
  return TopoFeature::get_shape_features(layer, "Terrain");
}

