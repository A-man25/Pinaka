#!/bin/bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
if ! command -v git >/dev/null 2>&1; then echo '[ERROR] Git is required. Install Xcode Command Line Tools: xcode-select --install'; exit 1; fi
if [[ ! -f "$ROOT/thirdparty/GLFW/glfw/include/GLFW/glfw3.h" ]]; then
  (cd "$ROOT" && git submodule update --init --recursive)
fi
if [[ ! -f "$ROOT/thirdparty/GLFW/glfw/include/GLFW/glfw3.h" ]]; then
  echo '[ERROR] GLFW submodule is missing.'; exit 1
fi
if [[ -x "$ROOT/thirdparty/Premake/bin/premake5" ]]; then
  echo "$ROOT/thirdparty/Premake/bin/premake5"; exit 0
fi
if [[ -x "$ROOT/build/tools/premake/premake5" ]]; then
  echo "$ROOT/build/tools/premake/premake5"; exit 0
fi
if command -v premake5 >/dev/null 2>&1; then command -v premake5; exit 0; fi
if command -v brew >/dev/null 2>&1; then
  echo '[INFO] Premake5 not found. Install with: brew install premake' >&2
else
  echo '[INFO] Premake5 required. Install Homebrew + Premake, or add a portable premake5 executable to PATH.' >&2
fi
exit 2
