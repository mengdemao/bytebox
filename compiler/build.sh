#！/bin/bash

cp arm_config .config
ct-ng build

cp aarch64_config .config
ct-ng build
