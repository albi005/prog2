#!/usr/bin/env bash

cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" || exit 1

zip -r "nhf.zip" *.c *.h owners animals treatments *.pdf
