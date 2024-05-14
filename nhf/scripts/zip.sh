#!/usr/bin/env nix-shell
#! nix-shell -i bash --pure --keep NIX_PATH
#! nix-shell -p bash zip doxygen nix

# https://nix.dev/tutorials/first-steps/reproducible-scripts
# NixOS <3

set -e

cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" || exit 1 #nhf/scripts/
cd .. #nhf/

./scripts/gen.py #generate example data
doxygen #generate relation diagrams

rm -fr out/submit
mkdir -p out/submit
zip "out/submit/src.zip" *.cpp *.hpp *.c *.h
zip "out/submit/data.zip" owners animals treatments

echo
echo -e "\033[0;31m Did you update the PDFs? \033[0m"
echo
