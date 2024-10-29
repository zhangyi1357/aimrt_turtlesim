set_root_namespace(aimrt_turtlesim)

add_subdirectory(protocol/car_proto)

add_subdirectory(module/car_module)
add_subdirectory(module/teleop_module)
add_subdirectory(module/simulation_module)

add_subdirectory(pkg/pkg_all)

# copy install files
add_custom_target(
  aimrt_turtlesim_build_all ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/install ${CMAKE_BINARY_DIR}
  DEPENDS aimrt::runtime::main
          aimrt_turtlesim::pkg_all)
