if (NOT OPENOCD_PATH)
  if (DEFINED ENV{OPENOCD_PATH})
    set(OPENOCD_PATH $ENV{OPENOCD_PATH})
    message("Using OPENOCD_PATH from environment ('${OPENOCD_PATH}')")
  else ()
    find_program (OPENOCD_PATH
      NAMES openocd
      DOC "path to openocd binary"
    )
  endif ()
endif ()

if (OPENOCD_PATH)
  message(STATUS "openocd: ${OPENOCD_PATH}")
  if (DEFINED ENV{OPENOCD_SEARCH_PATH} AND (NOT OPENOCD_SEARCH_PATH))
    set(OPENOCD_SEARCH_PATH $ENV{OPENOCD_SEARCH_PATH})
    message("Using OPENOCD_SEARCH_PATH from environment ('${OPENOCD_SEARCH_PATH}')")
  endif()
  if (OPENOCD_SEARCH_PATH)
    message(STATUS "openocd search path: ${OPENOCD_SEARCH_PATH}")
    set(OPENOCD_SEARCH_ARG "-s ${OPENOCD_SEARCH_PATH}")
  else()
    set(OPENOCD_SEARCH_ARG "")
  endif ()
endif ()

function(picoprobe_add_flash_target EXECUTABLE_NAME)
  if (NOT OPENOCD_PATH)
    message(WARNING "not generating flash target for ${EXECUTABLE_NAME}: openocd not found or set")
    return()
  endif()

  message(STATUS "generating target flash-${EXECUTABLE_NAME}")
  add_custom_target(flash-${EXECUTABLE_NAME}
    COMMAND ${OPENOCD_PATH} ${OPENOCD_SEARCH_ARG} -f interface/picoprobe.cfg -f target/rp2040.cfg -c \"program ${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}${CMAKE_EXECUTABLE_SUFFIX} verify reset exit\"
    DEPENDS ${EXECUTABLE_NAME}
    COMMENT "Flash ${EXECUTABLE_NAME}${CMAKE_EXECUTABLE_SUFFIX} with openocd"
  )
endfunction()

function(picoprobe_add_reset_target)
  if (NOT OPENOCD_PATH)
    message(WARNING "not generating reset target: openocd not found or set")
    return()
  endif()

  message(STATUS "generating target reset")
  add_custom_target(reset
    COMMAND ${OPENOCD_PATH} ${OPENOCD_SEARCH_ARG} -f interface/picoprobe.cfg -f target/rp2040.cfg -c \"init$<SEMICOLON> reset init$<SEMICOLON> exit\"
    COMMENT "Reset with openocd"
  )
endfunction()
