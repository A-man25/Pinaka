#!/bin/bash
# PINAKA | macOS menu and build driver. Does not require PowerShell.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
ACTION="${1:-menu}"
MODE="${2:-debug}"
ORANGE='\033[38;5;214m'; CYAN='\033[36m'; DIM='\033[2m'; RESET='\033[0m'
print_banner() {
  clear 2>/dev/null || true
  printf "${ORANGE}           )\\\n           ) \\       P I N A K A\n     ======)  )=====================>\n           ) /       ENGINE / PROJECT FORGE\n           )/${RESET}\n"
  printf "${DIM}          C++20 / GLFW / PREMAKE / MACOS${RESET}\n\n"
}
check_layout() {
  if [[ ! -d "$ROOT/src/PinakaEngine/Pinaka" ]]; then
    echo '[ERROR] Source layout not migrated. Run the Windows migration script on your original checkout, or move the legacy source tree manually.' >&2
    exit 1
  fi
}
get_premake() {
  local result
  result="$(/bin/bash "$ROOT/build/setup/SetupMacOS.sh")" || exit $?
  printf '%s\n' "$result" | tail -n 1
}
generate() {
  check_layout
  local pm arch
  pm="$(get_premake)"
  arch="$(uname -m)"; [[ "$arch" == 'arm64' ]] && arch='ARM64' || arch='x86_64'
  echo "[PINAKA] Generating gmake2 ($arch) ..."
  (cd "$ROOT" && PINAKA_ARCH="$arch" "$pm" --file="$ROOT/build/premake/premake5.lua" gmake2)
  echo '[OK] Generated proj/gmake2/Makefile'
}
build() {
  check_layout
  # Existing supplied engine has a Windows-only window implementation. Fail clearly.
  if [[ ! -d "$ROOT/src/PinakaEngine/Pinaka/Platform/MacOS" ]]; then
    echo '[BLOCKED] PINAKA currently has WindowsWindow only. macOS project generation works,' >&2
    echo 'but a Cocoa/GLFW MacOS Window implementation and platform entry wiring are required before building/running.' >&2
    exit 3
  fi
  [[ -f "$ROOT/proj/gmake2/Makefile" ]] || generate
  local arch cfg
  arch="$(uname -m)"; [[ "$arch" == 'arm64' ]] && arch='arm64' || arch='x86_64'
  cfg="${MODE,,}_${arch}"
  make -C "$ROOT/proj/gmake2" "config=$cfg" -j "$(sysctl -n hw.ncpu)"
}
run() {
  local arch cfg exe
  arch="$(uname -m)"; [[ "$arch" == 'arm64' ]] && arch='ARM64' || arch='x86_64'
  cfg="Debug"; [[ "$MODE" == 'release' ]] && cfg='Release'
  exe="$ROOT/build/bin/$cfg-macosx-$arch/PinakaStudio"
  if [[ ! -x "$exe" ]]; then echo "[ERROR] Missing $exe. Build first."; exit 4; fi
  (cd "$(dirname "$exe")" && ./PinakaStudio)
}
open_code() {
  local f="$ROOT/ide/vscode/Pinaka.code-workspace"
  if command -v code >/dev/null; then code "$f"; else open -a 'Visual Studio Code' "$f"; fi
}
diagnose() {
  echo "Root: $ROOT"
  [[ -d "$ROOT/src/PinakaEngine/Pinaka" ]] && echo '[OK] New source layout' || echo '[MISSING] New source layout'
  [[ -f "$ROOT/thirdparty/GLFW/glfw/include/GLFW/glfw3.h" ]] && echo '[OK] GLFW' || echo '[MISSING] GLFW'
  command -v clang++ || true
  command -v make || true
  command -v premake5 || true
  echo 'macOS compilation requires additional engine platform source code.'
}
menu() {
  print_banner
  printf ' [1] Generate Makefiles\n [2] Build Debug\n [3] Build Release\n [4] Run Studio Debug\n [5] Open VS Code\n [6] Diagnostics\n [0] Exit\n\n'
  while true; do
    read -r -p ' PINAKA > ' answer
    case "$answer" in
      1) generate;;
      2) MODE=debug; build;;
      3) MODE=release; build;;
      4) MODE=debug; run;;
      5) open_code;;
      6) diagnose;;
      0) exit 0;;
      *) echo 'Choose 0–6.';;
    esac
    echo
  done
}
case "$ACTION" in
  menu) menu;;
  generate) generate;;
  build) build;;
  run) run;;
  buildrun) build; run;;
  setup) get_premake >/dev/null && echo '[OK] Setup complete';;
  vscode) open_code;;
  diagnose) diagnose;;
  *) echo "Unknown action: $ACTION"; exit 2;;
esac
