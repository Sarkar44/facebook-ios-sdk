/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

import FBSDKCoreKit
import TestTools
import XCTest

// swiftlint:disable force_unwrapping
class WebViewAppLinkResolverTests: XCTestCase {

  var result: [String: Any]?
  var error: Error?
  let data = "foo".data(using: .utf8)!
  let provider = TestSessionProvider()
  lazy var resolver = WebViewAppLinkResolver(sessionProvider: provider)

  // MARK: - Dependencies

  func testCreatingWithDefaults() {
    XCTAssertEqual(
      ObjectIdentifier(WebViewAppLinkResolver.shared.sessionProvider),
      ObjectIdentifier(URLSession.shared),
      "Should use the shared system session by default"
    )
  }

  func testCreatingWithSession() {
    XCTAssertEqual(
      ObjectIdentifier(resolver.sessionProvider),
      ObjectIdentifier(provider),
      "Should be able to create with a session provider"
    )
  }

  // MARK: - Redirecting

  func testFollowRedirectsURL() {
    let task = TestSessionDataTask()
    provider.stubbedDataTask = task
    resolver.followRedirects(SampleURLs.valid) { _, _ in }

    XCTAssertEqual(
      provider.capturedRequest?.url,
      SampleURLs.valid,
      "Should create a url request with the provided url"
    )
    XCTAssertEqual(
      provider.capturedRequest?.allHTTPHeaderFields?.contains { key, value in
        key == "Prefer-Html-Meta-Tags" && value == "al"
      },
      true,
      "Should include a header for which html meta tags to prefer"
    )
    XCTAssertEqual(
      task.resumeCallCount,
      1,
      "Should start the data task to follow redirects"
    )
  }

  func testFollowRedirectsWithErrorOnly() {
    resolver.followRedirects(SampleURLs.valid) { potentialResult, potentialError in
      self.result = potentialResult
      self.error = potentialError
    }

    provider.capturedCompletion?(nil, nil, SampleError())

    XCTAssertNil(
      result,
      "Should not call the redirect completion with a result if there is also an error"
    )
    XCTAssertTrue(
      error is SampleError,
      "Should call the completion with the error from the redirect"
    )
  }

  func testFollowRedirectWithHTTPResponseOnly() {
    resolver.followRedirects(SampleURLs.valid) { potentialResult, potentialError in
      self.result = potentialResult
      self.error = potentialError
    }

    provider.capturedCompletion?(
      nil,
      SampleHTTPURLResponses.validStatusCode,
      nil
    )

    XCTAssertNil(
      result,
      "Should not have a result if there is no response data"
    )
    XCTAssertEqual(
      error as NSError?,
      SDKError.unknownError(
        withMessage: "Invalid network response - missing data"
      ) as NSError,
      "Should call the completion with an error indicating the missing data"
    )
  }

  func testFollowRedirectsWithValidHTTPResponse() {
    resolver.followRedirects(SampleURLs.valid) { potentialResult, potentialError in
      self.result = potentialResult
      self.error = potentialError
    }

    provider.capturedCompletion?(
      data,
      SampleHTTPURLResponses.validStatusCode,
      nil
    )

    validateResult(
      result: result,
      data: data,
      response: SampleHTTPURLResponses.validStatusCode!,
      error: error
    )
  }

  func testFollowRedirectsWithRedirectingHTTPResponseMissingLocationURL() {
    // Just testing the upper and lower bounds
    [300, 399].forEach { code in
      provider.dataTaskCallCount = 0
      resolver.followRedirects(SampleURLs.valid) { potentialResult, potentialError in
        self.result = potentialResult
        self.error = potentialError
      }

      provider.capturedCompletion?(
        data,
        SampleHTTPURLResponses.valid(statusCode: code),
        nil
      )

      XCTAssertEqual(
        provider.dataTaskCallCount,
        2,
        "Should create a second data task for the url redirect"
      )
    }
  }

  func testFollowRedirectsWithRedirectingHTTPResponseIncludingLocationURL() {
    let redirectURL = SampleURLs.valid(path: "redirected")
    resolver.followRedirects(SampleURLs.valid) { potentialResult, potentialError in
      self.result = potentialResult
      self.error = potentialError
    }

    provider.capturedCompletion?(
      data,
      SampleHTTPURLResponses.valid(
        statusCode: 300,
        headerFields: ["Location": redirectURL.absoluteString]
      ),
      nil
    )

    XCTAssertEqual(
      provider.dataTaskCallCount,
      2,
      "Should create a second data task for the url redirect"
    )
    XCTAssertEqual(
      provider.capturedRequest?.url,
      redirectURL,
      "The second request should be to the redirect url"
    )
  }

  // MARK: - Building Applink from AppLinkData

  func testBuildingLinkFromEmptyData() {
    let link = resolver.appLink(
      fromALData: [:],
      destination: SampleURLs.valid
    )
    XCTAssertEqual(
      link.sourceURL,
      SampleURLs.valid,
      "Should use the destination as the source url for the app link"
    )
    XCTAssertEqual(
      link.webURL,
      SampleURLs.valid,
      "The web url should default to the destination"
    )
    XCTAssertTrue(link.targets.isEmpty, "Should not have any targets by default")
  }

  func testBuildingLinkWithInvalidAppLinkData() {
    let link = resolver.appLink(
      fromALData: SampleAppLinkResolverData.invalid,
      destination: SampleURLs.valid
    )
    XCTAssertEqual(
      link.sourceURL,
      SampleURLs.valid,
      "Should use the destination as the source url for the app link"
    )
    XCTAssertEqual(
      link.webURL,
      SampleURLs.valid,
      "The web url should default to the destination"
    )
    XCTAssertEqual(
      link.targets.count,
      2,
      "Should create a target for each platform link"
    )
    guard let target = link.targets.first else {
      return XCTFail("Should create targets")
    }
    XCTAssertNil(
      target.url,
      "Should create a target even if the url is invalid"
    )
    XCTAssertTrue(
      target.appName.isEmpty,
      "Should be able to create a target without an app name"
    )
    XCTAssertNil(
      target.appStoreId,
      "Should create a target even if the app store ID is invalid"
    )
  }

  func testBuildingLinkWithShouldNotFallbackToWebURL() {
    ["no", "false", "0"].forEach { fallbackValue in
      let link = resolver.appLink(
        fromALData: SampleAppLinkResolverData.withShouldFallback(fallbackValue),
        destination: SampleURLs.valid
      )
      XCTAssertEqual(
        link.sourceURL,
        SampleURLs.valid,
        "Should use the destination as the source url for the app link"
      )
      XCTAssertNil(
        link.webURL,
        "The web url should be nil when the fallback is falsy"
      )
      XCTAssertTrue(
        link.targets.isEmpty,
        "Should not create targets for either platform"
      )
    }
  }

  func testBuildingLinkWithShouldFallbackToWebURL() {
    ["yes", "true", "1"].forEach { fallbackValue in
      let link = resolver.appLink(
        fromALData: SampleAppLinkResolverData.withShouldFallback(fallbackValue),
        destination: SampleURLs.valid
      )
      XCTAssertEqual(
        link.sourceURL,
        SampleURLs.valid,
        "Should use the destination as the source url for the app link"
      )
      XCTAssertEqual(
        link.webURL?.absoluteString,
        SampleAppLinkResolverData.urlString,
        "The web url should be used when the fallback is truthy"
      )
      XCTAssertTrue(
        link.targets.isEmpty,
        "Should not create targets for either platform"
      )
    }
  }

  // MARK: - Helpers

  func validateResult(
    result: [String: Any]?,
    data: Data,
    response: HTTPURLResponse,
    error: Error?,
    file: StaticString = #file,
    line: UInt = #line
  ) {
    XCTAssertEqual(
      result?["response"] as? HTTPURLResponse,
      response,
      "Should include the http response in the result",
      file: file,
      line: line
    )
    XCTAssertEqual(
      result?["data"] as? Data,
      data,
      "Should include the data in the result",
      file: file,
      line: line
    )
    XCTAssertNil(
      error,
      "Should not call the completion with an error and a result",
      file: file,
      line: line
    )
  }
}
