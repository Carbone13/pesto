pesto_compile_shaders_to_headers(
        ROOT ${CMAKE_CURRENT_SOURCE_DIR}
        VERTEX res/shaders/sprite/vs_sprite.sc
        FRAGMENT res/shaders/sprite/fs_sprite.sc
        VARYING_DEF res/shaders/sprite/varying.def.sc
        HEADER sprite_sc.h
        OUTPUT_DIR res/_generated/shaders/sprite
)

pesto_compile_texture(
        ROOT ${CMAKE_CURRENT_SOURCE_DIR}
        TEXTURE res/sprites/frog.png
        ARRAY_NAME frog_png
        OUTPUT_FILE res/_generated/sprites/frog.png.h
)

add_executable(test-sprites
        # Source
        src/main.cpp

        # Shaders
        res/shaders/sprite/fs_sprite.sc
        res/shaders/sprite/vs_sprite.sc
        # Sprites
        res/sprites/frog.png
        )

include_directories(res/_generated)
target_link_libraries(test-sprites pesto)