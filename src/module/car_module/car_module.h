#pragma once

#include <aimrt_module_cpp_interface/module_base.h>

namespace aimrt_turtlesim::car_module {

class CarModule : public aimrt::ModuleBase {
 public:
  [[nodiscard]] aimrt::ModuleInfo Info() const override { return aimrt::ModuleInfo{.name = "CarModule"}; }

  bool Initialize(aimrt::CoreRef core) override;
  bool Start() override;
  void Shutdown() override;

 private:
  auto GetLogger() { return core_.GetLogger(); }
  void MainLoop();

 private:
  aimrt::CoreRef core_;
  aimrt::channel::SubscriberRef subscriber_;
};

}  // namespace aimrt_turtlesim::car_module
