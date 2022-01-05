/*  This file is part of the Pinocchio automatic rigging library.
    Copyright (C) 2007 Ilya Baran (ibaran@mit.edu)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef DEBUGGING_H
#define DEBUGGING_H

#include "mathutils.h"
#include <iostream>

class Debugging
{
public:
    static std::ostream &out() { return *outStream; }
    static void setOutStream(std::ostream &os) { outStream = &os; }

private:
    static std::ostream *outStream;
};

#define DEBUG

#ifdef DEBUG
#define M_DEBUG(msg) std::cout << msg
#else
#define M_DEBUG(msg)
#endif

#endif // DEBUGGING_H
