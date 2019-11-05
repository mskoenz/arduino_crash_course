// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.10.2013 01:06:06 CEST
// File:    keys_n_chars.hpp

#ifndef __KEYS_N_CHARS_HEADER
#define __KEYS_N_CHARS_HEADER

namespace glob {
    uint8_t const up = 1;
    uint8_t const down = 2;
    uint8_t const on = 4;
    uint8_t const shift = 6;
    uint8_t const gui = 5;
    uint8_t const alt = 3;
    uint8_t const ctrl = 7;
    
    uint8_t tier[3] = {130, 131, 132};
}//end namespace glob

byte up[8] = {
  0b00000
, 0b00100
, 0b01110
, 0b10101
, 0b00100
, 0b00100
, 0b00100
, 0b00000
};
byte down[8] = {
  0b00000
, 0b00100
, 0b00100
, 0b00100
, 0b10101
, 0b01110
, 0b00100
, 0b00000
};
byte on[8] = {
  0b00000
, 0b00100
, 0b00100
, 0b10101
, 0b10101
, 0b10001
, 0b01110
, 0b00000
};
byte shift[8] = {
  0b00100
, 0b01010
, 0b10001
, 0b11011
, 0b01010
, 0b01010
, 0b01110
, 0b00000
};
byte gui[8] = {
  0b00000
, 0b00000
, 0b10001
, 0b01110
, 0b01010
, 0b01110
, 0b10001
, 0b00000
};
byte alt_custom[8] = {
  0b00000
, 0b00000
, 0b00000
, 0b11011
, 0b00100
, 0b00011
, 0b00000
, 0b00000
};
byte ctrl[8] = {
  0b00000
, 0b00000
, 0b00100
, 0b01010
, 0b10001
, 0b00000
, 0b00000
, 0b00000
};

namespace progmem {
    
    char buffer[7];
    
    prog_char const n00[] PROGMEM = "none  ";
    prog_char const n01[] PROGMEM = "      ";
    prog_char const n02[] PROGMEM = "      ";
    prog_char const n03[] PROGMEM = "      ";
    prog_char const n04[] PROGMEM = "key A ";
    prog_char const n05[] PROGMEM = "key B ";
    prog_char const n06[] PROGMEM = "key C ";
    prog_char const n07[] PROGMEM = "key D ";
    prog_char const n08[] PROGMEM = "key E ";
    prog_char const n09[] PROGMEM = "key F ";
    prog_char const n10[] PROGMEM = "key G ";
    prog_char const n11[] PROGMEM = "key H ";
    prog_char const n12[] PROGMEM = "key I ";
    prog_char const n13[] PROGMEM = "key J ";
    prog_char const n14[] PROGMEM = "key K ";
    prog_char const n15[] PROGMEM = "key L ";
    prog_char const n16[] PROGMEM = "key M ";
    prog_char const n17[] PROGMEM = "key N ";
    prog_char const n18[] PROGMEM = "key O ";
    prog_char const n19[] PROGMEM = "key P ";
    prog_char const n20[] PROGMEM = "key Q ";
    prog_char const n21[] PROGMEM = "key R ";
    prog_char const n22[] PROGMEM = "key S ";
    prog_char const n23[] PROGMEM = "key T ";
    prog_char const n24[] PROGMEM = "key U ";
    prog_char const n25[] PROGMEM = "key V ";
    prog_char const n26[] PROGMEM = "key W ";
    prog_char const n27[] PROGMEM = "key X ";
    prog_char const n28[] PROGMEM = "key Z ";
    prog_char const n29[] PROGMEM = "key Y ";
    prog_char const n30[] PROGMEM = "key 1 ";
    prog_char const n31[] PROGMEM = "key 2 ";
    prog_char const n32[] PROGMEM = "key 3 ";
    prog_char const n33[] PROGMEM = "key 4 ";
    prog_char const n34[] PROGMEM = "key 5 ";
    prog_char const n35[] PROGMEM = "key 6 ";
    prog_char const n36[] PROGMEM = "key 7 ";
    prog_char const n37[] PROGMEM = "key 8 ";
    prog_char const n38[] PROGMEM = "key 9 ";
    prog_char const n39[] PROGMEM = "key 0 ";
    prog_char const n40[] PROGMEM = "enter ";
    prog_char const n41[] PROGMEM = "escape";
    prog_char const n42[] PROGMEM = "backSp";
    prog_char const n43[] PROGMEM = "tab   ";
    prog_char const n44[] PROGMEM = "space ";
    prog_char const n45[] PROGMEM = "key ' ";
    prog_char const n46[] PROGMEM = "key ^ ";
    prog_char const n47[] PROGMEM = {'k','e','y',' ',(char)245, ' ', 0};
    prog_char const n48[] PROGMEM = "key ! ";
    prog_char const n49[] PROGMEM = "no key ";
    prog_char const n50[] PROGMEM = "key $ ";
    prog_char const n51[] PROGMEM = {'k','e','y',' ',(char)239, ' ', 0};
    prog_char const n52[] PROGMEM = {'k','e','y',' ',(char)225, ' ', 0};
    prog_char const n53[] PROGMEM = {'k','e','y',' ',(char)223, ' ', 0};
    prog_char const n54[] PROGMEM = "key , ";
    prog_char const n55[] PROGMEM = "key . ";
    prog_char const n56[] PROGMEM = "key - ";
    prog_char const n57[] PROGMEM = "caps  ";
    prog_char const n58[] PROGMEM = "F1    ";
    prog_char const n59[] PROGMEM = "F2    ";
    prog_char const n60[] PROGMEM = "F3    ";
    prog_char const n61[] PROGMEM = "F4    ";
    prog_char const n62[] PROGMEM = "F5    ";
    prog_char const n63[] PROGMEM = "F6    ";
    prog_char const n64[] PROGMEM = "F7    ";
    prog_char const n65[] PROGMEM = "F8    ";
    prog_char const n66[] PROGMEM = "F9    ";
    prog_char const n67[] PROGMEM = "F10   ";
    prog_char const n68[] PROGMEM = "F11   ";
    prog_char const n69[] PROGMEM = "F12   ";
    prog_char const n70[] PROGMEM = "prtScr";
    prog_char const n71[] PROGMEM = "sclLck";
    prog_char const n72[] PROGMEM = "pause ";
    prog_char const n73[] PROGMEM = "insert";
    prog_char const n74[] PROGMEM = "home  ";
    prog_char const n75[] PROGMEM = "pgUp  ";
    prog_char const n76[] PROGMEM = "delete";
    prog_char const n77[] PROGMEM = "end   ";
    prog_char const n78[] PROGMEM = "pgDown";
    prog_char const n79[] PROGMEM = {'a','r','r','o','w', 126, 0};
    prog_char const n80[] PROGMEM = {'a','r','r','o','w', 127, 0};
    prog_char const n81[] PROGMEM = {'a','r','r','o','w', glob::down, 0};
    prog_char const n82[] PROGMEM = {'a','r','r','o','w', glob::up, 0};
    prog_char const n83[] PROGMEM = "numLck";
    prog_char const n84[] PROGMEM = "pad / ";
    prog_char const n85[] PROGMEM = "pad * ";
    prog_char const n86[] PROGMEM = "pad - ";
    prog_char const n87[] PROGMEM = "pad + ";
    prog_char const n88[] PROGMEM = "padEtr";
    prog_char const n89[] PROGMEM = "pad 1 ";
    prog_char const n90[] PROGMEM = "pad 2 ";
    prog_char const n91[] PROGMEM = "pad 3 ";
    prog_char const n92[] PROGMEM = "pad 4 ";
    prog_char const n93[] PROGMEM = "pad 5 ";
    prog_char const n94[] PROGMEM = "pad 6 ";
    prog_char const n95[] PROGMEM = "pad 7 ";
    prog_char const n96[] PROGMEM = "pad 8 ";
    prog_char const n97[] PROGMEM = "pad 9 ";
    prog_char const n98[] PROGMEM = "pad 0 ";
    prog_char const n99[] PROGMEM = "pad . ";
    prog_char const n100[] PROGMEM = "key < ";
    prog_char const n101[] PROGMEM = "apps  ";
    prog_char const n102[] PROGMEM = {'k', 'e', 'y', ' ', glob::on, ' ', 0};
    prog_char const n103[] PROGMEM = "pad = ";
    prog_char const n104[] PROGMEM = "F13   ";
    prog_char const n105[] PROGMEM = "F14   ";
    prog_char const n106[] PROGMEM = "F15   ";
    prog_char const n107[] PROGMEM = "F16   ";
    prog_char const n108[] PROGMEM = "F17   ";
    prog_char const n109[] PROGMEM = "F18   ";
    prog_char const n110[] PROGMEM = "F19   ";
    prog_char const n111[] PROGMEM = "F20   ";
    prog_char const n112[] PROGMEM = "F21   ";
    prog_char const n113[] PROGMEM = "F22   ";
    prog_char const n114[] PROGMEM = "F23   ";
    prog_char const n115[] PROGMEM = "F24   ";
    prog_char const n127[] PROGMEM = "Mute  ";
    prog_char const n128[] PROGMEM = {'V','o','l',' ', glob::up,' ', 0};;
    prog_char const n129[] PROGMEM = {'V','o','l',' ', glob::down,' ', 0};;
    
    prog_char const n130[] PROGMEM = "tier 0";
    prog_char const n131[] PROGMEM = "tier 1";
    prog_char const n132[] PROGMEM = "tier 2";
    
    prog_char const m00[] PROGMEM = {' ', ' ', ' ', ' ', ' ', ' ', 0};
    prog_char const m01[] PROGMEM = {' ', ' ', glob::ctrl, ' ', ' ', ' ', 0};
    prog_char const m02[] PROGMEM = {' ', ' ', glob::shift, ' ', ' ', ' ', 0};
    prog_char const m03[] PROGMEM = {' ', glob::shift, ' ', glob::ctrl, ' ', ' ', 0};
    prog_char const m04[] PROGMEM = {' ', ' ', glob::alt, ' ', ' ', ' ', 0};
    prog_char const m05[] PROGMEM = {' ', glob::alt, ' ', glob::ctrl, ' ', ' ', 0};
    prog_char const m06[] PROGMEM = {' ', glob::alt, ' ', glob::shift, ' ', ' ', 0};
    prog_char const m07[] PROGMEM = {glob::alt, ' ', glob::shift, ' ', glob::ctrl, ' ', 0};
    prog_char const m08[] PROGMEM = {' ', ' ', glob::gui, ' ', ' ', ' ', 0};
    prog_char const m09[] PROGMEM = {' ', glob::gui, ' ', glob::ctrl, ' ', ' ', 0};
    prog_char const m10[] PROGMEM = {' ', glob::gui, ' ', glob::shift, ' ', ' ', 0};
    prog_char const m11[] PROGMEM = {glob::gui, ' ', glob::shift, ' ', glob::ctrl, ' ', 0};
    prog_char const m12[] PROGMEM = {' ', glob::gui, ' ', glob::alt, ' ', ' ', 0};
    prog_char const m13[] PROGMEM = {glob::gui, ' ', glob::alt, ' ', glob::ctrl, ' ', 0};
    prog_char const m14[] PROGMEM = {glob::gui, ' ', glob::alt, ' ', glob::shift, ' ', 0};
    prog_char const m15[] PROGMEM = {' ', glob::gui, glob::alt, glob::shift, glob::ctrl, ' ', 0};
    
    char const * const str_key[] PROGMEM = {
          n00, n01, n02, n03, n04, n05, n06, n07, n08, n09
        , n10, n11, n12, n13, n14, n15, n16, n17, n18, n19
        , n20, n21, n22, n23, n24, n25, n26, n27, n28, n29
        , n30, n31, n32, n33, n34, n35, n36, n37, n38, n39
        , n40, n41, n42, n43, n44, n45, n46, n47, n48, n49
        , n50, n51, n52, n53, n54, n55, n56, n57, n58, n59
        , n60, n61, n62, n63, n64, n65, n66, n67, n68, n69
        , n70, n71, n72, n73, n74, n75, n76, n77, n78, n79
        , n80, n81, n82, n83, n84, n85, n86, n87, n88, n89
        , n90, n91, n92, n93, n94, n95, n96, n97, n98, n99
        , n100,n101,n102,n103,n104,n105,n106,n107,n108,n109
        , n110,n111,n112,n113,n114,n115,n127,n128,n129,n130
        , n131,n132
    };
    
    char const * const str_mod[] PROGMEM = {
          m00, m01, m02, m03, m04, m05, m06, m07, m08, m09
        , m10, m11, m12, m13, m14, m15
    };
}//end namespace progmem

char * key_name(uint8_t i) {
    if(i > 126)
        i -= 11;
    strcpy_P(progmem::buffer, (char*)pgm_read_word(&progmem::str_key[i]));
    return progmem::buffer;
}
char * mod_name(uint8_t const & i) {
    strcpy_P(progmem::buffer, (char*)pgm_read_word(&progmem::str_mod[i]));
    return progmem::buffer;
}

#endif //__KEYS_N_CHARS_HEADER
