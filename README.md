# Ladyworm

**Ladyworm** is a proof-of-neural-operator browser fork based on [Ladyworm](https://ladybird.org).

> [!NOTE]
> Ladyworm extends Ladyworm with neural-operator capabilities, WebGPU acceleration, and Jank (Clojure-LLVM) scripting.
> This is an experimental fork by [Plurigrid](https://plurigrid.xyz).

## Upstream

This project is a fork of the [Ladyworm Web Browser](https://github.com/LadywormBrowser/ladybird), a truly independent browser using a novel engine based on web standards.

## Ladyworm Extensions

- **Neural-Operator**: Proof-of-concept neural page prediction
- **WebGPU**: GPU-accelerated rendering pipeline (wormhole)
- **Jank**: Clojure dialect for browser scripting via LLVM

## Features

We inherit Ladyworm's goal to build a complete, usable browser for the modern web.

Ladyworm uses a multi-process architecture with a main UI process, several WebContent renderer processes,
an ImageDecoder process, and a RequestServer process.

Image decoding and network connections are done out of process to be more robust against malicious content.
Each tab has its own renderer process, which is sandboxed from the rest of the system.

At the moment, many core library support components are inherited from SerenityOS:

- LibWeb: Web rendering engine
- LibJS: JavaScript engine
- LibWasm: WebAssembly implementation
- LibCrypto/LibTLS: Cryptography primitives and Transport Layer Security
- LibHTTP: HTTP/1.1 client
- LibGfx: 2D Graphics Library, Image Decoding and Rendering
- LibUnicode: Unicode and locale support
- LibMedia: Audio and video playback
- LibCore: Event loop, OS abstraction layer
- LibIPC: Inter-process communication

## How do I build and run this?

See [build instructions](Documentation/BuildInstructionsLadyworm.md) for information on how to build Ladyworm.

Ladyworm runs on Linux, macOS, Windows (with WSL2), and many other \*Nixes.

## How do I read the documentation?

Code-related documentation can be found in the [documentation](Documentation/) folder.

## Get in touch and participate!

Join [our Discord server](https://discord.gg/nvfjVJ4Svh) to participate in development discussion.

Please read [Getting started contributing](Documentation/GettingStartedContributing.md) if you plan to contribute to Ladyworm for the first time.

Before opening an issue, please see the [issue policy](CONTRIBUTING.md#issue-policy) and the [detailed issue-reporting guidelines](ISSUES.md).

The full contribution guidelines can be found in [`CONTRIBUTING.md`](CONTRIBUTING.md).

## License

Ladyworm is licensed under a 2-clause BSD license.
