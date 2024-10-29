#pragma once

#include <aimrt_module_cpp_interface/module_base.h>

#include <future>

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

 private:
  aimrt::CoreRef core_;
  aimrt::channel::PublisherRef publisher_;

  bool run_flag_ = true;
  std::promise<void> shutdown_promise_;
};

}  // namespace aimrt_turtlesim::teleop_module
