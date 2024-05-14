#!/usr/bin/env nix-shell
#! nix-shell -i bash --pure
#! nix-shell -p bash zip pandoc python312Packages.weasyprint
#
# https://nix.dev/tutorials/first-steps/reproducible-scripts
# NixOS <3

set -e

cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" || exit 1
cd ..

rm -fr out/submit
mkdir -p out/submit
zip "out/submit/src.zip" *.cpp *.hpp *.c *.h
zip "out/submit/data.zip" owners animals treatments

# pandoc terv.md -o terv.html
# weasyprint terv.html out/terv.pdf
# nvm, just open nhf/ in obsidian, set theme to catppuccin frappe,
# enable ignoring new lines and export to pdf
zip -Dr "out/submit/skeleton.zip" *.cpp *.hpp *.c *.h terv.pdf
