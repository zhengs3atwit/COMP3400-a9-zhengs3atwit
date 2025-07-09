setup() {
    if [ -d "/usr/lib/bats" ]; then
        load "/usr/lib/bats/bats-support/load"
        load "/usr/lib/bats/bats-assert/load"
        load "/usr/lib/bats/bats-file/load"
    elif [ -d "/opt/homebrew/lib" ]; then
        load "/opt/homebrew/lib/bats-support/load"
        load "/opt/homebrew/lib/bats-assert/load"
        load "/opt/homebrew/lib/bats-file/load"
    elif [ -d "/usr/local/lib" ]; then
        load "/usr/local/lib/bats-support/load"
        load "/usr/local/lib/bats-assert/load"
        load "/usr/local/lib/bats-file/load"
    else
        echo "bats installation not found!"
    fi
    export BATS_TEST_TIMEOUT=10

    PATH="$(pwd)/build:$PATH"
}



@test "partc_main" {
    run partc_main

    cat << EOF | assert_output -                            # Assert if output matches
USAGE: partc_main IN_FILE OUT_FILE NTHREADS
EOF
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
@test "partc_main tests/red_line.png out.png" {
    run partc_main tests/red_line.png out.png

    cat << EOF | assert_output -                            # Assert if output matches
USAGE: partc_main IN_FILE OUT_FILE NTHREADS
EOF
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}

@test "partc_main tests/red_line.png out.png 1" {
    rm -f "out.png"
    run partc_main tests/red_line.png out.png 1

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/red_line.out.png"
}
@test "partc_main tests/red_line.png out.png 2" {
    rm -f "out.png"
    run partc_main tests/red_line.png out.png 2

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/red_line.out.png"
}
@test "partc_main tests/red_line.png out.png 4" {
    rm -f "out.png"
    run partc_main tests/red_line.png out.png 4

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/red_line.out.png"
}
@test "partc_main tests/red_box.png out.png 1" {
    rm -f "out.png"
    run partc_main tests/red_box.png out.png 1

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/red_box.out.png"
}
@test "partc_main tests/red_box.png out.png 2" {
    rm -f "out.png"
    run partc_main tests/red_box.png out.png 2

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/red_box.out.png"
}
@test "partc_main tests/red_box.png out.png 4" {
    rm -f "out.png"
    run partc_main tests/red_box.png out.png 4

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/red_box.out.png"
}
@test "partc_main tests/A.png out.png 1" {
    rm -f "out.png"
    run partc_main tests/A.png out.png 1

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/A.out.png"
}
@test "partc_main tests/A.png out.png 2" {
    rm -f "out.png"
    run partc_main tests/A.png out.png 2

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/A.out.png"
}
@test "partc_main tests/A.png out.png 4" {
    rm -f "out.png"
    run partc_main tests/A.png out.png 4

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/A.out.png"
}
@test "partc_main tests/pencils.png out.png 1" {
    rm -f "out.png"
    run partc_main tests/pencils.png out.png 1

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/pencils.out.png"
}
@test "partc_main tests/pencils.png out.png 2" {
    rm -f "out.png"
    run partc_main tests/pencils.png out.png 2

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/pencils.out.png"
}
@test "partc_main tests/pencils.png out.png 4" {
    rm -f "out.png"
    run partc_main tests/pencils.png out.png 4

    assert_exists "out.png"                                 # Assert if output file not created
    assert_files_equal "out.png" "tests/pencils.out.png"
}
