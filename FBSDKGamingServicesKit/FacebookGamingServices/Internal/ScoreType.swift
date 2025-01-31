/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

/// The types of score a tournament can handle
enum ScoreType: String {
  case custom = "CUSTOM"
  case numeric = "NUMERIC"
  case time = "TIME"
}
