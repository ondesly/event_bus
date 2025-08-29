// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "event_bus",
    products: [
        .library(name: "event_bus", targets: ["c_event_bus"]),
    ],
    targets: [
        .target(
            name: "c_event_bus",
            path: "src",
            sources: [
                "event_bus/bus.cpp"
            ],
            publicHeadersPath: "event_bus",
            cSettings: [
                .headerSearchPath("src"),
            ]
        )
    ],
    cxxLanguageStandard: .cxx17
)
