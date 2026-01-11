#!/usr/bin/bash

cppcheck --enable=all \
    --inline-suppr \
    --project="${BUILD_DIR:-build}"/compile_commands.json \
    -I include \
    -i"${BUILD_DIR:-build}" --suppress="*:${BUILD_DIR:-build}/*" \
    -i"${EXT_DIR:-ext}" --suppress="*:${EXT_DIR:-ext}/*" \
    --suppress=missingInclude \
    --suppress=missingIncludeSystem \
    --suppress=unmatchedSuppression \
    --suppress=unusedFunction \
    --suppress=useStlAlgorithm \
    --check-level=exhaustive \
    --error-exitcode=1