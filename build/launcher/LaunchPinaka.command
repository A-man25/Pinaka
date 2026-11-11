#!/bin/bash
# PINAKA | macOS entry point (Finder or Terminal)
set -e
HERE="$(cd "$(dirname "$0")" && pwd)"
exec /bin/bash "$HERE/../scripts/PinakaMac.sh" "$@"
