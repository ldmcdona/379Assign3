/******************************************
 *
 * linklist.c - Modified 2018-04-05
 *
 * addapted from linklist.c in project 1
 *
 * Created by:
 * Craig Lindsay 1391493
 * Liam McDonald 1462799
 *
 *
 * linklist is a basic link list implementation specificaly for this project
 *
 * USEAGE:
 * create a new list by adding an item add_entry(char*, int); file_stats is expected to have
 * a valid value.
 *
 * delete the first item by calling delFirstEntryAndReturnHash(); it will delete the first item and
 * return the hash
 *
 * searching the linklist is not required and the functionality was removed
 *
 *
 ******************************************
 */


//struct entry
struct entry {
  int h;
  struct entry* next;
};


struct entry* head = NULL; // head represents the list, and points to its first element.





int addEntry(int h) {
  /* Creates a new entry for the link list and places it at the end of the list.
   *
   * Args:
   *     hash(int):   filetype if the entry
   *
   * Returns: int success status
   */

  struct entry* item1 = (struct entry*) malloc(sizeof(struct entry));
    
  item1->h = h;
  item1->next = NULL;
  
  if (head == NULL) {
    head = item1;
    return 1;
  }

  struct entry * listItem = head;
  while (listItem->next != NULL) {
    listItem = listItem->next;
  }
  listItem->next = item1;
  return 1;
}

int delFirstEntryAndReturnHash() {
  /*does what it says on the tin
   *
   * Args: None
   *
   * Returns: (int) hash value of entry
   */
  if (head != NULL) {
    int hashVal = head->h;
    struct entry* del = head;
    head = head->next;
    free(del);
    return hashVal;
  }
  return -1;
}
