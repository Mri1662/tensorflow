/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "mlir/Pass/Pass.h"  // from @llvm-project
#include "mlir/Pass/PassManager.h"  // from @llvm-project
#include "mlir/Transforms/Passes.h"  // from @llvm-project
#include "tensorflow/compiler/mlir/tensorflow/transforms/bridge.h"
#include "tensorflow/compiler/mlir/tensorflow/transforms/passes.h"
#include "tensorflow/compiler/mlir/tensorflow/utils/error_util.h"

namespace mlir {
namespace TFTPU {
extern void AddGraphExportLoweringPasses(OpPassManager &pm);
}  // namespace TFTPU
}  // namespace mlir

namespace {

// Registers a pipeline builder function for TF TPU bridge.
mlir::PassPipelineRegistration<> tpu_pipeline(
    "tf-tpu-bridge",
    "Run all the passes involved in transforming the graph before execution so "
    "that it is suitable for targeting TPUs.",
    [](mlir::OpPassManager& pm) {
      return mlir::TFTPU::CreateTPUBridgePipeline(pm);
    });

// Registers a pipeline builder function for TF Graph export.
mlir::PassPipelineRegistration<> tpu_export(
    "tf-graph-export",
    "Run passes to prepare for exporting module back to TF Graph.",
    mlir::TF::AddGraphExportLoweringPasses);

}  // anonymous namespace
