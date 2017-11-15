// This file is part of the AliceVision project.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <aliceVision/structures/mv_point3d.hpp>
#include <aliceVision/structures/mv_double3d.hpp>
#include <aliceVision/structures/mv_staticVector.hpp>

#include <array>


struct GC_cellInfo
{
    int cellId = -1;
    /// initialized to a large value if the tetrahedron is directly in front of one camera ELSE set to 0
    float cellSWeight = 0.0f;
    /// strong fullness: sum of weights for being the tetrahedron 2*sigma behind the point p
    float cellTWeight = 0.0f;
    /// true - occupied - full, false - free
    bool full = false;
    // float gEdgePhotoWeight[4];
    /// score for emptiness along each egde/facet
    std::array<float, 4> gEdgeVisWeight{{0.0f, 0.0f, 0.0f, 0.0f}};
    /// fullness score: sum of all weights for fullness (just after the point p)
    float in = 0.0f;
    /// emptiness score: sum of all weights for emptiness (before the point p)
    float out = 0.0f;
    /// first full tetrahedron score: sum of weights for T1 (tetrahedron just after the point p)
    float on = 0.0f;
    int color; // TODO FACA: label for connected components? // TODO FACA: not initialized


    void fwriteinfo(FILE* f) const
    {
        fwrite(&cellId, sizeof(int), 1, f);
        fwrite(&cellSWeight, sizeof(float), 1, f);
        fwrite(&cellTWeight, sizeof(float), 1, f);
        fwrite(&full, sizeof(bool), 1, f);
        fwrite(&in, sizeof(float), 1, f);
        fwrite(&out, sizeof(float), 1, f);
        fwrite(&on, sizeof(float), 1, f);

        // fwrite(gEdgePhotoWeight,sizeof(float),4,f);
        fwrite(&gEdgeVisWeight.front(), sizeof(float), 4, f);
    }

    void freadinfo(FILE* f, bool doNotCangeFull)
    {
        fread(&cellId, sizeof(int), 1, f);
        fread(&cellSWeight, sizeof(float), 1, f);
        fread(&cellTWeight, sizeof(float), 1, f);
        if(doNotCangeFull == true)
        {
            bool fullTmp;
            fread(&fullTmp, sizeof(bool), 1, f);
        }
        else
        {
            fread(&full, sizeof(bool), 1, f);
        }
        fread(&in, sizeof(float), 1, f);
        fread(&out, sizeof(float), 1, f);
        fread(&on, sizeof(float), 1, f);

        // fread(gEdgePhotoWeight,sizeof(float),4,f);
        fread(&gEdgeVisWeight.front(), sizeof(float), 4, f);
    }
};

struct GC_vertexInfo
{
    float pixSize = 0.0f;
    int nrc = 0; // TODO FACA: what is that? Is it different from cams->size()?
    int segSize = 0;
    int segId = -1;
    bool isOnSurface = false;
    staticVector<int> cams;

    /**
     * @brief Is the vertex a virtual point without associated camera? Like helper points or camera points.
     */
    inline bool isVirtual() const { return cams.empty(); }
    inline bool isReal() const { return !cams.empty(); }

    inline std::size_t getNbCameras() const
    {
        return cams.size();
    }

    inline int getCamera(std::size_t index) const
    {
        return cams[index];
    }

    void fwriteinfo(FILE* f) const
    {
        fwrite(&pixSize, sizeof(float), 1, f);
        fwrite(&nrc, sizeof(int), 1, f);
        fwrite(&segSize, sizeof(int), 1, f);
        fwrite(&segId, sizeof(int), 1, f);
        fwrite(&isOnSurface, sizeof(bool), 1, f);
        int n = cams.size();
        fwrite(&n, sizeof(int), 1, f);
        if(n > 0)
        {
            fwrite(&cams[0], sizeof(int), n, f);
        }
    }

    void freadinfo(FILE* f)
    {
        fread(&pixSize, sizeof(float), 1, f);
        fread(&nrc, sizeof(int), 1, f);
        fread(&segSize, sizeof(int), 1, f);
        fread(&segId, sizeof(int), 1, f);
        fread(&isOnSurface, sizeof(bool), 1, f);
        int n;
        fread(&n, sizeof(int), 1, f);
        if(n > 0)
        {
            cams.resize(n);
            fread(&cams[0], sizeof(int), n, f);
        }
    }
};

struct GC_camVertexInfo
{
    float sim; // TODO FACA: default value?
    int nrc = 0;
    int ncams = 0;
    point3d point;

    void fwriteinfo(FILE* f)
    {
        fwrite(&sim, sizeof(float), 1, f);
        fwrite(&nrc, sizeof(int), 1, f);
        fwrite(&ncams, sizeof(int), 1, f);
        fwrite(&point, sizeof(point3d), 1, f);
    }

    void freadinfo(FILE* f)
    {
        fread(&sim, sizeof(float), 1, f);
        fread(&nrc, sizeof(int), 1, f);
        fread(&ncams, sizeof(int), 1, f);
        fread(&point, sizeof(point3d), 1, f);
    }
};

