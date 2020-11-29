#include <stdio.h>
#include <glib.h>

const int MAX_LENGTH = 80;
const char *SEPARATOR  = " ";

gboolean cmper(gpointer lhs, gpointer rhs, gpointer str) {
  return !g_ascii_strcasecmp(lhs, str);
}

gint comparator_func(gconstpointer lhs, gconstpointer rhs, gpointer cnt) {
  gpointer p_lhs = g_hash_table_find(cnt, (GHRFunc)cmper, (gpointer)lhs);
  gpointer p_rhs = g_hash_table_find(cnt, (GHRFunc)cmper, (gpointer)rhs);

  return *((gint *)p_rhs) - *((gint *)p_lhs);
}

void print(gpointer str, gpointer cnt) {
  gpointer count = g_hash_table_find(cnt, (GHRFunc)cmper, str);
  printf("%s\t%d\n", (char* )str, *(gint* )cnt);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    return 1;
  }

  FILE* file = fopen(argv[1], "r");
  if ((file = fopen(argv[1], "r")) == NULL) {
    return 1;
  }

  GHashTable* ctable = g_hash_table_new(g_str_hash, g_str_equal);
  gchar text_line[MAX_LENGTH + 1];

  while (fgets(text_line, MAX_LENGTH + 1, file)) {
    text_line[strlen(text_line) - 1] = '\0';
    gchar** line_splitted = g_strsplit(text_line, SEPARATOR, -1);
    for (int i = 0; line_splitted[i]; ++i) {
      gpointer p_elem = g_hash_table_find(ctable, (GHRFunc)cmper, line_splitted[i]);
      if (p_elem) {
        (*(gint *)p_elem)++;
      }
      else {
        gint* new_cnt = g_new(gint, 1);
        *new_cnt = 1;
        gchar* word_tmp = g_strdup(line_splitted[i]);
        g_hash_table_insert(ctable, word_tmp, new_cnt);
      }
    }
    g_strfreev(line_splitted);
  }

  GList* cnt_sorted = g_hash_table_get_keys(ctable);
  cnt_sorted = g_list_sort_with_data(cnt_sorted, (GCompareDataFunc)comparator_func, ctable);

  g_list_foreach(cnt_sorted, print, ctable);

  g_list_free(cnt_sorted);
  g_hash_table_destroy(ctable);
  return 0;
}
