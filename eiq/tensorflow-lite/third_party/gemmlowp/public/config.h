// Copyright 2020 NXP
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

// map.h: a minimalist view-existing-buffer-as-a-matrix class,
// which is how gemmlowp interfaces with external matrix data.

#ifndef GEMMLOWP_PUBLIC_CONFIG_H_
#define GEMMLOWP_PUBLIC_CONFIG_H_

#include <cstddef>

namespace gemmlowp {

extern std::size_t min_storage_size;

}  // namespace gemmlowp

#endif  // GEMMLOWP_PUBLIC_CONFIG_H_