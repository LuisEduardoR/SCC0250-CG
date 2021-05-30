cmake_minimum_required(VERSION 3.18)
project(cgtrabalho1)

include(pmm.cmake)
pmm(CONAN)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

#find_package(OpenGL REQUIRED)
#find_package(GLEW 2 REQUIRED)
#find_package(glfw3 3 REQUIRED)

set(COMMON_SOURCES
    "src/Color.hpp"
    "src/Color.cpp"
    "src/Geometry.hpp"
    "src/Geometry.cpp"
    "src/Renderer.hpp"
    "src/Renderer.cpp"
    "src/Transform.hpp"
    "src/Transform.cpp"
    "src/Vector.hpp"
    "src/Vector.cpp"
    "src/Matrix.hpp"
    "src/Matrix.cpp"
    "src/Matrix4x4.hpp"
    "src/Matrix4x4.cpp"
    "src/Shader.hpp"
    "src/Shader.cpp"
    "src/WindowSystem.hpp"
    "src/WindowSystem.cpp"
    "src/Object2D.hpp"
    "src/Object2D.cpp"
    "src/Collider2D.hpp"
    "src/Time.hpp"
    "src/Transform.hpp"
    "src/Transform.cpp"
    "src/adven/Collider.hpp"
    "src/adven/CircleCollider.hpp"
    "src/Collider.cpp"
    "src/CircleCollider.cpp"
    "src/adven/GameObject.hpp"
    "src/adven/Scene.hpp"
    "src/adven/Component.hpp"
    "src/adven/IUpdatable.hpp"
    "src/adven/Moveable.hpp"
    "src/Scene.cpp"
    "src/GameObject.cpp"
    "src/Moveable.cpp"
    "src/ShapeRenderer.hpp"
    "src/ShapeRenderer.cpp"
    "src/TestScene.hpp"
    "src/TestScene.cpp"
    "src/Input.hpp"
    "src/Input.cpp"
    "src/Player.hpp"
    "src/Player.cpp"
    "src/PoissonDiscSampling.hpp"
    "src/PoissonDiscSampling.cpp"
    "src/Time.hpp"
    "src/Time.cpp"
)

add_executable(main
    "src/main.cpp"
    ${COMMON_SOURCES}
)

set(EXE_TARGETS
    main)

foreach(TARGET ${EXE_TARGETS})
    set_property(TARGET ${TARGET} PROPERTY CXX_EXTENSIONS OFF)
    target_compile_features(${TARGET} PUBLIC cxx_std_17)

    target_link_libraries(${TARGET} 
        PRIVATE
            #GL
            #GLEW
            #glfw
            CONAN_PKG::glew
            CONAN_PKG::glfw
    )

    target_compile_options(${TARGET}
        PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
            #-Werror             # Treat warnings as errors.
            -Wall               # Enables many warning but despite the name not all.
            -Wextra             # More warnings.
            -Wconversion        # Warn on implicit conversion that might alter a value.
            -Wsign-conversion   # Warn also about implict conversion between signed and unsigned types.
            #-pedantic-errors    # Error on language extensions.
        >
        $<$<CXX_COMPILER_ID:MSVC>:
            /WX     # Treat warnings as errors.
            /W4     # Warning level 4.
        >
    )
endforeach(TARGET)
