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

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <istream>
#include <sstream>

template <class T>
inline string toString(const T &obj)
{
    ostringstream stream;
    stream << obj;
    return stream.str();
}

inline vector<string> readWords(istream &stream)
{
    string whitespace = " \n\t\r";
    stream >> noskipws;

    char tmp[10000];
    stream.getline(tmp, 9990);
    string line(tmp);

    if (line.size() == 0)
        return vector<string>();

    while (line[line.size() - 1] == '\\')
    {
        line[line.size() - 1] = ' ';
        stream.getline(tmp, 9990);
        line = line + string(tmp);
    }

    // split the line into words
    vector<string> words;
    string::size_type pos = 0;
    while (pos != string::npos)
    {
        pos = line.find_first_not_of(whitespace, pos);
        if (pos == string::npos)
            break;
        string::size_type eow = line.find_first_of(whitespace, pos);
        words.push_back(string(line, pos, eow - pos));
        pos = eow;
    }

    return words;
}

template <int Bits>
void decimalToBits(int num, int bit_arr[])
{
    int i = 0;
    while (num / Bits)
    {
        bit_arr[i] = num % Bits;
        num /= Bits;
        i++;
    }
    bit_arr[i] = num;
    // std::reverse(bit_arr, bit_arr + 4);
}

// https://stackoverflow.com/questions/2978259/programmatically-create-static-arrays-at-compile-time-in-c
// A 3 by 3 grids if Dim==2, permute 9 samples from [low, low],[mid, low], ..., [hi, hi]
// A 3 by 3 by 3 grids if Dim==3, permute 9 samples from [low, low, low],[mid, low, low], ..., [hi, hi, hi]
// 0: low, 1:hi, 2:mid
template <int Dim>
struct Grid3
{
    static const int num_corners = std::pow(3, Dim);
    Grid3()
    {
        for (int i = 0; i < num_corners; ++i)
        {
            decimalToBits<3>(i, &m[i][0]);
            std::cout << i << ": ";
            std::copy(&m[i][0], &m[i][0] + Dim, std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
    }

    int bit(int i_corner, int j_bit) const { return m[i_corner][j_bit]; }

private:
    int m[num_corners][Dim] = {0};
};

#endif // UTILS_H_INCLUDED
