#include "simulation_module/simulation_module.h"

namespace aimrt_turtlesim::simulation_module {

bool SimulationModule::Initialize(aimrt::CoreRef core) {
  core_ = core;
  return true;
}

bool SimulationModule::Start() { return true; }

void SimulationModule::Shutdown() {}

}  // namespace aimrt_turtlesim::simulation_module
