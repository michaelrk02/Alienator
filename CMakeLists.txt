cmake_minimum_required(VERSION 3.0.2)

project("alienator")

add_executable(${PROJECT_NAME}
    "src/alienator.cpp"
    "src/button.cpp"
    "src/effect.cpp"
    "src/human.cpp"
    "src/in_game_scene.cpp"
    "src/main.cpp"
    "src/main_menu_scene.cpp"
    "src/map_chooser_scene.cpp"
    "src/muzzle_flash_effect.cpp"
    "src/projectile.cpp"
    "src/weapon.cpp"
    #"src/particles.cpp"
)

target_link_libraries(${PROJECT_NAME}
    "sfml-system"
    "sfml-window"
    "sfml-graphics"
    "sfml-audio"
)

