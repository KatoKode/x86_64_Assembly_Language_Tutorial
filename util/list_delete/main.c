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
  puts("\nTEST LIST_DELETE\n");

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

    int count = 0;
    for (void *iter = list_begin(list); iter; iter = list_next(list))
      print_vehicle(++count, (vehicle_t *)iter);

    puts("\nLIST_BEGIN AND LIST_NEXT SUCCESSFUL\n");

    list_sort(list, sort_cb);

    puts("LIST_SORT SUCCESSFUL\n");

    count = 0;
    for (void *iter = list_begin(list); iter; iter = list_next(list))
      print_vehicle(++count, (vehicle_t *)iter);

    puts("\nLIST_BEGIN AND LIST_NEXT SUCCESSFUL\n");

    puts("DELETING GMC VEHICLES FROM LIST\n");

    size_t ndeleted = 0L;
    char key[NAME_LEN] = "GMC";
    while (1) {
      if (list_delete(list, key, find_cb, delete_cb) < 0) {
        break;
      } else {
        ++ndeleted;
      }
    }

    putchar('\n');

    if (list_count(list) == (VEHICLE_COUNT - ndeleted)) {
      print_list(list, "LIST_DELETE SUCCESSFUL");
    }

    count = 0;
    for (void *iter = list_begin(list); iter; iter = list_next(list))
      print_vehicle(++count, (vehicle_t *)iter);

    if (count == (VEHICLE_COUNT - ndeleted))
      puts("\nLIST_BEGIN AND LIST_NEXT SUCCESSFUL\n");

    (void) strncpy(key, "Edsel", NAME_LEN);
    if (list_delete(list, key, find_cb, delete_cb) < 0)
      print_list(list, "LIST_DELETE FAILED AS EXPECTED");
    else 
      print_list(list, "LIST_DELETE DID NOT FAIL AS EXPECTED");

    (void) strncpy(key, "Datsun", NAME_LEN);
    if (list_delete(list, key, find_cb, delete_cb) < 0)
      print_list(list, "LIST_DELETE FAILED AS EXPECTED");
    else 
      print_list(list, "LIST_DELETE DID NOT FAIL AS EXPECTED");

    (void) strncpy(key, "Alfa Romeo", NAME_LEN);
    if (list_delete(list, key, find_cb, delete_cb) < 0)
      print_list(list, "\nLIST_DELETE FAILED UNEXPECTEDLY");
    else 
      print_list(list, "\nLIST_DELETE SUCCESSFUL");

    count = 0;
    for (void *iter = list_begin(list); iter; iter = list_next(list))
      print_vehicle(++count, (vehicle_t *)iter);

    putchar('\n');

    (void) strncpy(key, "Volkswagen", NAME_LEN);
    if (list_delete(list, key, find_cb, delete_cb) < 0)
      print_list(list, "\nLIST_DELETE FAILED UNEXPECTEDLY");
    else 
      print_list(list, "\nLIST_DELETE SUCCESSFUL");

    count = 0;
    for (void *iter = list_begin(list); iter; iter = list_next(list))
      print_vehicle(++count, (vehicle_t *)iter);

    putchar('\n');

    (void) strncpy(key, "Oldsmobile", NAME_LEN);
    if (list_delete(list, key, find_cb, NULL) < 0)
      print_list(list, "\nLIST_DELETE FAILED UNEXPECTEDLY (NO CALLBACK)");
    else 
      print_list(list, "\nLIST_DELETE SUCCESSFUL (NO CALLBACK)");

    count = 0;
    for (void *iter = list_begin(list); iter; iter = list_next(list))
      print_vehicle(++count, (vehicle_t *)iter);

    putchar('\n');

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
// DELETE_CB
//
void delete_cb (void const *p) {
  vehicle_t const *vhc = p;
  printf("%s: %-16s%-16s% 8d\n", __func__, vhc->make, vhc->model, vhc->year);
}
//------------------------------------------------------------------------------
//
// FIND_CB
//
int find_cb (void const *p1, void const *p2) {
  return strncmp((char const *)p1, ((vehicle_t *)p2)->make, NAME_LEN);
}
//------------------------------------------------------------------------------
//
// SORT_CB
//
int sort_cb (void const *p1, void const *p2) {
  int dir = strncmp(((vehicle_t *)p1)->make,
          ((vehicle_t *)p2)->make, NAME_LEN);
  return (dir ? dir : strncmp(((vehicle_t *)p1)->model,
        ((vehicle_t *)p2)->model, NAME_LEN));
}

