.global tiles_mcz
.global annie_mcz
.global animz_mcz
.global bitfont_bin
.global levels_mapz
.type tiles_mcz STT_COMMON
.type annie_mcz STT_COMMON
.type animz_mcz STT_COMMON
.type bitfont_bin STT_COMMON
.type levels_mapz STT_COMMON

.section .rodata
#.section .flash.text
#.section .text
.balign 4
    tiles_mcz: .incbin "../data/tiles.mcz",12
    annie_mcz: .incbin "../data/annie.mcz",12
    animz_mcz: .incbin "../data/animz.mcz",12
    bitfont_bin: .incbin "../data/bitfont.bin"
    levels_mapz: .incbin "../data/levels.mapz"
