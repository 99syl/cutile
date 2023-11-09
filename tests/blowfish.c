#define CUTILE_IMPLEM
#include "../blowfish.h"

int main(int ac, char** av)
{
    bool8 err = bool8_false;

    blowfish_context bctx;
    init_blowfish_context(&bctx, "TESTKEY", 7);
    u32 l = 1, r = 2;
    blowfish_encrypt(&bctx, &l, &r);
    err |= (l != 0xDF333FD2 || r != 0x30A71BB4);
    blowfish_decrypt(&bctx, &l, &r);
    err |= (l != 1 || r != 2);
    
    return err;
}
