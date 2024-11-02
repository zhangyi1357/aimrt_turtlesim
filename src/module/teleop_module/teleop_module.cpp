#include "teleop_module/teleop_module.h"

#include <aimrt_module_protobuf_interface/channel/protobuf_channel.h>
#include <ncurses.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <util/log_util.h>

#include "car_proto.pb.h"  // IWYU pragma: keep
#include "channel/channel_handle.h"

namespace aimrt_turtlesim::teleop_module {

bool TeleopModule::Initialize(aimrt::CoreRef core) {
  core_ = core;

  std::string topic_name = "/car/teleop";
  publisher_ = core_.GetChannelHandle().GetPublisher(topic_name);
  AIMRT_CHECK_ERROR_THROW(publisher_, "GetPublisher for topic {} failed", topic_name);

  bool ret = aimrt::channel::RegisterPublishType<aimrt_turtlesim::car_proto::KeyboardEvent>(publisher_);
  AIMRT_CHECK_ERROR_THROW(ret, "RegisterPublishType for KeyboardEvent failed");

  enableRawMode();

  return true;
}

bool TeleopModule::Start() {
  auto pub_executor = core_.GetExecutorManager().GetExecutor("teleop_pub_thread");
  AIMRT_CHECK_ERROR_THROW(pub_executor, "GetExecutor teleop_pub_thread failed");

  pub_executor.Execute([this]() { MainLoop(); });

  return true;
}

void TeleopModule::Shutdown() {
  run_flag_ = false;
  disableRawMode();
}

void TeleopModule::MainLoop() {
  try {
    aimrt::channel::PublisherProxy<aimrt_turtlesim::car_proto::KeyboardEvent> proxy(publisher_);

    while (run_flag_) {
      aimrt_turtlesim::car_proto::KeyboardEvent event;
      ProcessKeyboardEvents(event);
      proxy.Publish(event);
    }
  } catch (const std::exception& e) {
    AIMRT_ERROR("MainLoop error: {}", e.what());
  }
}

void TeleopModule::ProcessKeyboardEvents(aimrt_turtlesim::car_proto::KeyboardEvent& event) {
  fd_set rfds;
  struct timeval tv;

  FD_ZERO(&rfds);
  FD_SET(STDIN_FILENO, &rfds);

  // 设置超时时间为 10 ms
  tv.tv_sec = 0;
  tv.tv_usec = KEYBOARD_TIMEOUT_MS * 1000;

  // 使用select进行非阻塞读取
  int retval = select(STDIN_FILENO + 1, &rfds, nullptr, nullptr, &tv);

  if (retval > 0) {
    char c;
    if (read(STDIN_FILENO, &c, 1) == 1) {
      switch (c) {
        case 'w':
          event.set_up(true);
          break;
        case 's':
          event.set_down(true);
          break;
        case 'a':
          event.set_left(true);
          break;
        case 'd':
          event.set_right(true);
          break;
      }
    }
  }
}

void TeleopModule::enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios_);
  struct termios raw = orig_termios_;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void TeleopModule::disableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios_); }

}  // namespace aimrt_turtlesim::teleop_module
