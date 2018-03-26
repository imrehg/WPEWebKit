find_library(WIDEVINE_LIBRARY
    NAMES widevine_ce_cdm_shared
    HINTS "/home/charlie/WebPlatformEmbedded/prefix-path/lib"
)
find_path(WIDEVINE_INCLUDE_DIR
    NAMES cdm.h
    HINTS "/home/charlie/WebPlatformEmbedded/prefix-path/include"
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Widevine
    FOUND_VAR WIDEVINE_FOUND
    REQUIRED_VARS WIDEVINE_LIBRARY WIDEVINE_INCLUDE_DIR
)
if (WIDEVINE_FOUND)
    set(WIDEVINE_LIBRARIES ${WIDEVINE_LIBRARY})
    set(WIDEVINE_INCLUDE_DIRS ${WIDEVINE_INCLUDE_DIR})
endif ()

mark_as_advanced(WIDEVINE_LIBRARY WIDEVINE_INCLUDE_DIR)

include(FeatureSummary)
set_package_properties(Widevine PROPERTIES
    DESCRIPTION "A CDM implementation from Google."
    URL "http://thing.com"
)

