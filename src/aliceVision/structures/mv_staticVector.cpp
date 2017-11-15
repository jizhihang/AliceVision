// This file is part of the AliceVision project.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "mv_staticVector.hpp"

#include <cstdio>


int getArrayLengthFromFile(std::string fileName)
{
    FILE* f = fopen(fileName.c_str(), "rb");
    if(f == nullptr)
    {
        // printf("WARNING: file %s does not exists!\n", fileName.c_str());
        return 0;
    }

    int n = 0;
    fread(&n, sizeof(int), 1, f);
    if(n == -1)
    {
        fread(&n, sizeof(int), 1, f);
    }
    fclose(f);
    return n;
}
