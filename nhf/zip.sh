#!/usr/bin/env bash

cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" || exit 1

mkdir -p out/submit
zip -r "out/submit/src.zip" *.cpp *.hpp *.h
zip -r "out/submit/data.zip" owners animals treatments
