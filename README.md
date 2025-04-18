# CursorAssistant

[![Build Status](https://img.shields.io/github/actions/workflow/status/yourusername/CursorAssistant/ci.yml?branch=main)](https://github.com/yourusername/CursorAssistant/actions)  
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

**CursorAssistant** is a lightweight JUCE‑based audio plugin for real‑time session capture in your DAW. Hit **Record**, play your session, then **Stop** — the plugin drops a `CursorSession.wav` in your Documents folder.

---

## 🎛️ Features

- **Real‑time WAV recording** directly from your Master insert  
- **Threaded file I/O** using JUCE’s `AudioFormatWriter::ThreadedWriter`  
- **Simple Record/Stop UI** in the plugin editor  
- **Cross‑platform** (macOS, Windows, Linux) via JUCE + CMake + CPM  
- **Zero dependencies** beyond JUCE modules  
- **Automatic transport sync** — record follows host Play/Stop  

---

## 🚀 Quick Start

### Prerequisites

- **C++17** compiler  
- **CMake** ≥ 3.15  
- **CPM.cmake** helper in `cmake/CPM.cmake`  
- **JUCE** (fetched automatically via CPM)  
- A VST3/AU/AAX‑capable DAW (e.g. FL Studio, Ableton Live, Logic Pro)

### Clone & Build

```bash
git clone https://github.com/toofaloof/CursorAssistant.git
cd CursorAssistant
mkdir build && cd build
cmake ..
cmake --build . --config Release
