#ifndef DACTYL_EZ_H
#define DACTYL_EZ_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2cmaster.h"
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

// I2C aliases and register addresses (see "mcp23018.md")
#define I2C_ADDR        0b0100000
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

extern uint8_t mcp23018_status;

void init_dactyl(void);
void dactyl_blink_all_leds(void);
uint8_t init_mcp23018(void);
uint8_t dactyl_left_leds_update(void);

#define LED_BRIGHTNESS_LO       15
#define LED_BRIGHTNESS_HI       255


inline void dactyl_board_led_on(void)      { DDRD |=  (1<<6); PORTD |=  (1<<6); }
inline void dactyl_right_led_1_on(void)    { DDRB |=  (1<<5); PORTB |=  (1<<5); }
inline void dactyl_right_led_2_on(void)    { DDRB |=  (1<<6); PORTB |=  (1<<6); }
inline void dactyl_right_led_3_on(void)    { DDRB |=  (1<<7); PORTB |=  (1<<7); }
inline void dactyl_right_led_on(uint8_t led) { DDRB |= (1<<(led+4)); PORTB |= (1<<(led+4)); }

inline void dactyl_board_led_off(void)     { DDRD &= ~(1<<6); PORTD &= ~(1<<6); }
inline void dactyl_right_led_1_off(void)   { DDRB &= ~(1<<5); PORTB &= ~(1<<5); }
inline void dactyl_right_led_2_off(void)   { DDRB &= ~(1<<6); PORTB &= ~(1<<6); }
inline void dactyl_right_led_3_off(void)   { DDRB &= ~(1<<7); PORTB &= ~(1<<7); }
inline void dactyl_right_led_off(uint8_t led) { DDRB &= ~(1<<(led+4)); PORTB &= ~(1<<(led+4)); }

inline void dactyl_led_all_on(void)
{
    dactyl_board_led_on();
    dactyl_right_led_1_on();
    dactyl_right_led_2_on();
    dactyl_right_led_3_on();
}

inline void dactyl_led_all_off(void)
{
    dactyl_board_led_off();
    dactyl_right_led_1_off();
    dactyl_right_led_2_off();
    dactyl_right_led_3_off();
}

inline void dactyl_right_led_1_set(uint8_t n)    { OCR1A = n; }
inline void dactyl_right_led_2_set(uint8_t n)    { OCR1B = n; }
inline void dactyl_right_led_3_set(uint8_t n)    { OCR1C = n; }
inline void dactyl_right_led_set(uint8_t led, uint8_t n)  {
    (led == 1) ? (OCR1A = n) :
    (led == 2) ? (OCR1B = n) :
                 (OCR1C = n);
}

inline void dactyl_led_all_set(uint8_t n)
{
    dactyl_right_led_1_set(n);
    dactyl_right_led_2_set(n);
    dactyl_right_led_3_set(n);
}

#define KEYMAP(                                                 \
                                                                \
    /* left hand, spatial positions */                          \
    k00,k10,k20,k30,k40,k50,                                    \
    k01,k11,k21,k31,k41,k51,                                    \
    k02,k12,k22,k32,k42,k52,                                    \
    k03,k13,k23,k33,k43,k53,                                    \
    k04,k14,k24,k34,k44,                                        \
                            k55,k45,                            \
                                k35,                            \
                        k05,k15,k25,                            \
                                                                \
    /* right hand, spatial positions */                         \
            k08,k18,k28,k38,k48,k58,                            \
            k09,k19,k29,k39,k49,k59,                            \
            k0A,k1A,k2A,k3A,k4A,k5A,                            \
            k0B,k1B,k2B,k3B,k4B,k5B,                            \
                k1C,k2C,k3C,k4C,k5C,                            \
    k1D,k0D,                                                    \
    k2D,                                                        \
    k3D,k4D,k5D )                                               \
                                                                \
   /* matrix positions */                                       \
   {                                                            \
    { k00, k10, k20, k30, k40, k50 },                           \
    { k01, k11, k21, k31, k41, k51 },                           \
    { k02, k12, k22, k32, k42, k52 },                           \
    { k03, k13, k23, k33, k43, k53 },                           \
    { k04, k14, k24, k34, k44, KC_NO },                         \
    { k05, k15, k25, k35, k45, k55 },                           \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },               \
                                                                \
    { k08, k18, k28, k38, k48, k58 },                           \
    { k09, k19, k29, k39, k49, k59 },                           \
    { k0A, k1A, k2A, k3A, k4A, k5A },                           \
    { k0B, k1B, k2B, k3B, k4B, k5B },                           \
    { KC_NO, k1C, k2C, k3C, k4C, k5C },                         \
    { k0D, k1D, k2D, k3D, k4D, k5D },                           \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }                \
   }

#define KEYMAP_80(                                              \
                                                                \
    /* left hand, spatial positions */                          \
    k00,k10,k20,k30,k40,k50,                                    \
    k01,k11,k21,k31,k41,k51,                                    \
    k02,k12,k22,k32,k42,k52,                                    \
    k03,k13,k23,k33,k43,k53,                                    \
    k04,k14,k24,k34,k44,                                        \
                            k55,k45,                            \
                                k35,                            \
                        k05,k15,k25,                            \
                                                                \
    /* right hand, spatial positions */                         \
            k08,k18,k28,k38,k48,k58,                            \
            k09,k19,k29,k39,k49,k59,                            \
            k0A,k1A,k2A,k3A,k4A,k5A,                            \
            k0B,k1B,k2B,k3B,k4B,k5B,                            \
                k1C,k2C,k3C,k4C,k5C,                            \
    k1D,k0D,                                                    \
    k2D,                                                        \
    k3D,k4D,k5D )                                               \
                                                                \
   /* matrix positions */                                       \
   {                                                            \
    { k00, k10, k20, k30, k40, k50 },                           \
    { k01, k11, k21, k31, k41, k51 },                           \
    { k02, k12, k22, k32, k42, k52 },                           \
    { k03, k13, k23, k33, k43, k53 },                           \
    { k04, k14, k24, k34, k44, KC_NO },                         \
    { k05, k15, k25, k35, k45, k55 },                           \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },               \
                                                                \
    { k08, k18, k28, k38, k48, k58 },                           \
    { k09, k19, k29, k39, k49, k59 },                           \
    { k0A, k1A, k2A, k3A, k4A, k5A },                           \
    { k0B, k1B, k2B, k3B, k4B, k5B },                           \
    { KC_NO, k1C, k2C, k3C, k4C, k5C },                         \
    { k0D, k1D, k2D, k3D, k4D, k5D },                           \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }                \
   }

#endif
