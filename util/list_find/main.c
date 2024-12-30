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
  puts("\nTEST LIST_SORT\n");

  list_t *list;
  if ((list = list_alloc()) == NULL)
    puts("LIST_ALLOC FAILED");
  else if (list_init(list, sizeof(vehicle_t)) < 0)
    puts("LIST_INIT FAILED!");
  else {
    print_list(list, "LIST_INIT SUCCESSFUL");

    for (size_t i = 0; i < VEHICLE_COUNT; ++i) {
      if (list_add(list, &vehicle[i]) == NULL) {
        puts("LIST_ADD FAILED!");
        return -1;
      }
    }

    print_list(list, "LIST_ADD SUCCESSFUL");

    list_sort(list, vehicle_make_cb);
    int count = 0;
    for (void *iter = list_begin(list); iter; iter = list_next(list))
      print_vehicle(++count, (vehicle_t *)iter);
    puts("\nLIST_SORT BY VEHICLE MAKE SUCCESSFUL\n");

    if (list_find(list, &vehicle[12], find_cb) == NULL) {
      puts("LIST_FIND FAILED TO FIND ALFA ROMEO");
      return -1;
    } else
      puts("LIST_FIND FOUND ALFA ROMEO\n");

    if (list_find(list, &vehicle[14], find_cb) == NULL) {
      puts("LIST_FIND FAILED TO FIND LEXUS LS");
      return -1;
    } else
      puts("LIST_FIND FOUND LEXUS LS\n");

    if (list_find(list, &vehicle[22], find_cb) == NULL) {
      puts("LIST_FIND FAILED TO FIND VOLKSWAGEN CABRIOLET");
      return -1;
    } else
      puts("LIST_FIND FOUND VOLKSWAGEN CABRIOLET\n");


    if (list_find(list, &vehicle[23], find_cb) == NULL)
      puts("LIST_FIND FAILED TO FIND BUICK LUCERNE AS EXPECTED\n");
    else
      puts("LIST_FIND FOUND BUICK LUCERNE UNEXPECTEDLY\n");

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
//------------------------------------------------------------------------------
//
// PRINT_VEHICLE
//
void print_vehicle (int const no, vehicle_t const *vhc) {
  printf("%02d:   %-16s%-16s% 8d\n", no, vhc->make, vhc->model, vhc->year);
}
//------------------------------------------------------------------------------
//
// VEHICLE_MAKE_CB
//
int vehicle_make_cb (void const *p1, void const *p2) {
  return strncmp(((vehicle_t *)p1)->make,
      ((vehicle_t *)p2)->make, NAME_LEN - 1);
}
//------------------------------------------------------------------------------
//
// FIND_CB
//
int find_cb (void const *p1, void const *p2) {
  int dir;
  if ((dir = strncmp(((vehicle_t *)p1)->make,
          ((vehicle_t *)p2)->make, NAME_LEN - 1)) == 0) {
    return strncmp(((vehicle_t *)p1)->model,
        ((vehicle_t *)p2)->model, NAME_LEN - 1);
  }
  return dir;
}

