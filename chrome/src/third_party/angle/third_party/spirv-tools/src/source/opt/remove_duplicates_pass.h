// Copyright (c) 2017 Pierre Moreau
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef LIBSPIRV_OPT_REMOVE_DUPLICATES_PASS_H_
#define LIBSPIRV_OPT_REMOVE_DUPLICATES_PASS_H_

#include <unordered_map>

#include "decoration_manager.h"
#include "def_use_manager.h"
#include "ir_context.h"
#include "module.h"
#include "pass.h"

namespace spvtools {
namespace opt {

using IdDecorationsList =
    std::unordered_map<uint32_t, std::vector<opt::Instruction*>>;

// See optimizer.hpp for documentation.
class RemoveDuplicatesPass : public Pass {
 public:
  const char* name() const override { return "remove-duplicates"; }
  Status Process(opt::IRContext*) override;
  // TODO(pierremoreau): Move this function somewhere else (e.g. pass.h or
  // within the type manager)
  // Returns whether two types are equal, and have the same decorations.
  static bool AreTypesEqual(const opt::Instruction& inst1,
                            const opt::Instruction& inst2,
                            opt::IRContext* context);

 private:
  // Remove duplicate capabilities from the module attached to |ir_context|.
  //
  // Returns true if the module was modified, false otherwise.
  bool RemoveDuplicateCapabilities(opt::IRContext* ir_context) const;
  // Remove duplicate extended instruction imports from the module attached to
  // |ir_context|.
  //
  // Returns true if the module was modified, false otherwise.
  bool RemoveDuplicatesExtInstImports(opt::IRContext* ir_context) const;
  // Remove duplicate types from the module attached to |ir_context|.
  //
  // Returns true if the module was modified, false otherwise.
  bool RemoveDuplicateTypes(opt::IRContext* ir_context) const;
  // Remove duplicate decorations from the module attached to |ir_context|.
  //
  // Returns true if the module was modified, false otherwise.
  bool RemoveDuplicateDecorations(opt::IRContext* ir_context) const;
};

}  // namespace opt
}  // namespace spvtools

#endif  // LIBSPIRV_OPT_REMOVE_DUPLICATES_PASS_H_
