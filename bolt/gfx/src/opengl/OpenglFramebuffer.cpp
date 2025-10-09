#include "gfx/opengl/OpenglFramebuffer.hpp"
#include "gfx/opengl/GlUtils.hpp"
#include "gfx/opengl/gl_defines.h"
#include "util/common.h"

namespace bolt {
namespace gfx {

OpenglFramebuffer::OpenglFramebuffer(int width, int height) 
    : mWidth(width), mHeight(height),
      mRenderIndex(0), mDisplayIndex(1), mReadIndex(2) {
    
    // Create three complete framebuffers
    for (int i = 0; i < BUFFER_COUNT; ++i) {
        createBuffer(i);
    }
}

void OpenglFramebuffer::createBuffer(int index) {
    glGenFramebuffers(1, &mFbos[index]);
    
    // color render buffer
    glGenRenderbuffers(1, &mRboColors[index]);
    glBindRenderbuffer(GL_RENDERBUFFER, mRboColors[index]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB32F, mWidth, mHeight);
    
    // depth render buffer
    glGenRenderbuffers(1, &mRboDepths[index]);
    glBindRenderbuffer(GL_RENDERBUFFER, mRboDepths[index]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mWidth, mHeight);
    
    // attach render buffers
    GLint previousFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mFbos[index]);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mRboColors[index]);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRboDepths[index]);
    
    RUNTIME_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, 
                   "Incomplete framebuffer");
    
    glBindFramebuffer(GL_FRAMEBUFFER, previousFBO);
}

void OpenglFramebuffer::destroyBuffer(int index) {
    GLint previousFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mFbos[index]);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, previousFBO);
    
    glDeleteRenderbuffers(1, &mRboColors[index]);
    glDeleteRenderbuffers(1, &mRboDepths[index]);
    glDeleteFramebuffers(1, &mFbos[index]);
}

OpenglFramebuffer::~OpenglFramebuffer() {
    for (int i = 0; i < BUFFER_COUNT; ++i) {
        destroyBuffer(i);
    }
}

void OpenglFramebuffer::beginFrame() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFbos[mRenderIndex]);
}

void OpenglFramebuffer::endFrame() {
    // Rotate buffers: render -> display -> read -> render
    int nextRender = mDisplayIndex;
    int nextDisplay = mReadIndex;
    int nextRead = mRenderIndex;
    
    mRenderIndex = nextRender;
    mDisplayIndex = nextDisplay;
    mReadIndex = nextRead;
}

void OpenglFramebuffer::use() {
    beginFrame();
}

void OpenglFramebuffer::useEmbedded() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void OpenglFramebuffer::readBuffer(void* data) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mFbos[mReadIndex]);
    glReadPixels(0, 0, mWidth, mHeight, GL_RGB, GL_FLOAT, data);
}

GLuint OpenglFramebuffer::getCurrentRenderFBO() const {
    return mFbos[mRenderIndex];
}

GLuint OpenglFramebuffer::getDisplayFBO() const {
    return mFbos[mDisplayIndex];
}

GLuint OpenglFramebuffer::getReadFBO() const {
    return mFbos[mReadIndex];
}

int OpenglFramebuffer::bufferSize() const {
    // RGB with 32-bit floats per channel = 3 channels * 4 bytes per float
    return mWidth * mHeight * 3 * sizeof(float);
}

} // gfx
} // bolt