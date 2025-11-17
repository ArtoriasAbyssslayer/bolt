#pragma once

#include "PhongDrawable.hpp"

#include <vector>

namespace bolt {
namespace gfx {

class DrawableCylinder : public PhongDrawable {
public:
    DrawableCylinder(float height, float radius, int segments = 16);
    virtual ~DrawableCylinder() {}

    virtual const void* vertexData() const override { return mVertices.data(); }
    virtual uint64_t vertexCount() const override { return mVertices.size(); }
    virtual DrawOp drawOp() const override { return BOLT_GFX_INDEXED; }
    virtual const uint32_t* indexData() const override { return mIndices.data(); }
    virtual uint64_t indexCount() const override { return mIndices.size(); }

private:
    std::vector<PhongDrawableVertex> mVertices;
    std::vector<uint32_t> mIndices;
};

} // gfx
} // bolt
