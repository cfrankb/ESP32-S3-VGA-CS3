cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS
                       "src/VGA.cpp"
                       "src/Mode.cpp"
                       "src/FONT_9x16.cpp"
                       "src/FONT_8x8.cpp"
                       "src/FONT_6x8.cpp"
                       INCLUDE_DIRS "src"
                       PRIV_REQUIRES driver soc)

project(esp32s3vga)
