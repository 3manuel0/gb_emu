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
    [0x0C]	= "Elite Systems",
    [0x1A] = "Yanoman",
    [0x1D] = "Japan Clary",
    [0x1F] = "Virgin Games Ltd.3",
    [0x24] = "PCM Complete",
    [0x25] = "San-X",
    [0x28] = "Kemco",
    [0x29] = "SETA Corporation",
    [0x30] = "Infogrames5",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Indicates that the New licensee code should be used instead.",
    [0x34] = "Konami",
    [0x35] = "HectorSoft",
    [0x38] = "Capcom",
    [0x39] = "Banpresto",
    [0x3C] = "Entertainment Interactive (stub)",
    [0x3E] = "Gremlin",
    [0x41] = "Ubi Soft1",
    [0x42] = "Atlus",
    [0x44] = "Malibu Interactive",
    [0x46] = "Angel",
    [0x47] = "Spectrum HoloByte",
    [0x49] = "Irem",
    [0x4A] = "Virgin Games Ltd.3",
    [0x4D] = "Malibu Interactive",
    [0x4F] = "U.S. Gold",
    [0x50] = "Absolute",
    [0x51] = "Acclaim Entertainment",
    [0x52] = "Activision",
    [0x53] = "Sammy USA Corporation",
    [0x54] = "GameTek",
    [0x55] = "Park Place13",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x59] = "Milton Bradley Company",
    [0x5A] = "Mindscape",
    [0x5B] = "Romstar",
    [0x5C] = "Naxat Soft14",
    [0x5D] = "Tradewest",
    [0x60] = "Titus Interactive",
    [0x61] = "Virgin Games Ltd.3",
    [0x67] = "Ocean Software",
    [0x69] = "EA (Electronic Arts)",
    [0x6E] = "Elite Systems",
    [0x6F] = "Electro Brain",
    [0x70] = "Infogrames5",
    [0x71] = "Interplay Entertainment",
    [0x72] = "Broderbund",
    [0x73] = "Sculptured Software6",
    [0x75] = "The Sales Curve Limited7",
    [0x78] = "THQ",
    [0x79] = "Accolade15",
    [0x7A] = "Triffix Entertainment",
    [0x7C] = "MicroProse",
    [0x7F] = "Kemco",
    [0x80] = "Misawa Entertainment",
    [0x83] = "LOZC G.",
    [0x86] = "Tokuma Shoten",
    [0x8B] = "Bullet-Proof Software2",
    [0x8C] = "Vic Tokai Corp.16",
    [0x8E] = "Ape Inc.17",
    [0x8F] = "I’Max18",
    [0x91] = "Chunsoft Co.8",
    [0x92] = "Video System",
    [0x93] = "Tsubaraya Productions",
    [0x95] = "Varie",
    [0x96] = "Yonezawa19/S’Pal",
    [0x97] = "Kemco",
    [0x99] = "Arc",
    [0x9A] = "Nihon Bussan",
    [0x9B] = "Tecmo",
    [0x9C] = "Imagineer",
    [0x9D] = "Banpresto",
    [0x9F] = "Nova",
    [0xA1] = "Hori Electric",
    [0xA2] = "Bandai",
    [0xA4] = "Konami",
    [0xA6] = "Kawada",
    [0xA7] = "Takara",
    [0xA9] = "Technos Japan",
    [0xAA] = "Broderbund",
    [0xAC] = "Toei Animation",
    [0xAD] = "Toho",
    [0xAF] = "Namco",
    [0xB0] = "Acclaim Entertainment",
    [0xB1] = "ASCII Corporation or Nexsoft",
    [0xB2] = "Bandai",
    [0xB4] = "Square Enix",
    [0xB6] = "HAL Laboratory",
    [0xB7] = "SNK",
    [0xB9] = "Pony Canyon",
    [0xBA] = "Culture Brain",
    [0xBB] = "Sunsoft",
    [0xBD] = "Sony Imagesoft",
    [0xBF] = "Sammy Corporation",
    [0xC0] = "Taito",
    [0xC2] = "Kemco",
    [0xC3] = "Square",
    [0xC4] = "Tokuma Shoten",
    [0xC5] = "Data East",
    [0xC6] = "Tonkin House",
    [0xC8] = "Koei",
    [0xC9] = "UFL",
    [0xCA] = "Ultra Games",
    [0xCB] = "VAP, Inc.",
    [0xCC] = "Use Corporation",
    [0xCD] = "Meldac",
    [0xCE] = "Pony Canyon",
    [0xCF] = "Angel",
    [0xD0] = "Taito",
    [0xD1] = "SOFEL (Software Engineering Lab)",
    [0xD2] = "Quest",
    [0xD3] = "Sigma Enterprises",
    [0xD4] = "ASK Kodansha Co.",
    [0xD6] = "Naxat Soft14",
    [0xD7] = "Copya System",
    [0xD9] = "Banpresto",
    [0xDA] = "Tomy",
    [0xDB] = "LJN",
    [0xDD] = "Nippon Computer Systems",
    [0xDE] = "Human Ent.",
    [0xDF] = "Altron",
    [0xE0] = "Jaleco",
    [0xE1] = "Towa Chiki",
    [0xE2] = "Yutaka # Needs more info",
    [0xE3] = "Varie",
    [0xE5] = "Epoch",
    [0xE7] = "Athena",
    [0xE8] = "Asmik Ace Entertainment",
    [0xE9] = "Natsume",
    [0xEA] = "King Records",
    [0xEB] = "Atlus",
    [0xEC] = "Epic/Sony Records",
    [0xEE] = "IGS",
    [0xF0] = "A Wave",
    [0xF3] = "Extreme Entertainment",
    [0xFF] = "LJN"
};

static const char * cart_type[] = {
    [0x00] = "ROM ONLY",
    [0x01] = "MBC1",
    [0x02] = "MBC1+RAM",
    [0x03] = "MBC1+RAM+BATTERY",
    [0x05] = "MBC2",
    [0x06] = "MBC2+BATTERY",
    [0x08] = "ROM+RAM 9",
    [0x09] = "ROM+RAM+BATTERY 9",
    [0x0B] = "MMM01",
    [0x0C] = "MMM01+RAM",
    [0x0D] = "MMM01+RAM+BATTERY",
    [0x0F] = "MBC3+TIMER+BATTERY",
    [0x10] = "MBC3+TIMER+RAM+BATTERY 10",
    [0x11] = "MBC3",
    [0x12] = "MBC3+RAM 10",
    [0x13] = "MBC3+RAM+BATTERY 10",
    [0x19] = "MBC5",
    [0x1A] = "MBC5+RAM",
    [0x1B] = "MBC5+RAM+BATTERY",
    [0x1C] = "MBC5+RUMBLE",
    [0x1D] = "MBC5+RUMBLE+RAM",
    [0x1E] = "MBC5+RUMBLE+RAM+BATTERY",
    [0x20] = "MBC6",
    [0x22] = "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
    [0xFC] = "POCKET CAMERA",
    [0xFD] = "BANDAI TAMA5",
    [0xFE] = "HuC3",
    [0xFF] = "HuC1+RAM+BATTERY"
};


CART load_cart(char * cartName){

    unsigned char ch;

    size_t sz;

    char newCode[3] = "00";

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
        // extracting rom title
        if(i >= 0x134 && i < 0x143 ){

            cart.Title[str] = ch;
            str++;
        }

        // if(i < 0x14F)
        //     printf("%d ", ch);
        cart.roms_data[i] = ch;
    }
    // extracting rom header details
    cart.cgb = cart.roms_data[0x143];
    newCode[0] = cart.roms_data[0x144];
    newCode[1] = cart.roms_data[0x145];    
    cart.type = cart.roms_data[0x147];
    cart.size = cart.roms_data[0x148];
    cart.manif = cart.roms_data[0x14B];

    // calculate the header checksum
    u8 checksum = 0;
    for (u16 address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - cart.roms_data[address] - 1;
    }

    // printing the header
    printf("-------header----------------\n"); 
    printf("file size : %ld\n", sz);
    printf("Title: %s\n", cart.Title);
    printf("cgb: %x\n", cart.cgb);
    printf("manufacturer: %s %02x\n", cart.manif  == 0x33 ? "rom using new code" : getmanif[cart.manif], cart.manif );
    printf("New Code: %c%c\n", newCode[0], newCode[1]);
    printf("cart_type: %s %02x\n", cart_type[cart.type],cart.type);
    printf("rom_size: %dkib\t%d\n", 32 * (1 << cart.size), cart.size);
    printf("checksum_value : %x\n", cart.roms_data[0x14D]);
    printf("Checksum_calc : %x %s\n", checksum,checksum == cart.roms_data[0x14D] ? "good" : "bad");
    // printf("op : %x %x\n", cart.roms_data[0x28b], cart.roms_data[(u16) (cart.roms_data[0x0102] | (cart.roms_data[0x0103] << 8)) + 1]);
    printf("------------------------------\n"); 
    return cart;
}