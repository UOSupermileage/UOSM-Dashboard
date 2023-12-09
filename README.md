# UOSM-Dashboard

[View Documentation](https://uosupermileage.github.io/UOSM-Dashboard/))

## Getting Started

Requirements:
1. CLion (Education access if free for students, you can validate your student status using your GitHub student pack)
2. OpenOCD (Mac/Linux can install using their package manager, windows users should install the [precompiled binary](https://github.com/xpack-dev-tools/openocd-xpack/releases))
3. arm-none-eabi compiler (See instructions below)
4. ST-Link Driver (Required for windows to be able to flash the STM32)
5. CubeMX (Used to generate and edit project settings)

The team uses CLion for development. CLion is free for students. You will also need to install the compiler.

```bash
# MacOS
brew install --cask gcc-arm-embedded

# Ubuntu
# See https://lindevs.com/install-arm-gnu-toolchain-on-ubuntu

# Windows
# Install the latest compiler from https://developer.arm.com/downloads/-/gnu-rm

# Make sure the compiler is in your path
arm-none-eabi
```

```bash
# Once you've made your changes
git add . &&  commit -m "My changes"

git push origin main

# If you've modified UOSM-Core (Make sure you do this AFTER commiting your changes)
git subtree push --prefix UOSM-Core git@github.com:UOSupermileage/UOSM-Core.git main
```
