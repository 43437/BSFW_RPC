#!/bin/bash

rm -rf install
cd client
./release.sh

cd ../server
./release.sh

cd ../install
chmod a+x *
cd ..