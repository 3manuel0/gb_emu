#include "cart.h"

static const char * getmanif[] = {
        [0x00]  = "None",
        [0x01]  = "Nintendo",
        [0x08] = "Capcom",
        [0x09] = "HOT-B",
        [0x0A] = "Jaleco",
        [0x13]	= "EA (Electronic Arts)",
        [0x18] = "Hudson Soft",
        [0x19]	= "B-AI",
        [0x20] = "KSS",
        [0x0B]	= "Coconuts Japan",
        [0x0C]	= "Elite Systems"
// 13	EA (Electronic Arts)
// 18	Hudson Soft
// 19	ITC Entertainment
// 1A	Yanoman
// 1D	Japan Clary
// 1F	Virgin Games Ltd.3
// 24	PCM Complete
// 25	San-X
// 28	Kemco
// 29	SETA Corporation
// 30	Infogrames5
// 31	Nintendo
// 32	Bandai
// 33	Indicates that the New licensee code should be used instead.
// 34	Konami
// 35	HectorSoft
// 38	Capcom
// 39	Banpresto
// 3C	Entertainment Interactive (stub)
// 3E	Gremlin
// 41	Ubi Soft1
// 42	Atlus
// 44	Malibu Interactive
// 46	Angel
// 47	Spectrum HoloByte
// 49	Irem
// 4A	Virgin Games Ltd.3
// 4D	Malibu Interactive
// 4F	U.S. Gold
// 50	Absolute
// 51	Acclaim Entertainment
// 52	Activision
// 53	Sammy USA Corporation
// 54	GameTek
// 55	Park Place13
// 56	LJN
// 57	Matchbox
// 59	Milton Bradley Company
// 5A	Mindscape
// 5B	Romstar
// 5C	Naxat Soft14
// 5D	Tradewest
// 60	Titus Interactive
// 61	Virgin Games Ltd.3
// 67	Ocean Software
// 69	EA (Electronic Arts)
// 6E	Elite Systems
// 6F	Electro Brain
// 70	Infogrames5
// 71	Interplay Entertainment
// 72	Broderbund
// 73	Sculptured Software6
// 75	The Sales Curve Limited7
// 78	THQ
// 79	Accolade15
// 7A	Triffix Entertainment
// 7C	MicroProse
// 7F	Kemco
// 80	Misawa Entertainment
// 83	LOZC G.
// 86	Tokuma Shoten
// 8B	Bullet-Proof Software2
// 8C	Vic Tokai Corp.16
// 8E	Ape Inc.17
// 8F	I’Max18
// 91	Chunsoft Co.8
// 92	Video System
// 93	Tsubaraya Productions
// 95	Varie
// 96	Yonezawa19/S’Pal
// 97	Kemco
// 99	Arc
// 9A	Nihon Bussan
// 9B	Tecmo
// 9C	Imagineer
// 9D	Banpresto
// 9F	Nova
// A1	Hori Electric
// A2	Bandai
// A4	Konami
// A6	Kawada
// A7	Takara
// A9	Technos Japan
// AA	Broderbund
// AC	Toei Animation
// AD	Toho
// AF	Namco
// B0	Acclaim Entertainment
// B1	ASCII Corporation or Nexsoft
// B2	Bandai
// B4	Square Enix
// B6	HAL Laboratory
// B7	SNK
// B9	Pony Canyon
// BA	Culture Brain
// BB	Sunsoft
// BD	Sony Imagesoft
// BF	Sammy Corporation
// C0	Taito
// C2	Kemco
// C3	Square
// C4	Tokuma Shoten
// C5	Data East
// C6	Tonkin House
// C8	Koei
// C9	UFL
// CA	Ultra Games
// CB	VAP, Inc.
// CC	Use Corporation
// CD	Meldac
// CE	Pony Canyon
// CF	Angel
// D0	Taito
// D1	SOFEL (Software Engineering Lab)
// D2	Quest
// D3	Sigma Enterprises
// D4	ASK Kodansha Co.
// D6	Naxat Soft14
// D7	Copya System
// D9	Banpresto
// DA	Tomy
// DB	LJN
// DD	Nippon Computer Systems
// DE	Human Ent.
// DF	Altron
// E0	Jaleco
// E1	Towa Chiki
// E2	Yutaka # Needs more info
// E3	Varie
// E5	Epoch
// E7	Athena
// E8	Asmik Ace Entertainment
// E9	Natsume
// EA	King Records
// EB	Atlus
// EC	Epic/Sony Records
// EE	IGS
// F0	A Wave
// F3	Extreme Entertainment
// FF	LJN
    };

CART load_cart(char * cartName){
    unsigned char ch;
    size_t sz;
    char newCode[3] = "nn";
    FILE * f = fopen(cartName, "rb");
    CART cart = {0};
    if(f == NULL){
        printf("can't open file");
        exit(-1);
        return cart;
    }
    fseek(f, 0L, SEEK_END);
    sz = ftell(f);
    rewind(f);
    cart.roms_data = malloc(sz);
    int str = 0;
    for (size_t i = 0; i < sz; i++) {
        ch = fgetc(f);
        if(i >= 0x134 && i < 0x143 ){
            cart.Title[str] = ch;
            // printf("Title : %c\n", ch);
            str++;
        }
        if(i == 0x143){
            cart.cgb = ch;
        }
        if(i == 0x144){
            newCode[0] = ch;
        }
        if (i == 0x145) {
            newCode[0] = ch;
        }
        if(i == 0x147){
            cart.type = ch;
        }
        if(i == 0x148){
            cart.size = ch;
        }
        if(i == 0x14B){
            cart.manif = ch;
        }
        // if(i < 0x14F)
        //     printf("%d ", ch);

        cart.roms_data[i] = ch;
    }
    
    u8 checksum = 0;
    for (u16 address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - cart.roms_data[address] - 1;
    }

    // printing the header
    printf("-------header----------------\n"); 
    printf("file size : %ld\n", sz);
    printf("Title: %s\n", cart.Title);
    printf("cgb: %x\n", cart.cgb);
    printf("manufacturer: %s %02x\n", getmanif[cart.manif], cart.manif);
    printf("New Code: %c%c\n", newCode[0], newCode[1]);
    printf("cart_type: %d\n", cart.type);
    printf("rom_size: %dkib\t%d\n", 32 * (1 << cart.size), cart.size);
    printf("checksum_value : %x\n", cart.roms_data[0x14D]);
    printf("Checksum_calc : %x %s\n", checksum,checksum == cart.roms_data[0x14D] ? "good" : "bad");
    // printf("op : %x %x\n", cart.roms_data[0x28b], cart.roms_data[(u16) (cart.roms_data[0x0102] | (cart.roms_data[0x0103] << 8)) + 1]);
    printf("------------------------------\n"); 
    return cart;
}