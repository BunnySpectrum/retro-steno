set(RETRO_STENO_URL_BASE "https://github.com/bunnyspectrum/retro-steno/tree/HEAD")
macro(auto_set_url TARGET)
    file(RELATIVE_PATH URL_REL_PATH "${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_LIST_DIR}")
    pico_set_program_url(${TARGET} "${RETRO_STENO_URL_BASE}/${URL_REL_PATH}")
endmacro()
