# Find clang-tidy
find_program(
  CLANG_TIDY_EXE
  NAMES "clang-tidy"
  DOC "Path to clang-tidy executable"
  )
if(NOT CLANG_TIDY_EXE)
  message(STATUS "clang-tidy not found.")
else()
  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
  set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

# Function to enable clang-tidy for a target
function(enable_clang_tidy target)
  if(CLANG_TIDY_EXE)
    set_target_properties(
      ${target} PROPERTIES
        CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
  endif()
endfunction()