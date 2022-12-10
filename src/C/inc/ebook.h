#ifndef EBOOK_H
#define EBOOK_H
#include "xil_assert.h"
#include "xil_printf.h"
#include "xil_types.h"

extern u8 ebook[4][19][70];
extern u8 ebookpage;

void EbookInitial();
void DisplayEbook();

#endif
