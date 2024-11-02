#pragma once

#include <SDL2/SDL.h>
#include <aimrt_module_cpp_interface/executor/timer.h>
#include <aimrt_module_cpp_interface/module_base.h>

#include "car_proto.pb.h"  // IWYU pragma: keep

namespace aimrt_turtlesim::teleop_module {

using KeyboardEvent = aimrt_turtlesim::car_proto::KeyboardEvent;

class TeleopModule : public aimrt::ModuleBase {
 public:
  [[nodiscard]] aimrt::ModuleInfo Info() const override {
    return aimrt::ModuleInfo{.name = "TeleopModule"};
  }

  bool Initialize(aimrt::CoreRef core) override;
  bool Start() override;
  void Shutdown() override;

 private:
  auto GetLogger() { return core_.GetLogger(); }

  void MainLoop();
  void ListenKeyboardEvents(KeyboardEvent& event);

  bool InitSDL();

 private:
  aimrt::CoreRef core_;
  aimrt::channel::PublisherRef publisher_;
  std::shared_ptr<aimrt::executor::TimerBase> timer_;

  KeyboardEvent keyboard_event_;

  bool run_flag_ = true;

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_{nullptr, SDL_DestroyWindow};
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_{nullptr,
                                                                          SDL_DestroyRenderer};
};

}  // namespace aimrt_turtlesim::teleop_module
