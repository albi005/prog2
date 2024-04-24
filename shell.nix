{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    packages = with pkgs; [
        bear
        clang-tools
        gcc
        gdb
        zip
        doxygen_gui
        graphviz
    ];
    shellHook = ''
        export OPEN_DEBUG_PATH=${pkgs.vscode-extensions.ms-vscode.cpptools}/share/vscode/extensions/ms-vscode.cpptools/debugAdapters/bin/OpenDebugAD7;
        bear -- g++ -DMEMTRACE -U_FORTIFY_SOURCE -g -O0 --std=c++17 dummy_bear.cpp
    '';
}
