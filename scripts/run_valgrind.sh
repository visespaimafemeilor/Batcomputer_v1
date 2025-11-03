#!/usr/bin/bash

RUN_INTERACTIVE=${RUN_INTERACTIVE:-false}
BUILD_DIR=${BUILD_DIR:-build}
EXECUTABLE_NAME=${EXECUTABLE_NAME:-oop}


if [[ -n "$1" ]]; then
    BIN_DIR="$1"
elif [[ -d "install_dir/bin" ]]; then
    BIN_DIR="install_dir/bin"
else
    BIN_DIR="${BUILD_DIR}"
fi

echo "Using build directory: ${BIN_DIR}"
echo "Executable: ${EXECUTABLE_NAME}"


for f in "batsuit.txt" "family.txt" "criminals.txt"; do
    if [[ ! -f "${BIN_DIR}/${f}" ]]; then
        if [[ -f "${f}" ]]; then
            echo "Copying ${f} → ${BIN_DIR}/${f}"
            cp "${f}" "${BIN_DIR}/"
        else
            echo "Warning: ${f} not found in repository root or ${BIN_DIR}"
        fi
    fi
done


run_valgrind() {
    echo "🔍 Running Valgrind on ${BIN_DIR}/${EXECUTABLE_NAME} ..."
    timeout 25s valgrind --leak-check=full \
                         --show-leak-kinds=all \
                         --track-origins=yes \
                         --error-exitcode=1 \
                         "./${BIN_DIR}/${EXECUTABLE_NAME}"
    RESULT=$?
    if [[ $RESULT -eq 124 ]]; then
        echo "Timeout: programul probabil asteapta input interactiv."
    elif [[ $RESULT -ne 0 ]]; then
        echo "Valgrind exited with code $RESULT"
    else
        echo "Valgrind completed successfully."
    fi
}


if [[ "${RUN_INTERACTIVE}" = true ]]; then
    run_valgrind
else
    run_valgrind
fi
