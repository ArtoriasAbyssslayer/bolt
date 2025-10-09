// OpenglFramebuffer.hpp
#pragma once
#include "gfx/opengl/gl_defines.h" 
namespace bolt {
namespace gfx {
class OpenglFramebuffer {
public:
    OpenglFramebuffer(int width, int height);
    ~OpenglFramebuffer();
    
    void beginFrame();
    void endFrame();
    
    void use();           // Alias for beginFrame()
    void useEmbedded();   // Bind to screen framebuffer
    void readBuffer(void* data);
    
    GLuint getCurrentRenderFBO() const;
    GLuint getDisplayFBO() const;
    GLuint getReadFBO() const;
    int bufferSize() const;

private:
    static constexpr int BUFFER_COUNT = 3;
    
    int mWidth, mHeight;
    // Triple buffering arrays
    GLuint mFbos[BUFFER_COUNT];
    GLuint mRboColors[BUFFER_COUNT];
    GLuint mRboDepths[BUFFER_COUNT];
    
    // Buffer rotation indices
    int mRenderIndex;
    int mDisplayIndex;
    int mReadIndex;
    
    void createBuffer(int index);
    void destroyBuffer(int index);
};

} // gfx
} // bolt