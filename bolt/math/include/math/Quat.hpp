#pragma once

namespace bolt {
namespace math {

struct Quatf {
    float x;
    float y;
    float z;
    float w;

    Quatf(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

} // math
} // bolt
