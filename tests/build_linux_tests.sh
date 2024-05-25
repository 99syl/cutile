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

CFLAGS="-std=c11"
if [ $DEBUG ]
then
    CFLAGS="$CFLAGS -g3"
fi

for tes in ${TESTS[@]}
do
    SRC="$SCRIPT_DIR/$tes.c"
    OUTNAME="$SCRIPT_DIR/$tes"
    gcc $CFLAGS $SRC -o $OUTNAME 
done

