#include "car_module/car_module.h"

#include <aimrt_module_protobuf_interface/channel/protobuf_channel.h>
#include <util/log_util.h>

#include "car_proto.pb.h"  // IWYU pragma: keep
#include "channel/channel_handle.h"

namespace aimrt_turtlesim::car_module {

bool CarModule::Initialize(aimrt::CoreRef core) {
  core_ = core;
  return true;
}

bool CarModule::Start() { return true; }

void CarModule::Shutdown() {}

}  // namespace aimrt_turtlesim::car_module
