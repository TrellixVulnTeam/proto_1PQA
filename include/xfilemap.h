// -*- C++ -*-

/*
  Copyright (c) 2012-2013, University of Massachusetts Amherst.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*
 * @file:   xfilemap.h
 * @brief:  Handling file mapping
 * @author: Tongping Liu <http://www.cs.umass.edu/~tonyliu>
 */

#ifndef _XFILEMAP_H_
#define _XFILEMAP_H_

#include "xdefines.h"

class xfilemap {

public:
  void handleAccessTrap(void * addr, void * context) {
    return;
  }
  
  bool inRange(void * addr) {
    return false;
  }

  // We must keep track of file mapping every time.

private:
  void * start;
  void * end;
};

#endif /* _ */
