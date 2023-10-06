#pragma once

#include <vector>

namespace shape {

// Vertices coordinates
static std::vector<float> pyramidVertices{
    -0.5f, 0.0f, 0.5f, // COORDS
    0.0f, 0.0f,        // TEXCOORDS
    0.0f, -1.0f, 0.0f, // NORMALS

    -0.5f, 0.0f, -0.5f, // COORDS
    0.0f, 5.0f,         // TEXCOORDS
    0.0f, -1.0f, 0.0f,  // NORMALS

    0.5f, 0.0f, -0.5f, // COORDS
    5.0f, 5.0f,        // TEXCOORDS
    0.0f, -1.0f, 0.0f, // NORMALS

    0.5f, 0.0f, 0.5f,  // COORDS
    5.0f, 0.0f,        // TEXCOORDS
    0.0f, -1.0f, 0.0f, // NORMALS
    //---------Bottom side---------

    -0.5f, 0.0f, 0.5f, // COORDS
    0.0f, 0.0f,        // TEXCOORDS
    -0.8f, 0.5f, 0.0f, // NORMALS

    -0.5f, 0.0f, -0.5f, // COORDS
    5.0f, 0.0f,         // TEXCOORDS
    -0.8f, 0.5f, 0.0f,  // NORMALS

    0.0f, 0.8f, 0.0f,  // COORDS
    2.5f, 5.0f,        // TEXCOORDS
    -0.8f, 0.5f, 0.0f, // NORMALS
    //---------Left Side----------

    -0.5f, 0.0f, -0.5f, // COORDS
    5.0f, 0.0f,         // TEXCOORDS
    0.0f, 0.5f, -0.8f,  // NORMALS

    0.5f, 0.0f, -0.5f, // COORDS
    0.0f, 0.0f,        // TEXCOORDS
    0.0f, 0.5f, -0.8f, // NORMALS

    0.0f, 0.8f, 0.0f,  // COORDS
    2.5f, 5.0f,        // TEXCOORDS
    0.0f, 0.5f, -0.8f, // NORMALS
    //--------Non-facing side------

    0.5f, 0.0f, -0.5f, // COORDS
    0.0f, 0.0f,        // TEXCOORDS
    0.8f, 0.5f, 0.0f,  // NORMALS

    0.5f, 0.0f, 0.5f, // COORDS
    5.0f, 0.0f,       // TEXCOORDS
    0.8f, 0.5f, 0.0f, // NORMALS

    0.0f, 0.8f, 0.0f, // COORDS
    2.5f, 5.0f,       // TEXCOORDS
    0.8f, 0.5f, 0.0f, // NORMALS
    //--------Right side----------

    0.5f, 0.0f, 0.5f, // COORDS
    5.0f, 0.0f,       // TEXCOORDS
    0.0f, 0.5f, 0.8f, // NORMALS

    -0.5f, 0.0f, 0.5f, // COORDS
    0.0f, 0.0f,        // TEXCOORDS
    0.0f, 0.5f, 0.8f,  // NORMALS

    0.0f, 0.8f, 0.0f, // COORDS
    2.5f, 5.0f,       // TEXCOORDS
    0.0f, 0.5f, 0.8f  // NORMALS

    //-------Facing side----------
};

// Indices for vertices order
static std::vector<unsigned int> pyramidIndices{
    0,  1,  2,  // Bottom side
    0,  2,  3,  // Bottom side
    4,  6,  5,  // Left side
    7,  9,  8,  // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14  // Facing side
};

static std::vector<float> lightVertices{
    //  COORDINATES      //  EXPLANATION
    +0.1f, +0.1f, +0.1f, // ...........
    +0.1f, +0.1f, -0.1f, // ...........
    +0.1f, -0.1f, -0.1f, // ...........
    +0.1f, -0.1f, +0.1f, // ...........
    -0.1f, -0.1f, +0.1f, // ...........
    -0.1f, -0.1f, -0.1f, // ...........
    -0.1f, +0.1f, -0.1f, // ...........
    -0.1f, +0.1f, +0.1f, // ...........
};

// Indices for vertices order
static std::vector<unsigned int> lightIndices{
    0, 3, 2, 2, 1, 0, // front square
    0, 1, 6, 0, 7, 6, // right square
    6, 5, 4, 4, 6, 7, // back square
    5, 2, 3, 3, 4, 5, // left square
    3, 4, 7, 7, 0, 3, // down square
    2, 5, 6, 6, 1, 2, // up square
};

} //name