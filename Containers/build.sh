#!/bin/bash

cp ../build/bin/thread threadtest

cd threadtest
#podman build --format docker -t threadtest:latest -t fir.love.io:3005/threadtest:latest .
podman build --format docker -t threadtest:latest -t fir.love.io:3005/threadtest:latest .
podman push fir.love.io:3005/threadtest:latest