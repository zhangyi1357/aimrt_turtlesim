set_root_namespace(aimrt_turtlesim)

add_subdirectory(protocol/car_proto)

add_subdirectory(module/car_module)
add_subdirectory(module/teleop_module)
add_subdirectory(module/simulation_module)

add_subdirectory(pkg/pkg_all)
