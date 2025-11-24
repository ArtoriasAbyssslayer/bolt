#pragma once

#include "Drawable.hpp"
#include "TexturedMesh.hpp"

#include <assimp/scene.h>

#include <vector>
#include <string>

namespace bolt {
namespace gfx {

class AssimpModel : public SceneNode {
public:
    AssimpModel(const char* path);
    ~AssimpModel();
    
    void load();

    std::vector<TexturedMesh>& meshes() { return mMeshes; }

private:
    void loadModel(const char* path);
    void processNode(aiNode *node, const aiScene *scene);
    TexturedMesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<TextureDescriptor> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    // I don't think it's a good idea at all to store SceneNode in vectors, since pointers to them may be invalidated after adding to the vector. (pointers used for scene graph connectivity)
    // TODO: Their pointers should be stored instead (lifetime managed by AssimpModel)
    std::vector<TexturedMesh> mMeshes;
    std::string mDirectory;
    char* mPath;
};

} // gfx
} // bolt
