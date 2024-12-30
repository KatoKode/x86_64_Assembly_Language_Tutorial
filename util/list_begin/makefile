#-----------------------------------------------------------------------------
# Desc: x86_64 Assembly Language Tutorial
#
# Copyright © 2024 J McIntosh
#
#   This file is part of x86_64 Assembly Language Tutorial.
#
#   x86_64 Assembly Language Tutorial is free software; you can redistribute
#   it and/or modify it under the terms of the GNU General Public License as
#   published by the Free Software Foundation; version 3 of the License.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with x86_64 Assembly Language Tutorial.  If not, see
#   <https://www.gnu.org/licenses/>.
#-----------------------------------------------------------------------------
list_begin: main.o ../util/libutil.so
	gcc -g main.o ../util/libutil.so -o list_begin
main.o: main.c
	gcc -g -c main.c -o main.o
clean:
	rm -f list_begin main.o
