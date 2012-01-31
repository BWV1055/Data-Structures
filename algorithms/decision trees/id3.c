/*
 * ID3 decision tree generation algorithm
 */

struct dec_node {
	char attr_n;
	int n_children;
	struct dec_node** children;
	
};

struct dec_tree {
	int height;
	struct dec_node* root;
};

/* Dataset taken from http://www.cise.ufl.edu/~ddd/cap6635/Fall-97/Short-papers/2.htm */
char* dataset[] = 
{												/* Classification */
	"SUNNY",  	"HOT",    	"HIGH",    	"WEAK",		"NO",
	"SUNNY",	"HOT",    	"HIGH",    	"STRONG",	"NO",
	"OVERCAST",	"HOT",    	"HIGH",   	"WEAK",		"YES",
	"RAIN",		"MILD",   	"HIGH",   	"WEAK",		"YES",
	"RAIN",		"COOL",		"NORMAL",  	"WEAK",		"YES",
	"RAIN",		"COOL",  	"NORMAL",  	"STRONG",	"NO",
	"OVERCAST",	"COOL",  	"NORMAL",  	"STRONG",	"YES",
	"SUNNY", 	"MILD",  	"HIGH",    	"WEAK",		"NO",
	"SUNNY", 	"COOL",  	"NORMAL",  	"WEAK",		"YES",
	"RAIN",		"MILD",  	"NORMAL",  	"WEAK",		"YES",
	"SUNNY", 	"MILD",  	"NORMAL",  	"STRONG",	"YES",
	"OVERCAST",	"MILD",  	"HIGH",    	"STRONG",	"YES",
	"OVERCAST",	"HOT", 		"NORMAL",  	"WEAK",		"YES",
	"RAIN",  	"MILD",  	"HIGH",		"STRONG",	"NO",
	NULL
};

float entropy(int* a[], int attrib, int n_entries) {
	int i;
	float s = 0;
	int* p = calloc(n_entries*sizeof(int));
	for(i=0;i<n_entries;i++)
		p[a[i][attrib]]++;
	for(i=0;i<n_entries;i++) {
		if(!p[i])
		/* There is no gap in the values one attribute takes */
			break;
		s-=(p[i]/n_entries)*log(2, p[i]/n_entries);
	}
	free(p);
	return s;
}

float gain(int* a[], int attrib, int parent_attrib, int value_parent, int n_attrib, int n_entries) {
	int i, max_val_attrib = 0;
	float s, entropy, g;
	int* p = malloc(n_entries*sizeof(int));
	for(i=0;i<n_entries;i++)
		p[i] = malloc(n_entries*sizeof(int));
	for(i=0;i<n_entries;i++)
		p[a[i][attrib]][a[i][n_entries-1]]++;
	float g = entropy(a, attrib, n_entries);
	for(i=0;i<n_attrib;i++) {
		s=0;
		for(i=0;i<n_attrib;i++)
			s+=p[a[i][attrib]][a[i][n_entries-1]];
		entropy=0;
		for(i=0;i<n_attrib;i++)
			entropy-=p[a[i][attrib]][a[i][n_entries-1]]/s*(log(2, p[a[i][attrib]][a[i][n_entries-1]]/s));
		g-=p[a[i][attrib]]/n_entries * entropy;
	}
	free(p);
	return g;
}

dec_tree* build_id3(char* dataset[], int n_attrib, int n_entries) {
	int i;
	char* c;
	int* a = malloc(n_entries*sizeof(int));
	for(i=0;i<n_entries;i++)
		a[i] = malloc(n_attrib*sizeof(int));
	for(i=0;i<size;i+=n_attrib) {
		for(j=0;j<n_attrib;j++) {
			c = dataset[i*n_attrib+j];
			switch j {
			case 0: {
				if(strcmp(c, "SUNNY")==0) a[i][j] = 0;
				else if(strcmp(c, "OVERCAST")==0) a[i][j] = 1;
				else if(strcmp(c, "RAIN")==0) a[i][j] = 2;
				else return NULL;
			}
			case 1: {
				if(strcmp(c, "HOT")==0) a[i][j] = 0;
				else if(strcmp(c, "MILD")==0) a[i][j] = 1;
				else if(strcmp(c, "COLD")==0) a[i][j] = 2;
				else return NULL;
			}
			case 2: {
				if(strcmp(c, "HIGH")==0) a[i][j] = 0;
				else if(strcmp(c, "NORMAL")==0) a[i][j] = 1;
				else return NULL;
			}
			case 3: {
				if(strcmp(c, "WEAK")==0) a[i][j] = 0;
				else if(strcmp(c, "STRONG")==0) a[i][j] = 1;
				else return NULL;
			}
			case 4: {
				if(strcmp(c, "NO")==0) a[i][j] = 0;
				else if(strcmp(c, "YES")==0) a[i][j] = 1;
				else return NULL;
			}
			default:
				break;
		}
	}

	int avail_attribs_size = n_attrib;
	int* avail_attribs = malloc(avail_atrribs_size*sizeof(int));
	for(i=0;i<avail_attribs_size;i++)
		avail_attribs[i] = i;
	
	struct dec_tree* tree = calloc(sizeof(*tree));
	struct dec_node* root = calloc(sizeof(*root));
	struct dec_node* cur_node = root;

	while(avail_attribs_size) {
		for(j=0;j<cur_node->n_children;j++) {
		
		for(i=0;i<avail_attribs_size;i++) {
			max_gain = 0;
			g = gain(a, avail_attribs[i], parent_attrib, value_parent, n_attrib, n_entries);
			if(g>max_gain) {
				max_gain = g;
				attrib = i;
			}
		}
		for(i=attrib ;i<avail_attribs_size; i++)
			avail_attribs[i] = avail_attribs[i+1];
		avail_attribs_size--;
		struct dec_node* new_dec = calloc(sizeof(*new_dec));
		new_dec->attrib_n = attrib;
		new_dec->children = calloc(sizeof(*new_dec->children));
		cur_node->children[j] = new_dec;

		}
		cur_node = cur_node->children;
	}
	

	return tree;
}
