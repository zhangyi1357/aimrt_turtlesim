#include "simulation_module/simulation_module.h"

#include <aimrt_module_protobuf_interface/channel/protobuf_channel.h>
#include <aimrt_module_protobuf_interface/util/protobuf_tools.h>

#include "car_proto.pb.h"  // IWYU pragma: keep

namespace aimrt_turtlesim::simulation_module {

bool SimulationModule::Initialize(aimrt::CoreRef core) {
  core_ = core;

  return true;
}

bool SimulationModule::Start() { return true; }

void SimulationModule::Shutdown() {}

}  // namespace aimrt_turtlesim::simulation_module
