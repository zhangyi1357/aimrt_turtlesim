include(FetchContent)

FetchContent_Declare(
  aimrt
  GIT_REPOSITORY https://github.com/zhangyi1357/AimRT.git
  GIT_TAG aimrt-timer)

set(AIMRT_BUILD_NET_PLUGIN ON)
set(AIMRT_INSTALL OFF)

FetchContent_MakeAvailable(aimrt)