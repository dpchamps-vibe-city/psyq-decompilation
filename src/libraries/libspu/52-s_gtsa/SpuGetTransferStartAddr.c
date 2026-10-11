unsigned long SpuGetTransferStartAddr(void) {
    return (unsigned long)_spu_tsa << _spu_mem_mode_plus;
}
