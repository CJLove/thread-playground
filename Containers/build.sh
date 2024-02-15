#!/bin/bash


cd threadtest || return
docker build -t threadtest:latest -t fir.love.io:3005/threadtest:latest .
docker push fir.love.io:3005/threadtest:latest

cd ..
