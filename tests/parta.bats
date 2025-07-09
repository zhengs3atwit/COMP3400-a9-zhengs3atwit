setup() {
    if [ -d "/usr/lib/bats" ]; then
        load "/usr/lib/bats/bats-support/load"
        load "/usr/lib/bats/bats-assert/load"
    elif [ -d "/opt/homebrew/lib" ]; then
        load "/opt/homebrew/lib/bats-support/load"
        load "/opt/homebrew/lib/bats-assert/load"
    elif [ -d "/usr/local/lib" ]; then
        load "/usr/local/lib/bats-support/load"
        load "/usr/local/lib/bats-assert/load"
    else
        echo "bats installation not found!"
    fi
    export BATS_TEST_TIMEOUT=10

    PATH="$(pwd)/build:$PATH"
}

@test "parta_main" {
    run parta_main

    cat << EOF | assert_output -                            # Assert if output matches
USAGE: parta_main NTHREADS
EOF
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
@test "parta_main 0" {
    run parta_main 0

    cat << EOF | assert_output -                            # Assert if output matches
ERROR: NTHREADS should be positive integer
EOF
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
@test "parta_main 1" {
    run parta_main 1

    cat << EOF | assert_output -                            # Assert if output matches
Hello, I'm thread 0
Main cleans up
EOF
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "parta_main 2" {
    run parta_main 2

    output=$(echo "$output" | sort)
    cat << EOF | assert_output -                            # Assert if output matches
Hello, I'm thread 0
Hello, I'm thread 1
Main cleans up
EOF
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "parta_main 4" {
    run parta_main 4

    output=$(echo "$output" | sort)
    cat << EOF | assert_output -                            # Assert if output matches
Hello, I'm thread 0
Hello, I'm thread 1
Hello, I'm thread 2
Hello, I'm thread 3
Main cleans up
EOF
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "parta_main 8" {
    run parta_main 8

    output=$(echo "$output" | sort)
    cat << EOF | assert_output -                            # Assert if output matches
Hello, I'm thread 0
Hello, I'm thread 1
Hello, I'm thread 2
Hello, I'm thread 3
Hello, I'm thread 4
Hello, I'm thread 5
Hello, I'm thread 6
Hello, I'm thread 7
Main cleans up
EOF
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "parta_main X" {
    run parta_main X

    cat << EOF | assert_output -                            # Assert if output matches
ERROR: NTHREADS should be positive integer
EOF
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
