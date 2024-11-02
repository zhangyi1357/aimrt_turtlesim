#include "teleop_module/teleop_module.h"

#include <SDL2/SDL.h>
#include <aimrt_module_cpp_interface/channel/channel_handle.h>
#include <aimrt_module_protobuf_interface/channel/protobuf_channel.h>
#include <util/log_util.h>

#include "car_proto.pb.h"  // IWYU pragma: keep

namespace aimrt_turtlesim::teleop_module {

bool TeleopModule::Initialize(aimrt::CoreRef core) {
  core_ = core;

  std::string topic_name = "/car/teleop";
  publisher_ = core_.GetChannelHandle().GetPublisher(topic_name);
  AIMRT_CHECK_ERROR_THROW(publisher_, "GetPublisher for topic {} failed", topic_name);

  bool ret = aimrt::channel::RegisterPublishType<KeyboardEvent>(publisher_);
  AIMRT_CHECK_ERROR_THROW(ret, "RegisterPublishType for KeyboardEvent failed");

  return InitSDL();
}

bool TeleopModule::Start() {
  auto publish_executor = core_.GetExecutorManager().GetExecutor("teleop_publish_thread");
  AIMRT_CHECK_ERROR_THROW(publish_executor, "GetExecutor teleop_publish_thread failed");

  timer_ = aimrt::executor::CreateTimer(publish_executor, std::chrono::milliseconds(100), [this]() {
    aimrt::channel::PublisherProxy<KeyboardEvent> proxy(publisher_);
    proxy.Publish(keyboard_event_);
    keyboard_event_.Clear();
  });

  auto keyboard_executor = core_.GetExecutorManager().GetExecutor("teleop_keyboard_thread");
  AIMRT_CHECK_ERROR_THROW(keyboard_executor, "GetExecutor teleop_keyboard_thread failed");

  keyboard_executor.Execute([this]() { MainLoop(); });

  return true;
}

void TeleopModule::Shutdown() {
  run_flag_ = false;

  if (timer_) {
    timer_->Cancel();
    timer_->SyncWait();
  }
}

void TeleopModule::MainLoop() {
  try {
    while (run_flag_) {
      ListenKeyboardEvents(keyboard_event_);
      SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
      SDL_RenderClear(renderer_.get());
      SDL_RenderPresent(renderer_.get());
    }
  } catch (const std::exception& e) {
    AIMRT_ERROR("MainLoop error: {}", e.what());
  }
}

void TeleopModule::ListenKeyboardEvents(KeyboardEvent& event) {
  SDL_Event sdl_event;
  while (SDL_PollEvent(&sdl_event)) {
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);
    if (keyState[SDL_SCANCODE_UP]) {
      event.set_up(true);
    }
    if (keyState[SDL_SCANCODE_DOWN]) {
      event.set_down(true);
    }
    if (keyState[SDL_SCANCODE_LEFT]) {
      event.set_left(true);
    }
    if (keyState[SDL_SCANCODE_RIGHT]) {
      event.set_right(true);
    }
  }
}

bool TeleopModule::InitSDL() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    AIMRT_ERROR("SDL init failed: {}", SDL_GetError());
    return false;
  }

  window_.reset(SDL_CreateWindow("Teleop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                 SDL_WINDOW_SHOWN));
  if (!window_) {
    AIMRT_ERROR("SDL window create failed: {}", SDL_GetError());
    return false;
  }

  renderer_.reset(
      SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
  if (!renderer_) {
    AIMRT_ERROR("SDL renderer create failed: {}", SDL_GetError());
    return false;
  }

  return true;
}

}  // namespace aimrt_turtlesim::teleop_module
