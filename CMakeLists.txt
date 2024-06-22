cmake_minimum_required(VERSION 3.16)
project(Aircraft)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)

add_executable(Aircraft Aircraft/Aircraft.cpp
Aircraft/Aircraft.h
Aircraft/Animation.cpp
Aircraft/Animation.h
Aircraft/Application.cpp
Aircraft/Application.h
Aircraft/BloomEffect.cpp
Aircraft/BloomEffect.h
Aircraft/Button.cpp
Aircraft/Button.h
Aircraft/Category.h
Aircraft/Command.cpp
Aircraft/Command.h
Aircraft/CommandQueue.cpp
Aircraft/CommandQueue.h
Aircraft/Component.cpp
Aircraft/Component.h
Aircraft/Container.cpp
Aircraft/Container.h
Aircraft/DataTables.cpp
Aircraft/DataTables.h
Aircraft/EmitterNode.cpp
Aircraft/EmitterNode.h
Aircraft/Entity.cpp
Aircraft/Entity.h
Aircraft/GameOverState.cpp
Aircraft/GameOverState.h
Aircraft/GameServer.h
Aircraft/GameServer.cpp
Aircraft/GameState.cpp
Aircraft/GameState.h
Aircraft/KeyBinding.cpp
Aircraft/KeyBinding.h
Aircraft/Label.cpp
Aircraft/Label.h
Aircraft/Main.cpp
Aircraft/MenuState.cpp
Aircraft/MenuState.h
Aircraft/MultiplayerGameState.cpp
Aircraft/MultiplayerGameState.h
Aircraft/MusicPlayer.cpp
Aircraft/MusicPlayer.h
Aircraft/NetworkNode.cpp
Aircraft/NetworkNode.h
Aircraft/NetworkProtocol.h
Aircraft/Particle.h
Aircraft/ParticleNode.cpp
Aircraft/ParticleNode.h
Aircraft/PauseState.cpp
Aircraft/PauseState.h
Aircraft/Pickup.cpp
Aircraft/Pickup.h
Aircraft/Player.cpp
Aircraft/Player.h
Aircraft/PostEffect.cpp
Aircraft/PostEffect.h
Aircraft/Projectile.cpp
Aircraft/Projectile.h
Aircraft/ResourceHolder.h
Aircraft/ResourceHolder.inl
Aircraft/ResourceIdentifiers.h
Aircraft/SceneNode.cpp
Aircraft/SceneNode.h
Aircraft/SettingsState.cpp
Aircraft/SettingsState.h
Aircraft/SoundNode.cpp
Aircraft/SoundNode.h
Aircraft/SoundPlayer.cpp
Aircraft/SoundPlayer.h
Aircraft/SpriteNode.h
Aircraft/SpriteNode.cpp
Aircraft/State.cpp
Aircraft/State.h
Aircraft/StateIdentifiers.h
Aircraft/StateStack.cpp
Aircraft/StateStack.h
Aircraft/TextNode.cpp
Aircraft/TextNode.h
Aircraft/TitleState.cpp
Aircraft/TitleState.h
Aircraft/Utility.cpp
Aircraft/Utility.h
Aircraft/Utility.inl
Aircraft/World.cpp
Aircraft/World.h
Aircraft/JoystickWindows.h
Aircraft/JoystickWindows.cpp
Aircraft/InputField.cpp
Aircraft/InputField.h
Aircraft/EnterIPState.cpp
Aircraft/EnterIPState.h
Aircraft/IpAddress.h
Aircraft/IpAddress.cpp
Aircraft/BinaryDataHandler.h
Aircraft/BinaryDataHandler.cpp
)

#                               
FetchContent_MakeAvailable(SFML)

    target_link_libraries(Aircraft PRIVATE sfml-graphics sfml-audio sfml-network sfml-system sfml-window )
    target_compile_features(Aircraft PRIVATE cxx_std_17)


add_custom_target(data-target ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/*")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Resource $<TARGET_FILE_DIR:Aircraft>/)
if(WIN32)
    add_custom_command(
        TARGET Aircraft
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Aircraft>
        VERBATIM)
endif()

if(MSVC)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()


install(TARGETS Aircraft)
