#!/bin/bash
find . -type d ! -name . ! -path "*.git*" | xargs -I {} cp -a gen_index.sh {}/
find . -type d ! -name . ! -path "*.git*" | xargs -I {} cp -a copy_gen_index_sh.sh {}/
find . -type d ! -name . ! -path "*.git*" | xargs -I {} cp -a current.sh {}/
