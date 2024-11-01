#include "teleop_module/teleop_module.h"

#include <aimrt_module_protobuf_interface/channel/protobuf_channel.h>
#include <util/log_util.h>

#include "car_proto.pb.h"  // IWYU pragma: keep
#include "channel/channel_handle.h"

namespace aimrt_turtlesim::teleop_module {

bool TeleopModule::Initialize(aimrt::CoreRef core) {
  core_ = core;

  std::string topic_name = "car/teleop";
  publisher_ = core_.GetChannelHandle().GetPublisher(topic_name);
  AIMRT_CHECK_ERROR_THROW(publisher_, "GetPublisher for topic {} failed", topic_name);

  bool ret = aimrt::channel::RegisterPublishType<aimrt_turtlesim::car_proto::KeyboardEvent>(publisher_);
  AIMRT_CHECK_ERROR_THROW(ret, "RegisterPublishType for KeyboardEvent failed");

  return true;
}

bool TeleopModule::Start() {
  auto pub_executor = core_.GetExecutorManager().GetExecutor("teleop_pub_thread");
  AIMRT_CHECK_ERROR_THROW(pub_executor, "GetExecutor teleop_pub_thread failed");

  pub_executor.Execute([this]() { MainLoop(); });

  return true;
}

void TeleopModule::Shutdown() { run_flag_ = false; }

void TeleopModule::MainLoop() {
  try {
    aimrt::channel::PublisherProxy<aimrt_turtlesim::car_proto::KeyboardEvent> proxy(publisher_);

    while (run_flag_) {
      aimrt_turtlesim::car_proto::KeyboardEvent event;
      event.set_up(true);
      proxy.Publish(event);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  } catch (const std::exception &e) {
    AIMRT_ERROR("MainLoop error: {}", e.what());
  }
}

}  // namespace aimrt_turtlesim::teleop_module
