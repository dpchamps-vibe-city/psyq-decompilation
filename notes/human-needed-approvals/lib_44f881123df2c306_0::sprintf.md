# lib_44f881123df2c306_0::sprintf — human decision needed

- **Parked:** 2026-10-17T21:57:42.880Z
- **Reason:** asm-needs-human-approval
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libc2/34-sprintf/sprintf.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** Library park preserves the complete member TU unchanged; no disabled neighbor bodies or original-object fallback

## What the loop needs

The top escalation tier proposed a source construct the clean-source policy forbids,
and there is no higher agent to adjudicate it. Decide whether the construct is the
correct answer for this function. If it is, add the allowlist entry to
`.pi/autoloop.json` under `sourcePolicy.allowlist` and re-run the loop on this
target. If it is not, the function needs a different structural hypothesis.

## Policy findings

- `include/operations.h:?` — **platform-macro** — UDIVMOD_GUARDED: need an authoritative SDK binding plus a measured use, or two independent original-code uses
  ``

## Oracle report for the preserved attempt

```
top tier proposed a forbidden construct with no higher tier to adjudicate it
```

## Preserved attempt

```c
int sprintf(char *buf, const char *fmt, ...) {
  char tmp[0x200];
  FmtSpec st;
  va_list ap;
  unsigned int v;
  char *s;
  const unsigned char *digits;
  char *p;
  int n;
  int len;
  int c;
  int minus;
  int plus;
  int space;
  int zero;
  int alternate;

  va_start(ap, fmt);
  len = 0;
  c = *(const signed char *)fmt;
  if (c == 0) {
    goto done;
  }
  minus = '-';
  plus = '+';
  space = ' ';
  for (; c != 0; c = *(const signed char *)++fmt) {
    if (c != '%') {
      buf[len++] = c;
      continue;
    }
    st = D_000009E0;
    alternate = '#';
    zero = '0';
    for (;;) {
      c = *(const signed char *)++fmt;
      if (c == minus) {
        st.left = 1;
      } else if (c == plus) {
        st.plus = 1;
      } else if (c == space) {
        st.sign = c;
      } else if (c == alternate) {
        st.alt = 1;
      } else if (c == zero) {
        st.zero = 1;
      } else {
        break;
      }
    }
    if (c == '*') {
      st.width = *(*(int **)&ap)++;
      if (st.width < 0) {
        st.width = -st.width;
        st.left = 1;
      }
      c = *(const signed char *)++fmt;
    } else {
      while ((unsigned)(c - '0') < 10) {
        st.width = st.width * 10 + (c - '0');
        c = *(const signed char *)++fmt;
      }
    }
    if (c == '.') {
      c = *(const signed char *)++fmt;
      if (c == '*') {
        st.prec = *(*(int **)&ap)++;
        c = *(const signed char *)++fmt;
      } else {
        while ((unsigned)(c - '0') < 10) {
          st.prec = st.prec * 10 + (c - '0');
          c = *(const signed char *)++fmt;
        }
      }
      if (st.prec >= 0) {
        st.hasprec = 1;
      }
    }
    s = tmp + sizeof(tmp);
    if (st.left) {
      st.zero = 0;
    }

  modifier:
    switch (c) {
    case 'h':
      st.half = 1;
      c = *(const signed char *)++fmt;
      goto modifier;
    case 'l':
      st.lng = 1;
      c = *(const signed char *)++fmt;
      goto modifier;
    case 'L':
      st.dbl = 1;
      c = *(const signed char *)++fmt;
      goto modifier;
    case 'd':
    case 'i':
      if (st.lng) {
        v = *(*(long **)&ap)++;
      } else {
        v = *(*(int **)&ap)++;
      }
      if (st.half) {
        v = (short)v;
      }
      if ((int)v < 0) {
        v = -v;
        st.sign = minus;
      } else if (st.plus) {
        st.sign = plus;
      }
      goto decimal;
    case 'u':
      if (st.lng) {
        v = *(*(long **)&ap)++;
      } else {
        v = *(*(int **)&ap)++;
      }
      if (st.half) {
        v = (unsigned short)v;
      }
      st.sign = 0;
    decimal:
      if (!st.hasprec) {
        if (st.zero) {
          st.prec = st.width;
          if (st.sign) {
            st.prec = st.width - 1;
          }
        }
        if (st.prec <= 0) {
          st.prec = 1;
        }
      }
      n = 0;
      while (v) {
        *--s = v % 10 + '0';
        v /= 10;
        n++;
      }
      if (n < st.prec) {
        zero = '0';
        *--s = zero;
        n++;
        while (n < st.prec) {
          zero = '0';
        *--s = zero;
          n++;
        }
      }
      if (st.sign) {
        *--s = st.sign;
        n++;
      }
      break;
    case 'o':
      if (st.lng) {
        v = *(*(long **)&ap)++;
      } else {
        v = *(*(int **)&ap)++;
      }
      if (st.half) {
        v = (unsigned short)v;
      }
      if (!st.hasprec) {
        if (st.zero) {
          st.prec = st.width;
        }
        if (st.prec <= 0) {
          st.prec = 1;
        }
      }
      n = 0;
      while (v) {
        *--s = (v & 7) + '0';
        v >>= 3;
        n++;
      }
      if (st.alt && n && *(signed char *)s != (zero = '0')) {
        zero = '0';
        *--s = zero;
        n++;
      }
      while (n < st.prec) {
        zero = '0';
        *--s = zero;
        n++;
      }
      break;
    case 'p':
      st.prec = 8;
      st.hasprec = 1;
      st.lng = 1;
      /* FALLTHROUGH */
    case 'X':
      digits = upper_digits;
      goto hex;
    case 'x':
      digits = lower_digits;
    hex:
      if (st.lng) {
        v = *(*(long **)&ap)++;
      } else {
        v = *(*(int **)&ap)++;
      }
      if (st.half) {
        v = (unsigned short)v;
      }
      if (!st.hasprec) {
        if (st.zero) {
          st.prec = st.width;
          if (st.alt) {
            st.prec = st.width - 2;
          }
        }
        if (st.prec <= 0) {
          st.prec = 1;
        }
      }
      n = 0;
      while (v) {
        *--s = digits[v & 0xF];
        v >>= 4;
        n++;
      }
      while (n < st.prec) {
        *--s = '0';
        n++;
      }
      if (st.alt) {
        *--s = c;
        *--s = '0';
        n += 2;
      }
      break;
    case 'c':
      {
        unsigned char ch = **(int **)&ap;
        int *next = *(int **)&ap + 1;
        *--s = ch;
        *(int **)&ap = next;
      }
      n = 1;
      break;
    case 's':
      s = *(*(CharPtr **)&ap)++;
      if (st.alt) {
        n = *s++;
        if (st.hasprec && st.prec < n) {
          n = st.prec;
        }
      } else if (!st.hasprec) {
        n = strlen(s);
      } else if ((p = memchr(s, 0, st.prec)) != 0) {
        n = p - s;
      } else {
        n = st.prec;
      }
      break;
    case 'n':
      s = *(*(CharPtr **)&ap)++;
      if (st.half) {
        *(short *)s = len;
      } else if (st.lng) {
        *(long *)s = len;
      } else {
        *(int *)s = len;
      }
      continue;
    default:
      if (c != '%') {
        goto done;
      }
      buf[len++] = c;
      continue;
    }

    if (n < st.width && !st.left) {
      do {
        buf[len++] = space;
      } while (n < --st.width);
    }
    memmove(buf + len, s, n);
    len += n;
    while (n < st.width) {
      buf[len++] = space;
      n++;
    }
  }
done:
  buf[len] = 0;
  return len;
}
```
