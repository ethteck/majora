#include <ultra64.h>
#include <global.h>

void Kanfont_Nop800F4F40(GlobalContext* ctxt, UNK_TYPE param_2, UNK_TYPE param_3) {}

void Kanfont_LoadAsciiChar(GlobalContext* ctxt, u8 character, s32 iParm3) {
    Dmamgr_SendRequestAndWait((u32)ctxt->msgContext.font.unk0[(ctxt->msgContext).unk11EF0] + iParm3,
        (u32)&nes_font_static_vrom_start + character * 0x80 - 0x1000,
        0x80);
}

void Kanfont_LoadMessageBoxEnd(Font* font, u16 type) {
    Dmamgr_SendRequestAndWait((u32)font->unk7800, type * 0x80 + (u32)&message_static_vrom_start + 0x5000, 0x80);
}

void Kanfont_LoadOrderedFont(Font* font) {
    u32 loadOffset;
    s32 codePointIndex = 0;
    u32 writeLocation;

    while (1) {
        writeLocation = (u32)&font->unk7800[codePointIndex + 1];
        loadOffset = kanfontOrdering[codePointIndex] * 128;
        if (kanfontOrdering[codePointIndex] == 0) {
            loadOffset = 0;
        }
        Dmamgr_SendRequestAndWait(writeLocation, (u32)&nes_font_static_vrom_start + loadOffset, 0x80);
        if (kanfontOrdering[codePointIndex] == 140) break;
        codePointIndex++;
    }
}
