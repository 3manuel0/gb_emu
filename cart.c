#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

typedef  struct{
    u_int8_t* roms_data;
    u_int8_t Title[(0x143 - 0x134) + 1];
    u_int8_t cgb;
    u_int8_t manif;
    u_int8_t type;
    u_int8_t size;
}CART;


char * getmanif(char num){
    switch (num) {
        case 0x00 :	return "None";
        case 0x01  : return "Nintendo";
        case 0x08   : return "Capcom";
        case 0x09	: return "HOT-B";
        case 0x0A	: return "Jaleco";
        case 0x13 :	return "EA (Electronic Arts)";
        case 0x18	: return "Hudson Soft";
        case 0x19 :	return "B-AI";
        case 0x20	: return "KSS";
// 0B	Coconuts Japan
// 0C	Elite Systems
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
        default: return "Uknown";
    }
}

int main(int arc, char ** argv){
    unsigned char ch;
    size_t sz;
    char newCode[3];
    if(arc < 2) {
        printf("no argument given ./cart file-name\n");
        return -1;
    }
    FILE * f = fopen(argv[1], "rb");
    CART cart = {0};
    if(f == NULL){
        printf("can't open file");
        return 1;
    }
    fseek(f, 0L, SEEK_END);
    sz = ftell(f);
    rewind(f);
    cart.roms_data = malloc(sz);
    printf("sz : %ld\n", sz);
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
    printf("Title: %s\n", cart.Title);
    printf("cgb: %x\n", cart.cgb);
    printf("manf: %s\t %02x\n", getmanif(cart.manif), cart.manif);
    printf("New Code: %c%c\n", newCode[0], newCode[1]);
    printf("type: %d\n", cart.type);
    printf("size: %dkib\t%d\n", 32 * (1 << cart.size), cart.size);
    u_int8_t checksum = 0;
    for (u_int16_t address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - cart.roms_data[address] - 1;
    }
    printf("verfy checksum : %x\n", cart.roms_data[0x14D]);
    printf("Checksum : %x\n", checksum);
    // printf("op : %x %x\n", cart.roms_data[0x28b], cart.roms_data[(u_int16_t) (cart.roms_data[0x0102] | (cart.roms_data[0x0103] << 8)) + 1]);
    int i;
    u_int16_t addr = 0x0100;
    while(i < 400){
        if(cart.roms_data[addr] == 0xc3){ 
           printf("0x%.2x op : %x afop: %x\n", addr,cart.roms_data[addr], (u_int16_t) (cart.roms_data[addr + 1] | (cart.roms_data[addr + 2] << 8))); 
           addr = (u_int16_t) (cart.roms_data[addr + 1] | (cart.roms_data[addr + 2] << 8));
        }else {
           printf("0x%.2x : 0x%.2x\n", addr, cart.roms_data[addr]); 
            addr ++;
        }

        i++;
    }
    return 0;
}