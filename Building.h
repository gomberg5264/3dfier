/*
 Copyright (c) 2015 Hugo Ledoux
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#ifndef Building_h
#define Building_h

#include "TopoFeature.h"


class Building : public Flat
{
public:
  Building (char *wkt, std::string pid, std::string heightref_top, std::string heightref_base);
  bool        lift();
  std::string get_citygml();
  std::string get_csv();
  std::string get_obj_f(int offset, bool usemtl);
  std::string get_obj_f_floor(int offset);
  std::string get_obj_v_building_volume(int z_exaggeration);
  std::string get_obj_f_building_volume(int offset, bool usemtl);
  TopoClass   get_class();
  bool        is_hard();
  int         get_height_base();
private: 
  static std::string  _heightref_top;
  static std::string  _heightref_base;
  int                 _height_base;
};


#endif /* Building_h */

