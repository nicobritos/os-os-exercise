#include <stdint.h>       /* Para poder utilizar el tipo de dato uint8_t uint16_t, uint32_t */
#include <idtLoader.h>
#include <defs.h>
#include <interrupts.h>

#pragma pack(push)		/* Push de la alineación actual */
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

/*
 * Descriptor de interrupcion
 * https://wiki.osdev.org/Interrupt_Descriptor_Table
 */
typedef struct {
  uint16_t offset_l;        /* Desplazamiento de bits 0..15 */
  uint16_t selector;        /* Selector de segmento de codigo */
  uint8_t cero;             /* Desplazamiento de la tabla de pila */
  uint8_t access;           /* Tipo y atributos */
  uint16_t offset_m;        /* Desplazamiento de bits 16..31 */
  uint32_t offset_h;        /* Desplazamiento de bits 32..63 */
  uint32_t other_cero;      /* reservado */
} DESCR_INT;

#pragma pack(pop)		/* Reestablece la alinceación actual */


DESCR_INT * idt = (DESCR_INT *) 0;	// IDT de 255 entradas

static void setup_IDT_entry (int index, uint64_t offset);

void load_idt() {
  _cli();                            /* para configurar tabla de interrupciones sin que rompa  */

  // Comentado hasta que hagamos las excepciones
  setup_IDT_entry (0x00, (uint64_t)&_exception0Handler);        /* 0x00 Por que en la tabla es Zero Division Exception */
  setup_IDT_entry (0x06, (uint64_t)&_exceptionInvalidOpcodeHandler);        /* 0x06 Por que en la tabla es Invalid Opcode Exception */
  setup_IDT_entry (0x20, (uint64_t)&_irq00Handler);             /* 0x20 Puerto de salida  */
  setup_IDT_entry (0x21, (uint64_t)&_irq01Handler);
  setup_IDT_entry (0x80, (uint64_t)&_syscall);             /* int 80 */


  //Solo interrupcion timer tick habilitadas
  picMasterMask(0xFC);
  picSlaveMask(0xFF);

  _sti();                           /* vuelvo a habilitar las interrupciones */
}

static void setup_IDT_entry (int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t) 0;
}
