#!/bin/sh

pushd libgloat
makepkg -sfci
make clean
rm *.tar.*
popd

pushd external/egl
makepkg -sfci
make clean
rm *.tar.*
popd

pushd external/opengl
makepkg -sfci
make clean
rm *.tar.*
popd

pushd external/tinyxml2
makepkg -sfci
make clean
rm *.tar.*
popd
