#!/bin/bash

echo "Running valid test..."

cp tests/valid_1.txt input.txt
./compiler

echo "Running invalid test..."

cp tests/invalid_1.txt input.txt
./compiler