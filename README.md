# Novarys

**Novarys** is a custom emulator written in **Rust** for the *OVERTURE* architecture from the game *Turing Complete*.

The project was developed as a continuation of **Clowryys**, a custom assembler targeting the same architecture, with the goal of exploring low-level system design, binary execution, and emulator development.

Novarys is capable of loading and executing binaries compatible with the OVERTURE architecture while exposing the internal machine state for debugging and experimentation.

---

## Overview

Novarys was created to deepen my understanding of:

- Emulator and virtual machine design
- CPU architecture concepts
- Binary execution workflows
- Rust systems programming
- Low-level debugging and state management

The emulator focuses on correctness, architecture experimentation, and observability rather than raw performance.

It is primarily intended to work alongside [**Clowryys**](https://github.com/lasere77/clowryys), a custom assembler for the same architecture.

---

## Features

- Execution of OVERTURE-compatible binaries
- Register state visualization at each execution tick
- Basic instruction cycle emulation
- Custom architecture implementation
- Terminal-based execution environment
- Debug-oriented execution flow

---

## Installation / Build

### Requirements

- Rust
- Cargo

No additional external dependencies are required.

### Build & Run

```bash
cargo run path/to/binary/file
```

---

## Usage

Novarys executes binaries targeting the OVERTURE architecture.

During execution, the emulator displays the internal register state at each tick, making it easier to:

- Observe instruction execution
- Debug programs
- Understand architecture behavior
- Inspect machine state transitions

This behavior was intentionally designed to support experimentation and low-level debugging.

---

## Architecture Overview

Novarys implements a simplified CPU emulation pipeline:

1. **Binary loading**
   - Loads compiled OVERTURE binaries into emulator memory

2. **Instruction decoding**
   - Interprets binary instructions according to the architecture specification

3. **Execution cycle**
   - Updates registers and internal machine state
   - Executes ALU and control flow operations

4. **State visualization**
   - Displays register values and execution state in real time

The emulator is intentionally designed to stay close to the underlying architecture in order to expose low-level behavior as clearly as possible.

---

## Design Choices

### Rust implementation

Rust was chosen to explore systems programming concepts while benefiting from:

- Memory safety guarantees
- Strong type safety
- Performance-oriented abstractions
- Explicit resource management

The project also served as a practical introduction to Rust in the context of low-level tooling.

### Debug-oriented execution

Rather than hiding internal state, Novarys exposes register values continuously during execution.

This makes the emulator particularly useful for:

- Architecture experimentation
- Understanding instruction behavior
- Debugging assembled programs
- Educational exploration

### Architecture continuity

Novarys was designed as a continuation of the Clowryys ecosystem.

Together, both projects form a minimal toolchain for the OVERTURE architecture:

- **Clowryys** → assembler
- **Novarys** → emulator/runtime

---

## Current Limitations

- Terminal interface remains minimal
- Limited input/output capabilities
- No advanced debugging UI
- Execution performance not yet optimized
- Architecture support intentionally constrained to OVERTURE

---

## Future Improvements

Planned improvements include:

- Better terminal rendering and readability
- Improved input/output handling
- Enhanced debugging and inspection tools
- Better execution ergonomics
- Performance optimizations
- More user-friendly execution workflow

---

## What This Project Demonstrates

This project highlights practical experience with:

- Systems programming in Rust
- Emulator and CPU architecture design
- Binary execution and instruction decoding
- Register and memory management
- Machine state visualization
- Debugging low-level systems
- Structuring and maintaining a solo technical project

It also reflects a strong interest in computer architecture, runtime systems, and low-level software engineering.

---

## Related Project

- [**Clowryys**](https://github.com/lasere77/clowryys) — custom assembler for the OVERTURE architecture

---

## AI Assistance

Parts of this README were refined with the help of AI tools to improve clarity, structure, and overall presentation.

All technical content, design decisions, and implementation details are original and reflect the author's work.