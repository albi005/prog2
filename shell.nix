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
    '';
}
