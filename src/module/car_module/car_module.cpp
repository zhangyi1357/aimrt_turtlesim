#include "car_module/car_module.h"

#include <aimrt_module_protobuf_interface/channel/protobuf_channel.h>
#include <aimrt_module_protobuf_interface/util/protobuf_tools.h>

#include "car_proto.pb.h"  // IWYU pragma: keep

namespace aimrt_turtlesim::car_module {

bool CarModule::Initialize(aimrt::CoreRef core) {
  core_ = core;

  std::string topic_name = "/car/teleop";
  subscriber_ = core_.GetChannelHandle().GetSubscriber(topic_name);
  AIMRT_CHECK_ERROR_THROW(subscriber_, "Get subscriber for topic '{}' failed.", topic_name);

  bool ret = aimrt::channel::Subscribe<aimrt_turtlesim::car_proto::KeyboardEvent>(
      subscriber_, [this](aimrt::channel::ContextRef ctx_ref,
                          const std::shared_ptr<const aimrt_turtlesim::car_proto::KeyboardEvent> &msg) {
        AIMRT_INFO("KeyboardEvent: {}", msg->DebugString());
      });
  AIMRT_CHECK_ERROR_THROW(ret, "Subscribe for topic '{}' failed.", topic_name);
  return true;
}

bool CarModule::Start() { return true; }

void CarModule::Shutdown() {}

}  // namespace aimrt_turtlesim::car_module
