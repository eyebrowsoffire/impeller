// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <functional>
#include <memory>

#include "flutter/fml/macros.h"

namespace impeller {

class Context;
class RenderPass;
class RenderTarget;

//------------------------------------------------------------------------------
/// @brief      A collection of encoded commands to be submitted to the GPU for
///             execution. A command buffer is obtained from a graphics
///             `Context`.
///
///             To submit commands to the GPU, acquire a `RenderPass` from the
///             command buffer and record `Command`s into that pass. A
///             `RenderPass` describes the configuration of the various
///             attachments when the command is submitted.
///
///             A command buffer is only meant to be used on a single thread. If
///             a frame workload needs to be encoded from multiple threads,
///             setup and record into multiple command buffers. The order of
///             submission of commands encoded in multiple command buffers can
///             be controlled via either the order in which the command buffers
///             were created, or, using the `ReserveSpotInQueue` command which
///             allows for encoding commands for submission in an order that is
///             different from the encoding order.
///
class CommandBuffer {
 public:
  enum class Status {
    kPending,
    kError,
    kCompleted,
  };

  using CompletionCallback = std::function<void(Status)>;

  virtual ~CommandBuffer();

  virtual bool IsValid() const = 0;

  virtual void SetLabel(const std::string& label) const = 0;

  //----------------------------------------------------------------------------
  /// @brief      Schedule the command encoded by render passes within this
  ///             command buffer on the GPU.
  ///
  ///             A command buffer may only be committed once.
  ///
  /// @param[in]  callback  The completion callback.
  ///
  [[nodiscard]] virtual bool SubmitCommands(CompletionCallback callback) = 0;

  [[nodiscard]] bool SubmitCommands();

  virtual void ReserveSpotInQueue() = 0;

  //----------------------------------------------------------------------------
  /// @brief      Create a render pass to record render commands into.
  ///
  /// @param[in]  desc  The description of the render target this pass will
  ///                   target.
  ///
  /// @return     A valid render pass or null.
  ///
  virtual std::shared_ptr<RenderPass> CreateRenderPass(
      RenderTarget render_target) const = 0;

 protected:
  CommandBuffer();

 private:
  FML_DISALLOW_COPY_AND_ASSIGN(CommandBuffer);
};

}  // namespace impeller
