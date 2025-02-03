set_property(SOURCE data.s APPEND PROPERTY COMPILE_OPTIONS "-I" "${CMAKE_SOURCE_DIR}/data")
idf_component_register(
    SRCS 
    "actor.cpp"
    "animator.cpp"
    "colors.cpp"
    "draft.cpp"
    "engine.cpp"
    "game.cpp"
    "main.cpp"
    "map.cpp"
    "maparch.cpp"
    "tilesdata.cpp"
    "data.s"
    "joystick.cpp"
    INCLUDE_DIRS "."
    INCLUDE_DIRS "./include"
    REQUIRES esp32s3vga esp_adc driver)

