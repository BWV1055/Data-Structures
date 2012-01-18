/*
 *	Stores a list of all the nodes on this machine
 */

struct skip_node_list {
	struct skip_node *head;
	int size;
};
/* Adds a new skip node in the ordered list */
void snl_add(struct skip_node_list *l, struct skip_node *n) {
	sg_cursor it = l->head;
	while(it->data) {
		if(strcmp(it->data->key.name, n->data->key.name)<0 && it->next) {
			it = it->next;
			continue;
		}
		n->next = it->next;
		it->next = n;
		break;
	}
	l->size++;
}
/* Updates the value of a skip node */
void snl_update(struct skip_node_list *l, struct skip_node *n, int nValue) {
	sg_cursor it = l->head;
	while(it->data) {
		if(strcmp(it->data->key.name, n->data->key.name)) {
			it = it->next;
			continue;
		}
		it->data->value = nValue;
		break;
	}
}
/* Returns a skip node by id */
sg_cursor snl_get_by_id(struct skip_node_list *l, int id) {
	sg_cursor it = l->head;
	while(it->next) {
		if(it->id!=id)
			it = it->next;
		else
			break;
	}
	if(it->id==id)
		return it;
	return NULL;
}
/* Returns a skip node by key */
sg_cursor snl_get_by_key(struct skip_node_list *l, char *key) {
	sg_cursor it = l->head;
	while(it->next) {
		if(strcmp(it->data->key.name, key))
			it = it->next;
		else
			break;
	}
	if(!strcmp(it->data->key.name, key))
		return it;
	return NULL;
}
