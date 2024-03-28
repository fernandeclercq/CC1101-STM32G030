function(get_build_type CONFIG_BUILD_TYPE)

    if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(CONFIG_BUILD_TYPE ${BT_DEBUG} PARENT_SCOPE)

    elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
        set(CONFIG_BUILD_TYPE ${BT_RELEASE} PARENT_SCOPE)

    elseif(${CMAKE_BUILD_TYPE} MATCHES "MinSizeRel")
        set(CONFIG_BUILD_TYPE ${BT_MinSizeRel} PARENT_SCOPE)

    elseif(${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
        set(CONFIG_BUILD_TYPE ${BT_RelWithDebInfo} PARENT_SCOPE)

    endif()
    
endfunction()