#!/bin/bash
g++ -Wall -Wextra -fsanitize=address,undefined examples/*.cpp -I include -o app && ./app
