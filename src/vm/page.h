#ifndef VM_PAGE_H
#define VM_PAGE_H

#include <stdbool.h>
#include <list.h>
#include <hash.h>
#include "threads/init.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "threads/palloc.h"
#include "userprog/pagedir.h"
#include "threads/vaddr.h"

typedef struct page_table_entry
{
	uint32_t *uaddr;          /* virtual address of the page */
	uint32_t *paddr;          /* physical address of the page */

	struct thread *ut;        /* process that use this frame */
	bool is_swapped_out;      /* flag for swapped out */
	bool dirty;               /* dirty bit flag */
	bool writable;            /* writable flag */

	struct hash_elem helem;   /* hash element */
} PTE;

// struct hash page_table;       /* page table */

struct semaphore page_sema;   /* page semaphore */


void page_init(void);
// PTE* page_get_pte(uint32_t *upage);
// PTE* page_set_pte(uint32_t *upage, uint32_t *kpage);
void page_map(uint32_t *upage, uint32_t *kpage, bool writable);
void page_remove_pte(uint32_t *upage);
PTE* page_pte_lookup(uint32_t *addr);
void page_table_init(struct hash* h);
unsigned page_hash_hash_helper(const struct hash_elem * element, void * aux);
bool page_hash_less_helper(const struct hash_elem *a, const struct hash_elem *b, void *aux);


#endif /* vm/page.h */