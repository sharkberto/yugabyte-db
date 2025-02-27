// Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//

#pragma once

#include <map>

namespace yb {

template <class Object>
class SharedMemoryObject;

namespace tserver {

class TServerSharedData;
typedef SharedMemoryObject<TServerSharedData> TServerSharedObject;

// This records catalog version information for a given database.
struct CatalogVersionInfo {
  // Latest known version from pg_yb_catalog_version for the database.
  uint64_t current_version;
  uint64_t last_breaking_version;

  // Shared memory array db_catalog_versions_ index of the slot allocated for the database.
  int32_t  shm_index;
};

// Use ordered map to make computing fingerprint of the map easier.
using DbOidToCatalogVersionInfoMap = std::map<uint32_t, CatalogVersionInfo>;

} // namespace tserver
} // namespace yb
