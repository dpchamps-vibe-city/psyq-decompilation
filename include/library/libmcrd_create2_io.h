#ifndef LIBMCRD_CREATE2_IO_H
#define LIBMCRD_CREATE2_IO_H
/* Saturating card I/O retry boundary for LOW.OBJ _card_create2.
 * Evidence: the target's first (chan,0), second (chan,i+1) read loops and its
 * write loop are instruction-for-instruction the same 12-instruction body with a
 * bottom-tested counter, and each call site keeps a real `if (ev != 0) return ev;`
 * branch -- the shape an inlined static helper produces. Both helpers inline
 * completely: the owning object gains no symbol. */

static __inline__ s32 card_read_wait(s32 chan, s32 sector, u8 *buf)
{
    s32 retry = 0;
    s32 status;

    bzero(buf, 0x80);
    do {
        _clr_card_event();
        _card_read(chan, sector, buf);
        status = _get_card_event_x();
        if (status == 0) {
            break;
        }
        if (status == 4) {
            _clr_card_event();
            _card_clear(chan);
            _get_card_event_x();
        }
        retry++;
    } while (retry < 8);
    return status;
}

static __inline__ s32 card_write_wait(s32 chan, s32 sector, u8 *buf)
{
    s32 retry = 0;
    s32 status;

    do {
        _clr_card_event();
        _card_write(chan, sector, buf);
        status = _get_card_event_x();
        if (status == 0) {
            break;
        }
        if (status == 4) {
            _clr_card_event();
            _card_clear(chan);
            _get_card_event_x();
        }
        retry++;
    } while (retry < 8);
    return status;
}

#endif /* LIBMCRD_CREATE2_IO_H */
