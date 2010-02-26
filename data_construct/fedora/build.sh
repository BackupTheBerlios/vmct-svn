#!/bin/sh

autoreconf --install
./configure --with-log
make

