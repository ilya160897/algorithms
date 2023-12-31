add_custom_target(test-all)

function(add_algorithm_executable CATEGORY TARGET)
  set(
    SOURCES
    ${TARGET}.h
    test.cpp
  )

  add_executable(${TARGET} ${SOURCES})
  set_target_properties(${TARGET} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CATEGORY}")


  target_link_libraries(${TARGET}
    contrib_catch_main
  )

  add_custom_target(
    run_${TARGET}
    WORKING_DIRECTORY ${PROJECT_ROOT_DIR}
    DEPENDS ${TARGET}
    COMMAND ${PROJECT_BINARY_DIR}/${CATEGORY}/${TARGET})

  add_dependencies(test-all run_${TARGET})
endfunction()
