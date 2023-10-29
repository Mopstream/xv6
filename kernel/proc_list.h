struct proc_list {
    struct proc * p;
    struct proc_list * next;
    struct proc_list * prev;
};

void
proc_lst_init(struct proc_list *lst)
{
  lst->next = lst;
  lst->prev = lst;
}

int
proc_lst_empty(struct proc_list *lst) {
  return lst->next == lst;
}

void
proc_lst_remove(struct proc_list *e) {
  e->prev->next = e->next;
  e->next->prev = e->prev;
  bd_free(e);
}

struct proc_list*
proc_lst_pop(struct proc_list *lst) {
  if(lst->next == lst)
    panic("proc_lst_pop");
  struct proc_list *p = lst->next;
  proc_lst_remove(p);
  return p;
}

void
proc_lst_print(struct proc_list *lst)
{
  for (struct proc_list *p = lst->next; p != lst; p = p->next) {
    printf(" %d", p);
  }
  printf("\n");
}

void
proc_lst_push(struct proc_list *lst, struct proc_list * p)
{
  p->next = lst->next;
  p->prev = lst;
  lst->next->prev = p;
  lst->next = p;
}

