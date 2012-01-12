/*
 * Generic binary tree implementation
 */

struct bt* bt_init(struct generic_data data)
{
	struct bt *t = malloc(sizeof(*t));
	t->root = malloc(sizeof(*t->root));
	t->root->data = data;
	t->root->left = t->root->right = t->root->parent = NULL;
	t->flags = 0;
	return t;
}

bt_cursor bt_insert(struct bt_node n, struct generic_data data) {
	struct bt_node *new_n = malloc(sizeof(*new_n));
	if(n.left && n.right) {
		mds_error(E_TREE_NODE_FULL, "This node has no more empty slots to add children");
		return NULL;
	}
	new_n->data = data;
	new_n->left = new_n->right = NULL;
	if(!n.left)
		n.left = new_n;
	else	
		n.right = new_n;
	new_n->parent = &n;
	return new_n;
}

uchar_t bt_isProper(struct bt *t) {
	return bt_traversal_in(t, tr_node_proper);
}

void bt_subtr_trav_in(struct bt_node n, void(*f)(struct generic_data))
{
	if(n.left)
		bt_trav_in_order(n.left, f);
	f(n.data);
	if(n.right)
		bt_trav_in_order(n.right, f);
}

void bt_subtr_trav_pre(struct bt_node n, void(*f)(struct generic_data))
{
	f(n.data);
	if(n.left)
		bt_trav_in_order(n.left, f);
	if(n.right)
		bt_trav_in_order(n.right, f);
}

void bt_subtr_trav_post(struct bt_node n, void(*f)(struct generic_data))
{
	/* return (n.left?bt_trav_in_order(*n.left):0) && (n.right?bt_trav_in_order(*n.right):0) && f(n.data); */
	if(n.left)
		bt_trav_in_order(*n.left, f);
	if(n.right)
		bt_trav_in_order(*n.right, f);
	f(n.data);
}

struct generic_data* bt_get_left(struct bt_node n) {
	if(n.left)
		return &n.left->data;
	return NULL;
}

struct generic_data* bt_get_right(struct bt_node n) {
	if(n.right)
		return &n.right->data;
	return NULL;
}

struct generic_data* bt_get_parent(struct bt_node n) {
	if(n.parent)
		return &n.parent->data;
	return NULL;
}

void bt_set_left(struct bt_node n, struct generic_data data) {
	struct bt_node *n_new = malloc(sizeof(*n_new));
	if(n.left) {
		n.left->data = data;
		return;
	}
	n_new->data = data;
	n_new->left = n_new->right = NULL;
	n_new->parent = &n;
	n.left = n_new;
}

void bt_set_right(struct bt_node n, struct generic_data data) {
	struct bt_node *n_new = malloc(sizeof(*n_new));
	if(n.right) {
		n.right->data = data;
		return;
	}
	n_new->data = data;
	n_new->left = n_new->right = NULL;
	n_new->parent = &n;
	n.right = n_new;
}

void bt_set_parent(struct bt_node n, struct generic_data data) {
	if(n.parent)
		n.parent->data = data;
}

uchar_t bt_height(struct bt_node qNode) {
	return MAX((qNode.left?1+bt_height(*qNode.left):0), (qNode.right?1+bt_height(*qNode.right):0));
}

uchar_t bt_depth(struct bt_node qNode) {
	return (qNode.parent?1+bt_depth(*qNode.parent):0);
}

uchar_t bt_isInternal(struct bt_node n) {
	return n.left || n.right;
}

void bt_add_left(struct bt_node n, struct bt_node stroot) {
	if(n.left)
		return;
	n.left = &stroot;
	stroot.parent = n;
}

void bt_add_right(struct bt_node n, struct bt_node stroot) {
	if(n.right)
		return;
	n.right = &stroot;
	stroot.parent = n;
}	

void bt_remove_left(struct bt_node n) {
	if(!n.left)
		return;
	bt_subtr_trav_in(*n.left, bt_remove_node);
	n.left = NULL;
}
void bt_remove_right(struct bt_node n);





/* Useful node visiting functions */
void bt_n_chd(struct bt_node n) {
	n.total_descendants = n_chd_r(n);
}

inline uint n_chd_r(struct bt_node n) {
	return (n.left?1+n_chd_r(*n.left):0) + (n.right?1+n_chd_r(*n.right):0);
}
