/* main.c
 *
 * Copyright 2019 Code Zombie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "password-config.h"

#include <glib.h>
#include <stdlib.h>

#define PACKAGE_VERSION "1.0"

gint
main (gint   argc,
      gchar *argv[])
{
  g_autoptr(GOptionContext) context = NULL;
  g_autoptr(GError) error = NULL;
  gboolean version = FALSE;
  GOptionEntry main_entries[] = {
    { "version", 0, 0, G_OPTION_ARG_NONE, &version, "Show program version" },
    { NULL }
  };

  context = g_option_context_new ("- my command line tool");
  g_option_context_add_main_entries (context, main_entries, NULL);

  if (!g_option_context_parse (context, &argc, &argv, &error))
    {
      g_printerr ("%s\n", error->message);
      return EXIT_FAILURE;
    }

  if(argc <= 1){
    g_printerr("Insufficient parameters. Usage: password <length>");
    return EXIT_FAILURE;
  }


  int length = atoi(argv[1]);
  char *generated = (char *) malloc(length);
  int alphabet_length = 'z' - 'a';
  int rand_index = 0;
  int char_code = 0;
  for (int i = 0; i < length ; i++) {
    rand_index = rand() % alphabet_length;
    char_code = rand_index + 'a';
    generated[i] = char_code;
  }

  //Add upper case for two letters too
  int letter1_index = rand() % length;
  int letter2_index = rand() % length;

  for(int i = 0; i < length; i++){
    if(i == letter1_index || i == letter2_index){
      generated[i] = g_ascii_toupper (generated[i]);
    }
  }

  //Print the password
  printf("Generated: %s\n", generated);

  if (version)
    {
      g_printerr ("%s\n", PACKAGE_VERSION);
      //return EXIT_SUCCESS;
    }

  return EXIT_SUCCESS;
}
