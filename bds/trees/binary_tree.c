/*
 * Generic binary tree implementation
 */

struct bt* bt_init(struct generic_data d)
{
	struct bt *t = malloc(sizeof *t);
	t->root = malloc(sizeof(struct bt_node));
	t->root->d = d;
	t->root->l = t->root->r = NULL;
	return t;
}

void bt_insert(struct bt_node *p, struct generic_data d)
{
	struct bt_node *n = malloc(sizeof *n);
	n->v = d;
	n->l = n->r = NULL;
	if(!p->right) {
		p->r = n;
	} else {	
		n->l = p->l;
		p->l = n;
	}
}

void bt_trav_in_order(struct bt_node *n, void(*f)(struct generic_data))
{
	if(n->l)
		bt_trav_in_order(n->l, f);
	f(n->d);
	if(n->r)
		bt_trav_in_order(n->r, f);
}

void bt_trav_pre_order(struct bt_node *n, void(*f)(struct generic_data))
{
	f(n->d);
	if(n->l)
		bt_trav_in_order(n->l, f);
	if(n->r)
		bt_trav_in_order(n->r, f);
}

void bt_trav_post_order(struct bt_node *n, void(*f)(struct generic_data))
{
	if(n->l)
		bt_trav_in_order(n->l, f);
	if(n->r)
		bt_trav_in_order(n->r, f);
	f(n->d);
}
