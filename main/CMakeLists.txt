set_property(SOURCE data.s APPEND PROPERTY COMPILE_OPTIONS "-I" "${CMAKE_SOURCE_DIR}/data")
idf_component_register(
    SRCS 
    #"esp32_test.cpp" 
    #"actor.cpp"
    #"animator.cpp"
    #"colors.cpp"
    #"display.cpp"
    #"engine.cpp"
    #"font.cpp"
    #"game.cpp"
    #"level.cpp"
    #"main.cpp"
    #"map.cpp"
    #"maparch.cpp"
    #"tilesdata.cpp"
    #"tileset.cpp"
    #"data.s"
    "example1.cpp"
    INCLUDE_DIRS "."
    INCLUDE_DIRS "./include"
    REQUIRES esp32s3vga)

