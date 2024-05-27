SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

declare -a TESTS=(
    [0]="array"
    [1]="base64"
    [2]="blowfish"
    [3]="filesystem"
    [4]="hash_table"
    [5]="ini"
    [6]="shared_library"
    [7]="str"
)

# Builds .so for shared library test.
gcc -c -fpic "$SCRIPT_DIR/shared_library_sample.c"
gcc -shared -o "$SCRIPT_DIR/shared_library_sample.so" "$SCRIPT_DIR/shared_library_sample.o"

for tes in ${TESTS[@]}
do
    SRC="$SCRIPT_DIR/$tes.c"
    OUTNAME="$SCRIPT_DIR/$tes"
    gcc -std=c11 -g3 $SRC -o $OUTNAME 
    g++ -std=c++20 -g3 $SRC -o "${OUTNAME}_cpp" 
done

for tes in ${TESTS[@]}
do
    "$SCRIPT_DIR/$tes"
    "$SCRIPT_DIR/${tes}_cpp"
done
