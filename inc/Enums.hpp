#pragma once
///this Code likewise came form C++ 23 and me course resources
namespace Atlas
{
    enum class AddressMode
    {
        Wrap,    ///< Tile the texture.
        Mirror,  ///< Flip the texture coordinates at integer boundaries.
        Clamp,   ///< Clamp texture coordinates in the range 0..1.
        Border   ///< Use border color for out-of-range texture coordinates.
    };

    enum class FillMode
    {
        WireFrame,  ///< Polygons are drawn as line segments.
        Solid       ///< Polygons interiors are filled.
    };

    enum class CullMode
    {
        None,   ///< Always draw triangles.
        Front,  ///< Do not draw front-facing triangles.
        Back    ///< Do not draw back-facing triangles.
    };

}