#include <cstring>

#include "aimrt_pkg_c_interface/pkg_macro.h"
#include "car_module/car_module.h"
#include "simulation_module/simulation_module.h"
#include "teleop_module/teleop_module.h"

static std::tuple<std::string_view, std::function<aimrt::ModuleBase *()>>
    aimrt_module_register_array[]{
        {"TeleopModule",
         []() -> aimrt::ModuleBase * {
           return new aimrt_turtlesim::teleop_module::TeleopModule();
         }},
        {"SimulationModule",
         []() -> aimrt::ModuleBase * {
           return new aimrt_turtlesim::simulation_module::SimulationModule();
         }},
        {"CarModule",
         []() -> aimrt::ModuleBase * {
           return new aimrt_turtlesim::car_module::CarModule();
         }},
    };

AIMRT_PKG_MAIN(aimrt_module_register_array)
