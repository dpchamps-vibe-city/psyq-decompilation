#ifndef LIBMCRD_CREATE2_CHECKED_IO_H
#define LIBMCRD_CREATE2_CHECKED_IO_H

/* LOW.OBJ _card_create2: retry zeroing at 0x9D4 precedes the checksum loop
 * at 0x9E4, then card writes begin at 0xA00. Build-only hypothesis. */
static __inline__ s32 card_write_checked(s32 chan, s32 sector, u8 *buf)
{
    s32 retry = 0;
    s32 status;
    u8 *p = buf;
    u8 sum = 0;
    s32 j = 0x7E;

    do {
        sum ^= *p++;
    } while (--j >= 0);
    *p = sum;
    do {
        _clr_card_event();
        _card_write(chan, sector, buf);
        status = _get_card_event_x();
        if (status == 0)
            break;
        if (status == 4) {
            _clr_card_event();
            _card_clear(chan);
            _get_card_event_x();
        }
        retry++;
    } while (retry < 8);
    return status;
}

#endif
