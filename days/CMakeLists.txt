
file(GLOB _days day*)
foreach(_day ${_days})
    if(IS_DIRECTORY ${_day})
        add_subdirectory(${_day})
    endif()
endforeach()