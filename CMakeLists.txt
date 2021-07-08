cmake_minimum_required(VERSION 3.18)
project(cgtrabalho2)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${CMAKE_SOURCE_DIR}/external/SDL2Test/cmake/")

include(pmm.cmake)
pmm(CONAN)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

#find_package(OpenGL REQUIRED)
#find_package(GLEW 2 REQUIRED)
#find_package(glfw3 3 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(COMMON_SOURCES
    src/Assets/AssetLoader.cpp
    src/Assets/AssetLoader.hpp
    src/Assets/Texture2D.hpp
    src/Assets/Texture2D.cpp
    src/Assets/WavefrontObject.hpp
    src/Assets/WavefrontObject.cpp
    src/Assets/WavefrontParser.hpp
    src/Components/BaseEnemy.hpp
    src/Components/Boss.cpp
    src/Components/Boss.hpp
    src/Components/Camera.cpp
    src/Components/Camera.hpp
    src/Components/Component.cpp
    src/Components/Component.hpp
    src/Components/DamageOnContact.cpp
    src/Components/DamageOnContact.hpp
    src/Components/DestroyArea.cpp
    src/Components/DestroyArea.hpp
    src/Components/DestroyOnDie.cpp
    src/Components/DestroyOnDie.hpp
    src/Components/EnemyShip.cpp
    src/Components/EnemyShip.hpp
    src/Components/ExitOnDeath.cpp
    src/Components/ExitOnDeath.hpp
    src/Components/FollowObject.cpp
    src/Components/FollowObject.hpp
    src/Components/GameObject.cpp
    src/Components/GameObject.hpp
    src/Components/Health.cpp
    src/Components/Health.hpp
    src/Components/HealthBar.cpp
    src/Components/HealthBar.hpp
    src/Components/Moveable.cpp
    src/Components/Moveable.hpp
    src/Components/Player.cpp
    src/Components/Player.hpp
    src/Components/RendererComponent.hpp
    src/Components/RenderParamInput.hpp
    src/Components/RenderParamInput.cpp
    src/Components/Shooter.cpp
    src/Components/Shooter.hpp
    src/Components/SplitOnDie.cpp
    src/Components/SplitOnDie.hpp
    src/Components/TimedSpawner.cpp
    src/Components/TimedSpawner.hpp
    src/Components/Transform.cpp
    src/Components/Transform.hpp
    src/Components/WrapAround.cpp
    src/Components/WrapAround.hpp
    src/Events/Event.hpp
    src/Events/Listener.hpp
    src/Exceptions/Exceptions.cpp
    src/Exceptions/Exceptions.hpp
    src/Input/Input.cpp
    src/Input/Input.hpp
    src/Interfaces/IUpdatable.hpp
    src/Math/Matrix4x4.cpp
    src/Math/Matrix4x4.hpp
    src/Math/Vector.cpp
    src/Math/Vector.hpp
    src/Physics/CircleCollider.cpp
    src/Physics/CircleCollider.hpp
    src/Physics/Collider.cpp
    src/Physics/Collider.hpp
    src/Rendering/Color.cpp
    src/Rendering/Color.hpp
    src/Rendering/Geometry.cpp
    src/Rendering/Geometry.hpp
    src/Rendering/PoissonDiscSampling.cpp
    src/Rendering/PoissonDiscSampling.hpp
    src/Rendering/RenderData.hpp
    src/Rendering/Renderer.cpp
    src/Rendering/Renderer.hpp
    src/Rendering/RenderStateChange.hpp
    src/Rendering/Shader.cpp
    src/Rendering/Shader.hpp
    src/Rendering/TextureObject.cpp
    src/Rendering/TextureObject.hpp
    src/Scene/GameScene.cpp
    src/Scene/GameScene.hpp
    src/Scene/Scene.cpp
    src/Scene/Scene.hpp
    src/Time/Time.cpp
    src/Time/Time.hpp
    src/Utils/IOUtils.hpp
    src/Utils/TypeUtils.hpp
    src/WindowSystem/WindowSystem.cpp
    src/WindowSystem/WindowSystem.hpp
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

    target_include_directories(${TARGET}
        PRIVATE
            ${SDL2_INCLUDE_DIRS}
            ${SDL2_IMAGE_INCLUDE_DIRS}
    )

    target_link_libraries(${TARGET} 
        PRIVATE
            #GL
            #GLEW
            #glfw
            ${SDL2_LIBRARIES}
            ${SDL2_IMAGE_LIBRARIES}
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
            -U _GNU_SOURCE      # How many times do I have to say no extensions? (strerror_r)
        >
        $<$<CXX_COMPILER_ID:MSVC>:
            /WX     # Treat warnings as errors.
            /W4     # Warning level 4.
        >
    )
endforeach(TARGET)
