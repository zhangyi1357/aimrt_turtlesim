include(FetchContent)

FetchContent_Declare(
  aimrt
  GIT_REPOSITORY https://github.com/AimRT/aimrt.git
  GIT_TAG main)

set(AIMRT_BUILD_NET_PLUGIN ON)

FetchContent_MakeAvailable(aimrt)