// -*- C++ -*-

/*
  Author: Emery Berger, http://www.cs.umass.edu/~emery
 
  Copyright (c) 2007-8 Emery Berger, University of Massachusetts Amherst.

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

#ifndef _XONEHEAP_H_
#define _XONEHEAP_H_

/**
 * @class xoneheap
 * @brief Wraps a single heap instance.
 *        Since this class don't have private variables and doesn't
 *        inheritted from SourceHeap, thus SourceHeap won't be initialized
 *        multiple times.
 * @author Emery Berger <http://www.cs.umass.edu/~emery>
 * @author Tongping Liu <http://www.cs.umass.edu/~tonyliu>
 */

template <class SourceHeap>
class xoneheap {
public:

  void initialize (void) { getHeap()->initialize(); }
  void finalize (void) { getHeap()->finalize(); }

  void handleAccessTrap(void * addr, void * context) { getHeap()->handleAccessTrap(addr, context); }
  bool inRange(void * addr) { getHeap()->inRange(addr); }
 
  void * startProtection(void) {getHeap()->startProtection(); }
  void * stopProtection(void) {getHeap()->stopProtection(); }
  void setMemoryUnowned(void) { getHeap()->setMemoryUnowned(); }

  void * malloc (size_t sz) { return getHeap()->malloc(sz); }
  void free (void * ptr) { getHeap()->free(ptr); }
  size_t getSize (void * ptr) { return getHeap()->getSize(ptr); }
private:

  // Ensure the single instance of "SourceHeap"
  SourceHeap * getHeap (void) {
    static char heapbuf[sizeof(SourceHeap)];
    static SourceHeap * _heap = new (heapbuf) SourceHeap;
    return _heap;
  }
};


#endif // _XONEHEAP_H_
