add_custom_target(test-all)

message(STATUS "&&&&&&  &&&&&&&&&")
function(add_algorithm_executable CATEGORY TARGET)
  add_executable(${TARGET} ${ARGN})
  set_target_properties(${TARGET} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CATEGORY}")


  target_link_libraries(${TARGET}
    contrib_catch_main
  )
  
  message(STATUS "&&&&&& Project root dir: ${PROJECT_ROOT_DIR} &&&&&&&&&")
  message(STATUS "&&&&&& Project binary dir: ${PROJECT_BINARY_DIR} &&&&&&&")

  add_custom_target(
    run_${TARGET}
    WORKING_DIRECTORY ${PROJECT_ROOT_DIR}
    DEPENDS ${TARGET}
    COMMAND ${PROJECT_BINARY_DIR}/${CATEGORY}/${TARGET})

  add_dependencies(test-all run_${TARGET})
endfunction()
