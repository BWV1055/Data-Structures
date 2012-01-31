/*
 *	C4.5 algorithm, the successor of ID3, for building decision trees
 */

#include <math.h>

struct dec_node {
	char leaf;
	/* Filled only for leaf */
	int c_n;
	/* Outlook */
	int att_n;
	/* Each attribute has values: Sunny, Overcast, Rain */
	int sample_n;
	int* sample_v;
	/* Sunny: 5, Overcast: 4, Rain: 5 */
	int* sample_f;
	struct dec_node** chd;
	struct dec_node* parent;
};

struct dec_tree {
	struct dec_node* root;
	/* 4 or less if data is classified perfectly earlier */
	int attribs_n;
	/* Used Outlook, Humidity and Wind */
	int* attribs;
	int classif_n;
	/* YES/NO */
	int* classif;
};

float entropy_c(int* a[], int attrib, int attrib_v, int n_entries, int cc) {
	int i, classif, total = 0, a_v_c;
	int* c_f = calloc(n_entries*sizeof(int));
	float e = 0;
	for(i=0;i<n_entries;i++)
		/* Weak wind */
		if(a[i][attrib] == attrib_v) {
			classif = a[i][cc];
			c_f[classif]++;
			total++;
		}
	for(i=0;i<n_entries;i++)
		if(a_v_c = c_f[i])
			e-=(a_v_c/total)*log2(a_v_c/total);
	free(c_f);
	return e;
}

float entropy(int* a[], int n_entries, int cc) {
	float e = 0;
	int i;
	int* values = calloc(n_entries*sizeof(int));
	for(i=0;i<n_entries;i++) 
		values[a[i][cc]]++;
	for(i=0;i<n_entries;i++)
		if(values[i])
			e-=values[i]/n_entries*log2(values[i]/n_entries);
	return e;
}
/* Values appear in increasing order on a column 
 * Sunny<Overcast<Rain because this is the order in which they appear in the column */
float gain(int* a[], int attrib, int n_entries, int cc) {
	float g = 0;
	int i;
	int* attrib_values = calloc(n_entries*sizeof(int));
	for(i=0;i<n_entries;i++)
		attrib_values[a[i][attrib]]++;
	for(i=0;i<n_entries;i++) 
		if(attrib_values[i])
			g-=attrib_values[i]/n_entries*entropy_c(a, attrib, attrib_values[i], n_entries, cc);
	g+=entropy(a, n_entries, cc);
	return g;
}

void dt_statistics(int* a[], int attrib, int* p_sample_n, int** p_sample_v, int** p_sample_f, int n_entries) {
	int i;
	int* values = calloc(n_entries*sizeof(int));
	*p_sample_n = 0;
	for(i=0;i<n_entries;i++)
		values[a[i][attrib]]++;
	for(i=0;i<n_entries;i++)
		if(values[i]) {
			*p_sample_n++;
			*p_sample_v[p_sample_n] = i;
			*p_sample_f[p_sample_n] = values[i];
		}
	free(values);
}

/* n_attrib includes the classification column, last */
struct dec_tree* c45(char* training_data[], int n_attrib) {
	char *c, fully_class = 0, max_g, level_done = 0;
	int col = 0, line = 0, cur_total = 0;
	int avail_attribs = n_attrib-1;

	c = training_data[0];
	while(strcmp(c, NULL)) {
		cur_total++;
		if(cur_total%n_attrib==0){
			line++;
			col=0;
		}
		switch col {
			case 0: {
				if(strcmp(c, "SUNNY")==0) a[line][col] = 0;
				else if(strcmp(c, "OVERCAST")==0) a[line][col] = 1;
				else if(strcmp(c, "RAIN")==0) a[line][col] = 2;
				else return NULL;
			}
			case 1: {
				if(strcmp(c, "HOT")==0) a[line][col] = 0;
				else if(strcmp(c, "MILD")==0) a[line][col] = 1;
				else if(strcmp(c, "COLD")==0) a[line][col] = 2;
				else return NULL;
			}
			case 2: {
				if(strcmp(c, "HIGH")==0) a[line][col] = 0;
				else if(strcmp(c, "NORMAL")==0) a[line][col] = 1;
				else return NULL;
			}
			case 3: {
				if(strcmp(c, "WEAK")==0) a[line][col] = 0;
				else if(strcmp(c, "STRONG")==0) a[line][col] = 1;
				else return NULL;
			}
			case 4: {
				if(strcmp(c, "NO")==0) a[line][col] = 0;
				else if(strcmp(c, "YES")==0) a[line][col] = 1;
				else return NULL;
			}
			default:
				break;
		}
		c = training_data[cur_total];
	}

	struct dec_tree* d_tree = calloc(sizeof(*d_tree));
	d_tree->root = calloc(sizeof(struct dec_node));
	struct dec_node* cur_n = d_tree->root;

	int* attribs = calloc((n_attribs-1)*sizeof(int));
	for(i=0;i<n_attribs-1;i++)
		attribs[i] = i; /* TODO: put the value for the column number */

	max_g = 0;
	for(j=0;j<avail_attribs;j++) {
		g = gain(a, attribs[j], n_entries, cc);
		if(g>max_g) {
			max_pos = j;
			max_g = g;
		}
	}
	new_n->att_n = attribs[j];
	for(k=j;k<avail_attribs;k++)
		attribs[k] = attribs[k+1];
	avail_attribs--;
	
	cur_n->leaf = 0;
	dt_statistics(a, cur_n->att_n, &cur_n->sample_n, &cur_n->sample_v, &cur_n->sample_f, n_entries);
	cur_n->children = malloc(sizeof(*new_n->children));
	cur_n->parent = NULL;
	fully_class+=cur_n->children;

	while(!fully_class && avail_attribs) {
		for(i=0;i<cur_n->sample_n;i++) {
			struct dec_node* new_n = calloc(sizeof(*new_n));
			if(entropy_c(a, cur_n->att_n, cur_n->sample_v[i], n_entries, cc)==0) {
				/* Leaf node */
				new_n->leaf = 1;
				while(a[j++][cur_n->att_n]!=cur_n->sample_v[i]);
				new_n->c_n = a[j][cc];
				cur_n->children[i] = new_n;
				fully_class--;
				continue;
			}
			max_g = 0;
			for(j=0;j<avail_attribs;j++) {
				g = gain(a, attribs[j], n_entries, cc);
				if(g>max_g) {
					max_pos = j;
					max_g = g;
				}
			}

			new_n->att_n = attribs[j];
			for(k=j;k<avail_attribs;k++)
				attribs[k] = attribs[k+1];
			avail_attribs--;
			
			new_n->leaf = 0;
			dt_statistics(a, new_n->att_n, &new_n->sample_n, &new_n->sample_v, &new_n->sample_f, n_entries);
			new_n->children = malloc(sizeof(*new_n->children));
			new_n->parent = cur_n;
			fully_class+=new_n->children;
			cur_n->children[i] = new_n;
		}
		if(level_done) {
			while(cur_n->parent)
				cur_n = cur_n->parent;
			while(cur_n->children[0])
				cur_n = cur_n->children[0];
		} else {
			cur_n = cur_n->children[0];
	}
}

char* training_data[] = 
{
 /*	Outlook  Temperature   Humidity      Wind   Classification */  
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
