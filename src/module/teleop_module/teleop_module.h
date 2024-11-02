#pragma once

#include <aimrt_module_cpp_interface/module_base.h>
#include <termios.h>

#include <array>
#include <cstdint>
#include <future>

#include "car_proto.pb.h"  // IWYU pragma: keep

namespace aimrt_turtlesim::teleop_module {

class TeleopModule : public aimrt::ModuleBase {
 public:
  [[nodiscard]] aimrt::ModuleInfo Info() const override { return aimrt::ModuleInfo{.name = "TeleopModule"}; }

  bool Initialize(aimrt::CoreRef core) override;
  bool Start() override;
  void Shutdown() override;

 private:
  auto GetLogger() { return core_.GetLogger(); }
  void MainLoop();
  void ProcessKeyboardEvents(aimrt_turtlesim::car_proto::KeyboardEvent& event);
  void enableRawMode();
  void disableRawMode();
  bool isKeyPressed(char key);

 private:
  aimrt::CoreRef core_;
  aimrt::channel::PublisherRef publisher_;

  bool run_flag_ = true;
  std::promise<void> shutdown_promise_;

  std::array<bool, 128> key_states_{false};

  struct termios orig_termios_;
  int keyboard_fd_;

  static constexpr int64_t KEYBOARD_TIMEOUT_MS = 100;
};

}  // namespace aimrt_turtlesim::teleop_module
