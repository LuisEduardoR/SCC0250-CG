cmake_minimum_required(VERSION 3.18)
project(cgtrabalho1)

include(pmm.cmake)
pmm(CONAN)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

#find_package(OpenGL REQUIRED)
#find_package(GLEW 2 REQUIRED)
#find_package(glfw3 3 REQUIRED)

set(COMMON_SOURCES
    src/Components/Camera.hpp
    src/Components/Camera.cpp
    src/Components/ShapeRenderer.cpp
    src/Components/GameObject.hpp
    src/Components/GameObject.cpp
    src/Components/Player.cpp
    src/Components/Moveable.hpp
    src/Components/Transform.hpp
    src/Components/Transform.cpp
    src/Components/Player.hpp
    src/Components/Component.hpp
    src/Components/ShapeRenderer.hpp
    src/Components/Moveable.cpp
    src/WindowSystem/WindowSystem.cpp
    src/WindowSystem/WindowSystem.hpp
    src/Interfaces/IUpdatable.hpp
    src/Scene/Scene.hpp
    src/Scene/GameScene.cpp
    src/Scene/GameScene.hpp
    src/Scene/Scene.cpp
    src/Events/Listener.hpp
    src/Events/Event.hpp
    src/Input/Input.cpp
    src/Input/Input.hpp
    src/Physics/CircleCollider.cpp
    src/Physics/CircleCollider.hpp
    src/Physics/Collider.hpp
    src/Physics/Collider.cpp
    src/Time/Time.cpp
    src/Time/Time.hpp
    src/Math/Matrix4x4.hpp
    src/Math/Matrix4x4.cpp
    src/Math/Vector.cpp
    src/Math/Vector.hpp
    src/Rendering/Renderer.cpp
    src/Rendering/VertexData.hpp
    src/Rendering/Geometry3D.hpp
    src/Rendering/PoissonDiscSampling.cpp
    src/Rendering/Shader.cpp
    src/Rendering/Geometry3D.cpp
    src/Rendering/PoissonDiscSampling.hpp
    src/Rendering/Renderer.hpp
    src/Rendering/Geometry2D.hpp
    src/Rendering/Geometry2D.cpp
    src/Rendering/Color.cpp
    src/Rendering/Shader.hpp
    src/Rendering/Color.hpp
)

add_executable(main
    "src/main.cpp"
    ${COMMON_SOURCES}
)

set(EXE_TARGETS
    main)

foreach(TARGET ${EXE_TARGETS})
    set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 17)
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
