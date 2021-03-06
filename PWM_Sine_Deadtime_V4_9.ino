 //----------------------------------------------------------------------------------------------
// 3 - Phase Motor Driver using Arduino Mega
// Look-up tables used to create the Sine Waves
// Switch 1 selects the Motor Speed
// Switch 2 selects the Direction of the Motor
// POT = A0
// U1 = pin 6 Arduino Mega high side, U2 = pin 7 Arduino Mega low side
// V1 = 5 V2 = 2
// W1 = 11 W2 = 12
// Reverse the Look-up table to Reverse the motor direction !
// Added STOP/FORWARD/REVERSE feature to the RHS switch
// Added Speed control pot, to change speed in Manual mode position 1
// Author: Kash Patel
// Tested 24/06/2021
//---------------------------------------------------------------------------------------------------
int potVal = 0; // pot value for analog read
int finalVal = 0; // motor revised 0-12 Value
#define trimPot A0 // motor control 
int i=0;

int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorPin = A0;  
    int counter=0;
    int counter2=0;
    int setting=1;
    int setting2=1;
    int directionx=0;
int buttonState1 = 0;  
int buttonState2 = 0;  
int buttonPin1 = 14; // On/Off LHS
int buttonPin2 = 15; //Pin 15 = RHS Speed Button

//Unsigned Long
const uint16_t Datadeg0[] = {128, 128,  129,  130,  130,  131,  132,  132,  133,  134,  134,  135,  136,  137,  137,  138,  139,  139,  140,  141,  141,  142,  143,  143,  144,  145,
                             145,  146,  147,  148,  148,  149,  150,  150,  151,  152,  152,  153,  154,  154,  155,  156,  156,  157,  158,  158,  159,  160,  160,  161,  162,  162,  163,  164,  164,  165,  166,
                             166,  167,  168,  168,  169,  169,  170,  171,  171,  172,  173,  173,  174,  175,  175,  176,  176,  177,  178,  178,  179,  180,  180,  181,  181,  182,  183,  183,  184,  184,  185,
                             186,  186,  187,  187,  188,  189,  189,  190,  190,  191,  192,  192,  193,  193,  194,  194,  195,  196,  196,  197,  197,  198,  198,  199,  199,  200,  200,  201,  201,  202,  203,
                             203,  204,  204,  205,  205,  206,  206,  207,  207,  208,  208,  209,  209,  210,  210,  211,  211,  212,  212,  212,  213,  213,  214,  214,  215,  215,  216,  216,  217,  217,  217,
                             218,  218,  219,  219,  220,  220,  220,  221,  221,  222,  222,  222,  223,  223,  223,  224,  224,  225,  225,  225,  226,  226,  226,  227,  227,  227,  228,  228,  228,  229,  229,
                             229,  230,  230,  230,  231,  231,  231,  232,  232,  232,  232,  233,  233,  233,  234,  234,  234,  234,  235,  235,  235,  235,  236,  236,  236,  236,  236,  237,  237,  237,  237,
                             237,  238,  238,  238,  238,  238,  239,  239,  239,  239,  239,  239,  240,  240,  240,  240,  240,  240,  240,  240,  241,  241,  241,  241,  241,  241,  241,  241,  241,  241,  242,
                             242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
                             242,  242,  242,  242,  242,  241,  241,  241,  241,  241,  241,  241,  241,  241,  241,  240,  240,  240,  240,  240,  240,  240,  240,  239,  239,  239,  239,  239,  239,  238,  238,
                             238,  238,  238,  237,  237,  237,  237,  237,  236,  236,  236,  236,  236,  235,  235,  235,  235,  234,  234,  234,  234,  233,  233,  233,  232,  232,  232,  232,  231,  231,  231,
                             230,  230,  230,  229,  229,  229,  228,  228,  228,  227,  227,  227,  226,  226,  226,  225,  225,  225,  224,  224,  223,  223,  223,  222,  222,  222,  221,  221,  220,  220,  220,
                             219,  219,  218,  218,  217,  217,  217,  216,  216,  215,  215,  214,  214,  213,  213,  212,  212,  212,  211,  211,  210,  210,  209,  209,  208,  208,  207,  207,  206,  206,  205,
                             205,  204,  204,  203,  203,  202,  201,  201,  200,  200,  199,  199,  198,  198,  197,  197,  196,  196,  195,  194,  194,  193,  193,  192,  192,  191,  190,  190,  189,  189,  188,
                             187,  187,  186,  186,  185,  184,  184,  183,  183,  182,  181,  181,  180,  180,  179,  178,  178,  177,  176,  176,  175,  175,  174,  173,  173,  172,  171,  171,  170,  169,  169,
                             168,  168,  167,  166,  166,  165,  164,  164,  163,  162,  162,  161,  160,  160,  159,  158,  158,  157,  156,  156,  155,  154,  154,  153,  152,  152,  151,  150,  150,  149,  148,
                             148,  147,  146,  145,  145,  144,  143,  143,  142,  141,  141,  140,  139,  139,  138,  137,  137,  136,  135,  134,  134,  133,  132,  132,  131,  130,  130,  129,  128,  128,  127,
                             126,  125,  125,  124,  123,  123,  122,  121,  121,  120,  119,  118,  118,  117,  116,  116,  115,  114,  114,  113,  112,  112,  111,  110,  110,  109,  108,  107,  107,  106,  105,
                             105,  104,  103,  103,  102,  101,  101,  100,  99, 99, 98, 97, 97, 96, 95, 95, 94, 93, 93, 92, 91, 91, 90, 89, 89, 88, 87, 87, 86, 86, 85, 84, 84, 83, 82, 82, 81, 80, 80, 79, 79, 78, 77,
                             77, 76, 75, 75, 74, 74, 73, 72, 72, 71, 71, 70, 69, 69, 68, 68, 67, 66, 66, 65, 65, 64, 63, 63, 62, 62, 61, 61, 60, 59, 59, 58, 58, 57, 57, 56, 56, 55, 55, 54, 54, 53, 52, 52, 51, 51, 50,
                             50, 49, 49, 48, 48, 47, 47, 46, 46, 45, 45, 44, 44, 43, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 38, 38, 38, 37, 37, 36, 36, 35, 35, 35, 34, 34, 33, 33, 33, 32, 32, 32, 31, 31, 30, 30, 30,
                             29, 29, 29, 28, 28, 28, 27, 27, 27, 26, 26, 26, 25, 25, 25, 24, 24, 24, 23, 23, 23, 23, 22, 22, 22, 21, 21, 21, 21, 20, 20, 20, 20, 19, 19, 19, 19, 19, 18, 18, 18, 18, 18, 17, 17, 17, 17,
                             17, 16, 16, 16, 16, 16, 16, 15, 15, 15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
                             13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 18, 18, 18,
                             18, 18, 19, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 32, 32,
                             32, 33, 33, 33, 34, 34, 35, 35, 35, 36, 36, 37, 37, 38, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 54,
                             54, 55, 55, 56, 56, 57, 57, 58, 58, 59, 59, 60, 61, 61, 62, 62, 63, 63, 64, 65, 65, 66, 66, 67, 68, 68, 69, 69, 70, 71, 71, 72, 72, 73, 74, 74, 75, 75, 76, 77, 77, 78, 79, 79, 80, 80, 81,
                             82, 82, 83, 84, 84, 85, 86, 86, 87, 87, 88, 89, 89, 90, 91, 91, 92, 93, 93, 94, 95, 95, 96, 97, 97, 98, 99, 99, 100,  101,  101,  102,  103,  103,  104,  105,  105,  106,  107,  107,  108,
                             109,  110,  110,  111,  112,  112,  113,  114,  114,  115,  116,  116,  117,  118,  118,  119,  120,  121,  121,  122,  123,  123,  124,  125,  125,  126,  127,  128
                            };

const uint16_t Datadeg120[] = {227,  226,  226,  226,  225,  225,  225,  224,  224,  223,  223,  223,  222,  222,  222,  221,  221,  220,  220,  220,  219,  219,  218,  218,  217,  217,
                               217,  216,  216,  215,  215,  214,  214,  213,  213,  212,  212,  212,  211,  211,  210,  210,  209,  209,  208,  208,  207,  207,  206,  206,  205,  205,  204,  204,  203,  203,  202,
                               201,  201,  200,  200,  199,  199,  198,  198,  197,  197,  196,  196,  195,  194,  194,  193,  193,  192,  192,  191,  190,  190,  189,  189,  188,  187,  187,  186,  186,  185,  184,
                               184,  183,  183,  182,  181,  181,  180,  180,  179,  178,  178,  177,  176,  176,  175,  175,  174,  173,  173,  172,  171,  171,  170,  169,  169,  168,  168,  167,  166,  166,  165,
                               164,  164,  163,  162,  162,  161,  160,  160,  159,  158,  158,  157,  156,  156,  155,  154,  154,  153,  152,  152,  151,  150,  150,  149,  148,  148,  147,  146,  145,  145,  144,
                               143,  143,  142,  141,  141,  140,  139,  139,  138,  137,  137,  136,  135,  134,  134,  133,  132,  132,  131,  130,  130,  129,  128,  128,  127,  126,  125,  125,  124,  123,  123,
                               122,  121,  121,  120,  119,  118,  118,  117,  116,  116,  115,  114,  114,  113,  112,  112,  111,  110,  110,  109,  108,  107,  107,  106,  105,  105,  104,  103,  103,  102,  101,
                               101,  100,  99, 99, 98, 97, 97, 96, 95, 95, 94, 93, 93, 92, 91, 91, 90, 89, 89, 88, 87, 87, 86, 86, 85, 84, 84, 83, 82, 82, 81, 80, 80, 79, 79, 78, 77, 77, 76, 75, 75, 74, 74, 73, 72, 72,
                               71, 71, 70, 69, 69, 68, 68, 67, 66, 66, 65, 65, 64, 63, 63, 62, 62, 61, 61, 60, 59, 59, 58, 58, 57, 57, 56, 56, 55, 55, 54, 54, 53, 52, 52, 51, 51, 50, 50, 49, 49, 48, 48, 47, 47, 46, 46,
                               45, 45, 44, 44, 43, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 38, 38, 38, 37, 37, 36, 36, 35, 35, 35, 34, 34, 33, 33, 33, 32, 32, 32, 31, 31, 30, 30, 30, 29, 29, 29, 28, 28, 28, 27, 27, 27,
                               26, 26, 26, 25, 25, 25, 24, 24, 24, 23, 23, 23, 23, 22, 22, 22, 21, 21, 21, 21, 20, 20, 20, 20, 19, 19, 19, 19, 19, 18, 18, 18, 18, 18, 17, 17, 17, 17, 17, 16, 16, 16, 16, 16, 16, 15, 15,
                               15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
                               13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 20, 20,
                               20, 20, 21, 21, 21, 21, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 32, 32, 32, 33, 33, 33, 34, 34, 35, 35, 35,
                               36, 36, 37, 37, 38, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 54, 54, 55, 55, 56, 56, 57, 57, 58, 58,
                               59, 59, 60, 61, 61, 62, 62, 63, 63, 64, 65, 65, 66, 66, 67, 68, 68, 69, 69, 70, 71, 71, 72, 72, 73, 74, 74, 75, 75, 76, 77, 77, 78, 79, 79, 80, 80, 81, 82, 82, 83, 84, 84, 85, 86, 86, 87,
                               87, 88, 89, 89, 90, 91, 91, 92, 93, 93, 94, 95, 95, 96, 97, 97, 98, 99, 99, 100,  101,  101,  102,  103,  103,  104,  105,  105,  106,  107,  107,  108,  109,  110,  110,  111,  112,
                               112, 113,  114,  114,  115,  116,  116,  117,  118,  118,  119,  120,  121,  121,  122,  123,  123,  124,  125,  125,  126,  127,  128,  128,  128,  129,  130,  130,  131,  132,  132,
                               133,  134,  134,  135,  136,  137,  137,  138,  139,  139,  140,  141,  141,  142,  143,  143,  144,  145,  145,  146,  147,  148,  148,  149,  150,  150,  151,  152,  152,  153,  154,
                               154,  155,  156,  156,  157,  158,  158,  159,  160,  160,  161,  162,  162,  163,  164,  164,  165,  166,  166,  167,  168,  168,  169,  169,  170,  171,  171,  172,  173,  173,  174,
                               175,  175,  176,  176,  177,  178,  178,  179,  180,  180,  181,  181,  182,  183,  183,  184,  184,  185,  186,  186,  187,  187,  188,  189,  189,  190,  190,  191,  192,  192,  193,
                               193,  194,  194,  195,  196,  196,  197,  197,  198,  198,  199,  199,  200,  200,  201,  201,  202,  203,  203,  204,  204,  205,  205,  206,  206,  207,  207,  208,  208,  209,  209,
                               210,  210,  211,  211,  212,  212,  212,  213,  213,  214,  214,  215,  215,  216,  216,  217,  217,  217,  218,  218,  219,  219,  220,  220,  220,  221,  221,  222,  222,  222,  223,
                               223,  223,  224,  224,  225,  225,  225,  226,  226,  226,  227,  227,  227,  228,  228,  228,  229,  229,  229,  230,  230,  230,  231,  231,  231,  232,  232,  232,  232,  233,  233,
                               233,  234,  234,  234,  234,  235,  235,  235,  235,  236,  236,  236,  236,  236,  237,  237,  237,  237,  237,  238,  238,  238,  238,  238,  239,  239,  239,  239,  239,  239,  240,
                               240,  240,  240,  240,  240,  240,  240,  241,  241,  241,  241,  241,  241,  241,  241,  241,  241,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
                               242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  241,  241,  241,  241,  241,  241,  241,  241,
                               241,  241,  240,  240,  240,  240,  240,  240,  240,  240,  239,  239,  239,  239,  239,  239,  238,  238,  238,  238,  238,  237,  237,  237,  237,  237,  236,  236,  236,  236,  236,
                               235,  235,  235,  235,  234,  234,  234,  234,  233,  233,  233,  232,  232,  232,  232,  231,  231,  231,  230,  230,  230,  229,  229,  229,  228,  228,  228,  227,  227
                              };

const uint16_t Datadeg240[] = {28,  28, 27, 27, 27, 26, 26, 26, 25, 25, 25, 24, 24, 24, 23, 23, 23, 23, 22, 22, 22, 21, 21, 21, 21, 20, 20, 20, 20, 19, 19, 19, 19, 19, 18, 18, 18, 18,
                               18, 17, 17, 17, 17, 17, 16, 16, 16, 16, 16, 16, 15, 15, 15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
                               13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 17,
                               17, 17, 17, 17, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29,
                               29, 30, 30, 30, 31, 31, 32, 32, 32, 33, 33, 33, 34, 34, 35, 35, 35, 36, 36, 37, 37, 38, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 48, 49,
                               49, 50, 50, 51, 51, 52, 52, 53, 54, 54, 55, 55, 56, 56, 57, 57, 58, 58, 59, 59, 60, 61, 61, 62, 62, 63, 63, 64, 65, 65, 66, 66, 67, 68, 68, 69, 69, 70, 71, 71, 72, 72, 73, 74, 74, 75,
                               75, 76, 77, 77, 78, 79, 79, 80, 80, 81, 82, 82, 83, 84, 84, 85, 86, 86, 87, 87, 88, 89, 89, 90, 91, 91, 92, 93, 93, 94, 95, 95, 96, 97, 97, 98, 99, 99, 100,  101,  101,  102,  103,  103,
                               104,  105,  105,  106,  107,  107,  108,  109,  110,  110,  111,  112,  112,  113,  114,  114,  115,  116,  116,  117,  118,  118,  119,  120,  121,  121,  122,  123,  123,  124,  125,
                               125,  126,  127,  128,  128,  128,  129,  130,  130,  131,  132,  132,  133,  134,  134,  135,  136,  137,  137,  138,  139,  139,  140,  141,  141,  142,  143,  143,  144,  145,  145,
                               146,  147,  148,  148,  149,  150,  150,  151,  152,  152,  153,  154,  154,  155,  156,  156,  157,  158,  158,  159,  160,  160,  161,  162,  162,  163,  164,  164,  165,  166,  166,
                               167,  168,  168,  169,  169,  170,  171,  171,  172,  173,  173,  174,  175,  175,  176,  176,  177,  178,  178,  179,  180,  180,  181,  181,  182,  183,  183,  184,  184,  185,  186,
                               186,  187,  187,  188,  189,  189,  190,  190,  191,  192,  192,  193,  193,  194,  194,  195,  196,  196,  197,  197,  198,  198,  199,  199,  200,  200,  201,  201,  202,  203,  203,
                               204,  204,  205,  205,  206,  206,  207,  207,  208,  208,  209,  209,  210,  210,  211,  211,  212,  212,  212,  213,  213,  214,  214,  215,  215,  216,  216,  217,  217,  217,  218,
                               218,  219,  219,  220,  220,  220,  221,  221,  222,  222,  222,  223,  223,  223,  224,  224,  225,  225,  225,  226,  226,  226,  227,  227,  227,  228,  228,  228,  229,  229,  229,
                               230,  230,  230,  231,  231,  231,  232,  232,  232,  232,  233,  233,  233,  234,  234,  234,  234,  235,  235,  235,  235,  236,  236,  236,  236,  236,  237,  237,  237,  237,  237,
                               238,  238,  238,  238,  238,  239,  239,  239,  239,  239,  239,  240,  240,  240,  240,  240,  240,  240,  240,  241,  241,  241,  241,  241,  241,  241,  241,  241,  241,  242,  242,
                               242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
                               242,  242,  242,  242,  241,  241,  241,  241,  241,  241,  241,  241,  241,  241,  240,  240,  240,  240,  240,  240,  240,  240,  239,  239,  239,  239,  239,  239,  238,  238,  238,
                               238,  238,  237,  237,  237,  237,  237,  236,  236,  236,  236,  236,  235,  235,  235,  235,  234,  234,  234,  234,  233,  233,  233,  232,  232,  232,  232,  231,  231,  231,  230,
                               230,  230,  229,  229,  229,  228,  228,  228,  227,  227,  227,  226,  226,  226,  225,  225,  225,  224,  224,  223,  223,  223,  222,  222,  222,  221,  221,  220,  220,  220,  219,
                               219,  218,  218,  217,  217,  217,  216,  216,  215,  215,  214,  214,  213,  213,  212,  212,  212,  211,  211,  210,  210,  209,  209,  208,  208,  207,  207,  206,  206,  205,  205,
                               204,  204,  203,  203,  202,  201,  201,  200,  200,  199,  199,  198,  198,  197,  197,  196,  196,  195,  194,  194,  193,  193,  192,  192,  191,  190,  190,  189,  189,  188,  187,
                               187,  186,  186,  185,  184,  184,  183,  183,  182,  181,  181,  180,  180,  179,  178,  178,  177,  176,  176,  175,  175,  174,  173,  173,  172,  171,  171,  170,  169,  169,  168,
                               168,  167,  166,  166,  165,  164,  164,  163,  162,  162,  161,  160,  160,  159,  158,  158,  157,  156,  156,  155,  154,  154,  153,  152,  152,  151,  150,  150,  149,  148,  148,
                               147,  146,  145,  145,  144,  143,  143,  142,  141,  141,  140,  139,  139,  138,  137,  137,  136,  135,  134,  134,  133,  132,  132,  131,  130,  130,  129,  128,  128,  127,  126,
                               125,  125,  124,  123,  123,  122,  121,  121,  120,  119,  118,  118,  117,  116,  116,  115,  114,  114,  113,  112,  112,  111,  110,  110,  109,  108,  107,  107,  106,  105,  105,
                               104,  103,  103,  102,  101,  101,  100,  99, 99, 98, 97, 97, 96, 95, 95, 94, 93, 93, 92, 91, 91, 90, 89, 89, 88, 87, 87, 86, 86, 85, 84, 84, 83, 82, 82, 81, 80, 80, 79, 79, 78, 77, 77,
                               76, 75, 75, 74, 74, 73, 72, 72, 71, 71, 70, 69, 69, 68, 68, 67, 66, 66, 65, 65, 64, 63, 63, 62, 62, 61, 61, 60, 59, 59, 58, 58, 57, 57, 56, 56, 55, 55, 54, 54, 53, 52, 52, 51, 51, 50,
                               50, 49, 49, 48, 48, 47, 47, 46, 46, 45, 45, 44, 44, 43, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 38, 38, 38, 37, 37, 36, 36, 35, 35, 35, 34, 34, 33, 33, 33, 32, 32, 32, 31, 31, 30, 30,
                               30, 29, 29, 29, 28
                              };
//-------------------------------------------------------------------------------------------------------                              
const uint16_t DatadegStop[] = {00,  00,  00,  00,  00,  00,  00};
void degStopVal(int Low)
{  
  OCR1A = Low; 
  OCR1B = 255;  //255 = Low side drivers OFF
  OCR3A = Low;
  OCR3B = 255;  //255 = Low side drivers OFF
  OCR4A = Low;
  OCR4B = 255;  //255 = Low side drivers OFF
}
//-----------------------------------------------------------------------------------------------------

void deg0Val(int High)
{
  OCR1A = High; // Addition of dead time of 0.46 equating to 0.2% as the range is between 12.75 and 242.45 (5- 95%)
  OCR1B = (High + 2);
}

void deg120Val(int High)
{
  OCR3A = High;
  OCR3B = (High + 2);
}

void deg240Val(int High)
{
  OCR4A = High;
  OCR4B = (High + 2);
}

void potUpdate() {
sensorValue = (float)(analogRead(sensorPin) / 170.5);
}
//------------------------------------------------------------------------------------
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
//-------------------------------------------------------------------------------
void setup()
{
  TCCR4A = 0;
  TCCR4B = 0;
  TCCR4C = 0;
  TCNT4  = 0;

  TCCR3A = 0;
  TCCR3B = 0;
  TCCR3C = 0;
  TCNT3  = 0;

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  ICR4   = 255;      // sets PWM period frequency to 31.25Hz
  ICR3   = 255;
  ICR1   = 255;


  TCCR4A = _BV(WGM41) | _BV(COM4B0) | _BV(COM4B1) | _BV(COM4A1);
  TCCR4B = _BV(WGM43) | _BV(CS40);
  TCCR3A = _BV(WGM31) | _BV(COM3B0) | _BV(COM3B1) | _BV(COM3A1);
  TCCR3B = _BV(WGM33) | _BV(CS30);
  TCCR1A = _BV(WGM11) | _BV(COM1B0) | _BV(COM1B1) | _BV(COM1A1);
  TCCR1B = _BV(WGM13) | _BV(CS10);

  Serial.begin(115200); //115200

  // Set the PWM pin as output.  
  pinMode( 7, OUTPUT); //OCR4B low side U
  pinMode( 6, OUTPUT); //OCR4A high side U
  pinMode( 5, OUTPUT); //OCR3A high side V
  
  pinMode( 2, OUTPUT); //OCR3B low side V
  pinMode( 11, OUTPUT); //OCR1A high side W
  pinMode( 12, OUTPUT); //OCR1B low side W
//------------------------------------------------------------------------------  
{ 
  degStopVal(DatadegStop[0]);   // Stop all outputs    
}  
//-----------------------------------------------------------------------------
   pinMode(buttonPin1, INPUT_PULLUP);   
   pinMode(buttonPin2, INPUT_PULLUP);  
//---------------------------------OLED DISPLAY---------------------------------------  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // Address 0x3D for 128x64
  {    
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Motor  Control");
  display.display(); 
  delay(2000);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Hello  Folks");
  display.display(); 
  delay(2000);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speed:");
  display.print(setting);
  display.setCursor(0, 20);  
  display.print("Stop ");
  display.display(); 
}
 
//================================= MAIN CONTROL LOOP ===================================
void loop()
{  
   buttonState1=digitalRead(buttonPin1);
   if( buttonState1== HIGH)
   { 
//------------------------------CHECK FOR MOTOR STOP POSITION------------------------------
  if ((setting == 1) && (setting2 == 1))
{ 
  degStopVal(DatadegStop[0]);   // Stop all outputs    
}
  if ((setting == 2) && (setting2 == 1))
{ 
  degStopVal(DatadegStop[0]);   // Stop all outputs    
}
  if ((setting == 3) && (setting2 == 1))
{ 
  degStopVal(DatadegStop[0]);   // Stop all outputs    
}
  if ((setting == 4) && (setting2 == 1))
{ 
  degStopVal(DatadegStop[0]);   // Stop all outputs    
}

//------------------------------CHECK THE SPEED SETTING & FORWARD DIRECTION-----------------      
  if ((setting == 1) && (setting2 == 2))
{     
//------------------------ EXTRA CODE TO READ THE POT-------------------------------------- 
      potVal = analogRead(trimPot); 
      potVal = map(potVal, 0, 1023, 1023, 0);
   
      potVal= potVal/10;
      
//    potVal = analogRead(trimPot)/10; // reduce pot sensitivity 
    finalVal = (float)((potVal/0.3)); // 1.5 + 6 calculate potentiometer range 
    for (int H = 0; H < 1040; H++)
        {
          deg0Val(Datadeg0[H]);
          deg120Val(Datadeg120[H]);
          deg240Val(Datadeg240[H]);
          delayMicroseconds(finalVal);          
        }           

  } 
//---------------------------------------------------------------------------------------------   
if ((setting == 2) && (setting2 == 2))
{     
     for (int H = 0; H < 1040; H++)
        {
          deg0Val(Datadeg0[H]);
          deg120Val(Datadeg120[H]);
          deg240Val(Datadeg240[H]);
          delayMicroseconds(50);          
        }           

  }  
//---------------------------------------------------------------------------------------------     
if ((setting == 3) && (setting2 == 2))
{     
     for (int H = 0; H < 1040; H++)
        {
         
          deg0Val(Datadeg0[H]);
          deg120Val(Datadeg120[H]);
          deg240Val(Datadeg240[H]);
          delayMicroseconds(40);          
        }
  }

//---------------------------------------------------------------------------------------------           
if ((setting == 4) && (setting2 == 2))
{     
     for (int H = 0; H < 1040; H++)
        {
         
          deg0Val(Datadeg0[H]);
          deg120Val(Datadeg120[H]);
          deg240Val(Datadeg240[H]);
          delayMicroseconds(30);          // Fastest Speed 33 Hz
        }
  }
  
//----------------------------------------CHECK THE SPEED SETTING & REVERSE DIRECTION------------      
  if ((setting == 1) && (setting2 == 3))
{     
    
     for (int H = 1040; H > 0; H--)
        {
         
          deg0Val(Datadeg0[H]);
          deg120Val(Datadeg120[H]);
          deg240Val(Datadeg240[H]);
          
          delayMicroseconds(60); 
          //speed change 50 = 18hz,35 = 25.8hz (50 - 185 micro) 18= 50Hz, 33=28.5hz, 30 = 29,6hz
          // 29 = 30.7hz , 28 = 33Hz Fastest 
        }      

  } 
//---------------------------------------------------------------------------------------------   
if ((setting == 2) && (setting2 == 3))
{     
     for (int H = 1040; H > 0; H--)
        {
        
          deg0Val(Datadeg0[H]);
          deg120Val(Datadeg120[H]);
          deg240Val(Datadeg240[H]);
          
          delayMicroseconds(50);          
        }           

  }  
//---------------------------------------------------------------------------------------------     
if ((setting == 3) && (setting2 == 3))
{     
     for (int H = 1040; H > 0; H--)
        {
         
          deg0Val(Datadeg0[H]);
          deg120Val(Datadeg120[H]);
          deg240Val(Datadeg240[H]);      
          
          delayMicroseconds(40);          
        }
  }

//---------------------------------------------------------------------------------------------           
if ((setting == 4) && (setting2 == 3))
{     
     for (int H = 1040; H > 0; H--)
        {
         
          deg120Val(Datadeg120[H]);
          deg240Val(Datadeg240[H]);
          deg0Val(Datadeg0[H]);
          
          delayMicroseconds(30);          // Fastest Speed 33 Hz
        }
  }  
}
//----------------------------SPEED SETTING-------------------------------------     
else 
  {
     counter = (counter + 1); // Switch Debounce 10k loops
     if (counter >= 5000)
  {
     counter=0;
    (setting = setting +1);
    if (setting>=5)
    {
    setting = 1;
    }    
//------------------------------UPDATE OLED DISPLAY----------------------------
   if  (setting2 == 1)
{ 
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speed:");
  display.print(setting);   
  display.setCursor(0, 20);
  display.print("Stop ");
  display.display();  
} 
   if ((setting == 1) && (setting2 == 2))
   {
   display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speed:");
  display.print(setting);   
  display.setCursor(0, 20);
  display.print("Manual");
  display.display();  
   }
   else if (setting2 == 2)
{ 
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speed:");
  display.print(setting);   
  display.setCursor(0, 20);
  display.print("Forward ");
  display.display();  
} 
   if  (setting2 == 3)
{ 
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speed:");
  display.print(setting);   
  display.setCursor(0, 20);
  display.print("Reverse ");
  display.display();  
} 
   if(digitalRead(buttonPin1) == LOW) // Stop while Button still pressed
 {
  degStopVal(DatadegStop[0]);   // Stop all outputs
  delay(1500); // Delay to allow Motor to Stop
 }
} 
  }
//--------------------------------STOP/START AND DIRECTION CHANGE-----------------------
 buttonState2=digitalRead(buttonPin2);
   if(buttonState2== LOW)
{
   counter2 = (counter2 + 1); // Switch Debounce 10k loops
   if (counter2 >= 5000)
{
   counter2=0;  
 }
  (setting2 = setting2 +1);
   if (setting2>=4)
   {setting2 = 1;}  
//------------------------------UPDATE OLED DISPLAY----------------------------
   if  (setting2 == 1)
{ 
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speed:");
  display.print(setting);   
  display.setCursor(0, 20);
  display.print("Stop ");
  display.display();  
} 
   if ((setting == 1) && (setting2 == 2))
   {
   display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speed:");
  display.print(setting);   
  display.setCursor(0, 20);
  display.print("Manual");
  display.display();  
   }
   else if (setting2 == 2)
{ 
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speed:");
  display.print(setting);   
  display.setCursor(0, 20);
  display.print("Forward ");
  display.display();  
} 
   if  (setting2 == 3)
{ 
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speed:");
  display.print(setting);   
  display.setCursor(0, 20);
  display.print("Reverse ");
  display.display();  
}     

//------------------------------------ Stop while Button still pressed--------------
   if(digitalRead(buttonPin2) == LOW) 
 {
  degStopVal(DatadegStop[0]);   // Stop all outputs
  delay(1000); // Delay to allow Motor to Stop
 }
} 
  

//-----------------------------------------------------------------------------------------  
 }  
//----------------------------------------END----------------------------------------------
//   ledState = !ledState;// toggle ledState
