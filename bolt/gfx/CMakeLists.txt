project(bolt_gfx)

# find assimp (optional)
find_package(assimp)

add_subdirectory(vendored/glad)

option(BOLT_GFX_ENABLE_VULKAN "Enable Vulkan backend" OFF)
if(BOLT_GFX_ENABLE_VULKAN)
    find_package(Vulkan REQUIRED)
endif()

set(gfx_SRC
    src/Drawable.cpp
    src/FlatDrawable.cpp
    src/DrawableLine.cpp
    src/PhongDrawable.cpp
    src/DrawableCone.cpp
    src/DrawableCuboid.cpp
    src/DrawableCylinder.cpp
    src/DrawableSpheroid.cpp
    src/DrawableTriangle.cpp
    src/TexturedMesh.cpp

    src/Axis.cpp

    src/SceneNode.cpp
    src/SceneManager.cpp
    src/Camera.cpp
    src/Color.cpp
    src/PhongMaterial.cpp

    src/opengl/OpenglRenderSystem.cpp
    src/opengl/OpenglProgram.cpp
    src/opengl/OpenglTexture.cpp
    src/opengl/OpenglUniformBuffer.cpp
    src/opengl/OpenglFramebuffer.cpp
    src/opengl/GlUtils.cpp
    src/opengl/gl_defines.cpp
)
if(BOLT_GFX_ENABLE_VULKAN)
    list(APPEND gfx_SRC
        src/vulkan/VulkanRenderSystem.cpp
        src/vulkan/VulkanDrawable.cpp
        src/vulkan/VulkanDrawList.cpp
        src/vulkan/VulkanProgram.cpp
    )
endif()

if(TARGET assimp::assimp)
    list(APPEND gfx_SRC src/AssimpModel.cpp)
endif()

add_library(gfx ${gfx_SRC})
add_library(bolt::gfx ALIAS gfx)
target_include_directories(gfx
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE
    vendored/stb
)
target_link_libraries(gfx PRIVATE glad PUBLIC bolt::math bolt::util)
target_compile_definitions(gfx PRIVATE BOLT_GFX_ROOT="${PROJECT_SOURCE_DIR}")

if(BOLT_GFX_ENABLE_VULKAN)
    target_link_libraries(gfx PRIVATE Vulkan::Vulkan)
    target_compile_definitions(gfx PRIVATE BOLT_GFX_HAVE_VULKAN)
endif()

if(TARGET assimp::assimp)
    target_compile_definitions(gfx PRIVATE HAVE_ASSIMP)
    target_link_libraries(gfx PRIVATE assimp::assimp)
endif()

install(TARGETS gfx glad
        EXPORT gfxTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT gfxTargets
        FILE boltGfxTargets.cmake
        NAMESPACE bolt::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bolt
)

