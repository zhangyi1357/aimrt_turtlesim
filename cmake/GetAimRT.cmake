include(FetchContent)

FetchContent_Declare(
  aimrt
  GIT_REPOSITORY https://github.com/AimRT/aimrt.git
  GIT_TAG main)

FetchContent_MakeAvailable(aimrt)