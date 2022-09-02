#!/bin/bash

cp ../build/bin/thread threadtest
cp ../build/bin/thread threadtestdebug

cd threadtest
docker build -t threadtest:latest -t fir.love.io:3005/threadtest:latest .
docker push fir.love.io:3005/threadtest:latest

cd ..

cd threadtestdebug
docker build -t threadtestdebug:latest .
