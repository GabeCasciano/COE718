#ifndef __KDB_H
#define __KDB_H

#define KDB_SELECT  0x01
#define KDB_UP      0x08
#define KDB_RIGHT   0x10
#define KDB_DOWN    0x20
#define KDB_LEFT    0X40
#define KDB_MASK    0x79

extern uint32_t KDB_val;

extern void KDB_Init (void);
extern uint32_t KDB_get(void);
extern uint32_t KDB_button(void);
#endif //__KDB_H
