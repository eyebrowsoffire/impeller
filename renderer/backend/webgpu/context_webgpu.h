// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "impeller/renderer/context.h"

class ContextWebGPU final : public Context {
 private:
  bool IsValid() const override { return true; }

  std::shared_ptr<Allocator> GetPermanentsAllocator() const override {
    return nullptr;
  }

  std::shared_ptr<Allocator> GetTransientsAllocator() const override {
    return nullptr;
  }

  std::shared_ptr<ShaderLibrary> GetShaderLibrary() const override {
    return nullptr;
  }

  std::shared_ptr<SamplerLibrary> GetSamplerLibrary() const override {
    return nullptr;
  }

  std::shared_ptr<PipelineLibrary> GetPipelineLibrary() const override {
    return nullptr;
  }

  std::shared_ptr<CommandBuffer> CreateRenderCommandBuffer() const override {
    return nullptr;
  }

  std::shared_ptr<CommandBuffer> CreateTransferCommandBuffer() const override {
    return nullptr;
  }
}