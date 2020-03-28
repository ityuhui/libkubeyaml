# libkubeyaml
C library to parse yaml for kubernetes project

## Introduction
[libyaml](https://github.com/yaml/libyaml) has not implemented the detail parser function.

Other libraries does not support Windows platform or optional field.

So I write this library to parse the yaml file for my own project.
Now for parsing kubernetes config yaml. (~/.kube/config)

