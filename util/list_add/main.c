//-----------------------------------------------------------------------------
// Desc: x86_64 Assembly Language Tutorial
//
// Copyright © 2024 J McIntosh
//
//   This file is part of x86_64 Assembly Language Tutorial.
//
//   x86_64 Assembly Language Tutorial is free software; you can redistribute
//   it and/or modify it under the terms of the GNU General Public License as
//   published by the Free Software Foundation; version 3 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with x86_64 Assembly Language Tutorial.  If not, see
//   <https://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------------
#include "main.h"


//------------------------------------------------------------------------------
//
// MAIN
//
int main (int argc, char *argv[]) {
  puts("\nTEST LIST_ADD\n");

  list_t *list;
  if ((list = list_alloc()) == NULL)
    puts("LIST_ALLOC FAILED");
  else if (list_init(list, sizeof(vehicle_t)) < 0)
    puts("LIST_INIT FAILED!");
  else {
    print_list(list, "LIST_INIT SUCCESSFUL");

    for (size_t i = 0; i < VEHICLE_COUNT; ++i) {
      void *addr = list_add(list, &vehicle[i]);
      if (addr)
        printf("list_add:    address: %p    offset:% 4ld\n", addr,
            ((size_t)addr - (size_t)list_buffer(list)));
      else {
        puts("LIST_ADD FAILED!");
        return -1;
      }
    }

    print_list(list, "\nLIST_ADD SUCCESSFUL");

    // Add the 25th vehicle to the list.  Should fail due to list is full
    if (list_add(list, &vehicle[VEHICLE_COUNT + 1]) == NULL) {
      print_list(list, "LIST_ADD FAILED AS EXPECTED!");
    }

    list_term(list);
    print_list(list, "LIST_TERM SUCCESSFUL");
  }
  list_free(list);

  return 0;
}
//------------------------------------------------------------------------------
//
// PRINT_LIST
//
void print_list (list_t *list, char const *header) {
  puts(header);
  printf("\nlist:\ttotal:\t%lu\n\tcount:\t%lu\n" \
      "\to_size:\t%lu\n\tbuffer:\t%p\n\n", list->total, list->count,
      list->o_size, list->buffer);
}

