#!/bin/bash
export VULKAN_SDK=$HOME/VulkanSDK/1.3.261.1/macOS
export PATH=$VULKAN_SDK/bin:$PATH
export DYLD_LIBRARY_PATH=$VULKAN_SDK/lib:$DYLD_LIBRARY_PATH
export VK_ICD_FILENAMES=$VULKAN_SDK/etc/vulkan/icd.d/MoltenVK_icd.json
export VK_LAYER_PATH=$VULKAN_SDK/etc/vulkan/explicit_layer.d
clang++ -std=c++11 -o ./testmain ./main.cpp ~/VulkanSDK/1.3.261.1/macOS/lib/libvulkan.dylib -I ~/VulkanSDK/1.3.261.1/macOS/include