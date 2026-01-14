
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(package Ladyworm)

set(ladyworm_applications ladyworm ${ladyworm_helper_processes})

set(app_install_targets ${ladyworm_applications})

install(TARGETS ladyworm
  EXPORT ladywormTargets
  RUNTIME
    COMPONENT ladyworm_Runtime
    DESTINATION ${CMAKE_INSTALL_BINDIR}
  BUNDLE
    COMPONENT ladyworm_Runtime
    DESTINATION bundle
  LIBRARY
    COMPONENT ladyworm_Runtime
    NAMELINK_COMPONENT ladyworm_Development
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET browser
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILE_SET ladyworm
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS ${ladyworm_helper_processes}
  EXPORT ladywormTargets
  RUNTIME
    COMPONENT ladyworm_Runtime
    DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}
)

include("${LADYBIRD_SOURCE_DIR}/Meta/Lagom/get_linked_lagom_libraries.cmake")
foreach (application IN LISTS ladyworm_applications)
  get_linked_lagom_libraries("${application}" "${application}_lagom_libraries")
  list(APPEND all_required_lagom_libraries "${${application}_lagom_libraries}")
endforeach()
list(REMOVE_DUPLICATES all_required_lagom_libraries)

# Remove ladyworm shlib if it exists
list(REMOVE_ITEM all_required_lagom_libraries ladyworm)

if (APPLE)
    # Fixup the app bundle and copy:
    #   - Libraries from lib/ to Ladyworm.app/Contents/lib
    # Remove the symlink we created at build time for the lib directory first
    install(CODE "
    file(REMOVE \${CMAKE_INSTALL_PREFIX}/bundle/Ladyworm.app/Contents/lib)
    set(lib_dir \${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
    if (IS_ABSOLUTE ${CMAKE_INSTALL_LIBDIR})
      set(lib_dir ${CMAKE_INSTALL_LIBDIR})
    endif()

    set(contents_dir \${CMAKE_INSTALL_PREFIX}/bundle/Ladyworm.app/Contents)
    file(COPY \${lib_dir} DESTINATION \${contents_dir})
  "
            COMPONENT ladyworm_Runtime)
endif()

install(TARGETS ${all_required_lagom_libraries}
  EXPORT ladywormTargets
  COMPONENT ladyworm_Runtime
  LIBRARY
    COMPONENT ladyworm_Runtime
    NAMELINK_COMPONENT ladyworm_Development
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET server
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILE_SET ladyworm
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    ladyworm_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(ladyworm_INSTALL_CMAKEDIR)

install(
    FILES cmake/LadywormInstallConfig.cmake
    DESTINATION "${ladyworm_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT ladyworm_Development
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${ladyworm_INSTALL_CMAKEDIR}"
    COMPONENT ladyworm_Development
)

install(
    EXPORT ladywormTargets
    NAMESPACE ladyworm::
    DESTINATION "${ladyworm_INSTALL_CMAKEDIR}"
    COMPONENT ladyworm_Development
)

if (NOT APPLE)
    # On macOS the resources are handled via the MACOSX_PACKAGE_LOCATION property on each resource file
    install_ladyworm_resources("${CMAKE_INSTALL_DATADIR}/Lagom" ladyworm_Runtime)
endif()

if (ENABLE_INSTALL_FREEDESKTOP_FILES)
    set(FREEDESKTOP_RESOURCE_DIR "${LADYBIRD_SOURCE_DIR}/Meta/CMake/freedesktop")
    string(TIMESTAMP DATE "%Y-%m-%d" UTC)
    execute_process(
        COMMAND git rev-parse --short=10 HEAD
        WORKING_DIRECTORY ${LADYBIRD_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    configure_file("${FREEDESKTOP_RESOURCE_DIR}/org.plurigrid.Ladyworm.metainfo.xml.in" "${CMAKE_CURRENT_BINARY_DIR}/org.plurigrid.Ladyworm.metainfo.xml" @ONLY)
    install(FILES
        "${FREEDESKTOP_RESOURCE_DIR}/org.plurigrid.Ladyworm.svg"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps"
        COMPONENT ladyworm_Runtime
    )
    install(FILES
        "${FREEDESKTOP_RESOURCE_DIR}/org.plurigrid.Ladyworm.desktop"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
        COMPONENT ladyworm_Runtime
    )
    install(FILES
        "${FREEDESKTOP_RESOURCE_DIR}/org.plurigrid.Ladyworm.service"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/dbus-1/services"
        COMPONENT ladyworm_Runtime
    )
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/org.plurigrid.Ladyworm.metainfo.xml"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/metainfo"
        COMPONENT ladyworm_Runtime
    )
endif()
