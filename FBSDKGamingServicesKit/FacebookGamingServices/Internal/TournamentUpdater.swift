/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

import FBSDKCoreKit

enum TournamentUpdaterError: Error {
  case server(Error)
  case invalidScoreType
  case decoding
}

/**
  A graph request wrapper to update a tournament
 */
class TournamentUpdater {

  enum GraphRequest {
    static let scoreParameterKey = "score"

    static func path(identifier: String) -> String {
      "\(identifier)/update_score"
    }
  }

  let graphRequestFactory: GraphRequestFactoryProtocol

  /**
   Creates the TournamentUpdater
   */
  convenience init() {
    self.init(graphRequestFactory: GraphRequestFactory())
  }

  init(graphRequestFactory: GraphRequestFactoryProtocol) {
    self.graphRequestFactory = graphRequestFactory
  }

  /**
      Updates the given tournament with the given score

   - Parameter tournament: The tournament you want to update
   - Parameter score: The new score to update within the tournament
   - Parameter completionHandler: The caller's completion handler to invoke once the graph request is complete
   */

  func update<T: Score>(
    tournament: Tournament,
    score: T,
    completionHandler: @escaping (Result<Tournament, TournamentUpdaterError>) -> Void
  ) {
    var tournamentToUpdate = tournament
    do {
      try tournamentToUpdate.update(score: score)
    } catch {
      completionHandler(.failure(TournamentUpdaterError.invalidScoreType))
    }

    let parameters = [GraphRequest.scoreParameterKey: tournamentToUpdate.score]
    let request = graphRequestFactory.createGraphRequest(
      withGraphPath: GraphRequest.path(identifier: tournamentToUpdate.identifier),
      parameters: parameters as [String: Any],
      httpMethod: .post
    )

    request.start { _, result, error in
      if let error = error {
        completionHandler(.failure(.server(error)))
        return
      }
      guard
        let result = result as? [String: Bool],
        let data = try? JSONSerialization.data(withJSONObject: result, options: []),
        let serverResults = try? JSONDecoder().decode(ServerResult.self, from: data),
        serverResults.success
      else {
        completionHandler(.failure(.decoding))
        return
      }
      completionHandler(.success(tournamentToUpdate))
    }
  }
}
